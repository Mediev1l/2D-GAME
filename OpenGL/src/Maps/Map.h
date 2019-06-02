#ifndef MAP_H
#define MAP_H
#include <fstream>
#include <string>
#include <vector>
#include "Tile.h"
//#include "AssetManager/AssetManager.h"
class AssetManager;
class Map
{
public:
	Map(const Map&) = delete;
	Map();
	~Map();

	void Create(std::string name, std::string lvldatapath, Texture * text);
	std::string sName;
	//================================================================
	//= Podstawowe Gettery
	//================================================================
	GLuint getWidth() { return _width; };
	GLuint getHeight() { return _height; };
	bool GetSolid(GLuint x, GLuint y) { return _Tiles[size_t(y*_width + x)].GetSolid(); };
	Vec2d& getTilePos(GLuint x, GLuint y) { return _Tiles[size_t(y*_width + x)].GetPos(); };
	Vec2d& getTilePos(GLuint i) { return _Tiles[i].GetPos(); };
	Tile& getTile(GLuint i) { return _Tiles[i]; };
	Tile& getTile(GLuint x, GLuint y) { return _Tiles[size_t(y*_width+x)]; };
	GLuint getSize() { return (GLuint)_Tiles.size(); };
	Texture* getTexture() { return _texture; };

	//================================================================
	//= Podstawowe Settery
	//================================================================
	void LoadLevel(std::vector<std::pair<int, bool>> lvl);
	void setWidth(GLuint w) { _width = w; }
	void setHeight(GLuint w) { _height = w; }


private:
	std::vector<Tile> _Tiles;		//Przechowuje wszystkie kafelki
	Texture* _texture;
	//std::vector<Texture> _textures; //Przechwouje wszystkie textury (indeks wektora = idTextury)
	GLuint _width;					//Szerokoœæ Mapy
	GLuint _height;					//Wysokoœæ mapy
	//GLuint _nTextures;				//Liczba wszystkich textur
private:
};

class Map_Basement : public Map
{
public:
	Map_Basement();
};
#endif
