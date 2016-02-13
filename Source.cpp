#include <iostream>
#include "StackList.h"
#include "Calculator.h"

using namespace std;
using namespace VuKevin;


int main()
{
	//char *infix[] = { "(3+4)" };
	//int i = 0;
	//if (Calculator::checkDelimiters(infix[i]))
	//	cout << "Yay";
	//else
	//	cout << "Oh no :(" << endl;

	char* expr[] = { "12+(14*10+9)", "7 * 122 - (100 + 1/2) * 14", 
		"50 * 2 * 3 * (6/0)", "((17.2+2.9)*15-12.7)/(7-4.0)", 
		"5 + ((1 + 2) * 4) - 3", "12 * (4 + 6)", "1 + 2)/10", 
		"2.21/6*1.1+(3.145 -1.1)", "1 * 2.2 + x" };
	cout << endl; 
	cout << " " << "Stack Calculator Assignment" << endl << endl;
	int size = sizeof(expr) / sizeof(expr[0]); 
	for (int i = 0; i < size; i++) 
	{
		try 
		{ 
			cout << " " << "Infix Expression: " << expr[i] << endl; 
			cout << " " << "Postfix Expression: " << Calculator::infixToPostfix(expr[i]) << endl;
			cout << " " << "Result = " << Calculator::evaluate(expr[i]); 
		}
		catch (exception e) 
		{ 
			cout << " " << expr[i] << ": " << e.what();
		}
		cout << endl << endl; 
	}
	return 0;
}
