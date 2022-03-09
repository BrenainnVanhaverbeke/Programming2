#pragma once
#include "GameObject.h"
#include <string>


class Enemy : public GameObject
{
public:
	Enemy( );
	~Enemy( );

	virtual std::string ToString( ) const override;

private:
	static int m_InstanceCounter;
};


 
