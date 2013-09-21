/*
 * BorderImage.cpp
 *
 * SceneGraph - Copyright (c) 7 déc. 2012 - Jerome Mourey
 *
 * This software is provided 'as-is', without any express or
 * implied warranty. In no event will the authors be held
 * liable for any damages arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute
 * it freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented;
 *    you must not claim that you wrote the original software.
 *    If you use this software in a product, an acknowledgment
 *    in the product documentation would be appreciated but
 *    is not required.
 *
 * 2. Altered source versions must be plainly marked as such,
 *    and must not be misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any
 *    source distribution.
 *
 *  Created on: 7 déc. 2012
 */

#include "BorderImage.h"


#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Texture.hpp>

BorderImage::BorderImage()
    : m_texture(0)
    , m_left(0)
    , m_right(0)
    , m_top(0)
    , m_bottom(0)
    , m_width(0)
    , m_height(0)
    , m_need_update(true)
    , m_vertex_array(sf::TrianglesStrip, 24)
{
}

BorderImage::~BorderImage()
{
}

sf::Vector2u BorderImage::getSize() const
{
    return sf::Vector2u(m_width,m_height);
}

void BorderImage::setSize(sf::Vector2u size)
{
    m_width  = size.x;
    m_height = size.y;
    m_need_update = true;
}

void BorderImage::setWidth(unsigned int width)
{
    m_width  = width;
    m_need_update = true;
}

void BorderImage::setHeight(unsigned int height)
{
    m_height = height;
    m_need_update = true;
}

void BorderImage::setTexture(const sf::Texture& texture, unsigned int border)
{
    m_left = border;
    m_right = border;
    m_top = border;
    m_bottom = border;
    m_texture = &texture;
    m_need_update = true;
}

void BorderImage::setLeftBorder (unsigned int border)
{
    m_left = border;
    m_need_update = true;
}

void BorderImage::setRightBorder(unsigned int border)
{
    m_right = border;
    m_need_update = true;
}

void BorderImage::setTopBorder   (unsigned int border)
{
    m_top = border;
    m_need_update = true;
}

void BorderImage::setBottomBorder (unsigned int border)
{
    m_bottom = border;
    m_need_update = true;
}

unsigned int  BorderImage::leftBorder() const  { return m_left;  }
unsigned int BorderImage::rightBorder() const  { return m_right; }
unsigned int    BorderImage::topBorder() const  { return m_top;   }
unsigned int  BorderImage::bottomBorder() const { return m_bottom;}


void BorderImage::setColor(const sf::Color& color)
{
    for(int i=0;i<24;i++)
    {
	m_vertex_array[ i].color = color;
    }
}

void BorderImage::draw(sf::RenderTarget& target,sf::RenderStates states) const
{
    if( m_need_update == true)
    {
	updateVertices();
	m_need_update = false;
    }
    if (m_texture)
    {
	states.transform *= getTransform();
	states.texture = m_texture;
	target.draw(m_vertex_array,states);
    }
}

