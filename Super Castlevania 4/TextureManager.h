#pragma once
#include <unordered_map>

class Texture;

class TextureManager
{
public:
	static TextureManager* GetInstance();
	static void DrawSprite(const std::string& fileName, const Point2f& origin, const Rectf& sourceRect = Rectf{});
	static void Delete();

private:
	TextureManager();
	~TextureManager();
	TextureManager(const TextureManager&) = delete;
	TextureManager& operator=(const TextureManager&) = delete;

	static TextureManager* m_Instance;
	static std::unordered_map<std::string, Texture*> m_pTextures;
};