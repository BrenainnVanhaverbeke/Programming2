#pragma once
#include "Vector2f.h"
#include "GameObject.h"
#include "utils.h"
#include <vector>

class Character;

class TerrainObject : public GameObject
{
public:
	explicit TerrainObject(const std::vector<Point2f>& vertices, int zIndex);
	explicit TerrainObject(const std::vector<Point2f>& vertices, const Point2f& pivot, int zIndex);
	TerrainObject& operator=(const TerrainObject& rhs) = delete;
	TerrainObject& operator=(TerrainObject&& rhs) = delete;
	TerrainObject(const TerrainObject& other) = delete;
	TerrainObject(TerrainObject&& other) = delete;
	virtual ~TerrainObject();

	virtual void Update(float elapsedSec) override;
	virtual void Draw(int zIndex) const override;
	virtual void DrawDebug(int zIndex) const override;
	virtual void CheckOverlap(const Rectf& overlappingShape);
	virtual bool IsOverlapping(const Rectf& overlappingShape);

	virtual bool HandleCollisions(Character& character);
	virtual bool IsOnGround(const Character& character);

protected:
	const float m_AnchorOffset;
	const float m_RaycastOffset;
	std::vector<Point2f> m_Vertices;

	bool CheckVerticalCollisions(const std::vector<Point2f>& vertices, Character& character, utils::HitInfo hitInfo) const;
	bool CheckHorizontalCollisions(const std::vector<Point2f>& vertices, Character& character, utils::HitInfo hitInfo) const;

	std::vector<Point2f> GetRaycastAnchors(const Rectf& actorShape) const;
};