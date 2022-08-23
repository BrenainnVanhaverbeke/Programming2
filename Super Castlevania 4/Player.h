#pragma once
#include "Vector2f.h"
#include "Character.h"
#include "IOverlappingObject.h"

class Texture;
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
		hurt,
		subweapon,
		death,
		attacking
	};

	enum class AttackDirection
	{
		right,
		upRight,
		up,
		downRight,
		down
	};

public:
	explicit Player(LevelManager* pLevelManager);
	Player(const Player& other) = delete;
	Player(Player&& other) = delete;
	Player& operator=(const Player& rhs) = delete;
	Player& operator=(Player&& rhs) = delete;
	virtual ~Player();

	// Inherited via Character
	void Draw(int zIndex) const override;
	void DrawDebug(int zIndex) const override;
	virtual void Update(float elapsedSec) override;
	virtual void TakeDamage(int damage) override;

	// Inherited via IOverlappingObject
	virtual void CheckOverlap(const Rectf& overlappingShape) override;

	Rectf GetShape() const override;
	std::vector<Point2f> GetWeaponShape() const;
	int GetWeaponDamage() const;
	bool IsAttacking() const;

	void Relocate(Point2f newLocation);
	void AttemptInteraction();
	void Jump();
	void Attack();
	ProjectileTag Shoot();
	void CycleProjectileType();

private:
	ActionState m_ActionState;
	AttackDirection m_AttackDirection;

	Sprite* m_pAttackSprite;

	Rectf m_WeaponBaseShape;
	Transform m_AttackTransform;
	int m_WeaponDamage;

	bool m_IsDrawDebug;
	bool m_IsDucked;
	bool m_IsStill;
	bool m_IsAttacking;
	bool m_CanThrow;
	float m_AttackTime;
	float m_AccumulatedTime;
	float m_HurtTime;

	void UpdateState(const Uint8* pKeysState);
	void UpdateAttack(float elapsedSec);
	void UpdateAttackSprite(float elapsedSec);
	void CheckDeath();
	void HandleHurting(float elapsedSec);
	void UpdateAttackDirection();
	void UpdateGeneralAttackDirection(const Uint8* pKeysState);
	void UpdateJumpingAttackDirection(const Uint8* pKeysState);
	std::vector<Point2f> RotateWeaponShape(std::vector<Point2f>& weaponShape, float rotationAngle) const;

	std::string GetActionStateString() const;
	std::string GetAttackDirectionString() const;
	Sprite* GetAttackSprite() const;

	// Inherited via Character
	virtual Sprite* GetSprite() const override;
};