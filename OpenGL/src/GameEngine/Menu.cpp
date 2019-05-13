#include "Menu.h"

Menu::Menu(Sound & sound,Sound& effect, State & state, GLFWwindow* window, TextGenerator& text, Renderer& renderer)
	: _onmain(true)
	, _isclosing(false)
	, _ismuting(false)
	, _dimm(false)
	, position(ActualPosition::POSITION_MAIN_MENU)
	, _cursor(0)
	, gameEngineState(state)
	, gameSound(sound)
	, gameEffectSound(effect)
	, window(window)
	, _textgen(text)
	, _gamerenderer(renderer)
	, color(0.0, 0.28, 0.72, 1.0)
{
	// MENU INITIALIZATION 
	//na razie na sztywno pozniej z pliku @@@ nie chce mi sie teraz xd

	_menu.names.push_back("resume");
	_menu.names.push_back("options");
	_menu.names.push_back("main menu");
	_menu.names.push_back("exit");

	_options.names.push_back("sounds");
	_options.names.push_back("game");
	_options.names.push_back("back");

	_game.names.push_back("gamma");
	_game.names.push_back("menu pic");
	_game.names.push_back("back");
	_game.names.push_back("gamma value");
	_game.names.push_back("menu value");

	_picture.names.push_back("Menu1");
	_picture.names.push_back("Menu2");
	_picture.names.push_back("Menu3");
	_picture.names.push_back("Menu4");
	_picture.names.push_back("Menu5");
	_picture.names.push_back("Menu6");
	_picture.names.push_back("Menu7");
	_picture.names.push_back("Menu8");
	_picture.names.push_back("Menu9");
	_picture.names.push_back("Menu10");
	_picture.names.push_back("Menu11");
	_picture.names.push_back("Menu12");
	_picture.names.push_back("Menu13");
	_picture.names.push_back("Menu14");

	_sounds.names.push_back("mute");
	_sounds.names.push_back("volume");
	_sounds.names.push_back("effects");
	_sounds.names.push_back("back");
	_sounds.names.push_back("mute value");
	_sounds.names.push_back("volume lvl");
	_sounds.names.push_back("effects lvl");

	_mainmenu.names.push_back("start");
	_mainmenu.names.push_back("high scores");
	_mainmenu.names.push_back("options");
	_mainmenu.names.push_back("credits");
	_mainmenu.names.push_back("exit");

	_menutheme.names.push_back("MenuTheme1");
	_gametheme.names.push_back("GameTheme1");

	Vec2d scale(0.07, 0.10);

	setPicture();

	gameSound.PlayGameTheme(_menutheme.names.at(_menutheme.pos - 1));


	_textgen.setText("options0", "", Vec2d(0,0), 0, scale);
	_textgen.setMenu("options0", true);
	_textgen.setInfinity("options0", false);


	_textgen.setText("options1", "", Vec2d(0, 0), 0, scale);
	_textgen.setMenu("options1", true);
	_textgen.setInfinity("options1", false);


	_textgen.setText("options2", "", Vec2d(0, 0), 0, scale);
	_textgen.setMenu("options2", true);				
	_textgen.setInfinity("options2", false);		
													
	_textgen.setText("options3", "", Vec2d(0, 0), 0, scale);
	_textgen.setMenu("options3", true);				 
	_textgen.setInfinity("options3", false);		 
													 
	_textgen.setText("options4", "", Vec2d(0, 0), 0, scale);
	_textgen.setMenu("options4", true);
	_textgen.setInfinity("options4", false);

	_textgen.setText("options5", "", Vec2d(0, 0), 0, scale);
	_textgen.setMenu("options5", true);
	_textgen.setInfinity("options5", false);

	_textgen.setText("options6", "", Vec2d(0, 0), 0, scale);
	_textgen.setMenu("options6", true);
	_textgen.setInfinity("options6", false);

	
}


void Menu::setCursor(int position)
{
	_cursor = 0;
}
void Menu::PositionReset()
{
	position = ActualPosition::POSITION_MENU;
}

