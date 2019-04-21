#include "TextGenerator.h"

void TextGenerator::setText(std::string uniqueName, std::string text, Vec2d position, size_t duration, Vec2d size )
{
	if (_text.find(uniqueName) != _text.end())
	{
		_text[uniqueName].text = text;
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

bool TextGenerator::CheckDrawing(size_t index) const
{
	std::string ind = findIndex(index);
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
	std::string ind = findIndex(index);
	if (ind != "_ERROR")
		const_cast<TextGenerator*>(this)->_text.at(ind).color.a = value;
}

void TextGenerator::Infinity(std::string name, bool isConst)
{
	_text.at(name).constant = isConst;
}


bool TextGenerator::getTransparency(size_t index) const
{
	std::string ind = findIndex(index);
	if (ind != "_ERROR")
	{
		_text.at(ind).color.a >= 0.0f;
		return true;
	}
	else
		return false;
}

std::string TextGenerator::findIndex(size_t index) const
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
	std::string ind = findIndex(index);
	if (ind != "_ERROR")
		return _text.at(ind).size;
}

std::string TextGenerator::getText(size_t index) const
{
	std::string ind = findIndex(index);
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
	std::string ind = findIndex(index);
	if (ind != "_ERROR")
		return _text.at(ind).pos;

}

glm::vec4 TextGenerator::getColor(size_t index) const
{
	std::string ind = findIndex(index);
	if (ind != "_ERROR")
		return _text.at(ind).color;
}

bool TextGenerator::getFinish(size_t index) const
{

	std::string ind = findIndex(index);
	if (ind != "_ERROR")
	{
		if (_text.at(ind).finished == true)
			return true;
		else
			return false;
	}
}

