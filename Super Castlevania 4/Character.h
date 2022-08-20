#pragma once
#include "GameObject.h"
#include "Vector2f.h"
#include "IOverlappingObject.h"

class Sprite;
class MovementBehaviour;

class Character : public GameObject, public IOverlappingObject
{
public:
	explicit Character(Transform transform, Sprite* sprite, MovementBehaviour* movement, float width, float height, int zIndex, int health);
	Character& operator=(const Character& rhs) = delete;
	Character& operator=(Character&& rhs) = delete;
	Character(const Character& other) = delete;
	Character(Character&& other) = delete;
	virtual ~Character();

	virtual Rectf GetShape() const;
	virtual Vector2f& GetVelocity() const;
	virtual void TakeDamage(int damage);

	int GetHealth() const;

protected:
	Sprite* m_pSprite;
	MovementBehaviour* m_pMovementBehaviour;

	float m_Width;
	float m_Height;
	int m_Health;

	virtual Sprite* GetSprite() = 0;
};