void Menu::moveUP()
{
	gameEffectSound.Play("Cursor");

	switch (position)
	{
		case ActualPosition::POSITION_MAIN_MENU:
			_cursor > 0 ? _cursor-- : _cursor = (int)_mainmenu.names.size() - 1;
			break;	
	
		case ActualPosition::POSITION_MENU:

			_cursor > 0 ? _cursor -- : _cursor = (int)_menu.names.size() - 1;
			break;	
	
		case ActualPosition::POSITION_OPTIONS:

			_cursor > 0 ? _cursor-- : _cursor = (int)_options.names.size() - 1;
			break;
		
		case ActualPosition::POSITION_SOUND:

			_cursor > 0 ? _cursor-- : _cursor = (int)_sounds.names.size() - 4;
			break;
		case ActualPosition::POSITION_GAME:

			_cursor > 0 ? _cursor-- : _cursor = (int)_game.names.size() - 3;
			break;
	}
}

void Menu::moveDOWN()
{
	gameEffectSound.Play("Cursor");
	
	switch (position)
	{
		case ActualPosition::POSITION_MAIN_MENU:
			_cursor = (_cursor + 1) % _mainmenu.names.size();
			break;
		
		case ActualPosition::POSITION_MENU:

			_cursor = (_cursor + 1) % _menu.names.size();
			break;
	
		case ActualPosition::POSITION_OPTIONS:

			_cursor = (_cursor + 1) % _options.names.size();
			break;
		
		case ActualPosition::POSITION_SOUND:

			_cursor = (_cursor + 1) % (_sounds.names.size() - 3);
			break;
		case ActualPosition::POSITION_GAME:

			_cursor = (_cursor + 1) % (_menu.names.size() - 1);
			break;
	}
}

void Menu::MoveLeft()
{
	if (position == ActualPosition::POSITION_SOUND)
	{
		switch (_cursor)
		{
		case 0:
			if (gameSound.getMute() == true)
			{
				gameSound.Mute(false);
				gameEffectSound.Mute(false);
				if(_onmain)
					gameSound.PlayGameTheme(_menutheme.names.at(_menutheme.pos - 1));
				else
					gameSound.PlayGameTheme(_gametheme.names.at(_menutheme.pos - 1));
			}
			else
			{
				gameSound.Mute(true);
				gameEffectSound.Mute(true);
			}
			break;
		case 1:
			gameSound.VolumeDown();
			break;
		case 2:
			gameEffectSound.VolumeDown();
			break;
		}
	}
	else if (position == ActualPosition::POSITION_GAME)
	{
		switch (_cursor)
		{
		case 0:
			_gamerenderer.GammaDown();
			break;
		case 1:
			_picture.pos > 1 ? _picture.pos-- : _picture.pos = _picture.names.size();
			_dimm = true;
			break;
		}

	}


}

void Menu::MoveRight()
{
	if (position == ActualPosition::POSITION_SOUND)
	{
		switch (_cursor)
		{
		case 0:
			if (gameSound.getMute() == true)
			{
				gameSound.Mute(false);
				gameEffectSound.Mute(false);
				if (_onmain)
					gameSound.PlayGameTheme(_menutheme.names.at(_menutheme.pos - 1));
				else
					gameSound.PlayGameTheme(_gametheme.names.at(_menutheme.pos - 1));
			}
			else
			{
				gameSound.Mute(true);
				gameEffectSound.Mute(true);
			}
			break;
		case 1:
			gameSound.VolumeUp();
			break;
		case 2:
			gameEffectSound.VolumeUp();
			break;
		}
	}
	else if (position == ActualPosition::POSITION_GAME)
	{
		switch (_cursor)
		{
		case 0:
			_gamerenderer.GammaUp();
			break;
		case 1:
			_picture.pos < _picture.names.size() ? _picture.pos++ : _picture.pos = 1;
			_dimm = true;
			break;
		}
	}
}



