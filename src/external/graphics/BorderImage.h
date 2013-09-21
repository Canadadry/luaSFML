/*
 * BorderImage.h
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

#ifndef BORDERIMAGE_H_
#define BORDERIMAGE_H_

namespace sf{
class Texture;
class Color;
}

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/VertexArray.hpp>


class BorderImage : public sf::Drawable, public sf::Transformable
{
public:
	BorderImage();
	virtual ~BorderImage();


	sf::Vector2u getSize() const;
	void setSize(sf::Vector2u size);
	void setWidth(unsigned int width);
	void setHeight(unsigned int height);

	void setTexture(const sf::Texture& texture, unsigned int border);

	void setLeftBorder  (unsigned int leftBorder);
	void setRightBorder (unsigned int rightBorder);
	void setTopBorder   (unsigned int upBorder);
	void setBottomBorder(unsigned int downBorder);
	unsigned int   leftBorder() const;
	unsigned int  rightBorder() const;
	unsigned int    topBorder() const;
	unsigned int bottomBorder() const;

	void setColor(const sf::Color& color);
	sf::Color color() const;

private:
	const sf::Texture* m_texture;
	unsigned int m_left;
	unsigned int m_right;
	unsigned int m_top;
	unsigned int m_bottom;
	unsigned int m_width;
	unsigned int m_height;

	mutable sf::VertexArray    m_vertex_array;
	mutable bool m_need_update;

	void updateVertices() const;
	virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

};

#endif /* BORDERIMAGE_H_ */
