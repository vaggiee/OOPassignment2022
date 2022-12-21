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
	srand(time(NULL));
	
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
	
	avatar mya(0,tteam);
	map *map1=new map;
	
	map1->create_map(x,y);
	map1->set_map(x,y,mya,arrayW,arrayV,N);

	while (true) {
	// Clear the screen
		system("cls");
		map1->printmap(x,y);
		map1->check_neigh(arrayW, arrayV, x, y, N);

		if(_kbhit() && (_getch() == 'p' || _getch() == 'P'))
		{
			cout << "To paixnidi brhsketai se paush"<<endl;
			cout << "Ta nekra vampire einai:" << map1->get_deadV() << endl;
			cout << "Ta nekra werewolve einai:" << map1->get_deadW() << endl;
			system("pause");
		}
		map1->move(arrayW, arrayV,x,y, N);
		Sleep(500);
	}

	return 0;
}
