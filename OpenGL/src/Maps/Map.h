#ifndef MAP_H
#define MAP_H
#include <fstream>
#include <string>
#include <vector>
#include "Tile.h"
class Map
{
public:
	Map()= delete;
	Map(const Map&) = delete;
	Map(std::string FilePath, std::string BitmapsPath);
	~Map();

	//================================================================
	//= Podstawowe Gettery
	//================================================================
	GLuint getWidth() { return _width; };
	GLuint getHeight() { return _height; };
	GLuint getTexture(GLuint x, GLuint y) 
	{ return _textures[_Tiles[y*_width + x].getTextureID()].getID(); };
	Tile::Content getTileContent(GLuint x, GLuint y) 
	{ return _Tiles[y*_width + x].getContent(); };
	bool isObstacle(GLuint x, GLuint y) { return _Tiles[y*_width + x].isSolid(); };

	//================================================================
	//= Podstawowe Settery
	//================================================================
	void setTileContent(GLuint x, GLuint y, Tile::Content content);
	
private:
	std::vector<Tile> _Tiles;		//Przechowuje wszystkie kafelki
	std::vector<Texture> _textures; //Przechwouje wszystkie textury (indeks wektora = idTextury)
	GLuint _width;					//Szerokoœæ Mapy
	GLuint _height;					//Wysokoœæ mapy
	GLuint _nTextures;				//Liczba wszystkich textur
private:
};
#endif
