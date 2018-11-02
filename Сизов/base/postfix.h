#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <sstream>

using namespace std;

class TPostfix
{
	string infix;
	string postfix;
	string Compare(char a, char b);
	bool Operand(char p);
	bool Brackets();
	bool Term();
	void Split(string &str);
	void Input(string &v);
public:
	TPostfix(string _inf="")
	{
		infix = _inf;
	}
	string GetInfix() { return infix; }
	string GetPostfix() { return postfix; }
	string ToPostfix();
	double Calculate();
};

#endif