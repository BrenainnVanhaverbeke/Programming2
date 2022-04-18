#pragma once
#include <unordered_map>

class Texture;

class TextureManager
{
public:
	TextureManager(const TextureManager&) = delete;
	TextureManager(TextureManager&&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
	TextureManager& operator=(TextureManager&&) = delete;

	static TextureManager& GetInstance();
	void DeleteTextureManager();
	void DrawTexture(const std::string& fileName, const Rectf& sourceRect = Rectf{}, bool isFlipped = false);
	void DrawTexture(const std::string& fileName, const Point2f& point, const Rectf& sourceRect = Rectf{}, bool isFlipped = false);
	void GetTextureDimensions(const std::string& fileName, float& width, float& height) const;

private:
	TextureManager();
	~TextureManager();
	static TextureManager* m_Instance;
	std::unordered_map<std::string, Texture*> m_pTextures;

	void LoadTexture(const std::string& fileName);
};