#pragma once

#include "InputListener.h"
#include "InputManager.h"

using namespace std;

class Player : public InputListener {

	InputManager* m_inputMgr;
	void keyDownEvent(int input);

	//variables
	int m_minX;
	int m_maxX;
	int m_minY;
	int m_maxY;

public:

	//variables
	int m_X;
	int m_Y;
	int m_PrevX;
	int m_PrevY;
	int m_score;
	string m_name;
	int m_colour;
	int m_AsciiChar;


	Player(InputManager* inputMgr, int x, int y, int ascii, string name, int colour); //constructor

	void AttachKeys(int a, int b, int c, int d);
	void SetBorders(int minX, int maxX, int minY, int maxY);

};