#pragma once
#include "Vector2f.h"
#include "Character.h"
#include "IOverlappingObject.h"

class Texture;
class LevelManager;
class Sprite;
class MovementBehaviour;
enum class ProjectileTag;

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
	Player(const Player& other) = delete;
	Player(Player&& other) = delete;
	Player& operator=(const Player& rhs) = delete;
	Player& operator=(Player&& rhs) = delete;
	~Player();

	// Inherited via Character
	void Draw(int zIndex) const override;
	virtual void Update(float elapsedSec) override;
	
	// Inherited via IOverlappingObject
	virtual void CheckOverlap(const Rectf& overlappingShape) override;
	virtual bool IsOverlapping(const Rectf& overlappingShape) override;

	Rectf GetShape() const override;
	Rectf GetWeaponShape() const;
	int GetWeaponDamage() const;

	void Relocate(Point2f newLocation);
	void AttemptInteraction();
	void Jump();
	void Attack();
	ProjectileTag Shoot();
	bool IsFlipped() const;
	bool IsAttacking() const;
	void ToggleDrawDebug();

private:
	LevelManager* m_pLevelManager;
	ProjectileTag m_ProjectileTag;
	ActionState m_ActionState;

	Sprite* m_pAttackSprite;

	Rectf m_Weapon;
	int m_WeaponDamage;

	bool m_IsDrawDebug;
	bool m_IsDucked;
	bool m_IsStill;
	bool m_IsFlipped;
	bool m_IsAttacking;
	float m_AttackTime;

	void UpdateState(const Uint8* pKeysState);
	void UpdateAttack(float elapsedSec);
	void CheckDeath();

	void DrawDebug() const;
	std::string GetActionStateString() const;

	// Inherited via Character
	virtual Sprite* GetSprite() override;
};