void BorderImage::updateVertices() const
{
    // http://dan.lecocq.us/wordpress/wp-content/uploads/2009/12/strip.png
    //     i ->
    //   j  0     1    2    3
    //   |
    //   V  4     5    6    7
    //
    //      8     9    10   11
    //
    //     12    13    14   15
    //
    // => 	0, 4, 1, 5, 2, 6, 3, 7, 7, 11, 6, 10, 5, 9 ,4 ,8, 8 ,12 ,9 ,13, 10 ,14, 11,15

    const unsigned int triangleStripVextexCount = 24;
    const unsigned int triangleStripVertexOrder[triangleStripVextexCount] = {0, 4, 1, 5, 2, 6, 3, 7, 7, 11, 6, 10, 5, 9 ,4 ,8, 8 ,12 ,9 ,13, 10 ,14, 11,15};

    if (m_texture)
    {
	unsigned int x_pos[4] = {0 , m_left , m_width  - m_right  , m_width};
	unsigned int y_pos[4] = {0 , m_top  , m_height - m_bottom , m_height};
	sf::Vector2f verticesPosition[16];

	unsigned int t_width = m_texture->getSize().x;
	unsigned int t_height = m_texture->getSize().x;

	unsigned int x_textCoord[4] = {0,m_left , t_width  - m_right  , t_width};
	unsigned int y_textCoord[4] = {0,m_top  , t_height - m_bottom , t_height};
	sf::Vector2f verticesTextCoord[16];

	for(int i = 0; i< 4;i++)
	{
	    for(int j = 0; j< 4;j++)
	    {
		verticesPosition[i+4*j] = sf::Vector2f(x_pos[i],y_pos[j]);
		verticesTextCoord[i+4*j] = sf::Vector2f(x_textCoord[i],y_textCoord[j]);
	    }
	}

	for(int i = 0; i<triangleStripVextexCount;i++)
	{
	    m_vertex_array[ i].position  = verticesPosition [ triangleStripVertexOrder[i]];
	    m_vertex_array[ i].texCoords = verticesTextCoord[ triangleStripVertexOrder[i]];
	}
	/*
		m_vertex_array[ 0].position = verticesPosition[ 0];
		m_vertex_array[ 1].position = verticesPosition[ 4];
		m_vertex_array[ 2].position = verticesPosition[ 1];
		m_vertex_array[ 3].position = verticesPosition[ 5];
		m_vertex_array[ 4].position = verticesPosition[ 2];
		m_vertex_array[ 5].position = verticesPosition[ 6];
		m_vertex_array[ 6].position = verticesPosition[ 3];
		m_vertex_array[ 7].position = verticesPosition[ 7];
		m_vertex_array[ 8].position = verticesPosition[ 7];
		m_vertex_array[ 9].position = verticesPosition[11];
		m_vertex_array[10].position = verticesPosition[ 6];
		m_vertex_array[11].position = verticesPosition[10];
		m_vertex_array[12].position = verticesPosition[ 5];
		m_vertex_array[13].position = verticesPosition[ 9];
		m_vertex_array[14].position = verticesPosition[ 4];
		m_vertex_array[15].position = verticesPosition[ 8];
		m_vertex_array[16].position = verticesPosition[ 8];
		m_vertex_array[17].position = verticesPosition[12];
		m_vertex_array[18].position = verticesPosition[ 9];
		m_vertex_array[19].position = verticesPosition[13];
		m_vertex_array[20].position = verticesPosition[10];
		m_vertex_array[21].position = verticesPosition[14];
		m_vertex_array[22].position = verticesPosition[11];
		m_vertex_array[23].position = verticesPosition[15];


		m_vertex_array[ 0].texCoords = verticesTextCoord[ 0];
		m_vertex_array[ 1].texCoords = verticesTextCoord[ 4];
		m_vertex_array[ 2].texCoords = verticesTextCoord[ 1];
		m_vertex_array[ 3].texCoords = verticesTextCoord[ 5];
		m_vertex_array[ 4].texCoords = verticesTextCoord[ 2];
		m_vertex_array[ 5].texCoords = verticesTextCoord[ 6];
		m_vertex_array[ 6].texCoords = verticesTextCoord[ 3];
		m_vertex_array[ 7].texCoords = verticesTextCoord[ 7];
		m_vertex_array[ 8].texCoords = verticesTextCoord[ 7];
		m_vertex_array[ 9].texCoords = verticesTextCoord[11];
		m_vertex_array[10].texCoords = verticesTextCoord[ 6];
		m_vertex_array[11].texCoords = verticesTextCoord[10];
		m_vertex_array[12].texCoords = verticesTextCoord[ 5];
		m_vertex_array[13].texCoords = verticesTextCoord[ 9];
		m_vertex_array[14].texCoords = verticesTextCoord[ 4];
		m_vertex_array[15].texCoords = verticesTextCoord[ 8];
		m_vertex_array[16].texCoords = verticesTextCoord[ 8];
		m_vertex_array[17].texCoords = verticesTextCoord[12];
		m_vertex_array[18].texCoords = verticesTextCoord[ 9];
		m_vertex_array[19].texCoords = verticesTextCoord[13];
		m_vertex_array[20].texCoords = verticesTextCoord[10];
		m_vertex_array[21].texCoords = verticesTextCoord[14];
		m_vertex_array[22].texCoords = verticesTextCoord[11];
		m_vertex_array[23].texCoords = verticesTextCoord[15];
		//*/
    }
}
