#pragma once

#include <memory>
#include <vector>

#include "../Layers/Layer.h"
#include "../Layers/EnemyLayer.h"
#include "../Vector2/Vector2.h"

class Map
{
public:
	Map() = default;
	~Map() = default;

	void Draw();

	Layer* GetLayer(int index);
	std::vector<GameObject>* GetEnemies();
	inline const std::vector<std::unique_ptr<Layer>>& GetMapLayers() const { return mapLayers; }

	inline void AddLayer(std::unique_ptr<Layer> layer) { mapLayers.push_back(std::move(layer)); }
	inline void RemoveLayer() { mapLayers.pop_back(); }
	void AddEnemyLayer();

	void SetDimensions(int rows, int cols, int tileSize) {
		this->numRows = rows;
		this->numColumns = cols;
		this->tileSize = tileSize;
	}

	int GetRows() const { return numRows; }
	int GetColumns() const { return numColumns; }
	int GetTileSize() const { return tileSize; }

	Vector2 GetPosition() const { return position; }
	void SetPosition(const Vector2& newPosition) { position = newPosition; }
	void CreateMapCollider(const Vector2& position, const int width, const int height);

	bool isActive = false;
	std::weak_ptr<Collider> mapEnterTrigger;
	std::weak_ptr<GameObject> mapGO;
	
private:
	std::vector<std::unique_ptr<Layer>> mapLayers;
	std::unique_ptr <EnemyLayer> mapEnemies;

	Vector2 position;
	int numRows;
	int numColumns;
	int tileSize;
};

