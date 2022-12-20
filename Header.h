#pragma once

using namespace std;
/*0:Avatar 1:Werewolves 2:Vampires 3:water 4:tree*/
class entity {
public:

	entity(int in_type);
	int get_type();
	friend class map;
	friend class monsters;
private:
	int x;
	int y;
	int type;
};

class avatar : public entity {
public:
	avatar(int in_type, char in_team);
	friend void set_team(char ch, avatar av);
protected:
	char team;
};  


class monsters : public entity {
public:
	monsters(int in_type);
private:
	int dmg;
	int health;
	int healing;
	int shield;
};


class map {
public:
	void create_map(int x, int y);
	void set_map(int x, int y, avatar player, monsters** arrayW, monsters** arrayV,int N);
	void move(monsters** arrayW, monsters** arrayV,int x,int y, int N);
	void printmap(int x,int y);
private:
	entity*** map1;
};
