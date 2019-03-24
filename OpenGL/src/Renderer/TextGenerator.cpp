#include "TextGenerator.h"

void TextGenerator::setText(std::string uniqueName, std::string text, Vec2d position, size_t duration )
{
	if (_timer.delay(uniqueName, duration, true))
	{
		_text.emplace(uniqueName, params{ text, position });
	}
}

bool TextGenerator::CheckDrawing(size_t index) const
{
	std::map<std::string, params>:: const_iterator it;
	int counter = 0;

	for (it = _text.begin(); it != _text.end(); it++)
	{
		if (counter == index)
		{
			if (_timer.CheckState(it->first))
				return true;
			else
				return false;
				
		}
		counter++;
	}
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
	if (findIndex(index) != "_ERROR")
		return _text.at(findIndex(index)).size;
}

std::string TextGenerator::getText(size_t index) const
{
	if (findIndex(index) != "_ERROR")
		return _text.at(findIndex(index)).text;
}

Vec2ic TextGenerator::getSheetPosition(char letter) const
{
	switch ((size_t)letter)
	{
		case 32:
		{
			return Vec2ic(6, 2);
			break;
		}
		case 46:
		{
			return Vec2ic(7, 2);
			break;
		}
		case 33:
		{
			return Vec2ic(8, 2);
			break;
		}
		case 58:
		{
			return Vec2ic(9, 2);
			break;
		}
		default:
		{
			return Vec2ic((size_t)(letter - 65) % 10, (size_t)(letter - 65) / 10);
			break;
		}
	}
}

Vec2d TextGenerator::getPosition(size_t index) const
{
	if (findIndex(index) != "_ERROR")
		return _text.at(findIndex(index)).pos;

}

