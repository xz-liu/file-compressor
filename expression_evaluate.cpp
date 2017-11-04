//
// Created by joker on 2017/11/5.
//

int read_optrator(const char *opt);

double read_number(char *&num);

char order_between(int optTop, int optCur);

double evaluate(char *str);

double calculate(double num1, int optr, double num2 = 0.0);

#include "stack.h"

#include <sstream>
#include <string>
#include <cmath>
#include <cctype>
#include <cstring>
#include <cstdlib>
#include <algorithm>


#define OPTR_ADD 0
#define OPTR_MIN 1
#define OPTR_MUL 2
#define OPTR_DIV 3
#define OPTR_POW 4
#define OPTR_FAC 5
#define OPTR_LBR 6
#define OPTR_RBR 7
#define OPTR_NIL 8
#define OPTR_SIN 9
#define OPTR_COS 10
#define OPTR_TAN 11
#define OPTR_LOG 12
#define OPTR_ASIN 13
#define OPTR_ACOS 14
#define OPTR_ATAN 15
#define OPTR_ERR 16

const int optr_count = 16;

static const char pri[optr_count][optr_count] = {
        /*					+	-	*	/	^	!	(	)	0	sin(	cos(	tan(	log(	asin(	acos(	atan(		*/
        /*	+		*/        '>', '>', '<', '<', '<', '<', '<', '>', '>', '<', '<', '<', '<', '<', '<', '<',
        /*	-		*/        '>', '>', '<', '<', '<', '<', '<', '>', '>', '<', '<', '<', '<', '<', '<', '<',
        /*	*		*/        '>', '>', '>', '>', '<', '<', '<', '>', '>', '<', '<', '<', '<', '<', '<', '<',
        /*	/		*/        '>', '>', '>', '>', '<', '<', '<', '>', '>', '<', '<', '<', '<', '<', '<', '<',
        /*	^		*/        '>', '>', '>', '>', '>', '<', '<', '>', '>', '<', '<', '<', '<', '<', '<', '<',
        /*	!		*/        '>', '>', '>', '>', '>', '>', '<', '>', '>', '<', '<', '<', '<', '<', '<', '<',
        /*	(		*/        '<', '<', '<', '<', '<', '<', '<', '=', ' ', '<', '<', '<', '<', '<', '<', '<',
        /*	)		*/        ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
        /*	0		*/        '<', '<', '<', '<', '<', '<', '<', ' ', '=', '<', '<', '<', '<', '<', '<', '<',
        /*	sin(	*/        '<', '<', '<', '<', '<', '<', '<', 'c', ' ', '<', '<', '<', '<', '<', '<', '<',
        /*	cos(	*/        '<', '<', '<', '<', '<', '<', '<', 'c', ' ', '<', '<', '<', '<', '<', '<', '<',
        /*	tan(	*/        '<', '<', '<', '<', '<', '<', '<', 'c', ' ', '<', '<', '<', '<', '<', '<', '<',
        /*	log(	*/        '<', '<', '<', '<', '<', '<', '<', 'c', ' ', '<', '<', '<', '<', '<', '<', '<',
        /*	asin(	*/        '<', '<', '<', '<', '<', '<', '<', 'c', ' ', '<', '<', '<', '<', '<', '<', '<',
        /*	acos(	*/        '<', '<', '<', '<', '<', '<', '<', 'c', ' ', '<', '<', '<', '<', '<', '<', '<',
        /*	atan(	*/        '<', '<', '<', '<', '<', '<', '<', 'c', ' ', '<', '<', '<', '<', '<', '<', '<',
};

using namespace std;

const char eval[] = "2.7182818", pival[] = "3.14159265", degree[] = "*0.0174532925";

double fac(int i) {
    double x = 1;
    for (int j = 1; j <= i; j++) {
        x *= j;
    }
    return x;
}

void check_out_range(const char *str, bool reset = false, int slen = 0) {
    static int str_len;
    static const char *ini;
    if (reset) {
        str_len = slen;
        ini = str;
    } else {
        if (str - ini > str_len)
            throw std::exception();
    }
}

