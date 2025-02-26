#pragma once

#include <string>
#include <unordered_map>

#include "../Externals/TinyXML/tinyxml.h"

#include "../Map/Map.h"
#include "../Layers/TileLayer.h"

class FileHandler
{
public:
	/// @brief Loads a map from a file and stores it in the map library
	/// @param name : The name of the map to be stored in the map library
	/// @param filepath : The path to the file containing the map data (.tmx format)
	static bool LoadMap(const std::string& name, const std::string& filepath);

	/// @brief Initialises the specified map if it is in the map library
	/// @param name : The name of the map to be initialised and retrieved from the map library
	/// @return The initialised map 
	static std::weak_ptr<Map> InitialiseMap(const std::string& name);

private:
	static bool ParseMap(const std::string& name, const std::string& filepath);
	static Tileset ParseTileset(TiXmlElement* tilesetElement);
	static std::unique_ptr<TileLayer> ParseTileLayer(TiXmlElement* layerElement, const std::vector<Tileset>& tilesets, int tileSize, int numRows, int numColumns);

	static inline bool IsMapLoaded(const std::string& name) { return mapLib.find(name) != mapLib.end(); }

private:
	static std::unordered_map<std::string, std::shared_ptr<Map>> mapLib;

private:
	FileHandler() = delete;
	~FileHandler() = delete;
	FileHandler(const FileHandler&) = delete;
	FileHandler& operator=(const FileHandler&) = delete;
};

