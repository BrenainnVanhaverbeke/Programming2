#pragma once
#include "Vector2f.h"

class Level;

class Avatar
{
	enum class ActionState
	{
		waiting,
		moving,
		transforming,
		END
	};

public:
	Avatar();
	void Update(float elapsedSec, const Level* level);
	void Draw() const;
	void PowerUpHit();
	Rectf GetShape() const;

private:
	const float m_HorizontalSpeed;
	const float m_JumpSpeed;
	const float m_MaxTransformSec;

	const Vector2f m_Acceleration;

	float m_AccuTransformSec;
	int m_Power;

	Rectf m_Shape;
	Vector2f m_Velocity;
	ActionState m_ActionState;

	void UpdateHorizontalVelocity(float elapsedSec, const Uint8* pKeysState);
	void UpdateVerticalVelocity(float elapsedsec, const Level* level, const Uint8* pKeysState);
	void MoveAvatar(float elapsedSec);
	void HandleTransformation(float elapsedSec);
	void DrawPowerUpIndicators() const;
	Color4f GetColour() const;
};