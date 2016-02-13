#include "StackList.h"
#include "EmptyStack.h"

namespace VuKevin
{
	template <class Object>
	bool Stack<Object>::isConsecutive(const Object &data) const
	{
		StackNode<Object> *ptr;
		ptr = topNode;
		while (ptr->getNext() != NULL)
		{
			if (ptr->getElement() == data)
				if (ptr->getNext()->getElement() == data)
					return true;
			ptr = ptr->getNext();
		}
		return false;
	}

	template <class Object>
	void Stack<Object>::reverse() // Remember stacks are LIFO!
	{
		StackNode<Object> *ptr; // Set ptr1 to point to the top node
		ptr = topNode;
		int size = 1;
		int sizeCopy = 0;
		while (ptr->getNext() != NULL) // Get the size of the stack
		{
			size++;
			ptr = ptr->getNext();
		}
		Object* oPtr = new Object[size];
		Object t;
		int k = 0;
		while (size > 0) // Retrieve the important elements
		{
			t = topAndPop();
			*(oPtr + k) = t;
			size--;
			sizeCopy++;
			k++;
		}
		makeEmpty();
		int i = 0;
		while (sizeCopy > 0) // Reassign the new items
		{
			push(oPtr[i]);
			sizeCopy--;
			i++;
		}

		delete[] oPtr;
	}

	template <class Object>
	Stack<Object>::Stack() // Stack Constructor
	{
		topNode = NULL;
	}

	template <class Object>
	Stack<Object>::Stack(const Stack<Object>& rhs) // Stack Copy Constructor
	{
		topNode = NULL;
		*this = rhs;
	}

	template <class Object>
	Stack<Object>::~Stack() // Stack Destructor
	{
		makeEmpty();
		delete topNode;
	}

	template <class Object>
	bool Stack<Object>::isEmpty() const // is Empty
	{
		return((topNode == NULL));
	}

	template <class Object>
	void Stack<Object>::makeEmpty() // Make Empty
	{
		while (!isEmpty())
			pop();
	}

	template <class Object>
	void Stack<Object>::push(const Object& data) // Push an item onto the stack
	{
		StackNode<Object>* newNode = new StackNode<Object>(data, topNode);
		topNode = newNode;
	}

	template <class Object>
	void Stack<Object>::pop()  // Pop the top from the stack
	{
		if (isEmpty()) {
			 throw EmptyStack();
		 }
		StackNode<Object> *oldTop = topNode;
		topNode = topNode->getNext();
		delete oldTop;
	}

	template <class Object>
	const Object& Stack<Object>::top() const // Retrieve the top element
	{
		 if (isEmpty())
			 throw EmptyStack();
		StackNode<Object> node = *topNode;
		return(node.getElement());
	}

	template <class Object>
	Object Stack<Object>::topAndPop() // retrieve the top element and then pop the top off the stack
	{
		Object o = top();
		pop();
		return(o);
	}

	// Deep copy of linked Stack
	template <class Object>
	const Stack<Object>& Stack<Object>::operator =(const Stack<Object>& rhs)  // Assignment operator
	{
		if (this != &rhs)
		{
			makeEmpty();
			if (!(rhs.isEmpty()))
			{
				StackNode<Object> * rhsTopNode = rhs.topNode;
				StackNode<Object> * myTopNode = new StackNode<Object>(rhsTopNode->getElement());
				topNode = myTopNode;

				rhsTopNode = rhsTopNode->getNext();
				while (rhsTopNode != NULL) {
					myTopNode->setNext(new StackNode<Object>(rhsTopNode->getElement()));
					myTopNode = myTopNode->getNext();
					rhsTopNode = rhsTopNode->getNext();
				}
			}
		}
		return(*this);
	}

	template <class Object>
	std::ostream& Stack<Object>::printStack(std::ostream& outs) const
	{
		if (isEmpty())
			outs << "Empty Stack";
		else
		{
			outs << "TOP: ";
			StackNode<Object> * node = topNode;
			while (node != NULL)
			{
				outs << node->getElement();
				outs << "\n     ";           /// for visual alignment
				node = node->getNext();
			}
		}
		return(outs);
	}
}
