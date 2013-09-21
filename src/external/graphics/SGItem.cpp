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
	m_globalTransform = states.transform;
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

bool SGItem::containPoint(sf::Vector2f point) const
{
	return (point.x > 0) && (point.y > 0) && (point.x < m_width) && (point.y < m_height);
}

sf::Vector2f  SGItem::mapToItem(SGItem* finalBasis, sf::Vector2f  point) const
{
	sf::Vector2f  ret;
	//1 convert to parent
	ret = getTransform().transformPoint(point);
	//2 convert coord to root
	ret = m_globalTransform.transformPoint(ret);

	//if finalBasis is null mean we want to map to the root item
	if(finalBasis != NULL)
	{
		// 3 convert to parent of final
		ret = finalBasis->m_globalTransform.getInverse().transformPoint(ret);
		// 4 and finally to final
		ret = finalBasis->getInverseTransform().transformPoint(ret);
	}
	return ret;

}

sf::Vector2f  SGItem::mapFromItem(SGItem* initialBasis, sf::Vector2f  point) const
{
	sf::Vector2f  ret = point;
	if(initialBasis != NULL)
	{
		ret = initialBasis->getTransform().transformPoint(ret);
		ret = initialBasis->m_globalTransform.transformPoint(ret);
	}

	ret = m_globalTransform.getInverse().transformPoint(ret);
	ret = getInverseTransform().transformPoint(ret);

	return ret;
}



