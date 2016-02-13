#ifndef STACKNODE_H
#define STACKNODE_H

#include <iostream>

namespace VuKevin
{
	template <class DataType>
	class StackNode
	{
	public:
		StackNode(const DataType& theElement = DataType(), StackNode * node = NULL);
		const DataType& getElement() const;
		StackNode* getNext() const;
		void setNext(StackNode* node);
	private:
		DataType element;
		StackNode* next;

	};
}
#include "StackNode.cpp"
#endif
