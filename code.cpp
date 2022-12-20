#include <iostream>
#include "Header.h"
#pragma once

entity::entity(int in_type) {
	type = in_type;
	x = rand() % 10;
	y = rand() % 10;
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

monsters::monsters(int in_type) :entity(in_type) {
	dmg = 1 + rand() % 3;
	health = 1 + rand() % 5;
	healing = rand() % 3;
	shield = 1 + rand() % 2;
}

void set_team(char ch, avatar av) {
	av.team = ch;
}

int entity::get_type() {
	return type;
}

avatar::avatar(int in_type, char in_team):entity(in_type) {
	team = in_team;
}
//Move monsters
void map::move(monsters** arrayW, monsters** arrayV,int N) {
	
	//Move werewolves
	for (int i = 0; i < N; i++) {
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
			if ((arrayW[i]->x + 1) != N &&
				map1[arrayW[i]->x + 1][arrayW[i]->y] == NULL) {
				map1[arrayW[i]->x][arrayW[i]->y] = NULL;
				arrayW[i]->x = arrayW[i]->x + 1;
				map1[arrayW[i]->x][arrayW[i]->y] = arrayW[i];
				break;
			}
		case 3:
			if ((arrayW[i]->y + 1) != N &&
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
	//Move vampires
	for (int i = 0; i < N; i++) {
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
			if ((arrayV[i]->x + 1) != N &&
				map1[arrayV[i]->x + 1][arrayV[i]->y] == NULL) {

				map1[arrayV[i]->x][arrayV[i]->y] = NULL;
				arrayV[i]->x = arrayV[i]->x + 1;

				map1[arrayV[i]->x][arrayV[i]->y] = arrayV[i];
				break;
			}
		case 3:
			if ((arrayV[i]->y + 1) != N &&
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
			if ((arrayV[i]->y - 1) > 0 && (arrayV[i]->x + 1) != N &&
				map1[arrayV[i]->x+1][arrayV[i]->y - 1] == NULL) {

				map1[arrayV[i]->x][arrayV[i]->y] = NULL;
				arrayV[i]->y = arrayV[i]->y - 1;
				arrayV[i]->x = arrayV[i]->x + 1;

				map1[arrayV[i]->x][arrayV[i]->y] = arrayV[i];
				break;
			}
		case 6:
			if ((arrayV[i]->x + 1) != N && (arrayV[i]->y + 1) != N &&
				map1[arrayV[i]->x + 1][arrayV[i]->y+1] == NULL) {

				map1[arrayV[i]->x][arrayV[i]->y] = NULL;
				arrayV[i]->x = arrayV[i]->x + 1;
				arrayV[i]->y = arrayV[i]->y + 1;

				map1[arrayV[i]->x][arrayV[i]->y] = arrayV[i];
				break;
			}
		case 7:
			if ((arrayV[i]->y + 1) != N && (arrayV[i]->x - 1) > 0 &&
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
/*
void avatar::move(int in_type) {

}*/

void map::printmap(int N) {
	for (int i = 0; i < N; i++) {
		for (int j = 0; j< N; j++) {
			if (map1[i][j] == NULL) cout << "   ";
			else {
				switch (map1[i][j]->get_type()) {
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
