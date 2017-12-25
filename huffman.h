//
// Created by joker on 2017/11/18.
//

#ifndef DATA_STRUCTURE_EXP_HUFFMAN_H
#define DATA_STRUCTURE_EXP_HUFFMAN_H

#include <functional>
#include <iostream>
#include <sstream>
#include <fstream>
#include <utility>
#include <string>
#include <vector>
#include "map.h"
#include "basic.h"
#include "vector.h"
#include "bin_tree.h"

/**
 * huffman tree
 * implements compression and decompression using huffman tree
 */
template<class CharT = char>
class huffman : public bin_tree<CharT>, binary_io {
public:
	using ptr = typename bintree_node<CharT>::bnode_ptr;
	using const_ptr = typename bintree_node<CharT>::const_bnode_ptr;
	using code_ref = unsigned int;
	using code_pair = std::pair<CharT, code_ref>;
	//node info type
	struct info {
		size_t node_count;
		CharT node_char;
		ptr node_ptr;

		info(size_t c, CharT ch, ptr p)
			: node_count(c), node_char(ch), node_ptr(p) {}
		//comparator std::greater<> need operator>
		bool operator>(const info &t) const {
			return node_count > t.node_count;
		}
	};
private:
	::vector<CharT> original_str;
	map<CharT, code_ref> codes;
	map<CharT, size_t> ref_map;
#ifndef _MSC_VER
	ptr &root = bin_tree<CharT>::root;
#endif
	int para_size;

	static size_t count_of(info &t) { return t.node_count; }

	static CharT char_of(info &t) { return t.node_char; }

	static ptr &ptr_of(info &t) { return t.node_ptr; }
	//construct next code, 0 for left 1 for right
	static code_ref next_bit(code_ref ref, bool val) { return (ref << 1) | (code_ref)(val); }
	//finding the leftmost 1
	size_t bsr(code_ref ref) { return sizeof(code_ref) * 8 - __builtin_clz(ref) - 1; }
	//transfer from tree to actual code
	void construct(ptr now, code_ref code) {
		if (now->is_leaf()) {
			codes.insert({ now->val, code });
			return;
		}
		if (now->has_lchild())
			construct(now->lc, next_bit(code, 0));
		if (now->has_rchild())
			construct(now->rc, next_bit(code, 1));
	}
	//construct huffman tree from code
	void construct(ptr now, code_ref code, size_t code_len, CharT val) {
		if (code_len)
			if (code & (1 << (code_len - 1))) {
				if (!now->has_rchild())
					now->insert_as_rchild(CharT());
				construct(now->rc, code, code_len - 1, val);
			} else {
				if (!now->has_lchild())
					now->insert_as_lchild(CharT());
				construct(now->lc, code, code_len - 1, val);
			} else now->val = val;

	}
	//reverse original code
	//to make reading code easier
	static code_ref make_code(code_ref n, size_t sz) {
		code_ref res = 0;
		for (int i = 0; i < 8 * sizeof(code_ref); ++i)
			res |= ((n >> i) & 1) << (8 * sizeof(code_ref) - 1 - i);
		return res >> (sizeof(code_ref) * 8 - sz);
	}

	//construct huffman tree from string
	void construct() {
		//for selecting min and second min element from all chars
		priority_queue<info, ::vector<info>, std::greater<>> min_heap;
		//count chars shown time using map implemented(red-black tree)
		for (auto c : original_str)++ref_map[c];
		for (auto p : ref_map)//add all char to min heap
			min_heap.emplace(p.second, p.first, nullptr);
		while (true) {
			//first selected
			info left = min_heap.top();
			min_heap.pop();
			if (!ptr_of(left))//not created
				ptr_of(left) = new bintree_node<CharT>(char_of(left));
			if (min_heap.empty()) {//only remains one char
				//this char is root
				root = ptr_of(left); break;
			}
			//second selected
			info right = min_heap.top();
			min_heap.pop();
			if (!ptr_of(right))//not created
				ptr_of(right) = new bintree_node<CharT>(char_of(right));
			//selected node may not contain any char
			//now creating left and right' s root
			//which is a dummy, not containing any info
			root = new bintree_node<CharT>
				(CharT(), nullptr, ptr_of(left), ptr_of(right));
			ptr_of(left)->parent = //connect root with left and right
				ptr_of(right)->parent = root;
			//put back the node just created
			min_heap.push({ count_of(left) + count_of(right), CharT(), root });
		}
		//use leftmost 1 as a dummy 
		//so when writing it must be erased from code
		construct(root, 1);
	}

