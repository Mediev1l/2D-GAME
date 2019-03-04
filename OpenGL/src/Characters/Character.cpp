#include "Character.h"

void Character::consumeItem(const Item & item)
{
	_items.emplace_back(item);
	m_att_speed += item.getAttackSpeed();
	m_damage += item.getDamage();
	m_health += item.getHealth();
	m_speed += item.getMovementSpeed();
	m_shield += item.getShield();
}
