#include "Calculator.h"
#include <cstring>
#include "DivideByZero.h"
#include "UnbalancedParentheses.h"
#include "InvalidCharacters.h"


namespace cs20
{
	double Calculator::evaluate(const char * infix)
	{
		// TODO: Calculate the value of a mathematical expression given in infix notation.
		// Evaluate postfix
		double answer;
		answer = evaluatePostfix(infix);
		return answer;
	}
	char* Calculator::infixToPostfix(const char *infix)
	{
		// TODO: uses the stack to convert an input string (including parentheses) from infix 
		// notation to postfix notation. If the input string does not contain balanced parentheses, 
		// or if it contains invalid characters, throw a custom exception and stop.
		Stack<char> stackOfChars;
		if (checkDelimiters(infix) == false)
		{
			// std::cerr << "Throw a custom exception and stop" << std::endl;
			throw(UnbalancedParentheses());
			return nullptr;
		}
		if (checkValidChars(infix) == false)
		{
			// std::cerr << "Throw a custom exception and stop" << std::endl;
			throw(InvalidCharacter());
			return nullptr;
		}

		std::string postfix = "";
		for (unsigned int i = 0; i < strlen(infix); i++)
		{
			char chr = infix[i];
			if (isdigit(chr) || chr == '.')
				// add chr to end of the postfix expression
				postfix = postfix + chr;
			else if (chr == '(')
				stackOfChars.push(chr);
			else if (isOperator(chr))
			{
				while (!stackOfChars.isEmpty() && (weight(stackOfChars.top()) >= weight(chr))) // Consider the precedence utilizing weight
				{
					char c = stackOfChars.top();
					stackOfChars.pop();
					postfix = postfix + " ";
					postfix = postfix + c;
				}
				postfix = postfix + " ";
				stackOfChars.push(chr);
			}
			else if (chr == ')')
			{
				while (!stackOfChars.isEmpty() && stackOfChars.top() != '(')
				{
					char c = stackOfChars.top();
					stackOfChars.pop();
					postfix = postfix + " ";
					postfix = postfix + c;
				}
				if (stackOfChars.top() == '(')
					stackOfChars.pop();
			}
			else if (chr == '(')
			{
				char c = stackOfChars.top();
				stackOfChars.pop();
			}
		}
		while (!stackOfChars.isEmpty())
		{
			char c = stackOfChars.top();
			stackOfChars.pop();
			postfix = postfix + " ";
			postfix = postfix + c;
		}

		// Steps to return the newly made Postfix
		char *ptrToPostFix = new char[postfix.size() + 1];
		strcpy_s(ptrToPostFix, postfix.size() + 1, postfix.c_str()); // Or std::strcpy(ptrToPostFix, postfix.c_str()) if you disable deprecation settings
		return ptrToPostFix;
	}
	double Calculator::evaluatePostfix(const char * postfix)
	{
		// TODO: uses the stack to evaluate an input string in postfix notation. 
		// If a divide-by-zero error occurs, throw a custom exception and stop.
		postfix  = infixToPostfix(postfix);
		Stack<double> stackOfDoubles;
		for (unsigned int i = 0; i < strlen(postfix); i++) // Unsigned int to avoid mismatch
		{
			char token = postfix[i];
			if (isdigit(token))
			{
				double operand = 0;
				double convert = 0;
				int countHowManyDecPlaces = 0;
				bool isDecimal = false; // FLAG 
				while (i < strlen(postfix) && (isdigit(postfix[i]) || postfix[i] == '.'))
				{
					// if it's a decimal
					if (postfix[i] == '.')
					{
						i++;
						isDecimal = true;
						continue;
					}
					else
					{
						operand *= 10;
						convert = postfix[i] - '0';
						operand = operand + convert;
						i++;
						if (isDecimal)
						{
							countHowManyDecPlaces++;
						}
					}

				}
				if (countHowManyDecPlaces != 0) // Handling of decimal inputs
				{
					// 1 decimal place
					if (countHowManyDecPlaces == 1)
						operand = operand / 10;
					// 2 decimal places
					if (countHowManyDecPlaces == 2)
						operand = operand / 100;
					// 3 decimal places
					if (countHowManyDecPlaces == 3)
						operand = operand / 1000;
					// 4 decimal places
					if (countHowManyDecPlaces == 4)
						operand = operand / 10000;
					// 5 decimal places
					if (countHowManyDecPlaces == 5)
						operand = operand / 100000;
				}
				i--; // Decrement i inorder to stay return back to track
				stackOfDoubles.push(operand);
			}
			else if (isOperator(token))
			{
				double operand2 = stackOfDoubles.top(); stackOfDoubles.pop(); // Get two operands to prepare for calculator functions
				double operand1 = stackOfDoubles.top(); stackOfDoubles.pop();
				if (operand2 == 0 && (postfix[i] == '/' || postfix[i] == '%'))
				{
					throw DivideByZero();
					return 0;
				}
				if (token == '+') // Perform the operation: operand1 chr operand2
					stackOfDoubles.push(operand1 + operand2);
				if (token == '-') // Perform the operation: operand1 chr operand2
					stackOfDoubles.push(operand1 - operand2);
				if (token == '*') // Perform the operation: operand1 chr operand2
					stackOfDoubles.push(operand1 * operand2);
				if (token == '/') // Perform the operation: operand1 chr operand2
					stackOfDoubles.push(operand1 / operand2);
			}
		}
		double answer;
		answer = stackOfDoubles.top();
		return answer;
	}

