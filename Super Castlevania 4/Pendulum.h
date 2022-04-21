#pragma once
#include "GameObject.h"
#include "Vector2f.h"

class Pendulum : public GameObject
{
public:
	explicit Pendulum(float positionX, float positionY);

	// Inherited via GameObject
	virtual void Update(float elapsedSec) override;
	virtual void Draw() const override;
	virtual void CheckOverlap(const Rectf& overlappingShape) override;
	virtual bool IsOverlapping(const Rectf& overlappingShape) override;

private:
	float m_Length;
	float m_AngleVelocity;
	float m_AngleAcceleration;
	float m_Radius;
	float m_Damping;
	float m_Gravity;
	Point2f m_Position;
	
	void UpdateInput(float elapsedSec);
};