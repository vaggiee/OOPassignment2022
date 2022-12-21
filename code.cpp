#include <iostream>
#include <cstdlib>
#include <conio.h>
#include "Header.h"
#pragma once

//Entity constructor
entity::entity(int in_type) {
	type = in_type;
	x = rand() % 10;
	y = rand() % 10;
}

//Returns entity type
int entity::get_type() {
	return type;
}

//Monsters constructor
monsters::monsters(int in_type) :entity(in_type) {
	dmg = 1 + rand() % 3;
	health =5;
	healing = rand() % 3;
	shield = 1 + rand() % 2;
}

//Avatar constructor
avatar::avatar(int in_type, char in_team) :entity(in_type) {
	team = in_team;
}

//Sets avatars team
void set_team(char ch, avatar av) {
	av.team = ch;
}

//Map accessors
int map::get_deadW() {
	return deadW;
}
int map::get_deadV() {
	return deadV;
}

/*Create a 2d array of pointers*/
void map::create_map(int x, int y) {

	map1 = new entity **[x];
	for (int i = 0; i < x; i++) {

		map1[i] = new entity * [y];

		for (int j = 0; j < y; j++) {

			map1[i][j] = NULL;
		}
	}
}

/*Place entities in the map*/
void map::set_map(int x, int y,avatar player,monsters** arrayW, monsters** arrayV,int N) {
	int i = rand() % x;
	int j = rand() % y;
	map1[i][j] = &player;
	player.x = i;
	player.y = j;

/*Place objects*/
	for(int t=3;t<5;t++)
	{
		for (int i = 0; i < N; i++) {
			entity* object= new entity(t);
			while(1) {
				int k = rand() % x;
				int j = rand() % y;
				if(map1[k][j]==NULL) {
					map1[k][j] =object;
					break;
				}
			}
		}
	}
/*Place monsters*/
		for (int i = 0; i < N; i++) {
			while (1) {
				int k = rand() % x;
				int j = rand() % y;
				if (map1[k][j] == NULL) {
					map1[k][j] = arrayW[i];
					arrayW[i]->x = k;
					arrayW[i]->y = j;
					break;
				}
			}
		}
		for (int i = 0; i < N; i++) {
			while (1) {
				int k = rand() % x;
				int j = rand() % y;
				if (map1[k][j] == NULL) {
					map1[k][j] = arrayV[i];
					arrayV[i]->x = k;
					arrayV[i]->y = j;
					break;
				}
			}
		}
}

