#pragma once
#include "GameObject.h"
#include "Vector2f.h"

class Sprite;
class MovementBehaviour;

class Character : public GameObject
{
public:
	explicit Character(Transform transform, Sprite* sprite, float width, float height, const Vector2f& acceleration);
	Character& operator=(const Character& rhs) = delete;
	Character& operator=(Character&& rhs) = delete;
	Character(const Character& other) = delete;
	Character(Character&& other) = delete;
	virtual ~Character();

	virtual Rectf GetShape() const;
	virtual Vector2f& GetVelocity() const;

protected:
	Sprite* m_pSprite;
	MovementBehaviour* m_pMovementBehaviour;

	float m_Width;
	float m_Height;
};