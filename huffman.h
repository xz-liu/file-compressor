//
// Created by joker on 2017/11/18.
//

#ifndef DATA_STRUCTURE_EXP_HUFFMAN_H
#define DATA_STRUCTURE_EXP_HUFFMAN_H

#include <functional>
#include <utility>
#include <string>
#include <map>
#include "bin_tree.h"


template<class CharT>
class huffman : public bin_tree<CharT> {

    using ptr=typename bintree_node<CharT>::bnode_ptr;
    using const_ptr=typename bintree_node<CharT>::const_bnode_ptr;
    using bit_ref=unsigned int;
    using code_pair=std::pair<CharT, bit_ref>;

    struct triple {
        size_t node_count;
        CharT node_char;
        ptr node_ptr;
        triple(size_t c, CharT ch, ptr p)
                : node_count(c), node_char(ch), node_ptr(p) {}
        triple(){}
        bool operator>(const triple &t) const {
            return node_count > t.node_count;
        }
    };
    std::basic_string<CharT> original_str;
    priority_queue<triple, vector<triple>, std::greater<>> min_heap;
    std::map<CharT,bit_ref> codes;
    std::map<CharT, size_t> ref_map;
    ptr &root = bin_tree<CharT>::root;

    size_t count_of(triple &t) { return t.node_count; }

    CharT char_of(triple &t) { return t.node_char; }

    ptr &ptr_of(triple &t) { return t.node_ptr; }

    bit_ref next_bit(bit_ref ref, bool val)
    { return (ref << 1) | (bit_ref) (val); }

    inline size_t bsr(bit_ref ref)
    { return sizeof(bit_ref)*8-__builtin_clz(ref)-1;}

    void construct(ptr now, bit_ref code) {
        if (now->is_leaf()) {
            codes.insert({now->val, code});
            return;
        }
        if (now->has_lchild())
            construct(now->lc, next_bit(code, 0));
        if (now->has_rchild())
            construct(now->rc, next_bit(code, 1));
    }
    template <class Out,class Struct>
    static void write_obj(Out &out, Struct u){
        out.write(reinterpret_cast<CharT*>(&u), sizeof(u));
    }

    template <class Struct,class In>
    static Struct read_obj(In &in){
        Struct u;
        in.read(reinterpret_cast<CharT*>(&u), sizeof(u));
        return u;
    }
public:
    explicit huffman(const std::basic_string<CharT> &str):
            original_str((str)){
        for (auto c:str)ref_map[c]++;
        for (auto p:ref_map)
            min_heap.emplace(p.second, p.first, nullptr);
        while (true) {
            triple left = min_heap.top();
            min_heap.pop();
            if (!ptr_of(left))
                ptr_of(left) = new bintree_node<CharT>(char_of(left));
            if (min_heap.empty()) {
                root = ptr_of(left);
                break;
            }
            triple right = min_heap.top();
            min_heap.pop();
            if (!ptr_of(right))
                ptr_of(right) = new bintree_node<CharT>(char_of(right));
            root = new bintree_node<CharT>
                    (CharT(), nullptr, ptr_of(left), ptr_of(right));
            ptr_of(left)->parent =
            ptr_of(right)->parent = root;
            min_heap.push({count_of(left) + count_of(right), CharT(), root});
        }
        construct(root, 1);
    }

    std::map<CharT, size_t> counts() { return ref_map; }

    std::map<CharT,bit_ref> encoding() { return codes; }

    std::basic_string<CharT> str(){ return original_str;}

    template <class Out>void write(Out& out) {
        write_obj(out, original_str.size());
        write_obj(out, codes.size());
        for (auto &&p : codes) write_obj(out,p);
        vector<bit_ref> buffer(1);
        const size_t ref_size = sizeof(bit_ref) * 8;
        size_t sz_now = buffer.back() = 0;
        for (auto &&item : original_str) {
            size_t first_1 = bsr(codes[item]);
            bit_ref code = codes[item] & ~(1 << first_1);
            buffer.back() |= (code) << sz_now;
            if (sz_now + first_1 > ref_size) {
                sz_now = sz_now + first_1 - ref_size;
                buffer.push_back(code >> (first_1 - sz_now));
            } else sz_now += first_1;
        }
        for (auto &&item: buffer) {
            out.write(reinterpret_cast<CharT *>(&item), sizeof(item));
        }
    }
    template <class In,class Out> static void read(In& in,Out & out) {
        const size_t char_size = sizeof(CharT) * 8;
        const bit_ref mask = (bit_ref) -1;
        size_t para_size = read_obj<size_t>(in)
            , codes_size = read_obj<size_t>(in);
        std::map<CharT, bit_ref> codes;
        while (codes_size--)codes.insert(read_obj<code_pair>(in));
        CharT now;
        bit_ref code_now = 1;
        size_t code_size = 0;
        auto code = [&]() { return code_now | (1U << code_size); };
    }
};


#endif //DATA_STRUCTURE_EXP_HUFFMAN_H