//Moves monsters
void map::move(monsters** arrayW, monsters** arrayV, int x, int y,int N) {

	//Move werewolves
	for (int i = 0; i < N; i++) {
		if (arrayW[i] != NULL) {
			int t = rand() % 4;
			switch (t) {
			case 0:
				if ((arrayW[i]->x - 1) > 0 &&
					map1[arrayW[i]->x - 1][arrayW[i]->y] == NULL) {

					map1[arrayW[i]->x][arrayW[i]->y] = NULL;
					arrayW[i]->x = arrayW[i]->x - 1;
					map1[arrayW[i]->x][arrayW[i]->y] = arrayW[i];
					break;
				}
			case 1:
				if ((arrayW[i]->y - 1) > 0 &&
					map1[arrayW[i]->x][arrayW[i]->y - 1] == NULL) {

					map1[arrayW[i]->x][arrayW[i]->y] = NULL;
					arrayW[i]->y = arrayW[i]->y - 1;
					map1[arrayW[i]->x][arrayW[i]->y] = arrayW[i];
					break;
				}
			case 2:
				if ((arrayW[i]->x + 1) != x &&
					map1[arrayW[i]->x + 1][arrayW[i]->y] == NULL) {

					map1[arrayW[i]->x][arrayW[i]->y] = NULL;
					arrayW[i]->x = arrayW[i]->x + 1;
					map1[arrayW[i]->x][arrayW[i]->y] = arrayW[i];
					break;
				}
			case 3:
				if ((arrayW[i]->y + 1) != y &&
					map1[arrayW[i]->x][arrayW[i]->y + 1] == NULL) {

					map1[arrayW[i]->x][arrayW[i]->y] = NULL;
					arrayW[i]->y = arrayW[i]->y + 1;
					map1[arrayW[i]->x][arrayW[i]->y] = arrayW[i];
					break;
				}
			default:
				break;
			}
		}
	}

	//Move vampires
	for (int i = 0; i < N; i++) {
		if (arrayV[i] != NULL) {
			int t = rand() % 8;
			switch (t) {
			case 0:
				if ((arrayV[i]->x - 1) > 0 &&
					map1[arrayV[i]->x - 1][arrayV[i]->y] == NULL) {

					map1[arrayV[i]->x][arrayV[i]->y] = NULL;
					arrayV[i]->x = arrayV[i]->x - 1;

					map1[arrayV[i]->x][arrayV[i]->y] = arrayV[i];
					break;
				}
			case 1:
				if ((arrayV[i]->y - 1) > 0 &&
					map1[arrayV[i]->x][arrayV[i]->y - 1] == NULL) {

					map1[arrayV[i]->x][arrayV[i]->y] = NULL;
					arrayV[i]->y = arrayV[i]->y - 1;

					map1[arrayV[i]->x][arrayV[i]->y] = arrayV[i];
					break;
				}
			case 2:
				if ((arrayV[i]->x + 1) != x &&
					map1[arrayV[i]->x + 1][arrayV[i]->y] == NULL) {

					map1[arrayV[i]->x][arrayV[i]->y] = NULL;
					arrayV[i]->x = arrayV[i]->x + 1;

					map1[arrayV[i]->x][arrayV[i]->y] = arrayV[i];
					break;
				}
			case 3:
				if ((arrayV[i]->y + 1) != y &&
					map1[arrayV[i]->x][arrayV[i]->y + 1] == NULL) {

					map1[arrayV[i]->x][arrayV[i]->y] = NULL;
					arrayV[i]->y = arrayV[i]->y + 1;

					map1[arrayV[i]->x][arrayV[i]->y] = arrayV[i];
					break;
				}
			case 4:
				if ((arrayV[i]->x - 1) > 0 && (arrayV[i]->y - 1) > 0 &&
					map1[arrayV[i]->x - 1][arrayV[i]->y - 1] == NULL) {

					map1[arrayV[i]->x][arrayV[i]->y] = NULL;
					arrayV[i]->x = arrayV[i]->x - 1;
					arrayV[i]->y = arrayV[i]->y - 1;

					map1[arrayV[i]->x][arrayV[i]->y] = arrayV[i];
					break;
				}
			case 5:
				if ((arrayV[i]->y - 1) > 0 && (arrayV[i]->x + 1) != x &&
					map1[arrayV[i]->x + 1][arrayV[i]->y - 1] == NULL) {

					map1[arrayV[i]->x][arrayV[i]->y] = NULL;
					arrayV[i]->y = arrayV[i]->y - 1;
					arrayV[i]->x = arrayV[i]->x + 1;

					map1[arrayV[i]->x][arrayV[i]->y] = arrayV[i];
					break;
				}
			case 6:
				if ((arrayV[i]->x + 1) != x && (arrayV[i]->y + 1) != y &&
					map1[arrayV[i]->x + 1][arrayV[i]->y + 1] == NULL) {

					map1[arrayV[i]->x][arrayV[i]->y] = NULL;
					arrayV[i]->x = arrayV[i]->x + 1;
					arrayV[i]->y = arrayV[i]->y + 1;

					map1[arrayV[i]->x][arrayV[i]->y] = arrayV[i];
					break;
				}
			case 7:
				if ((arrayV[i]->y + 1) != y && (arrayV[i]->x - 1) > 0 &&
					map1[arrayV[i]->x][arrayV[i]->y + 1] == NULL) {

					map1[arrayV[i]->x][arrayV[i]->y] = NULL;
					arrayV[i]->y = arrayV[i]->y + 1;
					arrayV[i]->x = arrayV[i]->x - 1;

					map1[arrayV[i]->x][arrayV[i]->y] = arrayV[i];
					break;
				}
			default:
				break;
			}
		}
	}
}

