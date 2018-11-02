#include "postfix.h"
#include "stack.h"
#include <vector>
#include <regex>

bool TPostfix::Operand(char p)
{
	if (p == '+' || p == '-' || p == '*' || p == '/' || p == '(' || p == ')')
		return true;
	else return false;
}
string TPostfix::Compare(char a, char b)
{
	if ((a == '*' || a == '/') && (b == '*' || b == '/'))//одного порядка
		return "compare";
	else if ((a == '+' || a == '-') && (b == '+' || b == '-'))//одного порядка
		return "compare";
	else if ((a == '*' || a == '/') && (b == '+' || b == '-'))//большего порядка
		return "greater";
	else if ((a == '+' || a == '-') && (b == '*' || b == '/'))//меньшего порядка
		return "less";
	//else return"last elem if bracket";
}

void TPostfix::Input(string &v)
{
	string tmp;
	for (int i = 0; i < v.size(); i++)
	{
		if((int(v[i])>=65&&int(v[i])<=90)||(int(v[i])>=97&&int(v[i])<=122))//значения переменных в диапазоне
		{
			cout << "Введите переменную " << v[i]<<':';
			cin >> tmp;
			char var = v[i];
			int j = i;
			while (j < v.size())//замена всех одинаковых переменных в строке
			{
				if (var == v[j])
				{
					v.erase(j, 1);
					v.insert(j, tmp);
					j += tmp.size();
				}
				else j++;
			}
		}
	}
}

bool TPostfix::Brackets()//проверка на расстановку скобок
{
	int left = 0, right = 0;
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == '(')
			left++;
		else if (infix[i] == ')')
			right++;
		if (right > left)
			throw"ошибка в скобках";
	}
	if (left == right)
		return true;
	else return false;
}

bool TPostfix::Term()//проверка на колличество операндов и операций
{
	int operands = 0, operations = 0;
	for (int i = 0; i < infix.size(); i++)
	{
		if (infix[i] == '+' || infix[i] == '-' || infix[i] == '*' || infix[i] == '/')
			operations++;
		else if (!Operand(infix[i]))
		{
			while (infix[i] != '+' && infix[i] != '-'  && infix[i] != '*'  && infix[i] != '/')
			{
				i++;
				if (i == infix.size())
					break;
			}
			i--;
			operands++;
		}
	}
	if (operands == operations + 1)
		return true;
	else return false;
}

void TPostfix::Split(string &str)//разделить запятыми строчку
{
	if (str.back() != ',')
		str += ',';
}

string TPostfix::ToPostfix()
{
	if (!Brackets())
		throw"ошибка в расстановке скобок";
	int count = -1;//счетчик операндов
	TStack<char> op(infix.size());
	for (int i = 0; i < infix.size(); i++)
	{
		if (Operand(infix[i]))
		{
			if (op.IsEmpty() || infix[i] == '(')
			{
				if (infix[i] != '(')
					Split(postfix);
				op.Put(infix[i]);
				count++;
				continue;
			}
			else if (infix[i] == ')')
			{
				while (op.Back() != '(')
				{
					Split(postfix);
					postfix += op.Get();
					count--;
				}
				op.Get();
				count--;
			}
			else if ((op.Back()) == '(' || Compare(infix[i], op.Back()) == "greater")
			{
				op.Put(infix[i]);
				Split(postfix);
				count++;
			}
			else if (Compare(infix[i], op.Back()) == "less")
			{
				Split(postfix);
				while (!(op.IsEmpty()))
				{
					if (op.Back() == '(')
						break;
					postfix += op.Get();
					Split(postfix);
					count--;
				}
				op.Put(infix[i]);
				count++;
			}
			else if (Compare(infix[i], op.Back()) == "compare")
			{
				Split(postfix);
				postfix += op.Get();
				op.Put(infix[i]);
				Split(postfix);
			}
		}
		else
			postfix += infix[i];
		if (i == infix.size() - 1)
		{
			for (count; count >= 0; count--)
			{
				Split(postfix);
				postfix += op.Get();
			}
		}
	}
	return postfix;
}

double TPostfix::Calculate()
{
	if (!Term()||postfix=="")
		throw "Недостаточно операндов";
	Input(postfix);
	TStack<double> result(infix.size());
	string tmp;
	for (int i = 0; i < postfix.size(); i++)
	{
		if (postfix[i] == ',')
			continue;
		if (!Operand(postfix[i]))
		{
			while (postfix[i] != ',')
			{
				tmp += postfix[i];
				i++;
			}
			result.Put(atof(tmp.c_str()));
			tmp = "";
		}
		else
		{
			double t2 = result.Get(), t1 = result.Get();
			if (postfix[i] == '+')
				result.Put(t1 + t2);
			else if (postfix[i] == '-')
				result.Put(t1 - t2);
			else if (postfix[i] == '*')
				result.Put(t1 * t2);
			else if (postfix[i] == '/')
			{
				if (t2 == 0)
					throw "Деление на ноль невозможно";
				result.Put(t1 / t2);
			}
		}
	}
	return result.Get();
}
