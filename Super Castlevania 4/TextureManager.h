#pragma once
#include <unordered_map>

class Texture;

class TextureManager final
{
public:
	static TextureManager& GetInstance();
	void DeleteTextureManager();
	void DrawTexture(const std::string& fileName, const Rectf& sourceRect = Rectf{});
	void DrawTexture(const std::string& fileName, const Point2f& point, const Rectf& sourceRect = Rectf{});
	void GetTextureDimensions(const std::string& fileName, float& width, float& height) const;

private:
	TextureManager();
	~TextureManager();
	TextureManager(const TextureManager&) = delete;
	TextureManager(TextureManager&&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;
	TextureManager& operator=(TextureManager&&) = delete;
	static TextureManager* m_pInstance;
	std::unordered_map<std::string, Texture*> m_pTextures;

	void LoadTexture(const std::string& fileName);
};