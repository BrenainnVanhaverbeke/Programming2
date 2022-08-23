#pragma once
#include <vector>
#include "GameObject.h"

class Character;
class EnemySpawner;

class EnemyManager final : public GameObject
{
public:
	EnemyManager();
	virtual ~EnemyManager();

	void Update(float elapsedSec, Character* player);
	void HandleAttack(const std::vector<Point2f>& weaponShape, int weaponDamage, int zIndex);
	std::vector<Character*>& GetEnemies();

	// Inherited via GameObject
	virtual void Draw(int zIndex) const override;
	virtual void DrawDebug(int zIndex) const override;

private:
	const float m_DespawnDistance;

	std::vector<Character*> m_pEnemies;
	std::vector<EnemySpawner*> m_pSpawners;
	int m_EnemyCounter;

	void UpdateEnemies(float elapsedSec, Character* player);
	void UpdateSpawners(float elapsedSec, Character* player);

	bool ShouldEnemyDespawn(Character* enemy, Character* player);

	void DeleteEnemies();
	void DeleteSpawners();
	
	// Inherited via GameObject
	// Unused implementation
	virtual void Update(float elapsedSec) override;
};