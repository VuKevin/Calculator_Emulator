#pragma once
#include "StackList.h"
#include <string>


namespace VuKevin
{
	class Calculator
	{
	public:
		static double evaluate(const char* infix);
		static char* infixToPostfix(const char* infix);
		static double evaluatePostfix(const char* postfix);
		static bool checkDelimiters(const char* infix);
		static bool checkValidChars(const char* infix);
	private:
		static bool isOperator(char ch);
		static bool isValidChar(char ch);
		static int weight(char ch);
	};
}
