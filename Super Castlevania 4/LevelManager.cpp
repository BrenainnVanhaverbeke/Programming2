#include "pch.h"
#include "LevelManager.h"
#include "SVGParser.h"
#include "Texture.h"
#include "Stairs.h"
#include "Terrain.h"
#include <iostream>

LevelManager::LevelManager()
	: m_StageCounter{ 1 }
	, m_SegmentCounter{ 1 }
	, m_pTerrain{ nullptr }
	, m_pBackgroundTexture{ nullptr }
	, m_CollisionMode{ CollisionMode::terrain }
{
	LoadBackground();
	LoadSegment();
}

LevelManager::~LevelManager()
{
	delete m_pBackgroundTexture;
	delete m_pTerrain;
	m_pBackgroundTexture = nullptr;
	m_pTerrain = nullptr;
	DeleteStairs();
}

Terrain* LevelManager::GetTerrain() const
{
	return m_pTerrain;
}

Rectf LevelManager::GetBoundaries() const
{
	return m_Boundaries;
}

Point2f LevelManager::GetSpawn() const
{
	return m_SpawnPoint;
}

void LevelManager::Draw() const
{
	m_pBackgroundTexture->Draw();
	m_pTerrain->Draw();
	size_t nrOfStairs{ m_pStairs.size() };
	for (size_t i = 0; i < nrOfStairs; i++)
		m_pStairs[i]->Draw();
}

void LevelManager::HandleCollisions(const Rectf& actorShape, Transformation& actorTransform, Vector2f& actorVelocity)
{
	size_t nrOfStairs{ m_pStairs.size() };
	switch (m_CollisionMode)
	{
	case CollisionMode::terrain:
		m_pTerrain->HandleCollisions(actorShape, actorTransform, actorVelocity);
		break;
	case CollisionMode::stairs:
		m_pActiveStairs->HandleCollisions(actorShape, actorTransform, actorVelocity);
		if (m_pActiveStairs->IsEndReached(actorShape))
			m_CollisionMode = CollisionMode::terrain;
		break;
	case CollisionMode::background:
		break;
	default:
		break;
	}
}

bool LevelManager::IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const
{
	return m_pTerrain->IsOnGround(actorShape, actorVelocity);
}

void LevelManager::AttemptInteraction(const Rectf& shape)
{
	size_t nrOfStairs{ m_pStairs.size() };
	for (size_t i = 0; i < nrOfStairs; i++)
	{
		if (m_pStairs[i]->IsOverlapping(shape))
		{
			m_pActiveStairs = m_pStairs[i];
			m_CollisionMode = CollisionMode::stairs;
			return;
		}
	}
}

void LevelManager::DeleteStairs()
{
	size_t nrOfStairs{ m_pStairs.size() };
	for (size_t i = 0; i < nrOfStairs; i++)
		delete m_pStairs[i];
	m_pStairs.clear();
}

void LevelManager::NextStage()
{
	m_StageCounter++;
}

void LevelManager::NextSegment()
{
	m_SegmentCounter++;
}

void LevelManager::LoadBackground()
{
	if (m_pBackgroundTexture) delete m_pBackgroundTexture;
	std::string path{ "./Resources/Images/Stage " + std::to_string(m_StageCounter) + ".png" };
	m_pBackgroundTexture = new Texture(path);
}

void LevelManager::LoadSegment()
{
	std::string path{ "./Resources/SVGs/Segment " + std::to_string(m_StageCounter) + std::to_string(m_SegmentCounter) };
	LoadTerrain(path);
	LoadBoundaries(path);
	LoadSpawnPoint(path);
	LoadStairs(path);
}

void LevelManager::LoadTerrain(std::string path)
{
	path += " - Terrain.svg";
	if (m_pTerrain) delete m_pTerrain;
	m_pTerrain = new Terrain(path);
}

void LevelManager::LoadBoundaries(std::string path)
{
	path += " - Boundaries.svg";
	std::vector<std::vector<Point2f>> boundaries{};
	SVGParser::GetVerticesFromSvgFile(path, boundaries);

	float lowestX{ 9000.1f };
	float highestX{ -9000.1f };
	float lowestY{ 9000.1f };
	float highestY{ -9000.1f };
	size_t nrOfSets{ boundaries.size() };
	size_t nrOfVertices{};
	for (size_t i = 0; i < nrOfSets; i++)
	{
		std::vector<Point2f>& vertices{ boundaries[i] };
		nrOfVertices = vertices.size();
		for (size_t j = 0; j < nrOfVertices; j++)
		{
			Point2f& vertex{ vertices[j] };
			if (vertex.x < lowestX) lowestX = vertex.x;
			if (highestX < vertex.x) highestX = vertex.x;
			if (vertex.y < lowestY) lowestY = vertex.y;
			if (highestY < vertex.y) highestY = vertex.y;
		}
	}
	m_Boundaries = Rectf{ lowestX, lowestY, highestX - lowestX, highestY - lowestY };
}

void LevelManager::LoadSpawnPoint(std::string path)
{
	path += " - Spawn.svg";
	std::vector<std::vector<Point2f>> spawn{};
	SVGParser::GetVerticesFromSvgFile(path, spawn);
	m_SpawnPoint = spawn[0][0];
}

void LevelManager::LoadStairs(std::string path)
{
	path += " - Stairs.svg";
	std::vector<std::vector<Point2f>> stairsRaw;
	SVGParser::GetVerticesFromSvgFile(path, stairsRaw);
	if (m_pStairs.size() != 0) DeleteStairs();
	size_t nrOfStairs{ stairsRaw.size() };
	for (size_t i = 0; i < nrOfStairs; i++)
		m_pStairs.push_back(new Stairs(stairsRaw[i]));
}