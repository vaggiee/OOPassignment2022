#include <iostream> 
#include <ctime>
#include <cstdlib>
#include <Windows.h>
#include "Header.h"

using namespace std;
//Thn getkey thn brhkame sto internet
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
	cout << "Choose a team: W or w for werewolves and V or v for vampires"<<endl
		<<"If you got a magic potion,by pressing TAB you can heal your team!" << endl;
	cin >> tteam;
	//Checks users input
	while (tteam != 'W' && tteam != 'w' && tteam != 'V' && tteam != 'v') {
		cout << "Wrong input...";
		cout << "Choose a team: W or w for werewolves and V or v for vampires" << endl;
		cin >> tteam;		
	}

	int N = (x * y) / 15;

	//Allocate memory for pointer arrays of werewolves and vampires
	monsters** arrayW = new monsters* [N];
	monsters** arrayV = new monsters * [N];

	for (int i = 0; i < N;i++) {
		arrayW[i] = new monsters(1);
	}
	for (int i = 0; i < N; i++) {
		arrayV[i] = new monsters(2);
	}
	
	entity pot(5);
	avatar *mya=new avatar(0,tteam);
	map *map1=new map;
	
	map1->create_map(x,y);
	map1->set_map(x,y,mya,arrayW,arrayV,N,pot);

	int g = 1;
	//for time<12 it is day and for time>12 we got night
	for (int time = 0;g==1; time++) {
		// Clear the screen
		system("cls");
		//Shows the user if is night or day
		if (time < 12) {
			cout << endl << "Its day time"<<endl;
		}
		else {
					cout << endl << "Its night time"<<endl;
				}
		if(mya->get_team()=='V' || mya->get_team() == 'v')cout << "You are with the vampires" << endl;
		else{ cout << "Your team is werewolves" << endl; }
		map1->printmap(x, y,pot);
		//Geets users input
		switch (getKey()) {
		case VK_LEFT:
			map1->move_av(mya, x, y, 2);
			break;
		case VK_RIGHT:
			map1->move_av(mya, x, y, 3);
			break;
		case VK_UP:
			map1->move_av(mya, x, y, 0);
			break;
		case VK_DOWN:
			map1->move_av(mya, x, y, 1);
			break;
		case VK_TAB:
			if (mya->get_potion() > 0) {
				if (time>12 && (mya->get_team() == 'W' || mya->get_team() == 'w')) {
					for (int i = 0; i < N; i++) {
						if (arrayW[i]!=NULL) {
							arrayW[i]->avatarheal();
						}
					}
					mya->decreasepot();
				}
				else if (time<12 && (mya->get_team() == 'V' || mya->get_team() == 'v')) {
					for (int i = 0; i < N; i++) {
						if (arrayV[i] != NULL) {
							arrayV[i]->avatarheal();
						}
					}
					mya->decreasepot();
				}
				else { 
					cout << "You cant heal your team right now";
					Sleep(100);
				}
			}
			else {
						cout << "NOT ENOUGH POTIONS";
						Sleep(100);
					}
			break;
		case VK_ESCAPE:
			g = 0;
			break;
		case VK_SPACE:
			cout << endl << "The number of alive werewolves is: " << N - map1->get_deadW() << endl;
			cout << endl << "The number of alive vampires is: " << N - map1->get_deadV() << endl;
			cout << endl << "The number of potions is: " << mya->get_potion() << endl;
			system("pause");
			break;
 			}
		map1->check_neigh(arrayW, arrayV, x, y, N);
		map1->move(arrayW, arrayV, x, y, N);
		Sleep(50);
		if (time == 23) time = 0;
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
	delete map1;
	delete mya;
	cout << endl<< "Thanks for playing!!!Bye.." << endl;
	return 0;
}
