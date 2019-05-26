#ifndef _Menu_H
#define _Menu_H

//#include <GL/glew.h>
//#include "GLFW/glfw3.h"

#include "Utility/Enums.h"
#include "Renderer/Texture.h"
#include "Renderer/TextGenerator.h"
#include "Renderer/Renderer.h"
#include "GameEngine/Sound.h"
#include "Utility/Timer.h"
#include <array>


class Menu 
{
private:

	struct Selection
	{
		std::vector<std::string> names;
		size_t pos = 1;

	};


	//=====================
	//Actual State
	//=====================
	ActualPosition position;
	Selection _picture;
	Selection _mainmenu;
	Selection _menu;
	Selection _options;
	Selection _game;
	Selection _sounds;
	Selection _menutheme;
	Selection _gametheme;
	bool _dimm;
	bool _onmain;
	bool _isclosing;
	bool _ismuting;
	int _cursor;

	//=====================
	//Objects
	//=====================
	Texture* texture;
	State& gameEngineState;
	Sound& gameSound;
	Sound& gameEffectSound;
	Renderer& _gamerenderer;
	GLFWwindow* window; //moze na pozniej
	TextGenerator& _textgen;

	//=====================
	//SETTINGS
	//=====================
	double _menux;
	double _menuy;
	double _xratio;
	double _yratio;
	glm::vec4 color;

public:
	Menu() = delete;
	Menu(const Menu& cpy) = delete;
	Menu(Sound& sound, Sound& effect, State& state, GLFWwindow* window, TextGenerator& text, Renderer& renderer);

	void moveUP();
	void moveDOWN();
	void MoveLeft();
	void MoveRight();
	void enter();

	void ShowMenu(double x, double y);
	void Close();
	void Open();

	void ChangeMusic();
	void OnMainMenu(bool val);
	bool ToMainMenu();
	void ToMenu();
	bool getDimm();
	bool getSoundStatus();
	void setSoundStatus(bool ismuting);
	GLuint getTextureId() const;

private:
	
	void ShowGameMenu();
	void ShowMainMenu();
	void ShowOptions();
	void ShowSound();
	void ShowGame();

	void HideMenu();
	

	void SetColor();
	void setPicture();
	void setCursor(int position);
	void PositionReset();

};
#endif
