#include "TextGenerator.h"

void TextGenerator::setText(std::string uniqueName, std::string text, Vec2d position, size_t duration, Vec2d size )
{
	if (_text.find(uniqueName) != _text.end())
	{
		_text[uniqueName].text = text;
		_text[uniqueName].pos = position;
		return;
	}


	if (duration == 0)
	{
		if (_timer.delay(uniqueName, duration, true))
			_text.emplace(uniqueName, params{ text, position, size, true });
	}
	else
	{
		if (_timer.delay(uniqueName, duration + 2, true))
			_text.emplace(uniqueName, params{ text, position, size });
	}

	//if (_timer.delay(uniqueName, duration, true) && duration == 0)
	//{
	//	if(duration == 0)
	//		_text.emplace(uniqueName, params{ text, position, size, true });
	//	else
	//		_text.emplace(uniqueName, params{ text, position,size });
	//}
}

void TextGenerator::setSize(std::string name, Vec2d size)
{
	_text.at(name).size = size;
}

void TextGenerator::setMenu(std::string name, bool menu)
{
	_text.at(name).menu = menu;
}

bool TextGenerator::CheckDrawing(size_t index) const
{
	std::string ind = FindIndex(index);
	if (ind != "_ERROR")
	{
		if (_timer.CheckState(ind) || _text.at(ind).constant == true)
		{
			if (_timer.getDelay(ind) <= 1.0 &&  _text.at(ind).constant != true)
				const_cast<TextGenerator*>(this)->_text.at(ind).finished = true;
			else
				const_cast<TextGenerator*>(this)->_text.at(ind).finished = false;

			return true;
		}
		else
			return false;

	}

}

void TextGenerator::setTransparency(size_t index, float value) const
{
	std::string ind = FindIndex(index);
	if (ind != "_ERROR")
		const_cast<TextGenerator*>(this)->_text.at(ind).color.a = value;
}

bool TextGenerator::CheckDrawing(std::string name) const
{
	if (_timer.CheckState(name) || _text.at(name).constant == true)
	{
		if (_timer.getDelay(name) <= 1.0 &&  _text.at(name).constant != true)
			const_cast<TextGenerator*>(this)->_text.at(name).finished = true;
		else
			const_cast<TextGenerator*>(this)->_text.at(name).finished = false;

		return true;
	}
	else
		return false;
}

bool TextGenerator::CheckMenu(std::string name) const
{
	return _text.at(name).menu;
}


bool TextGenerator::getTransparency(std::string name) const
{
	if (_text.at(name).color.a >= 0.0f)
		return true;
	else
		return false;
}

bool TextGenerator::getFinish(std::string name) const
{
	if (_text.at(name).finished == true)
		return true;
	else
		return false;
}

glm::vec4 TextGenerator::getColor(std::string name) const
{
	return _text.at(name).color;
}

std::string TextGenerator::getText(std::string name) const
{
	return _text.at(name).text;
}

Vec2d TextGenerator::getSize(std::string name) const
{
	return _text.at(name).size;
}

Vec2d TextGenerator::getPosition(std::string name) const
{
	return _text.at(name).pos;
}

void TextGenerator::setTransparency(std::string name, float value) const
{
	const_cast<TextGenerator*>(this)->_text.at(name).color.a = value;
}

void TextGenerator::setInfinity(std::string name, bool isConst)
{
	_text.at(name).constant = isConst;
}


bool TextGenerator::getTransparency(size_t index) const
{
	std::string ind = FindIndex(index);
	if (ind != "_ERROR")
	{
		if (_text.at(ind).color.a >= 0.0f)
			return true;
		else
			return false;
	}
	else
		return false;
}

std::string TextGenerator::FindIndex(size_t index) const
{
	std::map<std::string, params>::const_iterator it;
	int counter = 0;

	for (it = _text.begin(); it != _text.end(); it++)
	{
		if (counter == index)
		{
			return it->first;

		}
		counter++;
	}

	return "_ERROR";
}

Vec2d TextGenerator::getSize(size_t index) const
{
	std::string ind = FindIndex(index);
	if (ind != "_ERROR")
		return _text.at(ind).size;
}

bool TextGenerator::getMenu(std::string name) const
{
	return _text.at(name).menu;
}

std::string TextGenerator::getText(size_t index) const
{
	std::string ind = FindIndex(index);
	if (ind != "_ERROR")
		return _text.at(ind).text;
}

Vec2i TextGenerator::getSheetPosition(char letter) const
{
	switch ((size_t)letter)
	{
		case 32:
		{
			return Vec2i(6, 2);
			break;
		}
		case 46:
		{
			return Vec2i(7, 2);
			break;
		}
		case 33:
		{
			return Vec2i(9, 2);
			break;
		}
		case 58:
		{
			return Vec2i(8, 2);
			break;
		}
		case 48:
		case 49:
		case 50:
		case 51:
		case 52:
		case 53:
		case 54:
		case 55:
		case 56:
		case 57:
			return Vec2i(letter-(size_t)48, 3);
			break;
		default:
		{
			return Vec2i((size_t)(letter - 65) % 10, (size_t)(letter - 65) / 10);
			break;
		}
	}
}

Vec2d TextGenerator::getPosition(size_t index) const
{
	std::string ind = FindIndex(index);
	if (ind != "_ERROR")
		return _text.at(ind).pos;

}

std::string TextGenerator::getName(size_t index) const
{
	std::string ind = FindIndex(index);
	if (ind != "_ERROR")
		return ind;
	else
		return "_ERROR";
}

glm::vec4 TextGenerator::getColor(size_t index) const
{
	std::string ind = FindIndex(index);
	if (ind != "_ERROR")
		return _text.at(ind).color;
}

bool TextGenerator::getFinish(size_t index) const
{

	std::string ind = FindIndex(index);
	if (ind != "_ERROR")
	{
		if (_text.at(ind).finished == true)
			return true;
		else
			return false;
	}
}

