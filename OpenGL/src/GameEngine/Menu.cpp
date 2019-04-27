#include "Menu.h"

Menu::Menu(Sound & sound, State & state, GLFWwindow* window, TextGenerator& text, Renderer& renderer)
	: _onmain(true)
	, _isclosing(false)
	, position(ActualPosition::POSITION_MAIN_MENU)
	, _cursor(0)
	, gameEngineState(state)
	, gameSound(sound)
	, window(window)
	, _textgen(text)
	, _gamerenderer(renderer)
	, color(0.0, 0.28, 0.72, 1.0)
{
	// MENU INITIALIZATION

	

	_menu.names.push_back("resume");
	_menu.names.push_back("options");
	_menu.names.push_back("main menu");
	_menu.names.push_back("exit");

	_options.names.push_back("sounds");
	_options.names.push_back("back");

	_sounds.names.push_back("mute");
	_sounds.names.push_back("volume");
	_sounds.names.push_back("back");
	_sounds.names.push_back("mute value");
	_sounds.names.push_back("volume lvl");

	_mainmenu.names.push_back("start");
	_mainmenu.names.push_back("high scores");
	_mainmenu.names.push_back("options");
	_mainmenu.names.push_back("credits");
	_mainmenu.names.push_back("exit");


	Vec2d scale(0.07, 0.10);


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
	gameSound.Play("Cursor");

	switch (position)
	{
		case ActualPosition::POSITION_MAIN_MENU:
			_cursor > 0 ? _cursor-- : _cursor = _mainmenu.names.size() - 1;
			break;	
	
		case ActualPosition::POSITION_MENU:

			_cursor > 0 ? _cursor -- : _cursor = _menu.names.size() - 1;
			break;	
	
		case ActualPosition::POSITION_OPTIONS:

			_cursor > 0 ? _cursor-- : _cursor = _options.names.size() - 1;
			break;
		
		case ActualPosition::POSITION_SOUND:

			_cursor > 0 ? _cursor-- : _cursor = _sounds.names.size() - 3;
			break;
		
	}
}

void Menu::moveDOWN()
{
	gameSound.Play("Cursor");
	
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

			_cursor = (_cursor + 1) % (_sounds.names.size() - 2);
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
				gameSound.Mute(false);
			else
				gameSound.Mute(true);
			break;
		case 1:
			gameSound.VolumeDown();
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
				gameSound.Mute(false);
			else
				gameSound.Mute(true);
			break;
		case 1:
			gameSound.VolumeUp();
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
				gameEngineState = State::START;
				gameSound.Play("Start", 0);
				break;
			
			case 1:			
				gameSound.Play("Error", 0);
				break;
			case 2:
				HideMenu();
				position = ActualPosition::POSITION_OPTIONS;
				break;
			case 3:
				gameSound.Play("Error", 0);
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
		gameSound.Play("Cursor");
		
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
				HideMenu();
				if(_onmain == true)
					position = ActualPosition::POSITION_MAIN_MENU;
				else
					position = ActualPosition::POSITION_MENU;
				break;
			
		}
		gameSound.Play("Cursor");
	}
	else if (position == ActualPosition::POSITION_SOUND)
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

void Menu::OnMainMenu(bool val)
{
	_isclosing = val;
}

bool Menu::ToMainMenu()
{
	return _isclosing;
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
	std::array<double, 2> options =
	{
		0.10,
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
	std::string mute;

	if (gameSound.getMute() == true)
		mute = "ON";
	else
		mute = "OFF";

	double scaleY;

	_onmain == true ? scaleY = 1 : scaleY = 0;


	std::array<double, 5> soundX =
	{
		0.3,
		0,
		0.3,
		0,
		0
	};

	std::array<double, 5> soundY =
	{
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
		else
		{
			_textgen.setText("options" + std::to_string(i), _sounds.names.at(i));
			_textgen.setPosition("options" + std::to_string(i), Vec2d(_xratio + soundX.at(i), (i + 1) * _yratio + scaleY + _menuy - soundY.at(i)) );
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
			
		}
	}
	else if (position == ActualPosition::POSITION_SOUND)
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
