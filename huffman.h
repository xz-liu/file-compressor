//
// Created by joker on 2017/11/18.
//

#ifndef DATA_STRUCTURE_EXP_HUFFMAN_H
#define DATA_STRUCTURE_EXP_HUFFMAN_H

#include <queue>
#include <vector>
#include <functional>
#include <algorithm>
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

        bool operator>(const triple &t) const {
            return node_count > t.node_count;
        }
    };
    std::basic_string<CharT> original_str;
    std::priority_queue<triple, std::vector<triple>, std::greater<triple>> min_heap;
    std::vector<code_pair> codes;
    std::map<CharT, size_t> ref_map;
    ptr &root = bin_tree<CharT>::root;

    size_t count_of(triple &t) { return t.node_count; }

    CharT char_of(triple &t) { return t.node_char; }

    ptr &ptr_of(triple &t) { return t.node_ptr; }

    bit_ref next_bit(bit_ref ref, bool val) {
        return (ref << 1) | (bit_ref) (val);
    }

    void construct(ptr now, bit_ref code) {
        if (now->is_leaf())
            codes.emplace_back(now->val, code);
        else {
            if (now->has_lchild())
                construct(now->lc, next_bit(code, 0));
            if (now->has_rchild())
                construct(now->rc, next_bit(code, 1));
        }
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

    std::vector<code_pair> encoding() { return codes; }

    std::basic_string<CharT> str(){ return original_str;}
};


#endif //DATA_STRUCTURE_EXP_HUFFMAN_H
