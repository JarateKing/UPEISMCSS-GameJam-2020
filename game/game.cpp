#include <bits/stdc++.h>
#include <windows.h>
using namespace std;

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
bool rando() {
	return rng() % 2;
}
int rando(int min, int max) {
	if (min == max) return min;
	return rng() % (max - min) + min;
}

#define DISP_W 100
#define DISP_H 30
#define MAP_W 1000
#define MAP_H 1000

char** world;
char** worldview;

pair<int, int> view = {100,100};
int health = 100;

struct Enemy {
	pair<int, int> pos;
	int health, maxhp,damageMult;
	char display;
	
	Enemy(pair<int, int> spawn) {
		pos = spawn;
		
		int type = rando(0, 3);
		if (type == 0) {
			health = 10;
			display = 'z';
			damageMult = 2;
		}
		else if (type == 1) {
			health = 20;
			display = 'x';
			damageMult = 1;
		}
		else {
			health = 15;
			display = 'y';
			damageMult = 3;
		}
		
		maxhp = health;
	}
	
	int GetDamage() {
		return (int)(rando(100 * damageMult, 250 * damageMult) * 0.01f);
	}
	
	void TakeDamage(int damage) {
		health -= damage;
		if (health <= 0)
			health = 0;
	}
};

vector<Enemy> enemies;

bool isKeyPressed(char c) {
	if (c >= 'a' && c <= 'z')
		c = c - 'a' + 'A';
	return GetKeyState(c) & 0x8000;
}

void drawhp() {
	string curhp = "-- HEALTH " + to_string(health) + "/100 ";
	printf("%s", curhp.c_str());
	for (int i = curhp.size(); i < DISP_W; i++)
		printf("-");
	printf("\n");
	for (int i = 0; i < min(health, DISP_W); i++)
		printf("=");
	for (int i = health; i < 100; i++)
		printf(" ");
	printf("\n");
	for (int i = 0; i < DISP_W; i++)
		printf("-");
	printf("\n");
}

void render() {
	int minx = view.first - (DISP_W / 2);
	int maxx = view.first - (DISP_W / 2) + DISP_W;
	int miny = view.second - (DISP_H / 2);
	int maxy = view.second - (DISP_H / 2) + DISP_H;
	
	// apply world to worldview
	for (int i = 0; i < DISP_H; i++)
		for (int j = 0; j < DISP_W; j++)
			worldview[i][j] = world[view.second - (DISP_H / 2) + i][view.first - (DISP_W / 2) + j];
		
	// add player
	worldview[DISP_H / 2][DISP_W / 2] = '0';
	
	// add enemies
	for (int i = 0; i < enemies.size(); i++) {
		auto curpos = enemies[i].pos;
		if (curpos.first >= minx && curpos.first < maxx && curpos.second >= miny && curpos.second < maxy)
			worldview[curpos.second - miny][curpos.first - minx] = enemies[i].display;
	}
	
	// render properly
	for (int i = 0; i < DISP_H; i++) {
		for (int j = 0; j < DISP_W; j++) {
			printf("%c", worldview[i][j]);
		}
		printf("\n");
	}
	
	drawhp();
}

void generate() {
	// generate grass / ground
	for (int i = 0; i < MAP_H; i++) {
		for (int j = 0; j < MAP_W; j++) {
			world[i][j] = ' ';
		}
	}
	
	// generate random trees
	int treeNum = rando(1000, 2000);
	for (int i = 0; i < treeNum; i++) {
		int x = rando(0, MAP_W);
		int y = rando(0, MAP_H);
		world[y][x] = 'T';
	}
	
	// generate random boulders
	int boulderNum = rando(400, 650);
	for (int i = 0; i < boulderNum; i++) {
		int r = rando(2, 8);
		int x = rando(r + r, MAP_W - r - r);
		int y = rando(r + r, MAP_H - r - r);
		
		for (int a = 2 * -r; a <= 2 * r; a++) {
			for (int b = 2 * -r; b <= 2 * r; b++) {
				double dist = (a - r) * (a - r) + (b - r) * (b - r);
				if (dist < (r * r))
					world[y + b][x + a] = 'B';
			}
		}
	}
	
	// generate random buildings
	int buildingNum = rando(500, 750);
	for (int i = 0; i < buildingNum; i++) {
		int w = rando(5, 20);
		int h = rando(5, 20);
		int x = rando(0, MAP_W - w);
		int y = rando(0, MAP_H - h);
		
		for (int a = x; a < x + w; a++)
			for (int b = y; b < y + h; b++)
				world[b][a] = 'H';
	}
}

int main() {
	world = new char*[MAP_H];
	for (int i = 0; i < MAP_H; i++) {
		world[i] = new char[MAP_W];
	}
	
	worldview = new char*[DISP_H];
	for (int i = 0; i < DISP_H; i++)
		worldview[i] = new char[DISP_W];
	
	generate();
	
	// fix spawning in invalid spots
	while (world[view.second][view.first] >= 'A' && world[view.second][view.first] <= 'Z') {
		view.first = rando(1, MAP_W - 1);
		view.second = rando(1, MAP_H - 1);
	}
	
	// spawn initial enemies
	for (int i = 0; i < 5; i++) {
		int x = rando(view.first - DISP_W / 2, view.first + DISP_W / 2);
		int y = rando(view.second - DISP_H / 2, view.second + DISP_H / 2);
		
		while (x >= 0 && x < MAP_W && y >= 0 && y < MAP_H && world[y][x] >= 'A' && world[y][x] <= 'Z') {
			x = rando(view.first - DISP_W / 2, view.first + DISP_W / 2);
			y = rando(view.second - DISP_H / 2, view.second + DISP_H / 2);
		}
		
		enemies.push_back(Enemy({x,y}));
	}
	
	render();
	
	while (_getwch()) {
		auto prevView = view;
		
		if (isKeyPressed('W'))
			view.second--;
		if (isKeyPressed('A'))
			view.first--;
		if (isKeyPressed('S'))
			view.second++;
		if (isKeyPressed('D'))
			view.first++;
		
		// check if out of bounds or invalid
		if ((view.first - (DISP_W / 2) <= 0) ||
			(view.first - (DISP_W / 2) + DISP_W > MAP_W) ||
			(view.second - (DISP_H / 2) <= 0) ||
			(view.second - (DISP_H / 2) + DISP_H > MAP_H) ||
			(world[view.second][view.first] >= 'A' && world[view.second][view.first] <= 'Z')) {
				
			view = prevView;
		}
		
		// check if attacking enemy
		for (int i = 0; i < enemies.size(); i++) {
			if (view.first == enemies[i].pos.first && view.second == enemies[i].pos.second) {
				enemies[i].TakeDamage(rando(1,10));
				
				if (enemies[i].health != 0) {
					health -= enemies[i].GetDamage();
				}
				else {
					enemies.erase(enemies.begin() + i);
					i--;
				}
				
				view = prevView;
			}
		}
		
		render();
	}
}