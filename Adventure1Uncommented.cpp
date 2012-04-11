#include <iostream>
#include <string>

using namespace std;

#define GRID_ROWS 10
#define GRID_COLUMNS 10

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

void playerSetup(){
	for(int i = 0; i < GRID_ROWS; i++){
		for(int j = 0; j < GRID_COLUMNS; j++){
			if( g_grid[i][j] == 'b' ){
				g_playerX = j;
				g_playerY = i;
			}
		}
	}
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
		if( direction == 'n' || direction == 'N' ){ if( options[0] ){ g_playerY--; badInput = false; } }
		if( direction == 's' || direction == 'S' ){ if( options[1] ){ g_playerY++; badInput = false; } }
		if( direction == 'e' || direction == 'E' ){ if( options[2] ){ g_playerX++; badInput = false; } }
		if( direction == 'w' || direction == 'W' ){ if( options[3] ){ g_playerX--; badInput = false; } }
	}while( cin.fail() || badInput);
}

void checkSpace(){
	if( g_grid[g_playerY][g_playerX] == 'e' ){
		cout << "Congratulations, you won the game.";
		cin.ignore();
		cin.ignore();
		exit(1);
	}
}

void main(){
	cout << "Escape the dungeon" << endl << "Press Enter..." << endl;
	cin.ignore();
	playerSetup();
	while(true){ 
		playerMove(); 
		checkSpace();
	}
}