	bool Calculator::checkDelimiters(const char * infix)
	{
		// TODO: checks an input string in infix notation for unbalanced parentheses using a stack.
		Stack <char> stackOfChars;
		for (unsigned int d = 0; d < strlen(infix); d++)
		{
			if (infix[d] == '(') // If it is a closing parentheses
				stackOfChars.push(infix[d]);
			else if (infix[d] == ')')
			{
				if (stackOfChars.isEmpty()) // Must be unbalanced
				{
					// std::cerr << "1: String is not balanced." << std::endl; Used for testing purposes to see where function was exiting.
					return false;
				}
				else if (!(stackOfChars.top() == '(' && infix[d] == ')')) // Must be unbalanced
				{
					// std::cerr << "2: String is not balanced." << std::endl;
					return false;
				}
				else
					stackOfChars.pop();
			}
		}
		if (stackOfChars.isEmpty())
		{
			// std::cerr << "3: String is balanced." << std::endl;
			return true;
		}
		else // it must be unbalanced
			// std::cerr << "4: String is not balanced." << std::endl;
			return false;
	}
	bool Calculator::checkValidChars(const char * infix)
	{
		// TODO: checks an input string in infix notation for illegal characters
		// (anything other than operators, blanks, parentheses, or digits); no stack is needed here.
		unsigned int i = 0;
		while (i < strlen(infix))
		{
			if (isValidChar(infix[i]))
				i++;
			else
				return false;
		}
		return true;
	}
	bool Calculator::isOperator(char ch)
	{
		// TODO: Helper method that returns true/false depending on
		// whether a character is an operator (+, -, *, /).
		return ch == '+' || ch == '-' || ch == '*' || ch == '/';
	}
	bool Calculator::isValidChar(char ch)
	{
		// TODO: helper method that returns true / false depending on whether 
		// character is a valid character
		// (+, -, *, / , 0, 1, 2 3, 4, 5, 6, 7, 8, 9, ‘(‘, ‘)’, ‘ ‘).
		return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '0' || ch == '1' ||
			ch == '2' || ch == '3' || ch == '4' || ch == '5' || ch == '6' || ch == '7' ||
			ch == '8' || ch == '9' || ch == '(' || ch == ')' || ch == ' ' || ch == '.';
	}
	int Calculator::weight(char ch)
	{
		// TODO: helper method that returns a weight for the incoming character. 
		// This method is used when evaluating the precedence of operators on the stack. 
		// Assign a value of “2” to the operators “*” and “/”; assign a value of “1” to 
		// the operators “+” and “-“; assign a value of “0” to everything else.
		if (ch == '*' || ch == '/')
			return 2;
		if (ch == '+' || ch == '-')
			return 1;
		return 0;
	}
}
