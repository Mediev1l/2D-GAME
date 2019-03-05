#include "GameEngine.h"

GameEngine::GameEngine()
	:
	  window(nullptr)
	, renderer(nullptr)
	, t()
	, SCR_WIDTH(800)
	, SCR_HEIGHT(800)
	, lastX(SCR_WIDTH / 2.0)
	, lastY(SCR_HEIGHT / 2.0)
	, firstMouse(true)
	, WindowName("Kacp3r3 & Bartek Playground")
	, delay(1)
	, camera(6,6)
{
}

void GameEngine::Game_Init()
{
	
	try {

		//================================================================
		//= Initialize GLFW and force to use 3.3 OpenGL
		//================================================================
		glfwInit();
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


		//================================================================
		//= Creating the Window
		//================================================================
		window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Hello World", NULL, NULL);
		if (!window)
		{
			glfwTerminate();
			//return -1; void nie zwraca
		}

		/* Make the window's context current */
		glfwMakeContextCurrent(window);

		//Fps lock
		//glfwSwapInterval(2);


		//================================================================
		//= Glew Initialization
		//================================================================
		if (glewInit() != GLEW_OK)
			std::cout << "ERROR";


		std::cout << glGetString(GL_VERSION) << std::endl;

		renderer = new Renderer(camera);
		_map = &renderer->getMap();
	}
	catch (std::runtime_error &e)
	{
		std::cout << e.what();
		int a;
		std::cin >> a;
	}

	//PLAYER ADDED HERE
	_characters.push_back(Hero(7.0, 7.0, 3.0, 0.8, "res/Sprites/Player/issac.png","res/Sprites/Tears/basic_tear.png"));
	_characters.push_back(Enemy(1.0, 6.0, 1.0, 0.8, "res/Sprites/Enemies/Skelly/skelly.png", "res/Sprites/Tears/basic_tear.png"));
	_characters.push_back(Enemy(4.0, 3.0, 1.0, 0.8, "res/Sprites/Enemies/Zombie/zombie.png", "res/Sprites/Tears/basic_tear.png"));
	camera.initCamera(_characters[0].getPos(),_map->getWidth(),_map->getHeight());
	//ITEMS Na razie jeden na sztywno || pozniej vektor wczytanych itemow z pliku
	//Na sztywno ustawianie na mapie ze jest tam item
	_items.emplace_back("res/Sprites/Items/", "res/Items/", 0);
	_items[0].setX(5);
	_items[0].setY(7);
	_map->setTileContent(5, 7, Tile::Content::Item);

	//HARDCODE
	_characters[0].setRange(50);

}

void GameEngine::Game_Run()
{

	// Game  Initialization
	Game_Init();

	


	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{

		//Providing delta Time
		t.Mark();
		while (t.getDelta() <= t.getSingleFrameTime())
		{
			t.Mark();
		}
		//Updating Label name
		std::string a = WindowName + " FPS: " + std::to_string((int)round(1 / t.getDelta()));
		glfwSetWindowTitle(window, a.c_str());

		// input
		// -----
		processInput();
		camera.UpdateCamera(_characters[0].getPos(),_characters[0].getOrigin()/2.0);
		Update();
		ProcessEnemiesMove(t.getDelta()<1.0?t.getDelta():0.01);

		//Renderowanie || rozdzielone by gracz byl rysowany na koncu
		renderer->RenderMap(camera);
		renderer->RenderItems(_items, camera);
		renderer->RenderCharacter(_characters, camera);
	
		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		/* Poll for and process events */
		glfwPollEvents();
	}

	glfwTerminate();
}


