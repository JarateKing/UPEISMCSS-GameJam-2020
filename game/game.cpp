#include <bits/stdc++.h>
using namespace std;

#define DISP_W 100
#define DISP_H 30
#define MAP_W 1000
#define MAP_H 1000

char** world;

pair<int, int> view = {500,500};

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
bool rando() {
	return rng() % 2;
}
int rando(int min, int max) {
	if (min == max) return min;
	return rng() % (max - min) + min;
}

void render() {
	for (int i = 0; i < DISP_H; i++) {
		for (int j = 0; j < DISP_W; j++) {
			cout << world[view.second - (DISP_H / 2) + i][view.first - (DISP_W / 2) + j];
		}
		cout << '\n';
	}
}

int main() {
	world = new char*[MAP_H];
	for (int i = 0; i < MAP_H; i++) {
		world[i] = new char[MAP_W];
		for (int j = 0; j < MAP_W; j++) {
			world[i][j] = rando() ? '.' : ',';
		}
	}
	
	render();
	
	char input;
	while (input = _getwch() && input != EOF) {
		if (input == 'W')
			view.second--;
		if (input == 'A')
			view.first--;
		if (input == 'S')
			view.second++;
		if (input == 'D')
			view.first++;
		
		render();
	}
}