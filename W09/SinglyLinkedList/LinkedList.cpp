#include "pch.h"
#include "LinkedList.h"

Node::Node(int value, Node* pNext)
	: value{ value }
	, pNext{ pNext }
{
}

LinkedList::LinkedList()
	: m_Size{ 0 }
	, m_pFirstNode{}
{
}

LinkedList::~LinkedList()
{
	Node* current{ m_pFirstNode };
	while (current)
	{
		Node* nextNode = current->pNext;
		delete current;
		current = nextNode;
	}
}

// Wrap the value in a new Node object and add it as first Node of the list
void LinkedList::PushFront(int  value)
{
	Node* newNode{ new Node(value) };
	if (m_pFirstNode)
	{
		newNode->pNext = m_pFirstNode;
		m_pFirstNode = newNode;
	}
	else
		m_pFirstNode = newNode;
	++m_Size;
}

// Remove and delete first Node
void LinkedList::PopFront()
{
	if (m_pFirstNode)
	{
		Node* firstNode{ m_pFirstNode };
		m_pFirstNode = firstNode->pNext;
		delete firstNode;
		firstNode = nullptr;
		--m_Size;
	}
}

// Remove all Nodes having this value
void LinkedList::Remove(int value)
{
	Node* current{m_pFirstNode};
	Node* previousNode{};
	while (current)
	{
		Node* nextNode{ current->pNext };
		if (current->value == value)
		{
			delete current;
			current = nullptr;
			if (previousNode)
				previousNode->pNext = nextNode;
			else
				m_pFirstNode = nextNode;
			--m_Size;
		}
		if(current) 
			previousNode = current;
		current = nextNode;
	}
}

// Wrap the value in a new Node object and insert it after the specified Node 
void LinkedList::InsertAfter(Node* pBefore, int value)
{
	Node* newNode{ new Node(value, pBefore->pNext) };
	pBefore->pNext = newNode;
	++m_Size;
}

// Return pointer to first Node
Node* LinkedList::Begin() const
{
	return m_pFirstNode;
}

// Return number of Node objects in the list
size_t LinkedList::Size() const
{
	return m_Size;
}

// Send the values of the list to the out object, use a space as element separator
std::ostream& operator<<(std::ostream& out, const LinkedList& list)
{
	Node* current{ list.Begin() };
	if (current)
	{
		while (current->pNext)
		{
			std::cout << current->value << " ";
			current = current->pNext;
		}
	}
	return out;
}
