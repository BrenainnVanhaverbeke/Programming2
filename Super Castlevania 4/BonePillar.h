#pragma once
#include "Character.h"
class BonePillar : public Character
{
	enum class ActionState
	{
		idle,
		charginMahLazor,
		firing,
		dying
	};

public:
	explicit BonePillar(const Transform& transform, int zIndex, int id);
	explicit BonePillar(const Point2f& origin, int zIndex, int id);
	BonePillar(const BonePillar& other) = delete;
	BonePillar(BonePillar&& other) = delete;
	BonePillar& operator=(const BonePillar& rhs) = delete;
	BonePillar& operator=(BonePillar&& rhs) = delete;
	virtual ~BonePillar() = default;

	// Inherited via Character
	virtual void Update(float elapsedSec) override;
	virtual void Draw(int zIndex) const override;
	virtual void CheckOverlap(const Rectf& overlappingShape) override;
	virtual void TakeDamage(int damage) override;
	virtual bool ShouldFire() override;
	virtual Point2f GetProjectileSpawn() const override;

private:
	ActionState m_ActionState;
	float m_ElapsedTime;
	bool m_HasFiredBurst;
	int m_FiredRounds;

	void HandleIdle(float elapsedSec);
	void HandleCharginMahLazor(float elapsedSec);
	void HandleFiring(float elapsedSec);
	void HandleDying(float elapsedSec);

	// Inherited via Character
	virtual Sprite* GetSprite() const override;
};