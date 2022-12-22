#include <iostream> 
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
#include "Header.h"

using namespace std;

int main() {
	int x, y;
	char tteam;
	srand(time(0));
	
	cout << "To WvV jekinhse! Gia na kaneis pause pata P kai to esc gia na termatisei to paixnidi"<<endl;
	cout << "Dwse diastaseis tou xarth" << endl;
	cin >> x >> y;
	cout << "Dialeje omada W gia werewolves,V gia vampires" << endl;
	cin >> tteam;
	int N = (x * y) / 15;
	monsters** arrayW = new monsters* [N];
	monsters** arrayV = new monsters * [N];

	for (int i = 0; i < N;i++) {
		arrayW[i] = new monsters(1);
	}
	for (int i = 0; i < N; i++) {
		arrayV[i] = new monsters(2);
	}
	
	avatar* mya=new avatar(0,tteam);
	map *map1=new map;
	
	map1->create_map(x,y);
	map1->set_map(x,y,*mya,arrayW,arrayV,N);

	while (true) {
	// Clear the screen
		system("cls");
		map1->printmap(x,y);

		map1->check_neigh(arrayW, arrayV, x, y, N);

		if (_kbhit())
		{
			if ((_getch() == 'p' || _getch() == 'P')) {
				cout << "To paixnidi brhsketai se paush" << endl;
				cout << "Ta nekra vampire einai:" << map1->get_deadV() << endl;
				cout << "Ta nekra werewolve einai:" << map1->get_deadW() << endl;
				system("pause");
			}
			if (_getch() == 72) {
				map1->move_av(*mya, x, y, 0);
			}
			if (_getch() == 80) {
				map1->move_av(*mya, x, y, 1);
			}
			if (_getch() == 75) {
				map1->move_av(*mya, x, y, 2);
			}
			if (_getch() == 77) {
				map1->move_av(*mya, x, y, 3);
			}
		}
		map1->move(arrayW, arrayV,x,y, N);
		Sleep(400);
	}

	//Delete allocated memory
	for (int i = 0; i < N; i++) {
		delete arrayW[i];
	}
	for (int i = 0; i < N; i++) {
		delete arrayV[i];
	}
	delete [] arrayW;
	delete [] arrayV;
	map1->deletemap(x);
	return 0;
}
