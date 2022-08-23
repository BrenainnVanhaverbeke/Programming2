#include "pch.h"
#include "UI.h"
#include "Player.h"
#include "Sprite.h"
#include "utils.h"
#include "ProjectileTag.h"

UI::UI(const Player* player, const Window& window)
	: m_pPlayer{ player }
	, m_WindowSize{ 0, 0, window.width, window.height }
	, m_pProjectileSprite{ new Sprite("Items.png") }
	, m_pUISprite{ new Sprite("UI.png") }
	, m_UIHeight{ 70.0f }
{
}

UI::~UI()
{
	delete m_pUISprite;
	delete m_pProjectileSprite;
	m_pUISprite = nullptr;
	m_pProjectileSprite = nullptr;
}

void UI::Update()
{
}

void UI::Draw() const
{
	// TODO: Figure out applying correct scaling
	//DrawUIBackground();
	glPushMatrix();
	{
		glScalef(G_SCALEFACTOR, G_SCALEFACTOR, 1.0f);
		DrawHealthBar();
		DrawActiveProjectile();
	}
	glPopMatrix();
}

void UI::DrawHealthBar() const
{
	m_pUISprite->SetSourceRect(GetUISourceRect(UIElements::healthBarTitle));
	m_pUISprite->Draw(Transform{ GetLocation(UIElements::healthBarTitle) });
	m_pUISprite->SetSourceRect(GetUISourceRect(UIElements::healthBarBackground));
	m_pUISprite->Draw(Transform{ GetLocation(UIElements::healthBarBackground) });
	m_pUISprite->SetSourceRect(GetUISourceRect(UIElements::healthBarForeground));
	m_pUISprite->Draw(Transform{ GetLocation(UIElements::healthBarForeground) });
}

void UI::DrawActiveProjectile() const
{
	m_pUISprite->SetSourceRect(GetUISourceRect(UIElements::projectileBackground));
	m_pUISprite->Draw(Transform{ GetLocation(UIElements::projectileBackground) });
	m_pProjectileSprite->SetSourceRect(GetProjectileSourceRect(m_pPlayer->GetProjectileTag()));
	m_pProjectileSprite->Draw(Transform{ GetLocation(UIElements::activeProjectile) });
}

void UI::DrawUIBackground() const
{
	const Color4f backgroundColour{ 0, 0, 0, 1.0f };
	Rectf background{ 0, m_WindowSize.height - m_UIHeight, m_WindowSize.width, m_WindowSize.height };
	utils::SetColor(backgroundColour);
	utils::FillRect(background);
}

// Welcome to magic number hell.

#pragma region Magic Number Hell

Point2f UI::GetLocation(UIElements type) const
{
	const float baseOffset{ 20.0f };
	const Rectf projectileSource{ 0, 0, 15.0f, 15.0f };
	switch (type)
	{
	case UIElements::healthBarTitle:
		return Point2f{ 16.0f, (m_WindowSize.height - GetUISourceRect(type).height - baseOffset) / G_SCALEFACTOR };
	case UIElements::healthBarBackground:
		return Point2f{ 68.0f, (m_WindowSize.height - GetUISourceRect(type).height - baseOffset) / G_SCALEFACTOR };
	case UIElements::healthBarForeground:
		return Point2f{ 68.0f, (m_WindowSize.height - GetUISourceRect(type).height - baseOffset) / G_SCALEFACTOR };
	case UIElements::projectileBackground:
		return Point2f{ 144.0f, (m_WindowSize.height - GetUISourceRect(type).height - baseOffset * 2) / G_SCALEFACTOR };
	case UIElements::activeProjectile:
	{
		Point2f location{};

		location.x = GetLocation(UIElements::projectileBackground).x + (projectileSource.width / 2);
		location.y = GetLocation(UIElements::projectileBackground).y + (projectileSource.height / 2);
		return location;
	}
	}
	return Point2f{};
}

Rectf UI::GetUISourceRect(UIElements type) const
{
	switch (type)
	{
	case UIElements::healthBarTitle:
		return Rectf{ 266.0f, 25.0f, 48.0f, 8.0f };
	case UIElements::healthBarBackground:
		return Rectf{ 314.0f, 41.0f, 64.0f, 8.0f };
	case UIElements::healthBarForeground:
		return Rectf{ 314.0f, 25.0f, 64.0f * (m_pPlayer->GetHealth() / 100.0f), 8.0f };
	case UIElements::projectileBackground:
		return Rectf{ 382.0f, 32.0f, 32.0f, 30.0f };
	}
	return Rectf{};
}

Rectf UI::GetProjectileSourceRect(ProjectileTag tag) const
{
	switch (tag)
	{
	case ProjectileTag::cross:
		return Rectf{ 127.0f, 17.0f, 15.0f, 15.0f };
	case ProjectileTag::dagger:
		return Rectf{ 49.0f, 33.0f, 15.0f, 15.0f };
	case ProjectileTag::axe:
		return Rectf{ 112.0f, 33.0f, 15.0f, 15.0f };
	}
	return Rectf{};
}

#pragma endregion Magic Number Hell