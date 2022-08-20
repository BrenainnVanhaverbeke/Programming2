#pragma once
#include <vector>
#include "GameObject.h"

class Character;
class EnemySpawner;

class EnemyManager final : public GameObject
{
public:
	EnemyManager();
	~EnemyManager();

	void Update(float elapsedSec, Character* player);

	// Inherited via GameObject
	virtual void Update(float elapsedSec) override;
	virtual void Draw(int zIndex) const override;

	void HandleAttack(const Rectf& weaponShape, int weaponDamage);

private:
	const float m_DespawnDistance;

	std::vector<Character*> m_pEnemies;
	std::vector<EnemySpawner*> m_pSpawners;

	void UpdateEnemies(float elapsedSec, Character* player);
	void UpdateSpawners(float elapsedSec, Character* player);

	bool ShouldEnemyDespawn(Character* enemy, Character* player);

	void DeleteEnemies();
	void DeleteSpawners();
};