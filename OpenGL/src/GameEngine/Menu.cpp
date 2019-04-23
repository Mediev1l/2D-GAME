#include "Menu.h"

Menu::Menu(Sound & sound, State & state, GLFWwindow* window, TextGenerator& text, Renderer& renderer)
	: _isclosing(false)
	, mainMenu(MainMenu::MAIN_START)
	, gameMenu(GameMenu::GAME_RESUME)
	, position(ActualPosition::POSITION_MENU)
	, gameEngineState(state)
	, gameSound(sound)
	, window(window)
	, _textgen(text)
	, _gamerenderer(renderer)
	, color(0.0, 0.28, 0.72, 1.0)
{
	// MENU INITIALIZATION

	//================================================================
	//= Menu
	//================================================================
	// RESUME - GAME MENU
	_textgen.setText("RESUME", "RESUME", Vec2d(xratio, menuy), 0, Vec2d(0.07, 0.10));
	_textgen.setMenu("RESUME", true);
	_textgen.setInfinity("RESUME", false);

	// OPTIONS - GAME MENU
	_textgen.setText("OPTIONS", "OPTIONS", Vec2d(xratio - 0.2, 1 * yratio + menuy), 0, Vec2d(0.07, 0.10));
	_textgen.setMenu("OPTIONS", true);
	_textgen.setInfinity("OPTIONS", false);

	// BACK TO MAIN MENU
	_textgen.setText("MAIN", "MAIN MENU", Vec2d(xratio - 0.55, 2 * yratio + menuy), 0, Vec2d(0.07, 0.10));
	_textgen.setMenu("MAIN", true);
	_textgen.setInfinity("MAIN", false);

	// GAME EXIT
	_textgen.setText("EXIT", "EXIT", Vec2d(xratio + 0.3, 3 * yratio + menuy), 0, Vec2d(0.07, 0.10));
	_textgen.setMenu("EXIT", true);
	_textgen.setInfinity("EXIT", false);

	//================================================================
	//= Options
	//================================================================

	// GAME SOUNDS
	_textgen.setText("SOUND", "SOUND", Vec2d(xratio + 0.15, 1 * yratio + menuy), 0, Vec2d(0.07, 0.10));
	_textgen.setMenu("SOUND", true);
	_textgen.setInfinity("SOUND", false);

	// GAME BACK
	_textgen.setText("BACK", "BACK", Vec2d(xratio + 0.3, 2 * yratio + menuy), 0, Vec2d(0.07, 0.10));
	_textgen.setMenu("BACK", true);
	_textgen.setInfinity("BACK", false);


	//================================================================
	//= Sounds
	//================================================================

	// SOUND MUTE
	_textgen.setText("MUTE", "MUTE:", Vec2d(xratio + 0.3, 1 * yratio + menuy), 0, Vec2d(0.07, 0.10));
	_textgen.setMenu("MUTE", true);
	_textgen.setInfinity("MUTE", false);

	_textgen.setText("MUTE VALUE", "", Vec2d(xratio + 0.3, 1 * yratio + menuy), 0, Vec2d(0.07, 0.10));
	_textgen.setMenu("MUTE VALUE", true);
	_textgen.setInfinity("MUTE VALUE", false);

	// SOUND VOLUME
	_textgen.setText("VOLUME", "VOLUME:", Vec2d(xratio, 2 * yratio + menuy), 0, Vec2d(0.07, 0.10));
	_textgen.setMenu("VOLUME", true);
	_textgen.setInfinity("VOLUME", false);

	_textgen.setText("VOLUME LVL", "", Vec2d(xratio, 2 * yratio + menuy), 0, Vec2d(0.07, 0.10));
	_textgen.setMenu("VOLUME LVL", true);
	_textgen.setInfinity("VOLUME LVL", false);

	// BACK
	_textgen.setText("BACK", "BACK", Vec2d(xratio + 0.3, 3 * yratio + menuy), 0, Vec2d(0.07, 0.10));
	_textgen.setMenu("BACK", true);
	_textgen.setInfinity("BACK", false);
}

void Menu::setGameMenu()
{
	gameMenu = GameMenu::GAME_RESUME;
}

