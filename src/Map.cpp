#include "Map.h"

Map::Map(std::string map):map(map), sizeX(map.find('\n')), sizeY(map.length() / sizeX){
}

Map::~Map(){}

char& Map::operator[](int index){
	return (map[index]);
}

int	Map::getWidth(){return (sizeX);}

int Map::getHeight(){return (sizeY);}

std::string	Map::getMap(){return (map);}