#pragma once
#ifndef DATA_STRUCTURE_EXP_BASIC_H
#define DATA_STRUCTURE_EXP_BASIC_H

template<class Seq>
void output_list(const Seq &list) {
	std::cout << "Size:" << list.size() << " Pos:" << (&list) << std::endl;
	for (const auto &x : list) {
		std::cout << x << " ";
	}
	std::cout << std::endl;
}

using uint = unsigned int;
using ulong = unsigned long long;

#ifdef _MSC_VER
//Visual Studio

#include <intrin.h>
#pragma intrinsic(_BitScanReverse)

uint __inline __builtin_clz(uint value) {
	unsigned long leading_zero = 0;
	if (_BitScanReverse(&leading_zero, value))
		return 31 - leading_zero;
	return 32;
}

#ifdef _WIN64
ulong __inline __builtin_clz(ulong value) {
	unsigned long leading_zero = 0;
	if (_BitScanReverse64(&leading_zero, value))
		return 63 - leading_zero;
	return 64;
}
#endif // _WIN64

#endif // _MSC_VER

struct binary_io {
	template<class Out, class Struct>
	static void write_obj(Out &out, Struct u) {
		out.write(reinterpret_cast<typename Out::char_type *>(&u), sizeof(u));
	}

	template<class Struct, class In>
	static In &read_obj(In &in, Struct &u) {
		in.read(reinterpret_cast<typename In::char_type *>(&u), sizeof(u));
		return in;
	}

	template<class Struct, class In>
	static Struct read_obj(In &in) {
		Struct u;
		in.read(reinterpret_cast<typename In::char_type *>(&u), sizeof(u));
		return u;
	}
};


#endif 
