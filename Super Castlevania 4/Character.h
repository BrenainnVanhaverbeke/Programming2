#pragma once
#include "GameObject.h"
#include "Vector2f.h"
#include "IOverlappingObject.h"
#include "CharacterTypes.h"
#include "ProjectileTag.h"

class Sprite;
class LevelManager;
class MovementBehaviour;

class Character : public GameObject, public IOverlappingObject
{
public:
	explicit Character(Transform transform, Sprite* sprite, MovementBehaviour* movement, CharacterTypes type, LevelManager* pLevelManager, float width, float height, int zIndex, int health, int id);
	explicit Character(Transform transform, Sprite* sprite, MovementBehaviour* movement, CharacterTypes type, ProjectileTag projectileTag, LevelManager* pLevelManager, float width, float height, int zIndex, int health, int id);
	Character& operator=(const Character& rhs) = delete;
	Character& operator=(Character&& rhs) = delete;
	Character(const Character& other) = delete;
	Character(Character&& other) = delete;
	virtual ~Character();

	virtual Rectf GetShape() const;
	virtual Vector2f& GetVelocity() const final;
	virtual void TakeDamage(int damage);
	virtual bool ShouldFire();
	virtual Point2f GetProjectileSpawn() const;
	virtual void SetIsFlipped(bool isFlipped);

	void AddImmuneId(int id);

	int GetHealth() const;
	int GetId() const;
	bool ShouldDie() const;
	bool IsFlipped() const;
	CharacterTypes GetCharacterType() const;
	ProjectileTag GetProjectileTag() const;
	std::vector<int> GetImmunityList() const;

	// Inherited via IOverlappingObject
	virtual bool IsOverlapping(const Rectf& overlappingShape) override;
	virtual bool IsOverlapping(const std::vector<Point2f>& overlappingShape) override;

	// Inherited via GameObject
	virtual void DrawDebug(int zIndex) const override;

protected:
	const int m_Id;

	Sprite* m_pSprite;
	MovementBehaviour* m_pMovementBehaviour;
	LevelManager* m_pLevelManager;

	ProjectileTag m_ProjectileTag;
	Point2f m_ProjectileSpawn;

	float m_Width;
	float m_Height;
	int m_Health;
	bool m_ShouldDie;
	bool m_ShouldFire;
	bool m_IsFlipped;

	CharacterTypes m_CharacterType;
	std::vector<int> m_ImmunityList;

	virtual Sprite* GetSprite() const = 0;



};