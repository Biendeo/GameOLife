// GameOLife.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Game.h"
#include <ctime>

using namespace Biendeo;
using namespace rlutil;

int main() {
	setConsoleTitle("THE GAME OF LIFE!!!");
	Game g(tcols() - 1, trows() - 1);
	hidecursor();
	g.Randomise();

	int keyPress = KEY_NUMDEL;
	int lastKeyPress = KEY_NUMDEL;

	const int refreshFrequency = 20;
	double refreshRate = 1 / static_cast<double>(refreshFrequency);
	double currentFrameTime = 0.0f;
	double deltaTime = 0.0f;

	const int framesPerGeneration = 2;
	int currentFramesThisGeneration = 0;

	clock_t lastUpdate = clock();
	int cursorX = 0;
	int cursorY = 0;
	bool editing = false;

	while (lastKeyPress != 'q') {
		clock_t currentUpdate = clock();
		deltaTime = static_cast<double>(currentUpdate - lastUpdate) / CLOCKS_PER_SEC;
		lastUpdate = currentUpdate;

		if (keyPress != 0) {
			lastKeyPress = keyPress;
		}

		currentFrameTime += deltaTime;

		if (currentFrameTime >= refreshRate) {
			if (editing) {
				if (lastKeyPress == 'w') {
					if (!g.IsOutOfBound(cursorX, cursorY - 1)) {
						cursorY--;
						locate(cursorX + 1, cursorY + 1);
					}
				} else if (lastKeyPress == 's') {
					if (!g.IsOutOfBound(cursorX, cursorY + 1)) {
						cursorY++;
						locate(cursorX + 1, cursorY + 1);
					}
				} else if (lastKeyPress == 'a') {
					if (!g.IsOutOfBound(cursorX - 1, cursorY)) {
						cursorX--;
						locate(cursorX + 1, cursorY + 1);
					}
				} else if (lastKeyPress == 'd') {
					if (!g.IsOutOfBound(cursorX + 1, cursorY)) {
						cursorX++;
						locate(cursorX + 1, cursorY + 1);
					}
				} else if (lastKeyPress == 'p') {
					editing = false;
					hidecursor();
					g.Draw();
				} else if (lastKeyPress == 'b') {
					if (g.Toggle(cursorX, cursorY)) {
						std::cout << "#";
					} else {
						std::cout << " ";
					}
					locate(cursorX + 1, cursorY + 1);
				}
			} else {
				if (lastKeyPress == 'p') {
					editing = true;
					showcursor();
					locate(cursorX + 1, cursorY + 1);
				} else {
					currentFramesThisGeneration++;
					while (currentFramesThisGeneration >= framesPerGeneration) {
						g.NextGeneration();
						g.Draw();
						currentFramesThisGeneration -= framesPerGeneration;
					}
				}
			}
			currentFrameTime -= refreshRate;
			lastKeyPress = 0;
		}

		keyPress = nb_getch();
	}

	showcursor();

	return 0;
}

