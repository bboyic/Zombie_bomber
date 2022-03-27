#ifndef UNIT_H
# define	UNIT_H

/*Unit Class*/

#include "Map.h"

enum GoTo{
	LEFT = 'a',
	RIGHT = 'd',
	UP = 'w',
	DOWN = 's'
};

class Unit{
	int		x;
	int		y;
protected:
	float	attackPower;
	float	health;
public:
	Unit();
	Unit(int x, int y);
	Unit(float heath, float attackPower);
	int				getHealth();
	void			damage(float damageStrength);
	virtual int		attack(void) = 0;
	int				getLocation();
	int&			getX();
	int&			getY();
	virtual ~Unit();
	bool	printStatus();
};

class Player: public Unit {
	int		max_x;
	int		max_y;
public:
	Player&	operator+=(int key);
	int		getLocation();
	bool	goToNextStep(int side);
	virtual int		attack(void);
	Player(int max_x, int max_y);
	Player();
	virtual ~Player();
};

class God: public Player{
public:
	God();
	God(int max_x, int max_y);
	int	attack(void);
	~God();
};

class OldMan: public Player{
public:
	OldMan();
	OldMan(int max_x, int max_y);
	int	attack(void);
	~OldMan();
};

class Zombie: public Unit {
public:
	Zombie(int x, int y);
	int	attack(void);
	Zombie();
	~Zombie();
}; 

#endif