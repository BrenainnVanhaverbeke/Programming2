#pragma once
#include "Character.h"
class Enemy :
    public Character
{
public:
    explicit Enemy(Transform transform, Sprite* sprite, float width, float height, const Vector2f& acceleration, const float activationDistance);
	Enemy& operator=(const Enemy& rhs) = delete;
	Enemy& operator=(Enemy&& rhs) = delete;
	Enemy(const Enemy& other) = delete;
	Enemy(Enemy&& other) = delete;
	virtual ~Enemy() = default;

private:
	const float m_ActivationDistance;
	
	bool m_IsActive;
};

