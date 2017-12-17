//
// Created by joker on 2017/11/17.
//

#ifndef DATA_STRUCTURE_EXP_EXP_3_H
#define DATA_STRUCTURE_EXP_EXP_3_H




#include <iostream>
#include <functional>
#include <bitset>
#include <sstream>
#include <experimental/filesystem>
#include "huffman.h"
#include "bin_tree.h"
#include "bst.h"

template<class T, class CharT = char>
void pre_order_init(std::basic_istream<CharT> &in,
	bin_tree<T> &new_tree, const T &sepreator) {
	new_tree.pre_order_init(in, sepreator);
}

inline void run_exp3_tests() {
	using std::cout;
	using std::endl;
	using std::bitset;
	using std::ios;
	cout << endl << "Exp 3 :binary trees" << endl << endl;
	cout << "Test huffman tree" << endl;
	
	namespace filesystem = std::experimental::filesystem;
    filesystem::path original_txt("ORIGINAL.txt"),
				compressed("ORIGINAL.COMPRESSED"),		
				processed ("PROCESSED.txt");
	std::ifstream input_text(original_txt,ios::binary);
	
	huffman<char> res(input_text); 
	std::ofstream output(compressed,ios::binary);
	res.write(output);
	input_text.close();
	output.clear();
	output.close();
	cout << "Char counts" << endl;
	for (auto &&x : res.counts()) {
		cout << x.first << ":" << x.second << endl;
	}
	cout << "Encoding" << endl;
	for (auto &&x : res.encoding()) {
		cout << x.first << ":" << bitset<16>(x.second) << endl;
	}
	std::ifstream read_compressed(compressed,ios::binary);
	std::ofstream processed_text(processed,ios::binary);

	huffman<char>::read(read_compressed, processed_text);
	read_compressed.close(); processed_text.close();
	const uintmax_t compressed_size = filesystem::file_size(compressed),
		original_size = filesystem::file_size(original_txt);
	cout << "Compressed length:" << compressed_size << endl;
	cout << "Original length:" << original_size << endl;
	cout << "Compression rate:" << ((double)compressed_size) / original_size << endl;

	bin_tree<char> char_tree;
	std::stringstream ss("abc##de#g##f###");
	cout << "Test traverse" << endl;
	cout << "Input: " << ss.str() << endl;
	pre_order_init<char>(ss, char_tree, '#');
	auto visit = [](char x) {
		cout << x << " ";
	};
	cout << "Pre order :" << endl;
	char_tree.trav_pre_order(visit);
	cout << endl;
	cout << "In order  :" << endl;
	char_tree.trav_in_order(visit);
	cout << endl;
	cout << "Post order :" << endl;
	char_tree.trav_post_order(visit);
	cout << endl;
	cout << "Level      :" << endl;
	char_tree.trav_level(visit);
	cout << endl;

	cout << "Test BST" << endl;
	auto bst_visit = [&](int x) { cout << x << " "; };
	bst<int> bstree;
	vector<int> toInsert{ 11, 2, 3, 42,
						 4, 6, 7, 42,
						 423, 433, 654, 765,
						 43, 4, 53, 454, 5 };
	for (auto x : toInsert) {
		cout << "Insert " << x;
		cout << " Pos: " << bstree.insert(x) << endl;
	}
	cout << "Insert Complete" << endl;
	bstree.for_each(bst_visit);
	cout << endl;
	for (int i = 5; i < 10; ++i) {
		cout << "Erase " << i << " ";
		cout << std::boolalpha << bstree.erase(i) << endl;
		bstree.for_each(bst_visit);
		cout << endl;
	}

	cout << "Sort from biggest to smallest:" << endl;
	bst<int, std::greater<>> big_tree{ 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
	big_tree.for_each(bst_visit);
	cout << endl;
};

#endif //DATA_STRUCTURE_EXP_EXP_3_H
