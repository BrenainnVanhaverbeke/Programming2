#pragma once
#include "GameObject.h"
#include <string>


class PickUp : public GameObject
{
public:
	PickUp( );
	~PickUp( );

	std::string ToString( ) const;

private:
	static int m_InstanceCounter;
};