void Menu::enter()
{

	if(position == ActualPosition::POSITION_MAIN_MENU)
	{
		switch (_cursor)
		{
			case 0:			
				HideMenu();
				_onmain = false;
				_isclosing = false;
				_ismuting = true;
				gameEngineState = State::START;
				gameEffectSound.Play("Start", 0);
				break;
			
			case 1:			
				gameEffectSound.Play("Error", 0);
				break;
			case 2:
				HideMenu();
				position = ActualPosition::POSITION_OPTIONS;
				break;
			case 3:
				gameEffectSound.Play("Error", 0);
				break;
			
			case 4:
				gameEngineState = State::CLOSING_MENU;
				_isclosing = false;
				//glfwSetWindowShouldClose(window, true);
				break;
			
		}


	}
	else if(position == ActualPosition::POSITION_MENU)
	{

		switch (_cursor)
		{
		case 0:
			gameEngineState = State::GAME;
			Close();
			break;

		case 1:
			HideMenu();
			position = ActualPosition::POSITION_OPTIONS;
			break;

		case 2:
			HideMenu();
			position = ActualPosition::POSITION_MAIN_MENU;
			gameEngineState = State::CLOSING_GAME;
			_onmain = true;
			_isclosing = true;
			
			break;

		case 3:
			gameEngineState = State::CLOSING_GAME;
			//glfwSetWindowShouldClose(window, true);
			break;

		}
		gameEffectSound.Play("Cursor");
		
	}
	else if(position == ActualPosition::POSITION_OPTIONS)
	{
		switch (_cursor)
		{
			case 0:		
				HideMenu();
				position = ActualPosition::POSITION_SOUND;
				break;
			case 1:
				//_gamerenderer.setGamma(0.5);
				//_dimm = true;
				HideMenu();
				position = ActualPosition::POSITION_GAME;
				break;
			case 2:
				HideMenu();
				if(_onmain == true)
					position = ActualPosition::POSITION_MAIN_MENU;
				else
					position = ActualPosition::POSITION_MENU;
				break;
			
		}
		gameEffectSound.Play("Cursor");
	}
	else if (position == ActualPosition::POSITION_SOUND)
	{
		switch (_cursor)
		{
			case 0:
				break;

			case 1:
				break;

			case 3:
				HideMenu();
				position = ActualPosition::POSITION_OPTIONS;
				break;
		}
	}
	else if (position == ActualPosition::POSITION_GAME)
	{
		switch (_cursor)
		{
		case 0:

			break;
		case 1:

			break;
		case 2:
			HideMenu();
			position = ActualPosition::POSITION_OPTIONS;
			break;
		}
	}

	setCursor(0);
}


void Menu::ShowMenu(double x, double y)
{
	_menux = x;
	_menuy = y;

	_xratio = _menux - 0.15;
	_yratio = 0.7;

	if(gameEngineState == State::MENU)
		_gamerenderer.ScreenDimmWithoutMenu(0.3f);

	//Dimm ONLY BACKGROUND
	if (_dimm == true && !_gamerenderer.isDark() && _onmain == true)
		_gamerenderer.ScreenDimmWithoutMenu(1.0f);
	else if(_onmain == true)
	{
		_dimm = false;
		setPicture();
		_gamerenderer.ScreenBright();
	}


	switch (position)
	{
		case ActualPosition::POSITION_MAIN_MENU:
			ShowMainMenu();
			break;
		
		case ActualPosition::POSITION_MENU:
			ShowGameMenu();
			break;
		
		case ActualPosition::POSITION_OPTIONS:
			ShowOptions();
			break;
		
		case ActualPosition::POSITION_SOUND:
			ShowSound();
			break;
		case ActualPosition::POSITION_GAME:
			ShowGame();
			break;
		
		
	}

		SetColor();
}

void Menu::HideMenu()
{
	_textgen.setInfinity("options0", false);
	_textgen.setInfinity("options1", false);
	_textgen.setInfinity("options2", false);
	_textgen.setInfinity("options3", false);
	_textgen.setInfinity("options4", false);	
	_textgen.setInfinity("options5", false);
	_textgen.setInfinity("options6", false);
}



void Menu::Close()
{

	HideMenu();

	PositionReset();
	setCursor(0);
}

void Menu::Open()
{
	gameEngineState = State::MENU;
	PositionReset();
	setCursor(0);
}

void Menu::ChangeMusic()
{
	gameSound.Stop();

	if(_onmain)
		gameSound.PlayGameTheme(_menutheme.names.at(_gametheme.pos - 1));
	else
	gameSound.PlayGameTheme(_gametheme.names.at(_gametheme.pos - 1));
	
}


void Menu::OnMainMenu(bool val)
{
	_isclosing = val;
}

bool Menu::ToMainMenu()
{
	return _isclosing;
}

bool Menu::getDimm()
{
	return _dimm;
}

