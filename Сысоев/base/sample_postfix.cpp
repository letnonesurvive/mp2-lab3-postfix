﻿#include <iostream>
#include <string>
#include "postfix.h"

using namespace std;

int main()
{
	string expression;
	TPostfix postfix("(((1+23)*1-22)+5)*2-7");
	double res;

	setlocale(LC_ALL, "Russian");
	//cout << "Введите арифметическое выражение: ";
	//cin >> expression;
	//cout << expression << endl;
	cout << "Арифметическое выражение: " << postfix.GetInfix() << endl;
	postfix.ToPostfix();
	cout << "Постфиксная форма: " << postfix.GetPostfix() << endl;
	res = postfix.Calculate();
	cout << res << endl;
	return 0;
}
