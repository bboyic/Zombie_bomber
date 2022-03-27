#include "main.h"

std::string	readMap(char *pathToMap){
	std::string		map;
	std::string		temp;
	std::ifstream	fin;

	fin.open(pathToMap);
	if (!fin.is_open())
		return (std::string("ERROR"));
	while (!fin.eof()){
		fin >> temp;
		map += temp + '\n';
	}
	fin.close();
	return (map);
}

bool checkX(std::string map){
	int standart = map.find('\n');
	int	x = 0;

	for (int index = 0; index < map.length(); ++index)
	{
		x = 0;
		while (map[index] != '\0' && map[index] != '\n'){
			if (map[index] != 'o' && map[index] != 'z' && map[index] != 'b')
				return (false);
			++index;
			++x;
		}
		if (standart != x || !standart)
			return (false);
	}
	return (true);
}

Map	parser(int argc, char **argv){
	std::string	stringMap;

	if (argc != 2)
		return (Map("ERROR"));
	stringMap = readMap(argv[1]);
	if (!checkX(stringMap))
		return (Map("ERROR"));

	Map map(stringMap);
	return (map);
}

void	printMap(Map map){
	for (int i = 0; i < map.getMap().length(); ++i){
		if (map.getMap()[i] == 'o')
			std::cout << "\u001b[44m" << " " << "\u001b[0m";
		else
			std::cout << map.getMap()[i];
	}
}

bool	checkAttack(Player*& player, std::vector <Zombie> &zombies, char key){
	for (int i = 0; i < zombies.size(); ++i){
		if (key == '1' && player->getX() - 1 == zombies[i].getX() && player->getY() == zombies[i].getY() && zombies[i].getHealth() > 0)
			zombies[i].damage(player->attack());
		if (key == '2' && player->getX() == zombies[i].getX() && player->getY() - 1 == zombies[i].getY() && zombies[i].getHealth() > 0)
			zombies[i].damage(player->attack());
		if (key == '3' && player->getX() + 1 == zombies[i].getX() && player->getY() == zombies[i].getY() && zombies[i].getHealth() > 0)
			zombies[i].damage(player->attack());
		if (key == '4' && player->getX() == zombies[i].getX() && player->getY() + 1 == zombies[i].getY() && zombies[i].getHealth() > 0)
			zombies[i].damage(player->attack());
	}
	return (true);
}

char	gamePlay(Player*& player, Map map, std::vector <Zombie> &zombies){
	char	key;
	int		location = player->getLocation();

	std::cin >> key;
	system("clear");
	checkAttack(player, zombies, key);
	*player += key;
	if (map[player->getLocation()] == 'b')
		player->damage(30);
	if (map[player->getLocation()] == 'z')
		player->damage(zombies[0].attack());
	map[player->getLocation()] = '^';
	player->printStatus();
	printMap(map.getMap());
	if (player->getHealth() <= 0){
		std::cout << "You dead\n";
		key = 'q';
	}
	return (key);
}

bool	checkZombie(int x, int y, Map map){
	int	position = (y * (map.getWidth() + 1)) + x;

	if (map.getMap()[position] == 'z')
		return (true);
	return (false);
}

std::vector <Zombie>	findZombies(Map map){
	std::vector <Zombie>	zombies;

	for (int y = 0; y < map.getHeight(); ++y)
		for (int x = 0; x < map.getWidth(); ++x)
			if (checkZombie(x, y, map))
				zombies.push_back(Zombie(x, y));
	return (zombies);
}

void	checkDeadZombies(std::vector <Zombie> zombies, Map& map){
	for (int i = 0; i < zombies.size(); ++i){
		if (zombies[i].getHealth() <= 0)
			map[(zombies[i].getY() * (map.getWidth() + 1)) + zombies[i].getX()] = 'o';
	}
}

int	chooseClass( void ){
	char	playerClass = 0;

	while (playerClass < '0' || playerClass > '3')
	{
		std::cout << "Choose a class\n \
		1) Simple Player\n \
		2) God\n \
		3) Old man\n";
		std::cin >> playerClass;
		if (playerClass < '0' || playerClass > '3')
			std::cout << "Wrong answer\n";
	}
	return (playerClass - 48);
}

void	allocatedPlayer(Player *&player, Map map, int playerClass){
	if (playerClass == 1)
		player = new Player(map.getWidth(), map.getHeight());
	if (playerClass == 2)
		player = new God(map.getWidth(), map.getHeight());
	if (playerClass == 3)
		player = new OldMan(map.getWidth(), map.getHeight());
	std::cout << player->getHealth() << std::endl;
}

int	start(Map map){
	Player		*player;
	std::vector <Zombie>	zombies;
	char		key = 0;

	if (map.getMap() == std::string("ERROR"))
		return (1);
	allocatedPlayer(player, map, chooseClass());
	zombies = findZombies(map);
	std::cout << "Press the key to start the game\n";
	while (key != 'q')
	{
		key = gamePlay(player, map, zombies);
		checkDeadZombies(zombies, map);
	}
	delete player;
	return (0);
}

int	main( int argc, char **argv ){
	return (start(parser(argc, argv)));
}