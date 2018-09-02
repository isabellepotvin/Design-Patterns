#pragma once
#include <string>
#include <random>
#include <time.h>
#include <iostream>

using namespace std;

//function prototypes
void gotoXY(int x, int y);
void textColour(int colour);


enum class NPCTypes { Tanzanite, Topaz, Musgravite, RedBeryl, Diamond, Jade };


class NPC
{

public:

	//variables
	int m_X;
	int m_Y;
	NPCTypes m_type;
	string m_name;
	int m_colour;
	int m_ascii;

	void draw(int x, int y) {
		gotoXY(x, y);
		textColour(m_colour);
		cout << (char)m_ascii;
	}
};