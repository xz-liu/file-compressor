#define _CRT_SECURE_NO_WARNINGS
#include "rb_tree.h"
#include <iostream>
#include <cstdlib>
#include <string>

int main() {
	using namespace std;
	rb_tree<int> rb;
	string s; double d;
	while(getline(cin,s)) {
		rb_tree<int>::position ptr = nullptr;
		switch (s[0]) {
		case 'i':
			sscanf(s.c_str() + 1, "%lf", &d);
			rb.insert(d);
			break;
		case 'e':
			sscanf(s.c_str() + 1, "%lf", &d);
			rb.erase(d);
			break;
		case 'f':
			sscanf(s.c_str() + 1, "%lf", &d);
			ptr = rb.find(d);
			if (ptr->val != d)ptr = nullptr;
			break;
		case 'c':
			rb.clear();
			break;
		}
		rb.output_tree(cout, ptr);
	}
	cin.get();
}
