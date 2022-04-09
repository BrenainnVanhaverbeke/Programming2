#pragma once
#include "GameObject.h"
#include "Vector2f.h"

class Character : public GameObject
{
public:
	explicit Character();
	explicit Character(float width, float height);
	explicit Character(Transform transform, float width, float height);
	virtual ~Character();

	virtual Rectf GetShape() const;

protected:
	float m_Width;
	float m_Height;

};