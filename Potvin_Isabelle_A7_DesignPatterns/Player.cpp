#include "Player.h"

//function prototypes
void gotoXY(int x, int y);
void textColour(int colour);

//constructor
Player::Player(InputManager* inputMgr, int x, int y, int ascii, string name, int colour) {
	
	m_inputMgr = inputMgr;

	//sets initial position
	m_X = x;
	m_Y = y;
	m_PrevX = x;
	m_PrevY = y;

	m_AsciiChar = ascii; //sets ascii character
	m_name = name; //sets player's name
	m_score = 0; //sets the score to zero
	m_colour = colour; //sets the colour associated with the player
}


void Player::keyDownEvent(int input) {
	
	switch (input) {
	case 'w':
	case 72:
		m_Y--; //move up
		break;

	case 's':
	case 80:
		m_Y++; //move down
		break;

	case 'd':
	case 77:
		m_X++; //move right
		break;
	
	case 'a':
	case 75:
		m_X--; //move left
		break;

	default:
		break;
	}

	//if the player has hit a border
	if (m_Y < m_minY || m_Y > m_maxY || m_X < m_minX || m_X > m_maxX) {
		m_X = m_PrevX;
		m_Y = m_PrevY;
	}
}

void Player::AttachKeys(int a, int b, int c, int d) {
	
	//attaches the player keys
	m_inputMgr->Attach(a);
	m_inputMgr->Attach(b);
	m_inputMgr->Attach(c);
	m_inputMgr->Attach(d);
}

void Player::SetBorders(int minX, int maxX, int minY, int maxY) {

	//sets the mins and maxs of the player
	m_minX = minX;
	m_maxX = maxX;
	m_minY = minY;
	m_maxY = maxY;
}
