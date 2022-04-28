#pragma once
#include "GameObject.h"
#include "Vector2f.h"

class Character : public GameObject
{
public:
	explicit Character(Transform transform, float width, float height, const Vector2f& acceleration);
	Character& operator=(const Character& rhs) = delete;
	Character& operator=(Character&& rhs) = delete;
	Character(const Character& other) = delete;
	Character(Character&& other) = delete;
	virtual ~Character() = default;

	virtual Rectf GetShape() const;
	virtual Vector2f& GetVelocity();

protected:
	const Vector2f m_Acceleration;

	float m_Width;
	float m_Height;
	Vector2f m_Velocity;

};