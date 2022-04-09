#include "pch.h"
#include "GameObject.h"

GameObject::GameObject()
	: GameObject(Transform{ 0.0f, 0.0f, 0.0f, 1.0f })
{
}

GameObject::GameObject(Transform transform)
	: m_Transform{ transform }
{
}

GameObject::~GameObject()
{
}

Transform GameObject::GetTransform() const
{
	return m_Transform;
}
