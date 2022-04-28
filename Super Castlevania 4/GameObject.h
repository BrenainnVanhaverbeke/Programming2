#pragma once
class GameObject
{
public:
	GameObject();
	explicit GameObject(const Point2f& origin);
	explicit GameObject(const Transform& transform);
	GameObject& operator=(const GameObject& rhs) = delete;
	GameObject& operator=(GameObject&& rhs) = delete;
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	virtual ~GameObject() = default;

	virtual void Update(float elapsedSec) = 0;
	virtual void Draw() const = 0;
	virtual void CheckOverlap(const Rectf& overlappingShape) = 0;
	virtual bool IsOverlapping(const Rectf& overlappingShape) = 0;

	Transform& GetTransform();

protected:
	Transform m_Transform;
	bool m_IsOverlapped;
};