#pragma once
#include <vector>
#include "Vector2f.h"
#include "GameObject.h"

class TerrainObject : public GameObject
{
public:
	explicit TerrainObject(const std::vector<Point2f>& vertices, bool isBackground);
	virtual ~TerrainObject();

	virtual void Draw() const override;

	virtual void HandleCollisions(const Rectf& actorShape, Transform& actorTransform, Vector2f& actorVelocity) const = 0;
	virtual bool IsOnGround(const Rectf& actorShape, const Vector2f& actorVelocity) const;

	bool IsBackground() const;

protected:
	std::vector<Point2f> m_Vertices;
	bool m_IsBackground;
};