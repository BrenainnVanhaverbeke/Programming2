#pragma once
#include "Vector2f.h"
#include "GameObject.h"
#include "ActionState.h"

class Texture;
class LevelManager;

class Player : public GameObject
{
public:
	explicit Player(LevelManager* pLevelManager);
	~Player();
	void Update(float elapsedSec) override;

	void Draw() const override;
	Rectf GetShape() const;

private:
	const float m_HorizontalSpeed;
	const float m_JumpForce;
	const float m_Width;
	const float m_Height;
	const Vector2f m_Acceleration;
	
	LevelManager* m_pLevelManager;
	Vector2f m_Velocity;
	ActionState m_ActionState;

	void UpdateVelocity(float elapsedSec);
	void UpdateAnimation(float elapsedSec);
	void UpdateHorizontalVelocity(float elapsedSec, const Uint8* pKeysState);
	void UpdateVerticalVelocity(float elapsedsec, const Uint8* pKeysState);
	void MoveAvatar(float elapsedSec);
	void Clamp();
};