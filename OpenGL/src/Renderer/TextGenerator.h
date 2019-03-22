

#ifndef _TextGenerator_H
#define _TextGenerator_H

#include <string>
#include <map>

#include "Utility/Vec2.h"
#include "Utility/Timer.h"

class TextGenerator
{
private:
	double _maxWidth;
	double _maxHeight;
	std::map<std::string, std::pair<std::string, Vec2ic>> _text;
	Timer& _timer;

public:

	TextGenerator() = delete;
	TextGenerator(const TextGenerator& cpy) = delete;
	TextGenerator(double maxWidth, double maxHeight, Timer& timer) : _maxWidth(maxWidth), _maxHeight(maxHeight), _timer(timer) {};

	void setText(std::string uniqueName, std::string text, Vec2i position, size_t duration);
	bool CheckDrawing(size_t index) const;

	size_t getSize() const { return _text.size(); };
	std::string getText(size_t index) const;
	Vec2ic getSheetPosition(char letter) const;
	Vec2ic getPosition(size_t index) const;
	

};

#endif