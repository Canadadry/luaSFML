#ifndef TILEMAP_H_
#define TILEMAP_H_

#include <vector>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics/Rect.hpp>

namespace sf{
class Texture;
}

class TileMap : public sf::Drawable, public sf::Transformable
{
public:
	TileMap();
	virtual ~TileMap();

	void setTexture(const sf::Texture& texture);
	void setTileSize(sf::Vector2u tileSize);

	void setIDForTile(unsigned int tileId,unsigned  int tileColumn,unsigned int tileRow);
	void setIDForTile(unsigned int tileId, sf::Vector2u pos);
	int  getIDForTile(unsigned int tileColumn,unsigned int tileRow) const;
	int  getIDForTile(sf::Vector2u pos) const;

	void setData(unsigned int columns,unsigned  int rows,const unsigned int* data = 0);

private:
	const sf::Texture*              m_tileset;
	unsigned int              m_textureWidthInTile;
	unsigned int              m_textureHeightInTile;
	unsigned int              m_tilemapWidthInTile;
	unsigned int              m_tilemapHeightInTile;
	unsigned int              m_tileWidthInPixel;
	unsigned int              m_tileHeightInPixel;
	std::vector<unsigned int> m_data;
	sf::VertexArray           m_vertex_array;

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;
	void setTilePosition(unsigned int column,unsigned  int row);
	void setTileRect(unsigned int column,unsigned  int row);
	void setTileColor(unsigned int column,unsigned  int row);
	bool initTexture();
	void initTiles();


	inline bool isValidePosition(unsigned int column,unsigned  int row) const
	{
		 return row < m_tilemapHeightInTile && column < m_tilemapWidthInTile;
	}

	inline unsigned int idFromPosition(unsigned int column,unsigned  int row) const
	{
		return row * m_tilemapWidthInTile + column;
	}


};

#endif /* TILEMAP_H_ */
