#pragma once
class GameObject
{
public:
	explicit GameObject(int zIndex = 0);
	explicit GameObject(const Point2f& origin, int zIndex = 0);
	explicit GameObject(const Transform& transform, int zIndex = 0);
	GameObject& operator=(const GameObject& rhs) = delete;
	GameObject& operator=(GameObject&& rhs) = delete;
	GameObject(const GameObject& other) = delete;
	GameObject(GameObject&& other) = delete;
	virtual ~GameObject() = default;

	virtual void Update(float elapsedSec) = 0;
	virtual void Draw(int zIndex) const = 0;
	virtual int GetZIndex() const;

	Transform& GetTransform();

protected:
	Transform m_Transform;
	bool m_IsOverlapped;
	int m_ZIndex;
};