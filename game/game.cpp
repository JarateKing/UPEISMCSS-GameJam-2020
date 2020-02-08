#include <iostream>

using namespace std;

#define DISP_W 100
#define DISP_H 30
char** display;

void render() {
	for (int i = 0; i < DISP_H; i++) {
		for (int j = 0; j < DISP_W; j++) {
			cout << display[i][j];
		}
		cout << '\n';
	}
}

int main() {
	display = new char*[DISP_H];
	for (int i = 0; i < DISP_H; i++) {
		display[i] = new char[DISP_W];
		for (int j = 0; j < DISP_W; j++) {
			display[i][j] = '.';
		}
	}
	
	render();
}