void Menu::setMainMenu()
{
	mainMenu = MainMenu::MAIN_START; 
}

void Menu::setOptions()
{
	options = GameOptions::GAME_OPTIONS_SOUND;
}

void Menu::setSoundOptions()
{
	soundoptions = GameSoundOptions::GAME_SOUND_MUTE;
}

void Menu::setPosition()
{
	position = ActualPosition::POSITION_MENU;
}

void Menu::moveUP()
{
	gameSound.Play("Cursor");

	switch (position)
	{
		case POSITION_MAIN_MENU:		
			mainMenu = static_cast<MainMenu>((mainMenu > 0 ?  mainMenu - 1 : mainMenu = static_cast<MainMenu>(MainMenu::MAIN_LAST -1)));
			break;	

		case POSITION_MENU:		
			gameMenu = static_cast<GameMenu>((gameMenu > 0 ? gameMenu - 1 : gameMenu = static_cast<GameMenu>(GameMenu::GAME_LAST - 1)));
			break;	

		case POSITION_OPTIONS:		
			options = static_cast<GameOptions>((options > 0 ? options - 1 : options = static_cast<GameOptions>(GameOptions::GAME_OPTIONS_LAST - 1)));
			break;
		
		case POSITION_SOUND:		
			soundoptions = static_cast<GameSoundOptions>((soundoptions > 0 ? soundoptions - 1 : soundoptions = static_cast<GameSoundOptions>(GameSoundOptions::GAME_SOUND_LAST - 1)));
			break;
		
	}
}

void Menu::moveDOWN()
{
	gameSound.Play("Cursor");

	switch (position)
	{
		case POSITION_MAIN_MENU:		
			mainMenu = static_cast<MainMenu>((mainMenu + 1) % MainMenu::MAIN_LAST);
			break;
		
		case POSITION_MENU:		
			gameMenu = static_cast<GameMenu>((gameMenu + 1) % GameMenu::GAME_LAST);
			break;
	
		case POSITION_OPTIONS:		
			options = static_cast<GameOptions>((options + 1) % GameOptions::GAME_OPTIONS_LAST);
			break;
		
		case POSITION_SOUND:		
			soundoptions = static_cast<GameSoundOptions>((soundoptions + 1) % GameSoundOptions::GAME_SOUND_LAST);
			break;
		
	}
}

void Menu::MoveLeft()
{
	if (position == POSITION_SOUND)
	{
		switch (soundoptions)
		{
		case GAME_SOUND_MUTE:
			if (gameSound.getMute() == true)
				gameSound.Mute(false);
			else
				gameSound.Mute(true);
			break;
		case GAME_SOUND_VOLUME:
			gameSound.VolumeDown();
			break;
		}
	}

}

void Menu::MoveRight()
{
	if (position == POSITION_SOUND)
	{
		switch (soundoptions)
		{
		case GAME_SOUND_MUTE:
			if (gameSound.getMute() == true)
				gameSound.Mute(false);
			else
				gameSound.Mute(true);
			break;
		case GAME_SOUND_VOLUME:
			gameSound.VolumeUp();
			break;
		}
	}
}



void Menu::enter()
{

	if(position == POSITION_MAIN_MENU)
	{
		switch (mainMenu)
		{
			case MAIN_START:			
				gameEngineState = State::INIT;
				break;
			
			case MAIN_OPTIONS:			
				
				position = ActualPosition::POSITION_OPTIONS;
			
			case MAIN_EXIT:
				gameEngineState = State::EXIT;
				//glfwSetWindowShouldClose(window, true);
				break;
			
		}
	}
	else if(position == POSITION_MENU)
	{
		switch (gameMenu)
		{
			case GAME_RESUME:			
				gameEngineState = State::GAME;
				Close();
				break;
			
			case GAME_OPTIONS:			
				HideMenu();
				setOptions();
				position = ActualPosition::POSITION_OPTIONS;
				break;
			
			case GAME_TOMAIN:
				break;
			
			case GAME_EXIT:
				gameEngineState = State::EXIT;
				//glfwSetWindowShouldClose(window, true);
				break;
			
		}
		
	}
	else if(position == POSITION_OPTIONS)
	{
		switch (options)
		{
			case GAME_OPTIONS_SOUND:		
				HideOptions();
				position = POSITION_SOUND;
				break;
			
			case GAME_OPTIONS_BACK:
				HideOptions();
				position = POSITION_MENU;
				break;
			
		}
	}
	else if (position == POSITION_SOUND)
	{
		switch (soundoptions)
		{
			case GAME_SOUND_MUTE:
				break;

			case GAME_SOUND_VOLUME:
				break;

			case GAME_SOUND_BACK:
				HideSound();
				position = POSITION_OPTIONS;
				break;
		}
	}

	gameSound.Play("Cursor");
}