	//get original information from compressed data 
	template<class Out>
	size_t get_original(const std::vector<bool> &bits, size_t rank, Out &out, ptr now) {
		if (rank >= bits.size())return rank;//read to end of file
		if (!para_size)return bits.size();//all chars read
		if (now->is_leaf()) {//reach an actual char
			write_obj(out, now->val);
			para_size--;//chars that should read decrease by 1
			return rank;
		}
		bool right = bits[rank];//continue reading the same charactor
		return get_original(bits, rank + 1, out, right ? now->rc : now->lc);
	}

	//get original information from compressed data 
	template<class Out>
	void get_original(const std::vector<bool> &bits, Out &out) {
		int rank = 0;
		while (rank < bits.size() && para_size) {
			//update position that has been read
			int new_rank = get_original(bits, rank, out, this->root);
			if (new_rank == rank)throw std::exception();
			rank = new_rank;
		}
	}

public:

	huffman(const huffman& rhs)
		:bin_tree<CharT>(rhs), original_str(rhs.original_str),
		codes(rhs.codes), ref_map(rhs.ref_map), para_size(rhs.para_size) {}

	explicit huffman(std::basic_istream<CharT> &in) {
		std::basic_stringstream<CharT> ss;
		CharT now;
		while (read_obj(in, now))
			original_str.emplace_back(now);
		construct();
	}

	explicit huffman(const std::basic_string<CharT> &str)
		:original_str(str.begin(), str.end()) {
		construct();
	}

	template<class Iter>huffman(Iter begin, Iter end)
		: original_str(begin, end) {
		construct();
	}

	//construct tree from all the code pairs
	huffman(const map<code_ref, CharT> &rev_codes, int p_size)
		: para_size(p_size) {
		root = new bintree_node<CharT>();
		for (auto &&item : rev_codes) {
			construct(root, item.first, bsr(item.first), item.second);
			codes.insert({ item.second, item.first });
		}
	}

	map<CharT, size_t> counts() const { return ref_map; }

	map<CharT, code_ref> encoding() const { return codes; }

	::vector<CharT> original() { return original_str; }

	//compile file
	template<class Out> void write(Out &out) {
		//write header
		//the file could be compressed
		//writing header for a compressed file
		//may cause file size to increase 
		write_obj(out, original_str.size());
		write_obj(out, codes.size());
		for (auto &&p : codes) {
			write_obj(out, p.first);
			write_obj(out, p.second);
		}
		//buffer
		::vector<code_ref> buffer(1);
		const size_t ref_size = sizeof(code_ref) * 8;
		size_t sz_now = buffer.back() = 0;
		for (auto &&item : original_str) {//for each char
			//get code length and leftmost 1
			size_t first_1 = bsr(codes[item]);
			//get code for this char
			code_ref code = make_code(codes[item], first_1);
			//fill buffer's last element
			buffer.back() |= (code) << sz_now;
			//if buffer' s last element does not have enough size
			if (sz_now + first_1 >= ref_size) {
				//fill the rest to new last element
				sz_now = sz_now + first_1 - ref_size;
				buffer.push_back(code >> (first_1 - sz_now));
			} else sz_now += first_1;//update size remain
		}
		for (auto &&item : buffer) write_obj(out, item);
	}
	//decompress compressed file
	template<class In, class Out> static huffman read(In &in, Out &out) {
		const size_t ref_size = sizeof(code_ref) * 8;
		//read header
		int para_size = read_obj<size_t>(in);
		int codes_size = read_obj<size_t>(in);
		if (para_size <= 0 || codes_size <= 0)
			throw std::exception();
		map<code_ref, CharT> codes;
		while (codes_size--) {
			auto first = read_obj<CharT>(in);
			auto second = read_obj<code_ref>(in);
			codes.insert({ second, first });
		}
		//read all compressed data to a buffer
		std::vector<bool> all;
		code_ref sz;
		while (read_obj(in, sz))
			for (int i = 0; i < ref_size; ++i) {
				all.push_back(sz & 1);
				sz >>= 1;
			}
		//create huffman tree from header's huffman code
		huffman<CharT> _ret_val(codes, para_size);
		//get original information
		_ret_val.get_original(all, out);
		return _ret_val;
	}
};


#endif //DATA_STRUCTURE_EXP_HUFFMAN_H
