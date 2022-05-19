#pragma once
#include "MovementBehaviour.h"

class LevelManager;
enum class ActionState;

class PlayerBehaviour : public MovementBehaviour
{
public:
	PlayerBehaviour(LevelManager* pLevelManager);
	
	// Inherited via MovementBehaviour
	virtual void Update(float elapsedSec, Character& character) override;
	
	void Jump(Character& character);
	void Attack();
	bool IsStill() const;
	bool IsFlipped() const;
	bool IsAttacking() const;
	ActionState GetActionState();
	int GetActionStateInt();

	virtual void Move(float elapsedSec, Character& character) override;

private:
	const float m_HorizontalSpeed;
	const float m_JumpForce;

	ActionState m_ActionState;
	LevelManager* m_pLevelManager;
	Rectf m_Weapon;
	bool m_IsStill;
	bool m_IsFlipped;
	bool m_IsAttacking;
	float m_AttackTime;

	// Inherited via MovementBehaviour
	virtual void UpdateVelocity(float elapsedSec, const Uint8* pKeysState) override;

	void UpdateState(const Uint8* pKeysState);
	void UpdateAttack(float elapsedSec, Character& character);
	void UpdateHorizontalVelocity(float elapsedSec, const Uint8* pKeysState);
	void UpdateVerticalVelocity(float elapsedsec, const Uint8* pKeysState);
	void Clamp(Transform& transform, Character& character);
};