//Prints map
void map::printmap(int x, int y) {
	for (int i = 0; i < x; i++) {
		for (int j = 0; j< y; j++) {
			if (map1[i][j] == NULL) cout << "   ";
			else {
				switch (map1[i][j]->get_type()) {
					case 0:
						cout << "AVA";
						break;
					case 1:
						cout << " W ";
						break;
					case 2:
						cout << " V ";
						break;
					case 3:
						cout << "WAT";
						break;
					case 4:
						cout << "TRE";
						break;
				}
			}
		}
		cout << endl;
	}
}

//Takes a position on the map that contains an entity type 1 or 2 and gives back the monster
monsters* map::ret_monster(monsters** arrayW, monsters** arrayV, entity* monster, int N) {
	switch (monster->get_type()) {
	case 1:

		for (int i = 0; i < N; i++) {
			if (arrayW[i] == monster) return arrayW[i];
		}		
	case 2:
		
		for (int j = 0; j < N; j++) {
			if (arrayV[j] == monster) return arrayV[j];
		}
	}
}

//both monsters choose if the want to heal one another
void map::heal(monsters* m1, monsters* m2) {
	
	if (m1->health < 5 && m2->healing>0) {
		int i = rand() % 2;
		if (i) {
			m1->health++;
			m2->healing--;
		}
	}
	if (m2->health < 5 && m1->healing>0) {
		int i = rand() % 2;
		if (i) {
			m2->health++;
			m1->healing--;
		}
	}

}

//attacker2 attacks if he can attacker1 AND CHECKS FOR WIN
void map::attack(monsters* attacker1, monsters* attacker2,int N) {

	if ( attacker2->dmg >= attacker1->dmg ) {

		if (attacker2->dmg > attacker1->shield) {
			attacker1->health = attacker1->health - attacker2->dmg + attacker1->shield;
			if (attacker1->health == 0) {
				//Count dead Werewolves-Vampires
				if (attacker1->get_type() == 1) {
					deadW++;
					if (deadW == N) {
						cout <<endl<< "VAMPIRES WON!!!";
						exit(0);
					}
				}
				else if(attacker2->get_type() == 2) {
					deadV++;
					if (deadV == N) {
						cout << endl << "VAMPIRES WON!!!";
						exit(0);
					}
				}
				map1[attacker1->x][attacker1->y] = NULL;
				attacker1 = NULL;
			}
		}

	}
}

