#include <iostream>
#include <ctime>
#include <cinttypes>
#include <experimental/filesystem>
#include "huffman.h"
#include <bitset>

int zip_main(int argc, char** argv) {
	using namespace std;
	time_t time_now = time(nullptr);
#define CHAR_TYPE uint8_t
	basic_ifstream<CHAR_TYPE> input(argv[1], ios::binary);
	basic_ofstream<CHAR_TYPE> output(argv[2], ios::binary);
	bool is_decompress = argc >= 4 && argv[3][0] == 'd';
	map<CHAR_TYPE, size_t> char_cnts;
	map<CHAR_TYPE, huffman<CHAR_TYPE>::code_ref> char_code;
	if (is_decompress) {
		try {
			auto res = huffman<CHAR_TYPE>::read(input, output);
			char_cnts = res.counts();
			char_code = res.encoding();
		}catch(...) {
			cout << "Decompress failed!";
			return 0;
		}
	}
	else {
		auto res = huffman<CHAR_TYPE>(input);
		res.write(output);
		char_cnts = res.counts();
		char_code = res.encoding();
	}
	input.close();
	output.close();
	
	namespace fs = experimental::filesystem;
	cout <<"Time : "<< (time(nullptr) - time_now) <<"   Compression Rate : "<<
		static_cast<double>(fs::file_size(fs::path(argv[is_decompress?1:2])))/
		file_size(fs::path(argv[is_decompress?2:1]))<< endl;


	for (uint i = 0; i < 256; i++) {
		cout << i << endl;
		if(char_code.find(i)!=char_code.end())
		cout << std::bitset<16>(char_code[i]);
		else cout << "DOES NOT EXIST";
		if (is_decompress) {
			cout << endl << "UNZIP";
		}
		else {
			cout << endl << char_cnts[i];
		}
		cout << endl;
	}
	return 0;
}

