#include "pch.h"
#include "Container.h"

Container::Container(int capacity)
	: m_Array{ new int[capacity] }, m_Size{ 0 }, m_Capacity{ capacity }, m_pElement{ &m_Array[0] }
{
}

Container::~Container()
{
	delete[] m_Array;
	m_Array = nullptr;
}

int Container::Size() const
{
	return m_Size;
}

int Container::Capacity() const
{
	return m_Capacity;
}

int Container::Get(int index) const
{
	return m_Array[index];
}

void Container::Set(int index, int newValue)
{
	m_Array[index] = newValue;
}

void Container::PushBack(int element)
{
	if (m_Size < m_Capacity)
	{
		m_Array[m_Size] = element;
		m_Size++;
	}
	else
	{
		Reserve((m_Capacity * 2) + 1);
		PushBack(element);
	}
}

void Container::Reserve(int newCapacity)
{
	if (m_Capacity < newCapacity)
	{
		int* newArray{ new int[newCapacity] };
		for (int i{ 0 }; i < m_Capacity; i++)
			newArray[i] = m_Array[i];
		delete[] m_Array;
		m_Array = newArray;
		m_Capacity = newCapacity;
		m_pElement = &m_Array[0];
	}
}

