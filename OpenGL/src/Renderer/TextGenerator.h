

#ifndef _TextGenerator_H
#define _TextGenerator_H

#include <string>
#include <map>
#include <GL/glew.h>
#include <algorithm>

#include "Utility/Vec2.h"
#include "Utility/Timer.h"

class TextGenerator
{
private:

	const struct params
	{
		params(std::string x, Vec2d p, Vec2d siz, bool infinite = false)
			:
			 text(x)
			, pos(p)
			, constant(infinite)
		{
			GLuint dlugosc = (GLuint)text.size();
			//Max dlugosci 0.8
			//Max wysokosci 0.4
			double stosunek = 0.4 / 0.8; //HAHA ALE SMIESZNE
			//Hardkodowane 16 jako max dlugosc
			if (siz._x == 0 && siz._y == 0)
			{
				double min = std::min((double)24, (double)dlugosc);
				size._x = 0.8 / min;
				double scaley = size._x * stosunek;
				size._y = scaley > 0.4 ? 0.4 : scaley;
			}
			else
			{
				size._x = siz._x;
				size._y = siz._y;
			}
				pos._x -= (size._x * dlugosc*2.8);

		}
		std::string text;
		Vec2d pos;
		Vec2d size;
		bool constant;
	};

	double _maxWidth;
	double _maxHeight;
	std::map<std::string, params> _text;
	Timer& _timer;

public:

	TextGenerator() = delete;
	TextGenerator(const TextGenerator& cpy) = delete;
	TextGenerator(double maxWidth, double maxHeight, Timer& timer) : _maxWidth(maxWidth), _maxHeight(maxHeight), _timer(timer) {};

	void setText(std::string uniqueName, std::string text, Vec2d position, size_t duration, Vec2d size = Vec2d(0,0));
	bool CheckDrawing(size_t index) const;



	size_t getAmount() const { return _text.size(); };
	std::string findIndex(size_t index) const;
	Vec2d getSize(size_t index) const;
	std::string getText(size_t index) const;
	Vec2i getSheetPosition(char letter) const;
	Vec2d getPosition(size_t index) const;
	

};

#endif