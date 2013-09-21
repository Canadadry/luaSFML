#include "SGItem.h"
#include<SFML/Graphics/RectangleShape.hpp>
#include <random>

SGItem::SGItem(SGItem* parent,sf::Drawable* content)
: m_width(0.0f)
, m_height(0.0f)
, m_debugContent(NULL)
, m_content(content)
, m_parentItem(parent)
, m_globalTransform()
{
	if(parent != NULL)
	{
		parent->m_childrensItem.push_back(this);
	}

	m_debugContent = new sf::RectangleShape(sf::Vector2f(0,0));
	m_debugContent->setFillColor(sf::Color(std::rand() % 256, std::rand() % 256, std::rand() % 256));
	m_debugContent->setOutlineColor(sf::Color::Black);
	m_debugContent->setOutlineThickness(2.0);

}

SGItem::~SGItem()
{
    if(m_parentItem != NULL)
    {
	std::vector<SGItem*> vec = m_parentItem->m_childrensItem;
	vec.erase(std::remove(vec.begin(), vec.end(), this), vec.end());
    }
}

SGItem* SGItem::parentItem() const
{
	return m_parentItem;
}

float SGItem::width()const
{
	return m_width;
}

float SGItem::height()const
{
	return m_height;
}

//sf::Drawable* SGItem::content() const
//{
//	return m_content;
//}

void SGItem::setWidth(float new_width)   { m_width  = new_width;  }
void SGItem::setHeight(float new_height) { m_height = new_height; }

void SGItem::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform.combine(getTransform());

	m_debugContent->setSize(sf::Vector2f(m_width,m_height));
	target.draw(*m_debugContent,states);

//	if(m_content != NULL)
//	{
//	    target.draw(*m_content,states);
//	}

	for(unsigned int i=0;i<m_childrensItem.size();i++)
	{
		target.draw(*m_childrensItem[i],states);
	}
}



