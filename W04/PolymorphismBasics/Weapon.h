#pragma once
#include "GameObject.h"
#include <string>


class Weapon : public GameObject
{
public:
	Weapon( );
	~Weapon( ); 

	std::string ToString( ) const;

private:
	static int m_InstanceCounter;
};

 