void Menu::ShowMenu(double x, double y)
{
	menux = x;
	menuy = y;


	xratio = x - 0.15;
	yratio = 0.7;

	if(_gamerenderer.HowDark() > 0.7)
		_gamerenderer.ScreenDimm(0.3f);

	//HideMenu();

	switch (position)
	{
		case POSITION_MAIN_MENU:		
			ShowMainMenu();
			break;
		
		case POSITION_MENU:		
			ShowGameMenu();
			break;
		
		case POSITION_OPTIONS:		
			ShowOptions();
			break;
		
		case POSITION_SOUND:		
			ShowSound();
			break;
		
		
	}

		ResetColors();
		SetColor();
}

void Menu::HideMenu()
{
	_textgen.setInfinity("RESUME", false);
	_textgen.setInfinity("OPTIONS", false);
	_textgen.setInfinity("MAIN", false);
	_textgen.setInfinity("EXIT", false);
		
}

void Menu::HideOptions()
{
	_textgen.setInfinity("SOUND", false);
	_textgen.setInfinity("BACK", false);
}

void Menu::HideSound()
{
	_textgen.setInfinity("MUTE", false);
	_textgen.setInfinity("MUTE VALUE", false);
	_textgen.setInfinity("VOLUME", false);
	_textgen.setInfinity("VOLUME LVL", false);
	_textgen.setInfinity("BACK", false);
}


void Menu::Close()
{
	switch (position)
	{
		case POSITION_MENU:
			HideMenu();
			break;
		case POSITION_OPTIONS:
			HideOptions();
			break;
		case POSITION_SOUND:
			HideSound();
			break;
	}

	_isclosing = true;

	setGameMenu();
	setOptions();
	setSoundOptions();
	setPosition();
}

void Menu::Open()
{
	gameEngineState = State::MENU;
	position = ActualPosition::POSITION_MENU;
}

bool Menu::isClosed()
{
	return _isclosing;
}

void Menu::setClosed(bool close)
{
	_isclosing = close;
}

void Menu::ShowGameMenu()
{
	// RESUME - GAME MENU
	_textgen.setText("RESUME", "RESUME", Vec2d(xratio, menuy), 0, Vec2d(0.07, 0.10));
	_textgen.setInfinity("RESUME", true);

	// OPTIONS - GAME MENU
	_textgen.setText("OPTIONS", "OPTIONS", Vec2d(xratio - 0.2, 1 * yratio + menuy), 0, Vec2d(0.07, 0.10));
	_textgen.setInfinity("OPTIONS", true);

	// BACK TO MAIN MENU
	_textgen.setText("MAIN", "MAIN MENU", Vec2d(xratio - 0.55, 2 * yratio + menuy), 0, Vec2d(0.07, 0.10));
	_textgen.setInfinity("MAIN", true);

	// GAME EXIT
	_textgen.setText("EXIT", "EXIT", Vec2d(xratio + 0.3, 3 * yratio + menuy), 0, Vec2d(0.07, 0.10));
	_textgen.setInfinity("EXIT", true);

	// GAME MENU COLOR RESET
	_textgen.setColor("RESUME", glm::vec4(1.0, 1.0, 1.0, 1.0));
	_textgen.setColor("OPTIONS", glm::vec4(1.0, 1.0, 1.0, 1.0));
	_textgen.setColor("MAIN", glm::vec4(1.0, 1.0, 1.0, 1.0));
	_textgen.setColor("EXIT", glm::vec4(1.0, 1.0, 1.0, 1.0));
}