double get_result(string str) {
    std::string original(str), processed;
    for (auto c : original) {
        if (c == 'P') {
            processed += pival;
        } else if (c == 'D') {
            processed += degree;
        } else if (isspace(c) || isupper(c))
            continue;
        else if (c == 'e') {
            processed += eval;
        } else processed.push_back(c);
    }
    char *input = new char[processed.size() + 10];
    strcpy(input, processed.c_str());
    check_out_range(input, true, processed.size());
    double result = evaluate(input);
    delete[]input;
    return result;
}


int read_optrator(const char *opt) {
    check_out_range(opt);
    switch (*opt) {
        case '+':
            return OPTR_ADD;
        case '-':
            return OPTR_MIN;
        case '*':
            return OPTR_MUL;
        case '/':
            return OPTR_DIV;
        case '^':
            return OPTR_POW;
        case '!':
            return OPTR_FAC;
        case '(':
            return OPTR_LBR;
        case ')':
            return OPTR_RBR;
        case '\0':
            return OPTR_NIL;
        case 's':
            return OPTR_SIN;
        case 'c':
            return OPTR_COS;
        case 't':
            return OPTR_TAN;
        case 'a':
            switch (opt[1]) {
                case 's':
                    return OPTR_ASIN;
                case 'c':
                    return OPTR_ACOS;
                case 't':
                    return OPTR_ATAN;
                default:
                    break;
            }
            break;
        case 'l':
            return OPTR_LOG;
    }
    throw exception();
    return OPTR_ERR;
}

double read_number(char *&num) {
    check_out_range(num);
    double d;
    sscanf(num, "%lf", &d);
    while (isdigit(*num) || (*num) == '.')num++;
    return d;
}

char order_between(int optTop, int optCur) {
    return pri[optTop][optCur];
}

void str_next(char *&str, int op) {
    check_out_range(str);
    if (op < OPTR_SIN) str++;
    else if (op < OPTR_ASIN)str += 4;
    else str += 5;
}

double evaluate(char *str) {
    try {
        stack<double> opnd;
        stack<int> optr;
        optr.push(OPTR_NIL);
        while (!optr.empty()) {
            check_out_range(str);
            if (isdigit(*str) || *str == '.') {
                opnd.push(read_number(str));
            } else {
                int op = read_optrator(str);
                if (op == OPTR_NIL && (optr.empty() ||
                                       (optr.size() == 1 && optr.top() != OPTR_NIL)))
                    throw exception();
                if (optr.top() == OPTR_NIL && op == OPTR_RBR)throw exception();
                switch (order_between(optr.top(), op)) {
                    case '<':
                        optr.push(op);
                        str_next(str, op);
                        break;
                    case 'c': {
                        if (opnd.empty())throw exception();
                        double num = opnd.top();
                        opnd.pop();
                        double res = calculate(num, optr.top());
                        opnd.push(res);
                        optr.pop();
                        str_next(str, op);
                    }
                        break;
                    case '=':
                        optr.pop();
                        str_next(str, op);
                        break;
                    case '>': {
                        int ops = optr.top();
                        if (ops < OPTR_FAC) {
                            double num2 = opnd.top();
                            opnd.pop();
                            double num1 = opnd.top();
                            opnd.pop();
                            double res = calculate(num1, optr.top(), num2);
                            opnd.push(res);
                        } else {
                            double num = opnd.top();
                            opnd.pop();
                            double res = calculate(num, optr.top());
                            opnd.push(res);
                        }
                        optr.pop();
                    }
                        break;
                    default:
                        throw exception();
                }
            }
        }
        return opnd.top();
    }
    catch (...) {
        return 0;
    }
}

double calculate(double num1, int optr, double num2) {
    switch (optr) {
        case OPTR_ADD:
            return num1 + num2;
        case OPTR_MIN:
            return num1 - num2;
        case OPTR_MUL:
            return num1 * num2;
        case OPTR_DIV:
            return num1 / num2;
        case OPTR_POW:
            return pow(num1, num2);
        case OPTR_FAC:
            return fac(num1);
        case OPTR_SIN:
            return sin(num1);
        case OPTR_COS:
            return cos(num1);
        case OPTR_TAN:
            return tan(num1);
        case OPTR_LOG:
            return log(num1);
        case OPTR_ASIN:
            return asin(num1);
        case OPTR_ACOS:
            return acos(num1);
        case OPTR_ATAN:
            return atan(num1);
        default:
            throw exception();
            break;
    }
}
