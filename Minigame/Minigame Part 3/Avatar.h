#pragma once
#include "Vector2f.h"

class Level;
class Texture;

class Avatar
{
	enum class ActionState
	{
		waiting,
		moving,
		transforming,
	};

public:
	Avatar();
	~Avatar();
	void Update(float elapsedSec, const Level* level);
	void Draw() const;
	void PowerUpHit();
	Rectf GetShape() const;

private:
	const float m_HorizontalSpeed;
	const float m_JumpSpeed;
	const float m_MaxTransformSec;
	const float m_ClipHeight;
	const float m_ClipWidth;
	const int m_NrOfFrames;
	const int m_NrFramesPerSec;

	const Vector2f m_Acceleration;
	const Texture* m_pSpritesTexture;

	float m_AccuTransformSec;
	float m_AnimTime;
	int m_Power;
	int m_AnimFrame;

	Rectf m_Shape;
	Vector2f m_Velocity;
	ActionState m_ActionState;

	void UpdateMotion(float elapsedSec, const Level* level);
	void UpdateAnimation(float elapsedSec);
	void UpdateHorizontalVelocity(float elapsedSec, const Uint8* pKeysState);
	void UpdateVerticalVelocity(float elapsedsec, const Level* level, const Uint8* pKeysState);
	void MoveAvatar(float elapsedSec, const Level* level);
	void Clamp(const Level* level);
	void HandleTransformation(float elapsedSec);
	void DrawPowerUpIndicators() const;
	Rectf GetSourceRect() const;
	Color4f GetColour() const;
};