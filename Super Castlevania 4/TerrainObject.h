#pragma once
#include "Vector2f.h"
#include "GameObject.h"
#include "utils.h"
#include <vector>

class TerrainObject : public GameObject
{
public:
	explicit TerrainObject(const std::vector<Point2f>& vertices, bool isBackground);
	explicit TerrainObject(const std::vector<Point2f>& vertices, const Point2f& pivot, bool isBackground);
	virtual ~TerrainObject();

	virtual void Update(float elapsedSec) override;
	virtual void Draw() const override;
	virtual void CheckOverlap(const Rectf& overlappingShape);
	virtual bool IsOverlapping(const Rectf& overlappingShape);

	virtual bool HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity);
	virtual bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity);

	bool IsBackground() const;

protected:
	const float m_AnchorOffset;
	const float m_RaycastOffset;
	std::vector<Point2f> m_Vertices;
	bool m_IsBackground;

	bool CheckVerticalCollisions(const std::vector<Point2f>& vertices, const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity, utils::HitInfo hitInfo) const;
	bool CheckHorizontalCollisions(const std::vector<Point2f>& vertices, const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity, utils::HitInfo hitInfo) const;

	std::vector<Point2f> GetRaycastAnchors(const Rectf& actorShape) const;
};