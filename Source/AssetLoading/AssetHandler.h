#pragma once

#include <memory>

#include "Asset.h"
#include "../Camera/Camera.h"

class AssetHandler
{
public:
	static Asset LoadTexture(const std::string& filepath);
	static Asset LoadFont(const std::string& filepath, int ptSize = 16);
	static Asset LoadMusic(const std::string& filepath);
	static Asset LoadSFX(const std::string& filepath);

	static void Clean();

	/// @brief Used to draw static textures that do not change based on camera e.g. (UI)
	static void DrawStatic(const Asset& texture, const Vector2& position, float width, float height, float scale = 1.0f, SDL_RendererFlip flip = SDL_FLIP_NONE, double rotationAngle = 0.0);

	/// @brief Used to draw dynamic textures that change based on camera e.g. (Whole backgrounds)
	static void DrawDynamic(const Asset& texture, const Vector2& position, float width, float height, float scrollSpeed = 1.0f, float scale = 1.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);
	
	/// @brief Used to draw tiles that change based on camera e.g. (Tilemaps)
	static void DrawTile(const Asset& texture, const Vector2& position, int tileSize, int row, int frame);

	/// @brief Used to draw animated textures that change based on camera e.g. (Player, enemies)
	static void DrawAnimation(const Asset& texture, const Vector2& position, float width, float height, int row, int frame, float scrollSpeed = 1.0f, float scale = 1.0f, SDL_RendererFlip flip = SDL_FLIP_NONE);

	/// @param loops : 0 = play once, -1 = loop indefinitely
	static void PlayMusic(const Asset& music, int loops = 0);

	/// @param loops : 0 = play once, -1 = loop indefinitely
	static void PlaySFX(const Asset& sfx, int loops = 0);

	/// @brief Sets the volume of the channel that the music is played on
	static inline void SetMusicVolume(int volume) { Mix_VolumeMusic(volume); }
	static void SetSFXVolume(const Asset& sfx, int volume);

	static void SetFontSize(const Asset& font, int size);
	static TTF_Font* GetFont(const Asset& font);
	static SDL_Texture* GetFontTexture(const std::string& filepath, int ptSize, const std::string& text, SDL_Color color);

	static inline void SetRenderer(SDL_Renderer* _renderer) { renderer = _renderer; }
	static inline void SetCamera(std::shared_ptr<Camera> _camera) { camera = _camera; }

private:
	static inline bool IsTextureValid(const Asset& texture) { return textureLib.find(texture) != textureLib.end(); }
	static bool IsAudioValid(const Asset& audio, bool isMusic = false);
	static inline bool IsFontValid(const Asset& font) { return fontLib.find(font) != fontLib.end(); }

private:
	static std::unordered_map<Asset, SDL_Texture*> textureLib;
	static std::unordered_map<Asset, Mix_Music*> musicLib;
	static std::unordered_map<Asset, Mix_Chunk*> sfxLib;
	static std::unordered_map<Asset, TTF_Font*> fontLib;

	static SDL_Renderer* renderer;
	static std::weak_ptr<Camera> camera;

private:
	AssetHandler() = delete;
	~AssetHandler() = delete;
	AssetHandler(const AssetHandler&) = delete;
	AssetHandler& operator=(const AssetHandler&) = delete;
};

