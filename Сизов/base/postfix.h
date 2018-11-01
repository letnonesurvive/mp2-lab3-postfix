#ifndef __POSTFIX_H__
#define __POSTFIX_H__

#include <string>
#include <sstream>

using namespace std;

class TPostfix
{
	string infix;
	string postfix;
	string compare(char a, char b);
	bool operand(char p);
	bool brackets();
	bool term();
	void split(string &str);
	void variable_input(string &v);
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