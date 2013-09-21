#ifndef _SG_ITEM_
#define _SG_ITEM_

#include <vector>

#include <SFML/Graphics/Transformable.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/RectangleShape.hpp>

class SGRessource;

class SGItem :public sf::Drawable, public sf::Transformable
{

public:
	SGItem(SGItem* parent=NULL,sf::Drawable* content=NULL);
	virtual ~SGItem();
	
	float width()const;
	float height()const;
	
	void setWidth(float new_width);
	void setHeight(float new_height);
	
	sf::Drawable* content() const;

	SGItem* parentItem() const;	


	bool containPoint(sf::Vector2f p) const;
	sf::Vector2f mapToItem(SGItem* finalBasis, sf::Vector2f point) const;
	sf::Vector2f mapFromItem(SGItem* initialBasis, sf::Vector2f point) const;

	
protected:
	virtual void draw(sf::RenderTarget &target, sf::RenderStates states) const;

private:
	float m_width;
	float m_height;	
	sf::RectangleShape*        m_debugContent;
	sf::Drawable*              m_content;
	SGItem*                    m_parentItem;
	std::vector<SGItem* >      m_childrensItem;
	mutable sf::Transform      m_globalTransform;
	
	void updateGlobalTransform();

};


#endif // endof _SG_ITEM_
