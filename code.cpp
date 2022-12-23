#include <iostream>
#include <cstdlib>
#include <Windows.h>
#include "Header.h"
#pragma once
using namespace std;
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
	dmg = 1 + rand() % 5;
	health =3;
	healing = rand() % 2;
	shield = 1 + rand() % 2;
}

//Maximize monsters health
void monsters::avatarheal() {
	health = 3;
}

//Avatar constructor
avatar::avatar(int in_type, char in_team) :entity(in_type) {
	team = in_team;
	potion = 1;
}

//Avatar accessors
char avatar::get_team() {
	return team;
}
int avatar::get_potion() {
	return potion;
}

//Sets avatars team
void set_team(char ch, avatar av) {
	av.team = ch;
}

//Decreases potions by 1
void avatar::decreasepot() {
	potion -= 1;
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

//Frees the memory used by the map
void map::deletemap(int x) {
	for (int i = 0; i < x; i++) {
		delete[] map1[i];
	}
	delete[] map1;
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
				if (arrayW[i]->x  > 0 &&
					map1[arrayW[i]->x - 1][arrayW[i]->y] == NULL) {

					map1[arrayW[i]->x][arrayW[i]->y] = NULL;
					arrayW[i]->x = arrayW[i]->x - 1;
					map1[arrayW[i]->x][arrayW[i]->y] = arrayW[i];
					break;
				}
			case 1:
				if (arrayW[i]->y > 0 &&
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
				if (arrayV[i]->x > 0 &&
					map1[arrayV[i]->x - 1][arrayV[i]->y] == NULL) {

					map1[arrayV[i]->x][arrayV[i]->y] = NULL;
					arrayV[i]->x = arrayV[i]->x - 1;

					map1[arrayV[i]->x][arrayV[i]->y] = arrayV[i];
					break;
				}
			case 1:
				if (arrayV[i]->y > 0 &&
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
				if (arrayV[i]->x > 0 && arrayV[i]->y > 0 &&
					map1[arrayV[i]->x - 1][arrayV[i]->y - 1] == NULL) {

					map1[arrayV[i]->x][arrayV[i]->y] = NULL;
					arrayV[i]->x = arrayV[i]->x - 1;
					arrayV[i]->y = arrayV[i]->y - 1;

					map1[arrayV[i]->x][arrayV[i]->y] = arrayV[i];
					break;
				}
			case 5:
				if (arrayV[i]->y  > 0 && (arrayV[i]->x + 1) != x &&
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
				if ((arrayV[i]->y + 1) != y && arrayV[i]->x > 0 &&
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

//Moves avatar
void map::move_av(avatar player, int x, int y, int num) {
	int k = ret_coo1(x, y);
	int l = ret_coo2(x, y);

	// Move the avatar based on the input

	if (num == 0) // Up arrow key
	{
		if (k > 0 && map1[k - 1][l] == NULL)
		{
			map1[k][l] = NULL;
			k--;
			map1[k][l] = &player;
			return;
		}
	}
	else if (num == 1) // Down arrow key
	{
		if (k + 1 < x && map1[k + 1][l] == NULL)
		{
			map1[k][l] = NULL;
			k++;
			map1[k][l] = &player;
			return;
		}
	}
	else if (num == 2) // Left arrow key
	{
		if (l > 0 && map1[k][l - 1] == NULL)
		{
			map1[k][l] = NULL;
			l--;
			map1[k][l] = &player;
			return;
		}
	}
	else if (num == 3) // Right arrow key
	{
		if (l + 1 > 0 && map1[k][l + 1] == NULL)
		{
			map1[k][l] = NULL;
			l++;
			map1[k][l] = &player;
			return;
		}
	}
	return;
}

//Prints map
void map::printmap(int x, int y) {
	for (int L = 0; L < y; L++) {
		cout << "__";
	}
	cout << endl;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (map1[i][j] == NULL) cout << "| ";
			else {
				switch (map1[i][j]->get_type()) {
				case 0:
					cout << "|A";
					break;
				case 1:
					cout << "|W";
					break;
				case 2:
					cout << "|V";
					break;
				case 3:
					cout << "|S";
					break;
				case 4:
					cout << "|T";
					break;
				default:
					cout << "|O";
					break;
				}
			}
		}
		cout << "|";
		cout << endl;
	}
	for (int L = 0; L < y; L++) {
		cout << "--";
	}
}

int map::ret_coo1(int x, int y) {
	int k = 0, l = 0;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (map1[i][j] != NULL && map1[i][j]->get_type() == 0) {
				return i;
			}
		}
	}
}

int map::ret_coo2(int x, int y) {
	int k = 0, l = 0;
	for (int i = 0; i < x; i++) {
		for (int j = 0; j < y; j++) {
			if (map1[i][j] != NULL && map1[i][j]->get_type() == 0) {
				return j;
			}
		}
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
	return NULL;
}

//Makes the pointer of mon NULL
void nul_mon(monsters** arrayW, monsters** arrayV, monsters* mon, int N) {
	if (mon->get_type() == 1) {
		for (int j = 0; j < N; j++) {
			if (arrayW[j] == mon) {
				arrayW[j] = NULL;
				return;
			}
		}
	}
	else if (mon->get_type() == 2) {
		for (int i = 0; i < N; i++) {
			if (arrayV[i] == mon) {
				arrayV[i] = NULL;
				return;
			}
		}
	}
	cout << "nullnotworking";
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

//attacker1 attacks if he can attacker2 AND CHECKS FOR WIN
void map::attack(monsters** arrayW, monsters** arrayV, monsters* attacker1, monsters* attacker2,int N) {

	if ( attacker1->dmg >= attacker2->dmg ) {

		if (attacker1->dmg > attacker2->shield) {
			attacker2->health -= attacker1->dmg+ attacker2->shield;
			//for (int l = 0; l < N; l++) {
			//	if (attacker2->get_type() == 1 && (arrayW[l]->health == attacker2->health)) system("pause");
			//}
			if (attacker2->health == 0) {
				//Count dead Werewolves-Vampires
				if (attacker2->get_type() == 1) {
					deadW++;
					if (deadW == N) {
						system("cls");
						cout <<endl<< "VAMPIRES WON!!!";
						Sleep(5000);
						exit(0);
					}
				}
				else if(attacker2->get_type() == 2) {
					deadV++;
					if (deadV == N) {
						system("cls");
						cout << endl << "VAMPIRES WON!!!";
						Sleep(5000);
						exit(0);
					}
				}
				map1[attacker2->x][attacker2->y] = NULL;
				nul_mon(arrayW, arrayV, attacker2,N);
			}
		}

	}
}

//checks around each monster from the two arrays and calls the functions heal or attack accordingly
void map::check_neigh(monsters** arrayW, monsters** arrayV, int x, int y,int N) {

	for (int i = 0; i < N; i++) {
		if (arrayW[i] != NULL) {
			if (arrayW[i]->x > 0 &&
				map1[arrayW[i]->x - 1][arrayW[i]->y] != NULL) {
				switch (map1[arrayW[i]->x-1][arrayW[i]->y]->get_type()) {
					case 1:
						heal(arrayW[i], ret_monster(arrayW,arrayV, map1[arrayW[i]->x - 1][arrayW[i]->y],N));
						continue;
					case 2:
						attack(arrayW,arrayV, arrayW[i], ret_monster(arrayW, arrayV, map1[arrayW[i]->x - 1][arrayW[i]->y], N),N);
						continue;
					default:
						break;
				}
				
			}
			if ((arrayW[i]->y + 1) !=y  &&
				map1[arrayW[i]->x][arrayW[i]->y + 1] != NULL) {
				switch (map1[arrayW[i]->x][arrayW[i]->y+1]->get_type()) {
					case 1:
						heal(arrayW[i], ret_monster(arrayW, arrayV, map1[arrayW[i]->x][arrayW[i]->y+1], N));
						continue;
					case 2:
						attack(arrayW, arrayV, arrayW[i], ret_monster(arrayW, arrayV, map1[arrayW[i]->x][arrayW[i]->y+1], N), N);
						continue;
					default:
						break;
				}
				
			}
			if ((arrayW[i]->x + 1) != x &&
				map1[arrayW[i]->x + 1][arrayW[i]->y] != NULL) {
				switch (map1[arrayW[i]->x + 1][arrayW[i]->y]->get_type()) {
				case 1:
					heal(arrayW[i], ret_monster(arrayW, arrayV, map1[arrayW[i]->x + 1][arrayW[i]->y], N));
					continue;
				case 2:
					attack(arrayW, arrayV, arrayW[i], ret_monster(arrayW, arrayV, map1[arrayW[i]->x + 1][arrayW[i]->y], N), N);
					continue;
				default:
					break;
				}
				
			}
			if (arrayW[i]->y > 0 &&
				map1[arrayW[i]->x][arrayW[i]->y - 1] != NULL) {
				switch (map1[arrayW[i]->x][arrayW[i]->y - 1]->get_type()) {
				case 1:
					heal(arrayW[i], ret_monster(arrayW, arrayV, map1[arrayW[i]->x][arrayW[i]->y - 1], N));
					continue;
				case 2:
					attack(arrayW, arrayV, arrayW[i], ret_monster(arrayW, arrayV, map1[arrayW[i]->x][arrayW[i]->y - 1], N), N);
					continue;
				default:
					break;
				}
				
			}
		}
	}

	for (int i = 0; i < N; i++) {
		if (arrayV[i] != NULL) {
			if (arrayV[i]->x > 0 &&
				map1[arrayV[i]->x - 1][arrayV[i]->y] != NULL) {
				switch (map1[arrayV[i]->x - 1][arrayV[i]->y]->get_type()) {
				case 1:
					attack(arrayW, arrayV, arrayV[i], ret_monster(arrayW, arrayV, map1[arrayV[i]->x - 1][arrayV[i]->y], N), N);
					continue;
				case 2:
					heal(arrayV[i], ret_monster(arrayW, arrayV, map1[arrayV[i]->x - 1][arrayV[i]->y], N));
					continue;
				default:
					break;
				}
				
			}
			if ((arrayV[i]->y + 1) != y &&
				map1[arrayV[i]->x][arrayV[i]->y + 1] != NULL) {
				switch (map1[arrayV[i]->x][arrayV[i]->y + 1]->get_type()) {				
				case 1:
					attack(arrayW, arrayV, arrayV[i], ret_monster(arrayW, arrayV, map1[arrayV[i]->x][arrayV[i]->y + 1], N), N);
					continue;
				case 2:
					heal(arrayV[i], ret_monster(arrayW, arrayV, map1[arrayV[i]->x][arrayV[i]->y + 1], N));
					continue;
				default:
					break;
				}
				
			}
			if ((arrayV[i]->x + 1) != x &&
				map1[arrayV[i]->x + 1][arrayV[i]->y] != NULL) {
				switch (map1[arrayV[i]->x + 1][arrayV[i]->y]->get_type()) {				
				case 1:
					attack(arrayW, arrayV, arrayV[i], ret_monster(arrayW, arrayV, map1[arrayV[i]->x + 1][arrayV[i]->y], N), N);
					continue;
				case 2:
					heal(arrayV[i], ret_monster(arrayW, arrayV, map1[arrayV[i]->x + 1][arrayV[i]->y], N));
					continue;
				default:
					break;
				}
				
			}
			if (arrayV[i]->y > 0 &&
				map1[arrayV[i]->x][arrayV[i]->y - 1] != NULL) {
				switch (map1[arrayV[i]->x][arrayV[i]->y - 1]->get_type()) {				
				case 1:
					attack(arrayW, arrayV, arrayV[i], ret_monster(arrayW, arrayV, map1[arrayV[i]->x][arrayV[i]->y - 1], N), N);
					continue;
				case 2:
					heal(arrayV[i], ret_monster(arrayW, arrayV, map1[arrayV[i]->x][arrayV[i]->y - 1], N));
					continue;
				default:
					break;
				}
				
			}
		}
	}

}
