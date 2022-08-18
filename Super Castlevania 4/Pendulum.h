#pragma once
#include "GameObject.h"
#include "Vector2f.h"

class Pendulum : public GameObject
{
public:
	explicit Pendulum(float positionX, float positionY);

	// Inherited via GameObject
	virtual void Update(float elapsedSec) override;
	virtual void Draw(int zIndex) const override;

	void ReleasePendulum();
	void ResetPendulum();
	void ModifyReleaseCompensation(float compensationModifier);

private:
	float m_Length;
	float m_AngleVelocity;
	float m_AngleAcceleration;
	float m_Radius;
	float m_Damping;
	float m_Gravity;
	float m_ReleaseSpeedCompensation;
	bool m_IsReleased;
	Point2f m_Position;
	Vector2f m_ReleaseVector;
	
	void UpdateSwing(float elapsedSec);
	void UpdateRelease(float elapsedSec);
	void UpdateInput(float elapsedSec);
	float ToRadians(float degrees);
	float ToDegrees(float radians);
	Vector2f GetReleaseVector();
};