
#pragma warning(disable:4996)
#include "exp_1.h"
#include "exp_2.h"
#include "exp_3.h"
#include "exp_4.h"
#include "exp_5.h"

int main() {
	//    freopen("D:\\x.txt","w",stdout);
	uint i;
#define RUN_CASE(x) case x:run_exp##x##_tests();break
	do {
		std::cout << "Choose a number from 1 to 5" << std::endl;
		std::cin >> i;
		switch (i) {
			RUN_CASE(1);
			RUN_CASE(2);
			RUN_CASE(3);
			RUN_CASE(4);
			RUN_CASE(5);
		default:break;;
		}
	} while (i<=5&&i>0);
	return 0;
}


