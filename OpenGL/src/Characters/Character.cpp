#include "Character.h"
#include "AssetManager/AssetManager.h"

Character::Character(std::string name, double x, double y, Vec2d OriSize, GLuint nFrames, Timer& t)
	:
	Stats()
	, Dynamic(name, x, y)
	, _ori(4, OriSize, _position)
	,_animation(nFrames,1.0/nFrames)
	,t(&t)
	,color(1.0f, 1.0f, 1.0f, 1.0f)
{
	_texture = AssetManager::Get().getSprite(name);
	_PifPafTexture = AssetManager::Get().getSprite("pifpafsheet");
};

Vec2i Character::getFrameIndex()
{
	return _animation.getAnimationIndex();
}

bool Character::isTransparent()
{
	if (color.a < 1.0)
		return true;
	else
		return false;
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

void Character::Blink(double delta)
{
	_ratio = delta;
	if (!isTouchable())
	{
		color.a += _ratio;

		if (color.a < 0)
			_ratio = abs(_ratio);
		else if (color.a > 1.0)
			_ratio = -_ratio;

	}
	else
		if(isTransparent())
			color.a += delta;

	if (color.a > 1.0)
		color.a = 1.0;
}
