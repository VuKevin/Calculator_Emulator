#ifndef STACKLIST_H
#define STACKLIST_H
#include "StackNode.h"
namespace VuKevin
{
	template <class Object>
	class Stack
	{
	public:
		Stack();
		Stack(const Stack& rhs);
		~Stack();

		bool isEmpty() const;
		void makeEmpty();
		void push(const Object& data);
		void pop();
		const Object& top() const;
		Object topAndPop();
		std::ostream& printStack(std::ostream& outs) const;

		const Stack& operator =(const Stack& rhs);

		// ASSIGNED:
		bool isConsecutive(const Object &data) const;
		void Stack<Object>::reverse();

	private:
		StackNode<Object> * topNode;
	};
}


#include "StackList.cpp"
#endif
