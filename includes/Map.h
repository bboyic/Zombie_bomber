#ifndef MAP_H
# define	MAP_H

/* MAP CLASS */
#include "main.h"

class Map {
	std::string			map;
	int					sizeX;
	int					sizeY;
public:
	Map(std::string map);
	~Map();
	char& operator[](int index);
	int			getWidth();
	int			getHeight();
	std::string	getMap();
};

#endif