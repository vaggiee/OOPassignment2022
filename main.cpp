#include <iostream> 
#include <ctime>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
#include "Header.h"

using namespace std;

WORD getKey() {
	HANDLE hin = GetStdHandle(STD_INPUT_HANDLE);
	INPUT_RECORD inrec;
	DWORD n;
	while (ReadConsoleInput(hin, &inrec, 1, &n) && n)
		if (inrec.EventType == KEY_EVENT && inrec.Event.KeyEvent.bKeyDown)
			return inrec.Event.KeyEvent.wVirtualKeyCode;
	cerr << "getKey failed\n";
	exit(EXIT_FAILURE);
	return 0;
}


int main() {
	int x, y;
	char tteam;
	srand(time(0));
	
	cout << " WvV has started !"<<endl<< "Press SPACE to pause and ESC to end the game!"<<endl;
	cout << "Give map dimensions" << endl;
	cin >> x >> y;
	cout << "Choose a team: W or w for werewolves and V or v for vampires"<<endl<<"By pressing left shift you can heal your team!" << endl;
	cin >> tteam;
	while (true) {
		if (tteam != 'W' || tteam != 'w' || tteam != 'V' || tteam != 'v') {
			cout << "Wrong input...";
			cout << "Choose a team: W or w for werewolves and V or v for vampires" << endl;
			cin >> tteam;
			break;
		}
	}
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
		switch (getKey()) {
		case VK_LEFT:
			map1->move_av(*mya, x, y, 2);
			break;
		case VK_RIGHT:
			map1->move_av(*mya, x, y, 3);
			break;
		case VK_UP:
			map1->move_av(*mya, x, y, 0);
			break;
		case VK_DOWN:
			map1->move_av(*mya, x, y, 1);
			break;
		case VK_ESCAPE:
			g = 0;
			break;
		case VK_SPACE:
			cout << endl << "The number of dead werewolves is:"<<map1->get_deadW() << endl;
			cout << endl << "The number of dead vampires is:" << map1->get_deadV() << endl;
			system("pause");
			break;
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
	cout << endl<< "Thanks for playing!!!Bye.." << endl;
	return 0;
}
