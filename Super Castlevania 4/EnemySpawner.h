#pragma once
#include "GameObject.h"

class Character;

class EnemySpawner final : public GameObject
{
public:
	EnemySpawner(std::string enemyType, const Point2f& location, int zIndex);
	~EnemySpawner() = default;

	void Update(float elapsedSec, Character* player);
	bool ShouldSpawn();
	Character* Spawn(Character* player);
	virtual void Draw(int zIndex) const override;

private:
	const std::string m_EnemyType;
	const Point2f m_Location;
	const float m_SpawnRange;
	const int m_ZIndex;

	bool m_HasActivated;
	bool m_ShouldSpawn;

	// Inherited via GameObject
	virtual void Update(float elapsedSec) override;
};