void Menu::ShowMainMenu()
{
}

void Menu::ShowOptions()
{
	// GAME SOUNDS
	_textgen.setText("SOUND", "SOUND", Vec2d(xratio + 0.15, 1 * yratio + menuy), 0, Vec2d(0.07, 0.10));
	_textgen.setInfinity("SOUND", true);

	// GAME BACK
	_textgen.setText("BACK", "BACK", Vec2d(xratio + 0.3, 2 * yratio + menuy), 0, Vec2d(0.07, 0.10));
	_textgen.setInfinity("BACK", true);

	// OPTIONS COLOR RESET
	_textgen.setColor("SOUND", glm::vec4(1.0, 1.0, 1.0, 1.0));
	_textgen.setColor("BACK", glm::vec4(1.0, 1.0, 1.0, 1.0));
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

	// SOUND MUTE
	_textgen.setText("MUTE", "MUTE:", Vec2d(xratio + 0.3, 1 * yratio + menuy), 0, Vec2d(0.07, 0.10));
	_textgen.setInfinity("MUTE", true);

	// MUTE ON/OFF
	_textgen.setText("MUTE VALUE", mute, Vec2d(xratio + offsetX, 1 * yratio + menuy), 0, Vec2d(0.07, 0.10));
	_textgen.setInfinity("MUTE VALUE", true);
	
	// SOUND VOLUME
	_textgen.setText("VOLUME", "VOLUME:", Vec2d(xratio, 2 * yratio + menuy), 0, Vec2d(0.07, 0.10));
	_textgen.setInfinity("VOLUME", true);

	// VOLUME LEVEL
	_textgen.setText("VOLUME LVL", volume, Vec2d(xratio + offsetX, 2 * yratio + menuy), 0, Vec2d(0.07, 0.10));
	_textgen.setInfinity("VOLUME LVL", true);

	// BACK
	_textgen.setText("BACK", "BACK", Vec2d(xratio + 0.3, 3 * yratio + menuy), 0, Vec2d(0.07, 0.10));
	_textgen.setInfinity("BACK", true);

	// SOUND COLOR RESET
	_textgen.setColor("MUTE", glm::vec4(1.0, 1.0, 1.0, 1.0));
	_textgen.setColor("MUTE VALUE", glm::vec4(1.0, 1.0, 1.0, 1.0));
	_textgen.setColor("VOLUME", glm::vec4(1.0, 1.0, 1.0, 1.0));
	_textgen.setColor("VOLUME LVL", glm::vec4(1.0, 1.0, 1.0, 1.0));
	_textgen.setColor("BACK", glm::vec4(1.0, 1.0, 1.0, 1.0));
}

void Menu::ResetColors()
{

}

void Menu::SetColor()
{
	if (position == POSITION_MAIN_MENU)
	{
	}
	else if (position == POSITION_MENU)
	{
		switch (gameMenu)
		{
			case GAME_RESUME:			
				_textgen.setColor("RESUME", color);
				break;
			
			case GAME_OPTIONS:			
				_textgen.setColor("OPTIONS", color);
				break;
			
			case GAME_TOMAIN:			
				_textgen.setColor("MAIN", color);
				break;
			
			case GAME_EXIT:			
				_textgen.setColor("EXIT", color);
				break;
			
		}
	}
	else if (position == POSITION_OPTIONS)
	{
		switch (options)
		{
			case GAME_OPTIONS_SOUND:	
				_textgen.setColor("SOUND", color);
				break;
			
			case GAME_OPTIONS_BACK:	
				_textgen.setColor("BACK", color);
				break;
			
		}
	}
	else if (position == POSITION_SOUND)
	{
		switch (soundoptions)
		{
			case GAME_SOUND_MUTE:
				_textgen.setColor("MUTE", color);
				_textgen.setColor("MUTE VALUE", color);
				break;
			case GAME_SOUND_VOLUME:
				_textgen.setColor("VOLUME", color);
				_textgen.setColor("VOLUME LVL", color);
				break;
			case GAME_SOUND_BACK:
				_textgen.setColor("BACK", color);
				break;
		}
	}
}
