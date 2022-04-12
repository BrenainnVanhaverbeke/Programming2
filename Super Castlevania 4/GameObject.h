#pragma once
class GameObject
{
public:
	explicit GameObject();
	explicit GameObject(const Point2f& origin);
	explicit GameObject(const Transform& transform);
	virtual ~GameObject();

	virtual void Update(float elapsedSec) = 0;
	virtual void Draw() const = 0;
	virtual void CheckOverlap(const Rectf& overlappingShape) = 0;
	virtual bool IsOverlapping(const Rectf& overlappingShape) const = 0;

	Transform GetTransform() const;

protected:
	Transform m_Transform;
	bool m_IsOverlapped;
};