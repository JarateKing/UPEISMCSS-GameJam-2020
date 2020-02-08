#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
#define fastio ios_base::sync_with_stdio(0);cin.tie(0);

#define DISP_W 100
#define DISP_H 30
#define MAP_W 200
#define MAP_H 200

char** world;

pair<int, int> view = {100,100};

mt19937 rng((uint32_t)chrono::steady_clock::now().time_since_epoch().count());
bool rando() {
	return rng() % 2;
}
int rando(int min, int max) {
	if (min == max) return min;
	return rng() % (max - min) + min;
}

bool isKeyPressed(char c) {
	if (c >= 'a' && c <= 'z')
		c = c - 'a' + 'A';
	return GetKeyState(c) & 0x8000;
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
		if ((view.first - (DISP_W / 2) < 0) || (view.first - (DISP_W / 2) + DISP_W >= MAP_W) || (view.second - (DISP_H / 2) < 0) || (view.second - (DISP_H / 2) + DISP_H >= MAP_H))
			view = prevView;
		
		render();
	}
}