bool Menu::getSoundStatus()
{
	return _ismuting;
}

void Menu::setSoundStatus(bool ismuting)
{
	_ismuting = ismuting;
}

GLuint Menu::getTextureId() const
{
	return texture->getID();
}


void Menu::ShowGameMenu()
{
	//Skalowanko Menu
	std::array<double, 4> menu = 
	{
		0,
		-0.2,
		-0.55,
		0.3
	};



	for (int i = 0; i < _menu.names.size(); i++)
	{	
		_textgen.setText("options" + std::to_string(i), _menu.names.at(i));
		_textgen.setPosition("options" + std::to_string(i), Vec2d(_xratio + menu.at(i), i * _yratio + _menuy));
		_textgen.setInfinity("options" + std::to_string(i), true);
		_textgen.setColor("options" + std::to_string(i), glm::vec4(1.0, 1.0, 1.0, 1.0));
	}
}

void Menu::ShowMainMenu()
{

	//Skalowanko Menu
	std::array<double, 5> mainmenu =
	{
		 0.2,
		-0.8,
		-0.2,
		-0.2,
		 0.3
	};

	for (int i = 0; i < _mainmenu.names.size(); i++)
	{
		_textgen.setText("options" + std::to_string(i), _mainmenu.names.at(i));
		_textgen.setPosition("options" + std::to_string(i), Vec2d(_xratio + mainmenu.at(i), (i + 1.3)  * _yratio + _menuy));
		_textgen.setInfinity("options" + std::to_string(i), true);
		_textgen.setColor("options" + std::to_string(i), glm::vec4(1.0, 1.0, 1.0, 1.0));
	}
}

void Menu::ShowOptions()
{
	//Skalowanko Opcji
	std::array<double, 3> options =
	{
		0.10,
		0.3,
		0.3
	};

	double scaleY;

	_onmain == true ? scaleY = 1 : scaleY = 0;




	for (int i = 0; i < _options.names.size(); i++)
	{
		_textgen.setText("options" + std::to_string(i), _options.names.at(i));
		_textgen.setPosition("options" + std::to_string(i), Vec2d(_xratio + options.at(i), (i + 1) * _yratio + scaleY + _menuy));
		_textgen.setInfinity("options" + std::to_string(i), true);
		_textgen.setColor("options" + std::to_string(i), glm::vec4(1.0, 1.0, 1.0, 1.0));
	}


}

void Menu::ShowSound()
{
	double offsetX = 2.5;

	std::string volume = std::to_string(static_cast<int>(100*gameSound.getVolume()));
	std::string effect = std::to_string(static_cast<int>(100 * gameEffectSound.getVolume()));
	std::string mute;

	if (gameSound.getMute() == true)
		mute = "ON";
	else
		mute = "OFF";

	double scaleY;

	_onmain == true ? scaleY = 1 : scaleY = 0;


	std::array<double, 7> soundX =
	{
		0.3,
		0,
		-0.2,
		0.3,
		0,
		0,
		0
	};

	std::array<double, 7> soundY =
	{
		0.3,
		0.3,
		0.3,
		0.3,
		0.3,
		0.3,
		0.3
	};





	for (int i = 0; i < _sounds.names.size(); i++)
	{
		if (_sounds.names.at(i) == "mute value")
		{
			_textgen.setText("options" + std::to_string(i), mute);
			_textgen.setPosition("options" + std::to_string(i), Vec2d(_xratio + offsetX,  1 * _yratio + scaleY + _menuy - soundY.at(i)));
		}
		else if (_sounds.names.at(i) == "volume lvl")
		{
			_textgen.setText("options" + std::to_string(i), volume);
			_textgen.setPosition("options" + std::to_string(i), Vec2d(_xratio + offsetX, 2 * _yratio + scaleY + _menuy - soundY.at(i)));
		}
		else if (_sounds.names.at(i) == "effects lvl")
		{
			_textgen.setText("options" + std::to_string(i), effect);
			_textgen.setPosition("options" + std::to_string(i), Vec2d(_xratio + offsetX, 3 * _yratio + scaleY + _menuy - soundY.at(i)));
		}
		else
		{
			_textgen.setText("options" + std::to_string(i), _sounds.names.at(i));
			_textgen.setPosition("options" + std::to_string(i), Vec2d(_xratio + soundX.at(i), (i + 1) * _yratio + scaleY + _menuy - soundY.at(i)) );
		}


		_textgen.setInfinity("options" + std::to_string(i), true);
		_textgen.setColor("options" + std::to_string(i), glm::vec4(1.0, 1.0, 1.0, 1.0));
	}

}

