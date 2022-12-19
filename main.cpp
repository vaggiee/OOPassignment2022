#include <iostream> 
#include <ctime>
#include <cstdlib>
#include "Header.h"

using namespace std;

int main() {
	int x, y;
	char tteam;
	srand(time(NULL));
	
	cout << "Dwse diastaseis" << endl;
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
	map1->printmap(N);
	
	map1->set_map(x,y,mya,arrayW,arrayV,N);
	map1->printmap(N);
	
	map1->move(arrayW,arrayV,N);
	map1->printmap(N);
	return 0;
}