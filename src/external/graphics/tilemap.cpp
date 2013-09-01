
#include "TileMap.h"
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <cstdlib>

TileMap::TileMap()
    : m_tileset(NULL)
    , m_textureWidthInTile(0)
    , m_textureHeightInTile(0)
    , m_tilemapWidthInTile(0)
    , m_tilemapHeightInTile(0)
    , m_tileWidthInPixel(0)
    , m_tileHeightInPixel(0)
    , m_data()
    , m_vertex_array(sf::Quads,0)
{}


TileMap::~TileMap()
{
}

void TileMap::setTexture(const sf::Texture& texture)
{
    if(m_tileset != &texture)
    {
	m_tileset = &texture;
	if(initTexture())
	{
	    initTiles();
	}
    }
}

void TileMap::setTileSize(sf::Vector2u tileSize)
{
    bool needUpdate = false;

    needUpdate = needUpdate || (tileSize.x != m_tileWidthInPixel);
    m_tileWidthInPixel  =tileSize.x;
    needUpdate = needUpdate || (tileSize.y != m_tileHeightInPixel);
    m_tileHeightInPixel = tileSize.y;
    if(needUpdate)
    {
	if(initTexture())
	{
	    initTiles();
	}
    }

}

bool TileMap::initTexture()
{
    bool ret = false;
    if(m_tileset != 0)
    {
	if(m_tileWidthInPixel != 0 && m_tileHeightInPixel != 0)
	{
	    sf::Vector2u textureSize  = m_tileset->getSize();
	    unsigned int new_width =  textureSize.x /m_tileWidthInPixel;
	    ret = ret || (new_width != m_textureWidthInTile);
	    m_textureWidthInTile  =new_width;
	    unsigned int new_height =  textureSize.y / m_tileHeightInPixel;
	    ret = ret || (new_width != m_textureWidthInTile);
	    m_textureHeightInTile = new_height;
	}
    }
    return ret;
}

void TileMap::initTiles()
{
    if(m_tileset != 0)
    {
	if(m_tileWidthInPixel != 0 && m_tileHeightInPixel != 0)
	{
	    if(m_textureWidthInTile != 0 && m_textureHeightInTile != 0)
	    {
		for(unsigned int row = 0; row<m_tilemapHeightInTile; row++)
		{
		    for(unsigned int col = 0; col<m_tilemapWidthInTile; col++)
		    {
			setTilePosition(col, row);
			setTileRect(col, row);
		    }
		}
	    }
	}
    }
}

void TileMap::setIDForTile(unsigned int tileId, unsigned int tileColumn, unsigned int tileRow)
{
    if(tileId < m_textureWidthInTile*m_textureHeightInTile)
    {
	if( isValidePosition(tileColumn,tileRow))
	{
	    m_data[idFromPosition(tileColumn,tileRow)] = tileId;
	    setTileRect(tileColumn,tileRow);
	}
    }
}

int TileMap::getIDForTile(unsigned int tileColumn, unsigned int tileRow) const
{
    int ret = -1;
    if( isValidePosition(tileColumn,tileRow))
    {
	ret = m_data[idFromPosition(tileColumn,tileRow)];
    }

    return ret;
}


void TileMap::setIDForTile(unsigned int tileId, sf::Vector2u pos)
{
    setIDForTile(tileId,pos.x,pos.y);
}

int  TileMap::getIDForTile(sf::Vector2u pos) const
{
    return getIDForTile(pos.x,pos.y);
}

void TileMap::setData(unsigned int columns, unsigned int rows, const unsigned int* data)
{
    if(columns != 0 && rows !=0)
    {
	m_data.clear();
	if(data == NULL) data = (unsigned int*)calloc(rows*columns,sizeof(unsigned int));
	m_data.assign(data, data+rows*columns);
	m_vertex_array.resize(rows*columns*4);
	m_tilemapWidthInTile = columns;
	m_tilemapHeightInTile = rows;

	initTiles();
    }
}

void TileMap::setTilePosition(unsigned int column, unsigned int row)
{
    int pos = (column+row*m_tilemapWidthInTile)*4;

    unsigned int left   = column * m_tileWidthInPixel;
    unsigned int right  = left   + m_tileWidthInPixel;
    unsigned int top    = row    * m_tileHeightInPixel;
    unsigned int bottom = top    + m_tileHeightInPixel;

    //	printf("position for tile %d (%d,%d,%d,%d) \n",pos,left,right,top,bottom);

    //	left   = 0;
    //	right  = 100;
    //	top    = 0;
    //	bottom = 100;

    m_vertex_array[pos + 0].position = sf::Vector2f(left,top);
    m_vertex_array[pos + 1].position = sf::Vector2f(left,bottom);
    m_vertex_array[pos + 2].position = sf::Vector2f(right,bottom);
    m_vertex_array[pos + 3].position = sf::Vector2f(right,top);
}

void TileMap::setTileRect(unsigned int column, unsigned int row)
{
    int pos = (column+row*m_tilemapWidthInTile)*4;

    unsigned int tile =  m_data[idFromPosition(column,row)];

    unsigned int tile_row    = tile / m_textureWidthInTile;
    unsigned int tile_column = tile % m_textureWidthInTile;

    float left   = tile_column*m_tileWidthInPixel;
    float right  = left + m_tileWidthInPixel;
    float top    = tile_row*m_tileHeightInPixel;
    float bottom = top + m_tileHeightInPixel;

    //	left   /= (float)m_tileset->getSize().x;
    //	right  /= (float)m_tileset->getSize().x;
    //	top    /= (float)m_tileset->getSize().y;
    //	bottom /= (float)m_tileset->getSize().y;
    //
    //	left   = 0.0;
    //	right  = 1.0;
    //	top    = 0.0;
    //	bottom = 1.0;

    //	printf("textcoord for tile %d (%f,%f,%f,%f) \n",pos,left,right,top,bottom);

    m_vertex_array[pos + 0].texCoords = sf::Vector2f(left, top);
    m_vertex_array[pos + 1].texCoords = sf::Vector2f(left, bottom);
    m_vertex_array[pos + 2].texCoords = sf::Vector2f(right, bottom);
    m_vertex_array[pos + 3].texCoords = sf::Vector2f(right, top);
}

void TileMap::setTileColor(unsigned int column,unsigned  int row)
{
    int pos = (column+row*m_tilemapWidthInTile)*4;

    m_vertex_array[pos + 0].color = sf::Color::White;
    m_vertex_array[pos + 1].color = sf::Color::White;
    m_vertex_array[pos + 2].color = sf::Color::White;
    m_vertex_array[pos + 3].color = sf::Color::White;

}

void TileMap::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    if (m_tileset)
    {
	states.transform *= getTransform();
	states.texture = m_tileset;
	target.draw(m_vertex_array,states);
    }
}
