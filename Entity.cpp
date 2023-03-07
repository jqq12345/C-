#include "Entity.h"

Entity::Entity()
{	
	m_sprite = NULL;

}

Entity::~Entity() {

}


CCSprite* Entity::getSprite()
{
	//if(m_sprite) return NULL;
	return this->m_sprite;
}

void Entity::bindSprite(CCSprite* sprite)
{
	this->m_sprite = sprite;
	this->addChild(m_sprite);
}