void Menu::ShowGame()
{
	double offsetX = 2.5;

	std::string gamma = std::to_string(static_cast<int>(100 * _gamerenderer.getMaxGamma()));


	double scaleY;

	_onmain == true ? scaleY = 1 : scaleY = 0;


	std::array<double, 5> gameX =
	{
		0.1,
		-0.6,
		0.3,
		0.3,
		0.3,

	};

	std::array<double, 5> gameY =
	{
		0,
		0,
		0,
		0,
		0
	};





	for (int i = 0; i < _game.names.size(); i++)
	{
		if (_game.names.at(i) == "gamma value")
		{
			_textgen.setText("options" + std::to_string(i), gamma);
			_textgen.setPosition("options" + std::to_string(i), Vec2d(_xratio + offsetX, 1 * _yratio + scaleY + _menuy - gameY.at(i)));
		}
		else if (_game.names.at(i) == "menu value")
		{
			_textgen.setText("options" + std::to_string(i), std::to_string(_picture.pos));
			_textgen.setPosition("options" + std::to_string(i), Vec2d(_xratio + offsetX, 2 * _yratio + scaleY + _menuy - gameY.at(i)));
		}
		else
		{
			_textgen.setText("options" + std::to_string(i), _game.names.at(i));
			_textgen.setPosition("options" + std::to_string(i), Vec2d(_xratio + gameX.at(i), (i + 1) * _yratio + scaleY + _menuy - gameY.at(i)));
		}


		_textgen.setInfinity("options" + std::to_string(i), true);
		_textgen.setColor("options" + std::to_string(i), glm::vec4(1.0, 1.0, 1.0, 1.0));
	}

}


void Menu::SetColor()
{



	if (position == ActualPosition::POSITION_MAIN_MENU)
	{
		switch (_cursor)
		{
		case 0:
			_textgen.setColor("options0", color);
			break;

		case 1:
			_textgen.setColor("options1", color);
			break;

		case 2:
			_textgen.setColor("options2", color);
			break;

		case 3:
			_textgen.setColor("options3", color);
			break;
		case 4:
			_textgen.setColor("options4", color);
			break;

		}
	}
	else if (position == ActualPosition::POSITION_MENU)
	{

		switch (_cursor)
		{
		case 0:
			_textgen.setColor("options0", color);
			break;
	
		case 1:
			_textgen.setColor("options1", color);
			break;
	
		case 2:
			_textgen.setColor("options2", color);
			break;
	
		case 3:
			_textgen.setColor("options3", color);
			break;
	
		}
	}
	else if (position == ActualPosition::POSITION_OPTIONS)
	{
		switch (_cursor)
		{
			case 0:	
				_textgen.setColor("options0", color);
				break;
			
			case 1:	
				_textgen.setColor("options1", color);
				break;
			case 2:
				_textgen.setColor("options2", color);
				break;
			
		}
	}
	else if (position == ActualPosition::POSITION_SOUND)
	{
		switch (_cursor)
		{
		case 0:
			_textgen.setColor("options0", color);
			_textgen.setColor("options4", color);
			break;

		case 1:
			_textgen.setColor("options1", color);
			_textgen.setColor("options5", color);
			break;
		case 2:
			_textgen.setColor("options2", color);
			_textgen.setColor("options6", color);
			break;
		case 3:
			_textgen.setColor("options3", color);
			break;

		}
	}
	else if (position == ActualPosition::POSITION_GAME)
	{
		switch (_cursor)
		{
		case 0:
			_textgen.setColor("options0", color);
			_textgen.setColor("options3", color);
			break;

		case 1:
			_textgen.setColor("options1", color);
			_textgen.setColor("options4", color);
			break;
		case 2:
			_textgen.setColor("options2", color);
			break;
		}
	}

}

void Menu::setPicture()
{
	texture = AssetManager::Get().getSprite(_picture.names.at(_picture.pos - 1));
	_gamerenderer.setPictureId(texture->getID());
}
