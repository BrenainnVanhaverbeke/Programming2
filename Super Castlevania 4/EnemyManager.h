#pragma once
#include <vector>
#include "GameObject.h"

class Character;

class EnemyManager final : public GameObject
{
public:
	EnemyManager() = default;
	~EnemyManager();

	// Inherited via GameObject
	virtual void Update(float elapsedSec) override;
	virtual void Draw(int zIndex) const override;

private:
	std::vector<Character*> m_pEnemies;

};