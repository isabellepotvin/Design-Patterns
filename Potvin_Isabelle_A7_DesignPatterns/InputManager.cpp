#include "InputManager.h"

InputManager::InputManager() {  //constructor

}

bool InputManager::Attach(int input) {

	//checks if the inputs have already been registered
	for (unsigned int i = 0; i < m_AttachedInputs.size(); i++) {
		if (input == m_AttachedInputs[i]) {
			return false;
		}
	}

	m_AttachedInputs.push_back(input); //registers input
}

void InputManager::Detach(int input) {

	//checks that the input is registered
	for (unsigned int i = 0; i < m_AttachedInputs.size(); i++) {
		if (input == m_AttachedInputs[i]) {
			m_AttachedInputs.erase(m_AttachedInputs.begin() + i); //erases input
			return;
		}
	}

}

void InputManager::Notify(int input) {

	if (m_Listeners.size() > 0) { //checks that there is at least one listener
		for (unsigned int i = 0; i < m_AttachedInputs.size(); i++) { //runs through all the attached inputs
			if (input == m_AttachedInputs[i]) { //checks that the input is registered
				for (int i = 0; i < m_Listeners.size(); i++){ //runs through all the listeners
					m_Listeners[i]->keyDownEvent(input); //calls the overridden function
				}
			}
		}
	}

}

void InputManager::SetListeners(InputListener* listener) {
	m_Listeners.push_back(listener);
}