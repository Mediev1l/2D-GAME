#include "Character.h"
#include "AssetManager/AssetManager.h"

Timer * Character::t = nullptr;

Character::Character(std::string name, double x, double y, Vec2d OriSize, GLuint nFrames)
	:
	Stats()
	, Dynamic(name, x, y)
	, _ori(4, OriSize, _position)
	,_animation(nFrames,1.0/nFrames)
	,color(1.0f, 1.0f, 1.0f, 1.0f)
	,_ratio(0.05f)
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
	if (color.a < 1.0f)
		return true;
	else
		return false;
}


void Character::consumeItem(const Item * item)
{
	//_items.emplace_back(item);
	m_att_speed -= item->getAttackSpeed();
	m_damage += item->getDamage();
	m_health += item->getHealth();
	m_speed += item->getMovementSpeed();
	m_shield += item->getShield();
}

void Character::updateAnimation(std::pair<Animation::Direction, Animation::Direction> dir, double deltaTime)
{
	_animation.UpdateAnimation(dir, deltaTime);
}

void Character::Blink()
{
	
	if(!isTouchable())
	{

		if (color.a <= 0.3f)
			_ratio = abs(_ratio);
		else if (color.a >= 1.0f)
			_ratio = -_ratio;

		color.a += _ratio;
	}
	else if(isTransparent())
		color.a = 1.0f;

	//else
		//if(isTransparent())
			//color.a += delta * 4;

	if (color.a > 1.0f)
		color.a = 1.0f;

	else if (color.a < 0.3f)
		color.a = 0.3f;
}
