#pragma once
class GameObject
{
public:
	explicit GameObject();
	explicit GameObject(Transform transform);
	virtual ~GameObject();

	virtual void Update(float elapsedSec) = 0;
	virtual void Draw() const = 0;

	Transform GetTransform() const;

protected:
	Transform m_Transform;
};