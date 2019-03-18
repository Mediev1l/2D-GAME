#include "Character.h"
#include "AssetManager/AssetManager.h"

Character::Character(std::string name, double x, double y, double w, GLuint nFrames) 
	:
	Stats()
	, Dynamic(name, x, y)
	, _ori(4, w, _position)
	,_animation(nFrames,1.0/nFrames)
{
	_texture = AssetManager::Get().getSprite(name);
	_PifPafTexture = AssetManager::Get().getSprite("pifpaf");
};

Vec2i Character::getFrameIndex()
{
	return _animation.getAnimationIndex();
}

void Character::consumeItem(const Item * item)
{
	//_items.emplace_back(item);
	m_att_speed += item->getAttackSpeed();
	m_damage += item->getDamage();
	m_health += item->getHealth();
	m_speed += item->getMovementSpeed();
	m_shield += item->getShield();
}

void Character::updateAnimation(std::pair<Animation::Direction, Animation::Direction> dir, double deltaTime)
{
	_animation.UpdateAnimation(dir, deltaTime);
}
