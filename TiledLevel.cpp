#include "TiledLevel.h"
#include "Game.h"
#include "TextureManager.h"
#include "Tile.h"

#include <fstream>

TiledLevel::TiledLevel(int rows, int cols, int tileWidth, int tileHeight,
	const char* tileData, const char* leveldata, const char* tileKey)
	: m_tilekey(tileKey)
	, m_rows(rows)
	, m_cols(cols)
{
	std::ifstream inFile(tileData);
	if (inFile.is_open())
	{
		char key;
		int x;
		int y;
		bool isObstacle;
		bool isHazard;
		while (!inFile.eof())
		{
			inFile >> key >> x >> y >> isObstacle >> isHazard;
			m_tiles.emplace(key,
				new Tile(
					{ x * tileWidth, y * tileHeight, tileWidth, tileHeight },
					{ 0.0f, 0.0f, (float)tileWidth, (float)tileHeight },
					isObstacle, isHazard));
		}
	}
	inFile.close();

	inFile.open(leveldata);
	if (inFile.is_open())
	{
		char key;
		m_levelTiles.resize(m_rows); //this is important or we could not use the subscripts
		for (int row = 0; row < m_rows; ++row)
		{
			m_levelTiles[row].resize(m_cols); //this is important or we could not use the subscripts
			for (int col = 0; col < m_cols; ++col)
			{
				inFile >> key;
				m_levelTiles[row][col] = m_tiles[key]->Clone(); //common prototype method
				m_levelTiles[row][col]->SetXY((float)(col * tileWidth), (float)(row * tileHeight));
				if (m_levelTiles[row][col]->IsObstacle())
				{
					m_obstacles.push_back(m_levelTiles[row][col]);
				}

			}
		}
	}
	inFile.close();
}

TiledLevel::~TiledLevel()
{

	for (int row = 0; row < m_rows; row++)
	{

		for (int col = 0; col < m_cols; col++)
		{
			delete m_levelTiles[row][col];
			m_levelTiles[row][col] = nullptr;
		}
	}
	m_levelTiles.clear();
	m_obstacles.clear();

	for (std::map<char, Tile*>::iterator i = m_tiles.begin(); i != m_tiles.end(); i++)
	{
		delete i->second;
		i->second = nullptr;
	}

	m_tiles.clear();
}

void TiledLevel::Update([[maybe_unused]] float deltaTime)
{

}

void TiledLevel::Render()
{
	for (int row = 0; row < m_rows; row++)
	{

		for (int col = 0; col < m_cols; col++)
		{

			SDL_RenderCopyF(Game::GetInstance().GetRenderer(), TextureManager::GetTexture(m_tilekey),
				m_levelTiles[row][col]->GetSourceTransform(), m_levelTiles[row][col]->GetDestinationTransform());

		}
	}

}