void GameEngine::processInput()
{

	//Debug info
	if (glfwGetKey(window, GLFW_KEY_P) == GLFW_PRESS)
	{
		std::cout << "PlayerX: " << _characters[0].getPos().getX() << '\n';
		std::cout << "PlayerY: " << _characters[0].getPos().getX() << '\n';
		//std::cout << "PlayerVelocity: " << _characters[0].getVelocity() << '\n';
		std::cout << "VectorX: " << camera.getTranslate()._x << '\n';
		std::cout << "VectorY: " << camera.getTranslate()._y << '\n';
		//for (size_t i = 0; i < _characters[0].getPifPafSize(); i++)
			//std::cout << "Bullet:" << i << " X: " << _characters[0].getOnepiFpaF((GLuint)i)._position.getX() << " Y:" << _characters[0].getOnepiFpaF((GLuint)i)._position.getY() << '\n';
		//std::cout << "boots: " << _items[0].getMovementSpeed() << '\n';
	}
	//Closing Window
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//PickupItems
	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{
		if (_canPickup)
		{
			ProcessItemPickup();
		}
	}

	if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
	{
		_characters[0].setSide(Character::UP);
		ProcessPlayerShoot();
	}
	if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
	{
		_characters[0].setSide(Character::DOWN);
		ProcessPlayerShoot();
	}
	if (glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS)
	{
		_characters[0].setSide(Character::LEFT);
		ProcessPlayerShoot();
	}
	if (glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS)
	{
		_characters[0].setSide(Character::RIGHT);
		ProcessPlayerShoot();
	}

	//MovementProcessor
	double deltaTime = t.getDelta();
	if ( glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
	{
		ProcessPlayerMove(deltaTime, Direction::UP);
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
	{
		ProcessPlayerMove(deltaTime, Direction::DOWN);
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
	{
		ProcessPlayerMove(deltaTime, Direction::LEFT);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
	{
		ProcessPlayerMove(deltaTime, Direction::RIGHT);
	}

	if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
	{

	}

	//Fun
	if (glfwGetKey(window, GLFW_KEY_1) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	if (glfwGetKey(window, GLFW_KEY_2) == GLFW_PRESS)
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	if (glfwGetKey(window, GLFW_KEY_O) == GLFW_PRESS)
	{
		CloseDoors();
	}
	if (glfwGetKey(window, GLFW_KEY_I) == GLFW_PRESS)
	{
		OpenDoors();
	}
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void GameEngine::framebuffer_size_callback(int width, int height)
{
	// make sure the viewport matches the new window dimensions; note that width and 
	// height will be significantly larger than specified on retina displays.
	glViewport(0, 0, width, height);
}


// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void GameEngine::mouse_callback(double xpos, double ypos)
{
	if (firstMouse)
	{
		lastX = xpos;
		lastY = ypos;
		firstMouse = false;
	}

	double xoffset = xpos - lastX;
	double yoffset = lastY - ypos; // reversed since y-coordinates go from bottom to top

	lastX = xpos;
	lastY = ypos;

	//camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void GameEngine::scroll_callback(double xoffset, double yoffset)
{
	//camera.ProcessMouseScroll(yoffset);
}

void GameEngine::ProcessPlayerMove(double deltaTime, Direction dir)
{
	//Zmienne upraszczaj¹ce kod
	double px = _characters[0].getTile().getPos()._x;
	double py = _characters[0].getTile().getPos()._y;
	double pv = _characters[0].getVelocity();
	double newX = px;
	double newY = py;

	//Ustaw flage na 0
	_canPickup = false;

	switch (dir)
	{
		case UP:
		{
			newY -= deltaTime * pv;
			break;
		}
		case DOWN:
		{
			newY += deltaTime * pv;
			break;
		}
		case LEFT:
		{
			newX -= deltaTime * pv;
			break;
		}
		case RIGHT:
		{
			newX += deltaTime * pv;
			break;
		}
	}

	if (newX < 0)newX = 0;
	if (newY < 0)newY = 0;

	CheckColissions(_characters[0], 0, newX, newY);

	if (!CheckColissions(_characters[0], 0, newX, newY))
	{
		_characters[0].setX(newX);
		_characters[0].setY(newY);
	}
}


void GameEngine::ProcessItemPickup()
{
	double px = _characters[0].getTile().getPos().getX();
	double py = _characters[0].getTile().getPos().getY();

	GLuint nearestid=-1;
	double distance=100.0;
	for (GLuint i = 0; i < _items.size(); ++i)
	{
		if (_items[i].getOnMap())
		{
			double localdist = abs(_items[i].getX() - px) + abs(_items[i].getY() - py);
			if (localdist < distance)
			{
				distance = localdist;
				nearestid = i;
			}
		}
	}
	
	if (nearestid != -1)
	{
		_characters[0].consumeItem(_items[nearestid]);
		_items[nearestid].setOnMap(false);
		_map->setTileContent((GLuint)_items[nearestid].getX(), (GLuint)_items[nearestid].getY(), Tile::Content::Nothing);
	}
}

void GameEngine::ProcessPlayerShoot()
{
	double px =_characters[0].getTile().getPos().getX();
	double py = _characters[0].getTile().getPos().getY();
	
	Character::Dir  pdir = _characters[0].getSide();
	std::vector<Projectile>& temp = _characters[0].getpiFpaF();

	if (delay <= 0.0f)
	{
		delay = 1.0;
	}
	if (delay == 1.0)
	{
		switch (pdir)
		{
		case UP:
		{
			temp.emplace_back(1, px, py - 0.1, 2, 0, Projectile::Dir::UP, true);
			break;
		}
		case DOWN:
		{
			temp.emplace_back(1, px, py + 0.1, 2, 0, Projectile::Dir::DOWN, true);
			break;
		}
		case LEFT:
		{
			temp.emplace_back(1, px - 0.1, py, 2, 0, Projectile::Dir::LEFT, true);
			break;
		}
		case RIGHT:
		{
			temp.emplace_back(1, px + 0.1, py - 0.1, 2, 0, Projectile::Dir::RIGHT, true);
			break;
		}

		}
	}
}


void GameEngine::Update()
{
	// Update pociskow
	std::vector<Projectile>& temp = _characters[0].getpiFpaF();
	double deltaTime = t.getDelta();

	// Tu mo¿na daæ mniejsz¹ wartosc i mnozyc * att speed 
	delay -= deltaTime;

	for (int i = 0; i < temp.size(); i++)
	{
		Projectile::Dir pdir = temp[i].getSide();
		double tempV = temp[i].Velocity;
		
		if (temp[i].getElapdedDistance() < _characters[0].getRange() / 10)
		{

			switch (pdir)
			{
				case UP:
				{
					temp[i]._position.setY(temp[i]._position.getY() - deltaTime * tempV) ;
					temp[i].setElapsedDistance(temp[i].getElapdedDistance() + deltaTime * tempV);
					break;
				}
				case DOWN:
				{
					temp[i]._position.setY(temp[i]._position.getY ()+deltaTime * tempV) ;
					temp[i].setElapsedDistance(temp[i].getElapdedDistance() + deltaTime * tempV);
					break;
				}
				case LEFT:
				{
					temp[i]._position.setX(temp[i]._position.getX()- deltaTime * tempV) ;
					temp[i].setElapsedDistance(temp[i].getElapdedDistance() + deltaTime * tempV);
					break;
				}
				case RIGHT:
				{
					temp[i]._position.setX(temp[i]._position.getX() + deltaTime * tempV) ;
					temp[i].setElapsedDistance(temp[i].getElapdedDistance() + deltaTime * tempV);
					break;
				}
				
			}
			if (CheckCollisionsBullet(temp[i], 0, temp[i].getX(), temp[i].getY()))
			{
				temp[i].setExistance(false);
				temp.erase(temp.begin() + i);
				i -= 1;
			}

		}
		else
		{
			temp[i].setExistance(false);
			temp.erase(temp.begin() + i);
		}
	}
}

void GameEngine::ProcessEnemiesMove(double deltaTime)
{
	//Zmienne upraszczaj¹ce kod
	double px = _characters[0].getTile().getPos().getX();
	double py = _characters[0].getTile().getPos().getY();
	for (GLuint i = 1; i < (GLuint)_characters.size(); ++i)
	{
		double mx = _characters[i].getTile().getPos().getX();
		double my = _characters[i].getTile().getPos().getY();
		double mv = _characters[i].getVelocity();
		Vec2d Move(_characters[i].getTile().getPos().getX() - px, _characters[i].getTile().getPos().getY() - py);
		
		//Potrzebne zmienne
		bool move1 = true;
		bool move2 = true;
		double newX = mx;
		double newY = my;


		//Trochê Matmy
		double VelLength = Move.getLength();
		double HowMuchInX = abs(Move.getX() / VelLength);
		double HowMuchInY = abs(Move.getY() / VelLength);


		//Rozpatrzmy kierunki
		Direction dir[2];
		const double margin = 0.1;
		dir[0] = CalculateDirection(Move.getX(),false, margin);
		dir[1] = CalculateDirection(Move.getY(),true, margin);

		for(GLuint i=0;i<2;i++)
		{
			switch (dir[i])
			{
			case UP:
			{
				newY -= deltaTime * mv * HowMuchInY;
				break;
			}
			case DOWN:
			{
				newY += deltaTime * mv* HowMuchInY;
				break;
			}
			case LEFT:
			{
				newX -= deltaTime * mv* HowMuchInX;
				break;
			}
			case RIGHT:
			{
				newX += deltaTime * mv* HowMuchInX;
				break;
			}
			case NONE:
			{
				break;
			}
			}
		}

		//Safety checks
		if (newY < 0)newY = 0;
		if (newX < 0)newX = 0;
		if (newX > _map->getWidth() - 1) newX = _map->getWidth();
		if (newY > _map->getHeight() - 1) newY = _map->getHeight();
		//Check in X
		move1 = !CheckColissions(_characters[i], i, newX, my);
		//Check in Y
		move2 = !CheckColissions(_characters[i], i, mx, newY);


		//Wykonaj ruch
			if (move1)
			{
				//Je¿eli w drug¹ stronie nie ma ruchu
				if (!move2)
				{
					//Policz czy jest sens i dodaj do pierwotnego kierunku
					double value = mv * deltaTime*HowMuchInY;
					if (dir[0] == LEFT)
					{
						if(value>0.05 && !CheckColissions(_characters[i],i,newX-value,my)) newX -= value;
					}
					else
					{
						if (value > 0.05 && !CheckColissions(_characters[i], i, newX + value, my)) newX += value;
					}
					
				}
				_characters[i].setX(newX);
			}
			if (move2)
			{
				if (!move1)
				{
					double value = mv * deltaTime*HowMuchInX;
					if (dir[1] == UP)
					{
						if (value > 0.05&&!CheckColissions(_characters[i], i, mx, newY-value)) newY -= value;
					}
					else
					{
						if (value > 0.05&&!CheckColissions(_characters[i], i, mx, newY + value)) newY += value;
					}
				}
				_characters[i].setY(newY);
			}
	}
	
}

void GameEngine::OpenDoors()
{
	GLuint x = (GLuint)ceil(_map->getWidth() / 2.0) - 1;
	GLuint y = (GLuint)ceil(_map->getHeight() / 2.0) - 1;
	GLuint id[] = { x,0,0,y,_map->getWidth() - 1,y };

	for (GLuint i = 0; i < 6; i+=2)
	{
		_map->setTileContent(id[i], id[i + 1], Tile::Content::Doors);
	}
	renderer->OpenDoors();
}

void GameEngine::CloseDoors()
{
	GLuint x = (GLuint)ceil(_map->getWidth() / 2.0) - 1;
	GLuint y = (GLuint)ceil(_map->getHeight() / 2.0) - 1;
	GLuint id[] = { x,0,0,y,_map->getWidth() - 1,y };

	for (GLuint i = 0; i < 6; i += 2)
	{
		_map->setTileContent(id[i], id[i + 1], Tile::Content::Obstacle);
	}
	renderer->CloseDoors();
}

GameEngine::Direction GameEngine::CalculateDirection(double x, bool pionowo, double margin)
{
	if (!pionowo)
	{
		if (abs(x) > margin)
		{
			if (x > 0) return LEFT;
			else return  RIGHT;
		}
		else return  NONE;
	}
	else
	{
		if (abs(x) > margin)
		{
			if (x > 0) return UP;
			else return DOWN;
		}
		else return  NONE;
	}
}

bool GameEngine::CheckColissions(const Character & obj, GLuint index, double x, double y)
{
	//Some utility variables
	auto getIndex = [&](GLuint x, GLuint y) { return y * _map->getWidth() + x; };
	GLuint xx = (GLuint)floor(x);
	GLuint yy = (GLuint)floor(y);
	//Safety checks
	if (xx < 1)xx = 1;
	if (yy < 1)yy = 1;
	//if (xx + 2 > _map->getWidth())xx = _map->getWidth() - 1;
	//if (yy + 2 > _map->getHeight())yy = _map->getHeight() - 1;

	//Check map Around Character
	std::vector<GLuint>indexesToCheck = {getIndex(xx-1,yy-1),getIndex(xx,yy-1),getIndex(xx+1,yy - 1),
								  getIndex(xx - 1,yy),getIndex(xx,yy),getIndex(xx + 1,yy),
								  getIndex(xx - 1,yy + 1),getIndex(xx,yy + 1),getIndex(xx + 1,yy + 1) };
	std::vector<GLuint>indexes;
	Tile tmp(true, Tile::Content::Player, Vec2d(x, y), 0, obj.getOrigin());
	for (GLuint i = 0; i < indexesToCheck.size(); ++i)
	{
		if (ShapeOverlap_DIAGS(tmp, _map->getTile((GLuint)indexesToCheck[i])))
		{
			indexes.push_back(indexesToCheck[i]);
		}
	}

	for (GLuint i = 0; i < indexes.size(); ++i)
	{
		//std::cout << "Kolizja!" << '\n';
		switch (_map->getTileContent(indexes[i]))
		{
			//Nigdy sie nie wydarzy ale co tam
		case Tile::Content::Nothing:
		{
			break;
		}
		case Tile::Content::Character:
		case Tile::Content::Obstacle:
		{
			//Tutaj return
			return true;
			break;
		}
		case Tile::Content::Item:
		{
			//Tutaj proces przechwycenia itemka
			if (index == 0)_canPickup = true;
			break;
		}
		case Tile::Content::Doors:
		{
			if (index == 0) break;
			return true;
		}
		default:
			break;
		}
	}

	//a teraz kolizje z innymi characterami
	for (GLuint j = 0; j < _characters.size(); ++j)
	{
		if (j != index) if (ShapeOverlap_DIAGS(tmp, _characters[j].getTile())) return true;
	}

	return false;
}

//One Lone Coder Overlapping Algorithm
bool GameEngine::ShapeOverlap_DIAGS(Tile &r1, Tile &r2)
{
	Tile *poly1 = &r1;
	Tile *poly2 = &r2;

	for (int shape = 0; shape < 2; shape++)
	{
		if (shape == 1)
		{
			poly1 = &r2;
			poly2 = &r1;
		}

		// Check diagonals of polygon...
		for (GLuint p = 0; p < poly1->getVertexCount(); p++)
		{
			Vec2d line_r1s = poly1->getPos();
			Vec2d line_r1e = poly1->getVertex(p);

			// ...against edges of the other
			for (GLuint q = 0; q < poly2->getVertexCount(); q++)
			{
				Vec2d line_r2s = poly2->getVertex(q);
				Vec2d line_r2e = poly2->getVertex((q + 1) % poly2->getVertexCount());

				// Standard "off the shelf" line segment intersection
				double h = (line_r2e.getX() - line_r2s.getX()) * (line_r1s.getY() - line_r1e.getY()) - (line_r1s.getX() - line_r1e.getX()) * (line_r2e.getY() - line_r2s.getY());
				double t1 = ((line_r2s.getY() - line_r2e.getY()) * (line_r1s.getX() - line_r2s.getX()) + (line_r2e.getX() - line_r2s.getX()) * (line_r1s.getY() - line_r2s.getY())) / h;
				double t2 = ((line_r1s.getY() - line_r1e.getY()) * (line_r1s.getX() - line_r2s.getX()) + (line_r1e.getX() - line_r1s.getX()) * (line_r1s.getY() - line_r2s.getY())) / h;

				if (t1 >= 0.0f && t1 < 1.0f && t2 >= 0.0f && t2 < 1.0f)
				{
					return true;
				}
			}
		}
	}
	return false;
}

bool GameEngine::CheckCollisionsBullet(const Projectile & bullet, GLuint index, double x, double y)
{
	//Some utility variables
	auto getIndex = [&](GLuint x, GLuint y) { return y * _map->getWidth() + x; };
	GLuint xx = (GLuint)floor(x);
	GLuint yy = (GLuint)floor(y);
	//Safety checks
	if (xx < 1)xx = 1;
	if (yy < 1)yy = 1;
	//if (xx + 2 > _map->getWidth())xx = _map->getWidth() - 1;
	//if (yy + 2 > _map->getHeight())yy = _map->getHeight() - 1;

	//Check map Around Character
	std::vector<GLuint>indexesToCheck = { getIndex(xx - 1,yy - 1),getIndex(xx,yy - 1),getIndex(xx + 1,yy - 1),
								  getIndex(xx - 1,yy),getIndex(xx,yy),getIndex(xx + 1,yy),
								  getIndex(xx - 1,yy + 1),getIndex(xx,yy + 1),getIndex(xx + 1,yy + 1) };
	std::vector<GLuint>indexes;
	Tile tmp(true, Tile::Content::Player, Vec2d(x, y), 0, bullet.getOrigin());
	for (GLuint i = 0; i < indexesToCheck.size(); ++i)
	{
		if (ShapeOverlap_DIAGS(tmp, _map->getTile((GLuint)indexesToCheck[i])))
		{
			indexes.push_back(indexesToCheck[i]);
		}
	}

	for (GLuint i = 0; i < indexes.size(); ++i)
	{
		//std::cout << "Kolizja!" << '\n';
		switch (_map->getTileContent(indexes[i]))
		{
			//Nigdy sie nie wydarzy ale co tam
		case Tile::Content::Nothing:
		{
			break;
		}
		case Tile::Content::Obstacle:
		{
			//Tutaj return
			return true;
			break;
		}
		case Tile::Content::Item:
		{
			//Tutaj proces przechwycenia itemka
			break;
		}
		case Tile::Content::Doors:
		{
			return true;
		}
		default:
			break;
		}
	}

	//a teraz kolizje z innymi characterami
	for (GLuint j = 1; j < _characters.size(); ++j)
	{
		if (ShapeOverlap_DIAGS(tmp, _characters[j].getTile()))
		{
			if (_characters[j].TakeDamage(bullet))
			{
				_characters.erase(_characters.begin() + j);
				j -= 1;
			}
			return true;
		}
	}

	return false;
}
