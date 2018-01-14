#include <iostream>
#include <string>


int add(int a, int b) {
	return a + b;
}

int minus(int a, int b) {
	return a - b;
}

int times(int a, int b) {
	return a * b;
}

int divide(int a, int b) {
	return b == 0 ? 0 : a / b;
}

int calc(char op, int a, int b){
	switch (op){
	case 'a':
	case 'A':
		return add(a, b);
	case 'm':
	case 'M':
		return minus(a, b);
	case 't':
	case 'T':
		return times(a, b);
	case 'd':
	case 'D':
		return divide(a, b);
	default:
		return 0;
	}
}

int main() {
	calc('a', 1, 2);
	calc('m', 2, 3);
	calc('t', calc('d', 8, 2), calc('a', 3, 4));

	return 0;
}