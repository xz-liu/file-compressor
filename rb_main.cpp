#define _CRT_SECURE_NO_WARNINGS
#include "rb_tree.h"
#include <iostream>
#include <cstdlib>
#include <string>
#include <ctime>

int rb_main() {
	using namespace std;
	rb_tree < double > rb;
	string s; double d;
	srand(time(nullptr));
	while(getline(cin,s)) {
		rb_tree<double>::position ptr = nullptr;
		switch (s[0]) {
		case 'i':
			if(sscanf(s.c_str() + 1, "%lf", &d))
				rb.insert(d);
			break;
		case 'e':
			if(sscanf(s.c_str() + 1, "%lf", &d))
				rb.erase(d);
			break;
		case 'f':
			if (sscanf(s.c_str() + 1, "%lf", &d)) {
				ptr = rb.find(d);
				if (ptr && ptr->val != d)ptr = nullptr;
			}break;
		case 'c':
			rb.clear();
			break;
		case 'r':
			rb.clear();
			const size_t max_size = 50;
			const size_t cnt = rand() % max_size + 1;
			for (size_t i = 0; i < cnt; ++i) {
				rb.insert(rand() % max_size);
			}
		}
		rb.output_tree(cout, ptr);
	}
	return 0;
}
