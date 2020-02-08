#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);

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
			printf("%c", world[view.second - (DISP_H / 2) + i][view.first - (DISP_W / 2) + j]);
		}
		printf("\n");
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
	
	while (_getwch()) {
		if (GetKeyState('W') & 0x8000)
			view.second--;
		if (GetKeyState('A') & 0x8000)
			view.first--;
		if (GetKeyState('S') & 0x8000)
			view.second++;
		if (GetKeyState('D') & 0x8000)
			view.first++;
		
		render();
	}
}