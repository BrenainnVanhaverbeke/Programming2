#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"
#include <iostream>

TextureManager* TextureManager::m_Instance{ nullptr };

TextureManager::TextureManager()
{
	std::cout << "Texture manager instance created.\n";
}

TextureManager::~TextureManager()
{
	std::cout << "Texture manager deconstructing.\n";
	std::unordered_map<std::string, Texture*>::iterator iterator{ m_pTextures.begin() };
	Texture* texture;
	while (iterator != m_pTextures.end())
	{
		texture = iterator->second;
		delete texture;
		iterator++;
	}
	m_pTextures.clear();
}

TextureManager& TextureManager::GetInstance()
{
	if (!m_Instance)
		m_Instance = new TextureManager();
	return *m_Instance;
}

void TextureManager::DeleteTextureManager()
{
	delete m_Instance;
	m_Instance = nullptr;
}

void TextureManager::GetTextureDimensions(const std::string& fileName, float& width, float& height) const
{
	if (m_pTextures.contains(fileName))
	{
		width = m_pTextures.at(fileName)->GetWidth();
		height = m_pTextures.at(fileName)->GetHeight();
	}
}

void TextureManager::DrawTexture(const std::string& fileName, const Rectf& sourceRect, bool isFlipped)
{
	DrawTexture(fileName, Point2f{}, sourceRect, isFlipped);
}

void TextureManager::DrawTexture(const std::string& fileName, const Point2f& point, const Rectf& sourceRect, bool isFlipped)
{
	if (m_pTextures.find(fileName) == m_pTextures.end())
		LoadTexture(fileName);
	m_pTextures.at(fileName)->Draw(point, sourceRect);
}

void TextureManager::LoadTexture(const std::string& fileName)
{
	const std::string imagesFolder{ "./Resources/Images/" };
	std::cout << "Creating new texture. Filename: " << fileName << std::endl;
	m_pTextures.insert(std::make_pair(fileName, new Texture(imagesFolder + fileName)));
}