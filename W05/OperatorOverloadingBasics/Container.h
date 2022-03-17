#pragma once

class Container final
{
public:
	Container( int capacity = 10); 
	~Container( );
	Container( const Container& other ) = delete;
	Container& operator=( const Container& other ) = delete;
	Container( Container&& other )noexcept = delete;           
	Container& operator=( Container&& other )noexcept = delete;
	int& operator[](int index);
	int& operator[](int index) const;

	int Size( ) const;
	int Capacity( ) const;
	int Get( int index ) const;
	void Set( int index, int value );
	void PushBack( int element );

private:
	int m_Size;
	int m_Capacity;
	int *m_pElement;

	void Reserve( int newCapacity );
};
