#pragma once
#include "Vector2f.h"
#include "Character.h"

class Texture;
class LevelManager;
class Sprite;
class Projectile;

class Player final : public Character
{
	enum class ActionState
	{
		idle,
		walking,
		ducking,
		crouching,
		upstairs,
		downstairs,
		jumping,
		subweapon,
		hurt,
		death,
	};

public:
	explicit Player(LevelManager* pLevelManager);
	~Player();

	virtual void Update(float elapsedSec) override;
	virtual void CheckOverlap(const Rectf& overlappingShape) override;
	virtual bool IsOverlapping(const Rectf& overlappingShape) override;

	void Draw() const override;
	Rectf GetShape() const override;
	void Relocate(Point2f newLocation);
	void AttemptInteraction();
	void Jump();
	void Attack();
	void ToggleDrawDebug();

private:
	const float m_HorizontalSpeed;
	const float m_JumpForce;
	
	LevelManager* m_pLevelManager;
	Sprite* m_pSprite;
	Projectile* m_pProjectile;
	ActionState m_ActionState;
	Rectf m_Weapon;
	bool m_IsDrawDebug;
	bool m_IsDucked;
	bool m_IsStill;
	bool m_IsFlipped;
	bool m_IsAttacking;
	float m_AttackTime;

	void UpdateState(const Uint8* pKeysState);
	void UpdateVelocity(float elapsedSec, const Uint8* pKeysState);
	void UpdateHorizontalVelocity(float elapsedSec, const Uint8* pKeysState);
	void UpdateVerticalVelocity(float elapsedsec, const Uint8* pKeysState);
	void UpdateAttack(float elapsedSec);
	void MovePlayer(float elapsedSec);
	void Clamp();
	void CheckDeath();

	void DrawDebug() const;
	std::string GetActionStateString() const;
};