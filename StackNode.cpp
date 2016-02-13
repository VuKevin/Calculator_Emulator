#include "StackNode.h"

namespace VuKevin
{
	template <class DataType>
	StackNode<DataType>::StackNode(const DataType& theElement, StackNode<DataType> * node)
	{
		element = theElement;
		next = node;
	}

	template <class DataType>
	const DataType& StackNode<DataType>::getElement() const
	{
		return(element);
	}

	template <class DataType>
	StackNode<DataType>* StackNode<DataType>::getNext() const
	{
		return(next);
	}

	template <class DataType>
	void StackNode<DataType>::setNext(StackNode<DataType>* node)
	{
		next = node;
	}

}
