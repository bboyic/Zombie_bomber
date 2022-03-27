#include "Unit.h"
#include <iostream>

bool Unit::printStatus(){
	std::cout << "HEALTH: " << health << std::endl;
	std::cout << "ATTACK: " << attackPower << std::endl;
	std::cout << "COORDINATE: " << x << " | " << y << std::endl;
	return (true);
}

Unit::Unit(int x, int y): x(x), y(y), health(10), attackPower(100){
}

Player&	Player::operator+=(int key) {
	goToNextStep(key);
	return (*this);
}

void	Unit::damage(float damageStrength){
	health -= damageStrength;
}

int	Player::attack(void){
	std::cout << "Attaaack!" << std::endl;
	return (attackPower);
}

int	Zombie::attack(void){
	std::cout << "braaain\n";
	return (attackPower);
}

int	God::attack(void){
	std::cout << "holy attack\n";
	return (attackPower);
}

int	OldMan::attack(void){
	std::cout << "Old man punch\n";
	return (attackPower);
}

int	Unit::getHealth(){return (health);}

int&	Unit::getX() {return(x);}

int&	Unit::getY() {return(y);}

bool	Player::goToNextStep(int side){
	if (side == UP && this->getY() > 0)
		--(this->getY());
	if (side == DOWN && this->getY() + 1 < max_y)
		++(this->getY());
	if (side == LEFT && this->getX() > 0)
		--(this->getX());
	if (side == RIGHT && this->getX() + 1 < max_x)
		++(this->getX());
	return (true);
}

int	Player::getLocation(){
	return ((this->getY() * (max_x + 1)) + this->getX());
}

Zombie::Zombie(int x, int y): Unit(x, y){}

Zombie::Zombie(): Unit(0, 0){}

Zombie::~Zombie(){}

Player::Player(){}

Player::~Player(){}

Player::Player(int max_x, int max_y): max_x(max_x), max_y(max_y){}

God::God(int max_x, int max_y): Player(max_x, max_y){
	health = 1000;
	attackPower = 100;
}

God::~God(){}

OldMan::OldMan(int max_x, int max_y): Player(max_x, max_y){
	health = 20;
	attackPower = 1;
}

OldMan::~OldMan(){}

Unit::Unit(): attackPower(5), health(100), x(0), y(0){}

Unit::~Unit(){}