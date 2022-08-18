#pragma once

class Character;

class EnemySpawner
{
public:
	EnemySpawner(std::string enemyType, const Point2f& location);
	~EnemySpawner() = default;

	bool ShouldSpawn(Character* player);
	Character* Spawn();

private:
	const std::string m_EnemyType;
	const Point2f m_Location;

	bool m_HasActivated;
};