#pragma once

#include <iostream>
#include <string>
#include <vector>
#include <iomanip>
#include <windows.h>
#include <conio.h>

using namespace std;

class InputListener {
public:
	virtual void keyDownEvent(int input) = 0;
};