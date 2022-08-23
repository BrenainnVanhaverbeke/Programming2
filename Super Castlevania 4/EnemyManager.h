#pragma once
#include <vector>
#include "GameObject.h"

class Character;
class Player;
class EnemySpawner;
class ProjectileManager;

class EnemyManager final : public GameObject
{
public:
	explicit EnemyManager(ProjectileManager* projectileManager);
	virtual ~EnemyManager();

	void Update(float elapsedSec, Character* player);
	void HandleAttack(Player* player);
	std::vector<Character*>& GetEnemies();

	// Inherited via GameObject
	virtual void Draw(int zIndex) const override;
	virtual void DrawDebug(int zIndex) const override;

private:
	ProjectileManager* m_pProjectileManager;

	std::vector<Character*> m_pEnemies;
	std::vector<EnemySpawner*> m_pSpawners;
	int m_EnemyCounter;

	void UpdateEnemies(float elapsedSec, Character* player);
	void UpdateSpawners(float elapsedSec, Character* player);

	bool ShouldEnemyDespawn(Character* enemy, Character* player);

	void DeleteEnemies();
	void DeleteSpawners();
	void CheckDeletion();
	
	// Inherited via GameObject
	// Unused implementation
	virtual void Update(float elapsedSec) override;
};