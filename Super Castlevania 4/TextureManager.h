#pragma once
#include <unordered_map>

class Texture;

class TextureManager
{
public:
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;

	static TextureManager& GetInstance();
	void DeleteTextureManager();
	void DrawSprite(const std::string& fileName, const Transform& origin, const Rectf& sourceRect = Rectf{}, bool isFlipped = false);
	void GetTextureDimensions(const std::string& fileName, float& width, float& height) const;

private:
	TextureManager();
	~TextureManager();
	static TextureManager* m_Instance;
	std::unordered_map<std::string, Texture*> m_pTextures;

	void LoadTexture(const std::string& fileName);
};