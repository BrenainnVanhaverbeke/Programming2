#include "pch.h"
#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(int zIndex)
	: GameObject(Transform{ 0.0f, 0.0f, 0.0f, 1.0f }, zIndex)
{
}

GameObject::GameObject(const Point2f& origin, int zIndex)
	: GameObject(Transform{ origin, 0.0f, 1.0f }, zIndex)
{
}

GameObject::GameObject(const Transform& transform, int zIndex)
	: m_Transform{ transform }
	, m_IsOverlapped{ false }
	, m_ZIndex{ zIndex }
{
}

int GameObject::GetZIndex() const
{
	return m_ZIndex;
}

Transform& GameObject::GetTransform()
{
	return m_Transform;
}
