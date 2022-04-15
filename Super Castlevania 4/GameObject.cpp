#include "pch.h"
#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject()
	: GameObject(Transform{ 0.0f, 0.0f, 0.0f, 1.0f })
{
}

GameObject::GameObject(const Point2f& origin)
	: GameObject(Transform{ origin, 0.0f, 1.0f })
{
}

GameObject::GameObject(const Transform& transform)
	: m_Transform{ transform }
	, m_IsOverlapped{ false }
{
}

GameObject::~GameObject()
{
}

Transform GameObject::GetTransform() const
{
	return m_Transform;
}