//checks around each monster from the two arrays and calls the functions heal or attack accordingly
void map::check_neigh(monsters** arrayW, monsters** arrayV, int x, int y,int N) {

	for (int i = 0; i < N; i++) {
		if (arrayW[i] != NULL) {
			if ( (arrayW[i]->x - 1) > 0 &&
				map1[arrayW[i]->x - 1][arrayW[i]->y] != NULL) {
				switch (map1[arrayW[i]->x-1][arrayW[i]->y]->get_type()) {
				case 1:
					heal(arrayW[i], ret_monster(arrayW,arrayV, map1[arrayW[i]->x - 1][arrayW[i]->y],N));
					break;
				case 2:
					attack(arrayW[i], ret_monster(arrayW, arrayV, map1[arrayW[i]->x - 1][arrayW[i]->y], N),N);
					break;
				}
				continue;
			}
			if ((arrayW[i]->y + 1) !=y  &&
				map1[arrayW[i]->x][arrayW[i]->y + 1] != NULL) {
				switch (map1[arrayW[i]->x][arrayW[i]->y+1]->get_type()) {
				case 1:
					heal(arrayW[i], ret_monster(arrayW, arrayV, map1[arrayW[i]->x][arrayW[i]->y+1], N));
					break;
				case 2:
					attack(arrayW[i], ret_monster(arrayW, arrayV, map1[arrayW[i]->x][arrayW[i]->y+1], N), N);
					break;
				}
				continue;
			}
			if ((arrayW[i]->x + 1) != x &&
				map1[arrayW[i]->x + 1][arrayW[i]->y] != NULL) {
				switch (map1[arrayW[i]->x + 1][arrayW[i]->y]->get_type()) {
				case 1:
					heal(arrayW[i], ret_monster(arrayW, arrayV, map1[arrayW[i]->x + 1][arrayW[i]->y], N));
					break;
				case 2:
					attack(arrayW[i], ret_monster(arrayW, arrayV, map1[arrayW[i]->x + 1][arrayW[i]->y], N), N);
					break;
				}
				continue;
			}
			if ((arrayW[i]->y - 1) > 0 &&
				map1[arrayW[i]->x][arrayW[i]->y - 1] != NULL) {
				switch (map1[arrayW[i]->x][arrayW[i]->y - 1]->get_type()) {
				case 1:
					heal(arrayW[i], ret_monster(arrayW, arrayV, map1[arrayW[i]->x][arrayW[i]->y - 1], N));
					break;
				case 2:
					attack(arrayW[i], ret_monster(arrayW, arrayV, map1[arrayW[i]->x][arrayW[i]->y - 1], N), N);
					break;
				}
				continue;
			}
		}
	}

	for (int i = 0; i < N; i++) {
		if (arrayV[i] != NULL) {
			if ((arrayV[i]->x - 1) > 0 &&
				map1[arrayV[i]->x - 1][arrayV[i]->y] != NULL) {
				switch (map1[arrayV[i]->x - 1][arrayV[i]->y]->get_type()) {
				case 1:
					heal(arrayV[i], ret_monster(arrayW, arrayV, map1[arrayV[i]->x - 1][arrayV[i]->y], N));
					break;
				case 2:
					attack(arrayV[i], ret_monster(arrayW, arrayV, map1[arrayV[i]->x - 1][arrayV[i]->y], N), N);
					break;
				}
				continue;
			}
			if ((arrayV[i]->y + 1) != y &&
				map1[arrayV[i]->x][arrayV[i]->y + 1] != NULL) {
				switch (map1[arrayV[i]->x][arrayV[i]->y + 1]->get_type()) {
				case 1:
					heal(arrayV[i], ret_monster(arrayW, arrayV, map1[arrayV[i]->x][arrayV[i]->y + 1], N));
					break;
				case 2:
					attack(arrayV[i], ret_monster(arrayW, arrayV, map1[arrayV[i]->x][arrayV[i]->y + 1], N), N);
					break;
				}
				continue;
			}
			if ((arrayV[i]->x + 1) != x &&
				map1[arrayV[i]->x + 1][arrayV[i]->y] != NULL) {
				switch (map1[arrayV[i]->x + 1][arrayV[i]->y]->get_type()) {
				case 1:
					heal(arrayV[i], ret_monster(arrayW, arrayV, map1[arrayV[i]->x + 1][arrayV[i]->y], N));
					break;
				case 2:
					attack(arrayV[i], ret_monster(arrayW, arrayV, map1[arrayV[i]->x + 1][arrayV[i]->y], N), N);
					break;
				}
				continue;
			}
			if ((arrayV[i]->y - 1) > 0 &&
				map1[arrayV[i]->x][arrayV[i]->y - 1] != NULL) {
				switch (map1[arrayV[i]->x][arrayV[i]->y - 1]->get_type()) {
				case 1:
					heal(arrayV[i], ret_monster(arrayW, arrayV, map1[arrayV[i]->x][arrayV[i]->y - 1], N));
					break;
				case 2:
					attack(arrayV[i], ret_monster(arrayW, arrayV, map1[arrayV[i]->x][arrayV[i]->y - 1], N), N);
					break;
				}
				continue;
			}
		}
	}

}
