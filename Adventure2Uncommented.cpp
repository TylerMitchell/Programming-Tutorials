#include <iostream>
#include <string>

using namespace std;

int GRID_ROWS = 10;
int GRID_COLUMNS = 10;

char g_grid[10][10] = { {'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
					  {'x', 'x', 'k', 'w', 'd', 'w', 'w', 'x', 'x', 'x'},
					  {'x', 'x', 'x', 'x', 'x', 'x', 'w', 'x', 'x', 'x'},
					  {'w', 'w', 'w', 'x', 'x', 'x', 'w', 'x', 'x', 'e'},
					  {'k', 'x', 'w', 'x', 'x', 'x', 'w', 'x', 'x', 'd'},
					  {'x', 'x', 'b', 'w', 'w', 'w', 'w', 'w', 'x', 'w'},
					  {'x', 'x', 'x', 'w', 'x', 'w', 'x', 'x', 'x', 'w'},
					  {'w', 'w', 'w', 'w', 'x', 'w', 'w', 'w', 'w', 'w'},
					  {'w', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'},
					  {'w', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x', 'x'} };

int g_playerX;
int g_playerY;

int g_numDoors = 0;
int g_numKeys  = 0;

bool* g_keyring;
int* g_keyX;
int* g_keyY;
int* g_doorX;
int* g_doorY;

void gameSetup(){
	for(int i = 0; i < GRID_ROWS; i++){
		for(int j = 0; j < GRID_COLUMNS; j++){
			if( g_grid[i][j] == 'b' ){ 
				g_playerX = j;
				g_playerY = i;
			}
			if( g_grid[i][j] == 'k' ){ 
				g_numKeys++;
			}
			if( g_grid[i][j] == 'd' ){
				g_numDoors++;
			}
		}
	}
	g_keyring = new bool[g_numKeys];
	for(int i = 0;i < g_numKeys;i++){
		g_keyring[i] = false;
	}
	g_keyX = new int[g_numKeys];
	g_keyY = new int[g_numKeys];
	g_doorX = new int[g_numDoors];
	g_doorY = new int[g_numDoors];
	int indexK = 0;
	int indexD = 0;
	for(int i = 0; i < GRID_ROWS; i++){
		for(int j = 0; j < GRID_COLUMNS; j++){
			if( g_grid[i][j] == 'k' ){
				g_keyX[indexK] = j;
				g_keyY[indexK] = i;
				indexK++;
			}
			if( g_grid[i][j] == 'd' ){
				g_doorX[indexD] = j;
				g_doorY[indexD] = i;
				indexD++;
			}
		}
	}
}

bool isDoor(){
	if( g_grid[g_playerY][g_playerX] == 'd' ){
		for(int i = 0; i < g_numDoors; i++){
			if( g_doorX[i] == g_playerX && g_doorY[i] == g_playerY ){ //
				bool hadKey = false;
				for(int j = 0;j < g_numKeys; j++){
					if( g_keyring[j] == true ){
						g_keyring[j] = false;
						hadKey = true;
					}
				}
				if(hadKey){
					g_grid[g_playerY][g_playerX] = 'w';
					cout << "You unlocked the door" << endl;
					return false;
				}
				else{
					cout << "You need a key to unlock this door" << endl;
					return true;
				}
			}
		}
	}
	return false;
}

void playerMove(){
	cout << "Current Location = {" << g_playerX << ", " << g_playerY << "}" << endl;
	bool options[4] = {0,0,0,0};
	string opNames[4] = {"(n)orth", "(s)outh", "(e)ast", "(w)est"};
	if( (g_playerY - 1) >= 0 && g_grid[g_playerY - 1][g_playerX] != 'x' ){
		options[0] = true; 
	}
	if( (g_playerY + 1) <= GRID_COLUMNS && g_grid[g_playerY + 1][g_playerX] != 'x' ){
		options[1] = true; 
	}
	if( (g_playerX - 1) >= 0 && g_grid[g_playerY][g_playerX - 1] != 'x'  ){
		options[3] = true; 
	}
	if( (g_playerX + 1) <= GRID_ROWS && g_grid[g_playerY][g_playerX + 1] != 'x' ){
		options[2] = true; 
	}
	string output = "Which direction would you like to go? {";
	for(int i = 0; i < 4; i++){
		if( options[i] ){
			output += opNames[i];
			if( i != 3 ){ output += ", "; }
		}
		if( i == 3 ){
			output += "}\n";
		}
	}
	bool badInput = true;
	do{
		cout << output << endl;
		char direction;
		cin >> direction;
		int lastX = g_playerX;
		int lastY = g_playerY;
		if( direction == 'n' || direction == 'N' ){ if( options[0] ){ g_playerY--; badInput = false; } }
		if( direction == 's' || direction == 'S' ){ if( options[1] ){ g_playerY++; badInput = false; } }
		if( direction == 'e' || direction == 'E' ){ if( options[2] ){ g_playerX++; badInput = false; } }
		if( direction == 'w' || direction == 'W' ){ if( options[3] ){ g_playerX--; badInput = false; } }
		if( isDoor() ){
			badInput = true;
			g_playerX = lastX;
			g_playerY = lastY;
		}
	}while( cin.fail() || badInput);
}

void pickupKey(){
	for(int i = 0;i < g_numKeys;i++){
		if( g_playerX == g_keyX[i] && g_playerY == g_keyY[i] ){ 
			g_keyring[i] = true; 
			cout << "\nYou found a key!!!\n"; 
			g_grid[g_playerY][g_playerX] = 'w';
		}
	}
	cin.ignore(2);
}

void checkSpace(){
	if( g_grid[g_playerY][g_playerX] == 'e' ){
		cout << "Congratulations, you won the game.";
		cin.ignore(2);
		delete[] g_keyring; 
		delete[] g_keyX;
		delete[] g_keyY;
		delete[] g_doorX;
		delete[] g_doorY;
		exit(1);
	}
	if( g_grid[g_playerY][g_playerX] == 'k' ){
		pickupKey();
	}
}

void main(){
	cout << "Escape the dungeon" << endl << "Press Enter..." << endl;
	cin.ignore();
	gameSetup();
	while(true){
		playerMove();
		checkSpace();
	}
}