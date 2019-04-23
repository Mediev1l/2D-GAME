

#ifndef _TextGenerator_H
#define _TextGenerator_H

#include <string>
#include <map>
#include <GL/glew.h>
#include <algorithm>
#include <glm.hpp>

#include "Renderer/Texture.h"
#include "Utility/Vec2.h"
#include "Utility/Timer.h"
#include "AssetManager/AssetManager.h"

class TextGenerator
{
private:

	struct params
	{
		params() = default;
		params(std::string x, Vec2d p, Vec2d siz, bool infinite = false)
			:
			 text(x)
			, pos(p)
			, constant(infinite)
			, finished(false)
			, menu(false)
			, color(1.0f, 1.0f, 1.0f, 1.0f)
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
				infinite == false ? color.a = 0.0f : 1.0f;


		}
		std::string text;
		Vec2d pos;
		Vec2d size;
		bool constant;
		bool finished;
		bool menu;
		glm::vec4 color;
	};

	double _maxWidth;
	double _maxHeight;
	std::map<std::string, params> _text;
	Timer& _timer;
	Texture* texture;
	

public:

	TextGenerator() = delete;
	TextGenerator(const TextGenerator& cpy) = delete;
	TextGenerator(double maxWidth, double maxHeight, Timer& timer) : _maxWidth(maxWidth), _maxHeight(maxHeight), _timer(timer) 
	{
		texture = AssetManager::Get().getSprite("Font");
	};

	//================================================================
	//= SETTERS
	//================================================================

	void setText(std::string uniqueName, std::string text, Vec2d position, size_t duration, Vec2d size = Vec2d(0,0));
	void setSize(std::string name, Vec2d size);
	void setMenu(std::string name, bool menu);
	void setColor(std::string name, glm::vec4 col) { _text[name].color = col; };
	void setInfinity(std::string name, bool isConst);

	//================================================================
	//= GETTERS
	//================================================================
	bool getMenu(std::string name) const;
	size_t getAmount() const { return _text.size(); };
	GLuint getTexture() const { return texture->getID(); };
	Vec2i getSheetPosition(char letter) const;

	//================================================================
	//= GET BY INDEX
	//================================================================
	bool CheckDrawing(size_t index) const;
	std::string FindIndex(size_t index) const;
	bool getTransparency(size_t index) const;
	bool getFinish(size_t index) const;
	glm::vec4 getColor(size_t index) const;
	std::string getText(size_t index) const;
	Vec2d getSize(size_t index) const;
	Vec2d getPosition(size_t index) const;
	std::string getName(size_t index) const;

	//================================================================
	//= SET BY INDEX
	//================================================================
	void setTransparency(size_t index, float value) const;

	//================================================================
	//= GET BY UNIQUE NAME
	//================================================================
	bool CheckDrawing(std::string name) const;
	bool CheckMenu(std::string name) const;
	bool getTransparency(std::string name) const;
	bool getFinish(std::string name) const;
	glm::vec4 getColor(std::string name) const;
	std::string getText(std::string name) const;
	Vec2d getSize(std::string name) const;
	Vec2d getPosition(std::string name) const;

	//================================================================
	//= SET BY UNIQUE NAME
	//================================================================
	void setTransparency(std::string name, float value) const;

};

#endif