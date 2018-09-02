#pragma once

#include "InputListener.h"

using std::vector;

class InputManager{

public:

	InputManager(); //constructor

	bool Attach(int input);
	void Detach(int input);
	void Notify(int input);

	void SetListeners(InputListener* listener);


private:

	//variables
	vector<InputListener*> m_Listeners;
	vector<int> m_AttachedInputs;


};
