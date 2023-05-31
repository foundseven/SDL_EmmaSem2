#pragma once
#include "GameObject.h"

#include <map>
#include <vector>

class Tile;

class TiledLevel : public GameObject
{
public:
	TiledLevel(int rows, int cols, int tileWidth, int  tileHeight,
		const char* tileData, const char* levelData, const char* tileKey);
	~TiledLevel();
	virtual void Update(float deltaTime) override;
	virtual void Render() override;

	std::vector<Tile*>& GetObsticales() { return m_obstacles; }

private:
	const char* m_tilekey;
	int m_rows;
	int m_cols;

	std::map<char, Tile*> m_tiles;
	std::vector<std::vector<Tile*>> m_levelTiles; //2D vector 
	std::vector<Tile*> m_obstacles;


};

