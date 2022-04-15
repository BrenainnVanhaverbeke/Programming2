#include "pch.h"
#include "TextureManager.h"
#include "Texture.h"
#include <iostream>

TextureManager* TextureManager::m_Instance{ nullptr };
std::unordered_map<std::string, Texture*> TextureManager::m_pTextures;

TextureManager* TextureManager::GetInstance()
{
    if (!m_Instance)
        m_Instance = new TextureManager();
    return m_Instance;
}

void TextureManager::DrawSprite(const std::string& fileName, const Point2f& origin, const Rectf& sourceRect)
{
    const std::string imagesFolder{ "./Resources/Images/" };
    if (m_pTextures.find(fileName) == m_pTextures.end())
    {
        std::cout << "Creating new texture. Filename: " << fileName << std::endl;
        m_pTextures.insert(std::make_pair(fileName, new Texture(imagesFolder + fileName)));
    }
    m_pTextures.at(fileName)->Draw(origin, sourceRect);
}

void TextureManager::Delete()
{
    std::cout << "TextureManager Delete() called.\n";
    delete m_Instance;
    m_Instance = nullptr;
}

TextureManager::TextureManager()
{
    std::cout << "Texture manager initialising.\n";
}

TextureManager::~TextureManager()
{
    std::cout << "Texture manager deconstructing.\n";
    std::unordered_map<std::string, Texture*>::iterator iterator{ m_pTextures.begin() };
    while (iterator != m_pTextures.end())
    {
        iterator = m_pTextures.erase(iterator);
    }
    m_pTextures.clear();
}
