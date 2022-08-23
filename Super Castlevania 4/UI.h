#pragma once

class Player;
class Sprite;

enum class ProjectileTag;
enum class UIElements
{
	healthBarTitle,
	healthBarBackground,
	healthBarForeground,
	projectileBackground,
	activeProjectile
};

class UI final
{
public:
	explicit UI(const Player* player, const Window& window);
	UI(const UI& other) = delete;
	UI(UI&& other) = delete;
	UI& operator=(const UI& rhs) = delete;
	UI& operator=(UI&& rhs) = delete;
	~UI();
	
	void Update();
	void Draw() const;

private:
	const Player* m_pPlayer;
	const Rectf m_WindowSize;
	const float m_UIHeight;

	Sprite* m_pProjectileSprite;
	Sprite* m_pUISprite;
	Rectf m_HealthBar;

	void DrawUIBackground() const;
	void DrawHealthBar() const;
	void DrawActiveProjectile() const;

	Point2f GetLocation(UIElements type) const;
	Rectf GetUISourceRect(UIElements type) const;
	Rectf GetProjectileSourceRect(ProjectileTag tag) const;
};