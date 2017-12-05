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
#include <bitset>
#include <vector>
#include <map>
#include "basic.h"
#include "bin_tree.h"


template<class CharT>
class huffman : public bin_tree<CharT>,binary_io{

	using ptr = typename bintree_node<CharT>::bnode_ptr;
	using const_ptr = typename bintree_node<CharT>::const_bnode_ptr;
	using code_ref = unsigned int;
	using code_pair = std::pair<CharT, code_ref>;

	struct info {
		size_t node_count;
		CharT node_char;
		ptr node_ptr;

		info(size_t c, CharT ch, ptr p)
			: node_count(c), node_char(ch), node_ptr(p) {}

		info() {}

		bool operator>(const info &t) const {
			return node_count > t.node_count;
		}
	};

	std::basic_string<CharT> original_str;
	std::map<CharT, code_ref> codes;
	std::map<CharT, size_t> ref_map;
#ifndef _MSC_VER
	ptr &root = bin_tree<CharT>::root;
#endif
	int para_size;

	size_t count_of(info &t) { return t.node_count; }

	CharT char_of(info &t) { return t.node_char; }

	ptr &ptr_of(info &t) { return t.node_ptr; }

	code_ref next_bit(code_ref ref, bool val) { return (ref << 1) | (code_ref)(val); }

	inline size_t bsr(code_ref ref) { return sizeof(code_ref) * 8 - __builtin_clz(ref) - 1; }

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

	void construct(ptr now, code_ref code, size_t code_len, CharT val) {
		if (code_len)
			if (code & (1 << (code_len - 1))) {
				if (!now->has_rchild())
					now->insert_as_rchild(CharT());
				construct(now->rc, code, code_len - 1, val);
			}
			else {
				if (!now->has_lchild())
					now->insert_as_lchild(CharT());
				construct(now->lc, code, code_len - 1, val);
			}
		else now->val = val;

	}

	static code_ref make_code(code_ref n, size_t sz) {
		code_ref res = 0;
		for (int i = 0; i < 8 * sizeof(code_ref); ++i)
			res |= ((n >> i) & 1) << (8 * sizeof(code_ref) - 1 - i);
		return res >> (sizeof(code_ref) * 8 - sz);
	}


	void construct() {
		::priority_queue<info, ::vector<info>, std::greater<>> min_heap;
		for (auto c : original_str)ref_map[c]++;
		for (auto p : ref_map)
			min_heap.emplace(p.second, p.first, nullptr);
		while (true) {
			info left = min_heap.top();
			min_heap.pop();
			if (!ptr_of(left))
				ptr_of(left) = new bintree_node<CharT>(char_of(left));
			if (min_heap.empty()) {
				root = ptr_of(left);
				break;
			}
			info right = min_heap.top();
			min_heap.pop();
			if (!ptr_of(right))
				ptr_of(right) = new bintree_node<CharT>(char_of(right));
			root = new bintree_node<CharT>
				(CharT(), nullptr, ptr_of(left), ptr_of(right));
			ptr_of(left)->parent =
				ptr_of(right)->parent = root;
			min_heap.push({ count_of(left) + count_of(right), CharT(), root });
		}
		construct(root, 1);
	}

	template<class Out>
	size_t get_original(const std::vector<bool> &bits, size_t rank, Out &out, ptr now) {
		if (rank >= bits.size())return rank;
		if (!para_size)return 0;
		if (now->is_leaf()) {
			out << now->val;
			para_size--;
			return rank;
		}
		bool right = bits[rank];
		return get_original(bits, rank + 1, out, right ? now->rc : now->lc);
	}

	template<class Out>
	void get_original(const std::vector<bool> &bits, Out &out) {
		int rank = 0;
		while (rank < bits.size() && para_size) {
			rank = get_original(bits, rank, out, root);
		}
	}

public:
	
	explicit huffman(std::basic_istream<CharT> &in) {
		std::basic_stringstream<CharT> ss;
		CharT now;
		while (read_obj(in, now)) ss << now;
		original_str = ss.str();
		construct();
	}

	explicit huffman(const std::basic_string<CharT> &str)
		:original_str((str)) {
		construct();
	}

	explicit huffman(const std::map<code_ref, CharT> &rev_codes, int p_size)
		: para_size(p_size) {
		root = new bintree_node<CharT>();
		for (auto &&item : rev_codes) {
			construct(root, item.first, bsr(item.first), item.second);
			codes.emplace(item.second, item.first);
		}
	}

	std::map<CharT, size_t> counts() { return ref_map; }

	std::map<CharT, code_ref> encoding() { return codes; }

	std::basic_string<CharT> str() { return original_str; }

	template<class Out> void write(Out &out) {
		write_obj(out, original_str.size());
		write_obj(out, codes.size());
		for (auto &&p : codes) {
			write_obj(out, p.first);
			write_obj(out, p.second);
		}
		std::vector<code_ref> buffer(1);
		const size_t ref_size = sizeof(code_ref) * 8;
		size_t sz_now = buffer.back() = 0;
		for (auto &&item : original_str) {
			size_t first_1 = bsr(codes[item]);
			code_ref code = make_code(codes[item], first_1);
			buffer.back() |= (code) << sz_now;
			if (sz_now + first_1 >= ref_size) {
				sz_now = sz_now + first_1 - ref_size;
				buffer.push_back(code >> (first_1 - sz_now));
			}
			else sz_now += first_1;
		}
		for (auto &&item : buffer) write_obj(out, item);
	}

	template<class In, class Out> static void read(In &in, Out &out) {
		const size_t ref_size = sizeof(code_ref) * 8;
		int para_size = read_obj<size_t>(in);
		int codes_size = read_obj<size_t>(in);
		std::map<code_ref, CharT> codes;
		while (codes_size--) {
			auto first = read_obj<CharT>(in);
			auto second = read_obj<code_ref>(in);
			codes.emplace(second, first);
		}
		std::vector<bool> all;
		code_ref sz;
		while (read_obj(in, sz))
			for (int i = 0; i < ref_size; ++i) {
				all.push_back(sz & 1);
				sz >>= 1;
			}
		huffman<CharT>(codes, para_size).get_original(all, out);
	}
};


#endif //DATA_STRUCTURE_EXP_HUFFMAN_H
