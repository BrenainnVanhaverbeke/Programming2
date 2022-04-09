#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
	: GameObject(Transformation{ 0.0f, 0.0f, 0.0f, 1.0f })
{
}

GameObject::GameObject(Transformation transform)
	: m_Transform{ transform }
{
}

GameObject::~GameObject()
{
}
