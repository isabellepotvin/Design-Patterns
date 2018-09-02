/*

Isabelle Potvin
December 5, 2017
Assignment 7 - Design Patterns


Objective:
This program allows users to play a game that was created using the Singleton, Observer, and Factory design patterns. 
America's Next Top Robber is a two-player game where the users are competing against each other to collect 'gems' and to 
try and earn more points than their opponent. (More details are provided in the "How to Play" section of the application.)

Design Patterns:
- I have implemented the Singleton design pattern with both the timer manager and the NPCFactory.
- I have also used the Observer design pattern to observe if any of the WASD and/or arrow keys are pressed. If they are, 
  the input managers notify the functions that "move" the players.
- Finally, I used the Factory design pattern to create the 6 different types of gems throughout my game.

*/


#include "InputListener.h"
#include "InputManager.h"
#include "Player.h"
#include "TimerMgr.h"
#include "NPCFactory.h"



enum States {
	MainMenu,
	Game,
	Instructions,
	Exit
};



//function prototypes
States mainMenu();
void game();
void instructions();

void drawBoard(Player* player1, Player* player2);
void displayScore(Player* player1, Player* player2);
void drawPlayers(Player* player1, Player* player2);
void createGem(Player* player1, Player* player2, vector<NPC*>* gems);
void timerEnd(Player* player1, Player* player2, vector<NPC*>* gems);
bool collision(Player* player, vector<NPC*>* gems, NPC* wantedGem);

void gotoXY(int x, int y);
void textColour(int colour);






int main() {

	srand(time(NULL));

	//variables
	States currentState = MainMenu;

	//switches through the different states until the user decides to 'exit'
	do {
		switch (currentState) {
		
		//MAIN MENU
		case MainMenu:
			currentState = mainMenu(); //calls function that displays the main menu
			break;

		//GAME
		case Game:
			game(); //calls function that runs through the game
			currentState = MainMenu; //returns to main menu after user is done the game
			break;

		//DISPLAYS INSTRUCTIONS
		case Instructions:
			instructions(); //calls function that displays the instructions on how to play
			currentState = MainMenu; //returns to main menu after user presses enter
			break;

		//DEFAULT (invalid state)
		default:
			system("cls");
			textColour(15); //sets the text colour to white
			cout << "Invalid state";
			system("pause");
			break;
		}
	} while (currentState != Exit);

	//displays exit message
	system("cls");
	gotoXY(40, 10);
	textColour(15); //sets the text colour to white
	cout << "Thanks for playing! Goodbye.";
	gotoXY(40, 12);

	system("pause");

	return 0;
}






#pragma region STATE RELATED FUNCTIONS

//this function diplays the main menu and prompts users to select a state
States mainMenu() {

	system("cls");
	textColour(15); //sets the text colour to white

	//variables
	string input;
	int choice;
	int x = 38;
	int y = 10;
	bool isValid;

	//displays welcome message
	gotoXY(x - 12, y - 4);
	cout << "*  *  *  *  *   Welcome to America's Next Top Robber   *  *  *  *  *";

	//displays menu options
	gotoXY(x, y);
	cout << "Please select one of the following options:";
	gotoXY(x, y + 2);
	cout << "   1. Play Game";
	gotoXY(x, y + 3);
	cout << "   2. How to Play";
	gotoXY(x, y + 4);
	cout << "   3. Exit";


	//asks user to enter their choice
	do {

		isValid = true;

		gotoXY(x, y + 8);
		cout << "Enter your selection:                                                 ";
		gotoXY(x + 22, y + 8);
		getline(cin, input);



		//checks for invalid choice
		if (input.size() == 1) {

			choice = input[0] - 48; //saves input as an int

			//checks if the number is between 1 and 3
			if (choice < 1 || choice > 3) {
				isValid = false;
			}

		}
		else { isValid = false; }

		//displays error message
		if (!isValid) {
			gotoXY(x, y + 9);
			cout << "Invalid choice.";
		}

	} while (!isValid); //loops until user enters valid choice

	return (States)choice; //return user's choice

}




#pragma region GAME RELATED FUNCTIONS

//this function draws the elements of the game that don't change
void drawBoard(Player* player1, Player* player2) {

	textColour(15); //sets the text colour to white

	//draws horizontal line
	gotoXY(0, 2);
	for (int i = 0; i < 120; i++) {
		cout << (char)196;
	}

	//draws vertical line
	gotoXY(50, 0);
	cout << (char)179;
	gotoXY(50, 1);
	cout << (char)179;
	gotoXY(50, 2);
	cout << (char)193;

	//draws vertical line
	gotoXY(70, 0);
	cout << (char)179;
	gotoXY(70, 1);
	cout << (char)179;
	gotoXY(70, 2);
	cout << (char)193;

	//displays player1's name
	gotoXY(2, 1);
	textColour(player1->m_colour);
	cout << setw(20) << setfill(' ') << left << player1->m_name;

	//displays player2's name
	gotoXY(98, 1);
	textColour(player2->m_colour);
	cout << setw(20) << setfill(' ') << right << player2->m_name;

}

//this function displays each players' score at the top of the console window
void displayScore(Player* player1, Player* player2) {
		
	//displays player1's score
	textColour(player1->m_colour);
	gotoXY(28, 1);
	cout << setw(20) << setfill(' ') << right << player1->m_score;

	//displays player2's score
	textColour(player2->m_colour);
	gotoXY(73, 1);
	cout << setw(20) << setfill(' ') << left << player2->m_score;
}

//this function draws the players 
void drawPlayers(Player* player1, Player* player2) {

	//erases previous player 1
	if (player1->m_X != player1->m_PrevX || player1->m_Y != player1->m_PrevY) {
		gotoXY(player1->m_PrevX, player1->m_PrevY);
		cout << (char)255; //draws blank
		player1->m_PrevX = player1->m_X;
		player1->m_PrevY = player1->m_Y;
	}

	//erases previous player 2
	if (player2->m_X != player2->m_PrevX || player2->m_Y != player2->m_PrevY) {
		gotoXY(player2->m_PrevX, player2->m_PrevY);
		cout << (char)255; //draws blank
		player2->m_PrevX = player2->m_X;
		player2->m_PrevY = player2->m_Y;
	}

	//draws player 1
	textColour(player1->m_colour);
	gotoXY(player1->m_X, player1->m_Y);
	cout << (char)player1->m_AsciiChar;

	//draws player 2
	textColour(player2->m_colour);
	gotoXY(player2->m_X, player2->m_Y);
	cout << (char)player2->m_AsciiChar;
}

//this funtion is called when the initial timers end (it creates a new gem and a new timer)
void createGem(Player* player1, Player* player2, vector<NPC*>* gems) {
	
	//sets a random location
	int x, y;
	bool collision;
	do {
		collision = false;

		x = rand() % 120; //random x
		y = rand() % 27 + 3; //random y

		//checks if the another gem is already in the random location
		for (int i = 0; i < gems->size(); i++) {
			if ((*gems)[i] != nullptr) {
				if (x == (*gems)[i]->m_X && y == (*gems)[i]->m_Y) {
					collision = true;
				}
			}
		}
	} while ((x == player1->m_X && y == player1->m_Y) || (x == player2->m_X && y == player2->m_Y) || collision == true); //loops if there is already a player or a gem in the random location


	gems->push_back(NPCFactory::GetInstance()->createNPC((NPCTypes)(rand() % 6), x, y)); //creates new gem
									 
	gems->back()->draw(x, y); //draws the gem

	TimerMgr::GetInstance()->createTimer(10000, timerEnd, player1, player2, gems); //creates new timer
}
//this function is called when the new timers end (it calls the function createGem and it erases the oldest gem)
void timerEnd(Player* player1, Player* player2, vector<NPC*>* gems) {

	createGem(player1, player2, gems);

	//erases oldest gem
	if ((*gems)[0] != nullptr) {
		gotoXY((*gems)[0]->m_X, (*gems)[0]->m_Y);
		cout << ' ';
		delete (*gems)[0];
	}
	gems->erase(gems->begin());
}

//this function checks if a player has captured a gem and assigns points accordingly
bool collision(Player* player, vector<NPC*>* gems, NPC* wantedGem) {
	
	for (int i = 0; i < gems->size(); i++) {
		if ((*gems)[i] != nullptr) {
			if (player->m_X == (*gems)[i]->m_X && player->m_Y == (*gems)[i]->m_Y) { //checks if the player collides with a gem

				if ((*gems)[i]->m_type == wantedGem->m_type) { //checks if it is the wanted gem
					
					player->m_score += 5000;

					//deletes gem
					delete (*gems)[i];
					(*gems)[i] = nullptr;

					return true;
				}
				else if (player->m_score > 1050) { //if it is not the wanted gem
					player->m_score -= 1050;
				}
				else { //if it is not the wanted gem and their score is less than 1050
					player->m_score = 0;
				}

				//deletes gem
				delete (*gems)[i];
				(*gems)[i] = nullptr;

				return false;
			}
		}
	}
	return false;
}

#pragma endregion

//this function runs through the game
void game() {

	system("cls");

	//variables
	int key = 0;
	const int asciiChar = 219;
	string nameP1, nameP2;
	vector<NPC*> gems;
	NPC* wantedGem;
	bool gemFound = false;

	//prompts player 1 to enter their name
	do {
		gotoXY(30, 10);
		cout << "Player 1, please enter your name: ";
		getline(cin, nameP1); 
		if (nameP1.length() > 20 || nameP1.length() < 1) { //if the entry is invalid
			gotoXY(64, 10);
			cout << "                                                        ";
			gotoXY(30, 11);
			cout << "** Invalid name. Please enter a name that is less than 20 characters.";
		}
		else {
			gotoXY(30, 11);
			cout << "                                                                      ";
		}
	} while (nameP1.length() > 20 || nameP1.length() < 1);

	//prompts player 2 to enter their name
	do {
		gotoXY(30, 13);
		cout << "Player 2, please enter your name: ";
		getline(cin, nameP2);
		if (nameP2.length() > 20 || nameP2.length() < 1) { //if the entry is invalid
			gotoXY(64, 13);
			cout << "                                                        ";
			gotoXY(30, 14);
			cout << "** Invalid name. Please enter a name that is less than 20 characters.";
		}
		else {
			gotoXY(30, 11);
			cout << "                                                                      ";
		}
	} while (nameP2.length() > 20 || nameP2.length() < 1);



	system("cls");

	//creates the input managers for the players
	InputManager* inputMgr1 = new InputManager(); //for player 1
	InputManager* inputMgr2 = new InputManager(); //for player 2

	//creates players
	Player* player1 = new Player(inputMgr1, 30, 15, asciiChar, nameP1, 11);
	Player* player2 = new Player(inputMgr2, 90, 15, asciiChar, nameP2, 13);

	//registers the keys for the players
	player1->AttachKeys('w', 'a', 's', 'd');
	player2->AttachKeys(72, 75, 77, 80);

	//sets the limits of the players movement
	player1->SetBorders(0, 119, 3, 29);
	player2->SetBorders(0, 119, 3, 29);

	//sets each player as a listener
	inputMgr1->SetListeners(player1);
	inputMgr2->SetListeners(player2);

	//displays intial game console
	drawBoard(player1, player2);
	displayScore(player1, player2);
	drawPlayers(player1, player2);

	//creates timers
	TimerMgr::GetInstance()->createTimer(3000, createGem, player1, player2, &gems);
	TimerMgr::GetInstance()->createTimer(4000, createGem, player1, player2, &gems);
	TimerMgr::GetInstance()->createTimer(5000, createGem, player1, player2, &gems);
	TimerMgr::GetInstance()->createTimer(6000, createGem, player1, player2, &gems);
	TimerMgr::GetInstance()->createTimer(7000, createGem, player1, player2, &gems);
	TimerMgr::GetInstance()->createTimer(8000, createGem, player1, player2, &gems);
	TimerMgr::GetInstance()->createTimer(9000, createGem, player1, player2, &gems);
	TimerMgr::GetInstance()->createTimer(10000, createGem, player1, player2, &gems);
	TimerMgr::GetInstance()->createTimer(11000, createGem, player1, player2, &gems);
	TimerMgr::GetInstance()->createTimer(12000, createGem, player1, player2, &gems);
	TimerMgr::GetInstance()->createTimer(12500, createGem, player1, player2, &gems);
	TimerMgr::GetInstance()->createTimer(13500, createGem, player1, player2, &gems);
	TimerMgr::GetInstance()->createTimer(14500, createGem, player1, player2, &gems);
	TimerMgr::GetInstance()->createTimer(15500, createGem, player1, player2, &gems);
	TimerMgr::GetInstance()->createTimer(16500, createGem, player1, player2, &gems);
	TimerMgr::GetInstance()->createTimer(17500, createGem, player1, player2, &gems);
	TimerMgr::GetInstance()->createTimer(18500, createGem, player1, player2, &gems);
	TimerMgr::GetInstance()->createTimer(19500, createGem, player1, player2, &gems);
	TimerMgr::GetInstance()->createTimer(20500, createGem, player1, player2, &gems);
	TimerMgr::GetInstance()->createTimer(21500, createGem, player1, player2, &gems);
	TimerMgr::GetInstance()->createTimer(22500, createGem, player1, player2, &gems);


	//displays the wanted gem
	gotoXY(52, 0);
	textColour(7); //sets the text colour to a pale white
	cout << "Mr. Banks wants a";
	wantedGem = NPCFactory::GetInstance()->createNPC((NPCTypes)(rand() % 6), 0, 0); //picks random gem
	gotoXY(51 + (int)((19 - wantedGem->m_name.length() - 4) / 2), 1); //goes to a location (centres the text)
	textColour(wantedGem->m_colour);
	cout << (char)wantedGem->m_ascii << " " << wantedGem->m_name << " " << (char)wantedGem->m_ascii; //displays the wanted gem

	
	//loops through the game until someone wins or until the escape key is pressed
	do {

		if (_kbhit()) { //if a player hits a key
			key = _getch(); //saves key that was hit
			inputMgr1->Notify(key); //notifies the listener
			inputMgr2->Notify(key); //notifies the listener

			gemFound = collision(player1, &gems, wantedGem); //checks if player1 has landed on a gem

			if (!gemFound) {
				gemFound = collision(player2, &gems, wantedGem); //checks if player2 has landed on a gem
			}

		}

		TimerMgr::GetInstance()->tickTimers(); //checks if the timers have ended
		drawPlayers(player1, player2); //draws the players
		displayScore(player1, player2); //displays the score

		//displays a new wanted gem
		if (key != 27 && player1->m_score < 50000 && player2->m_score < 50000) {
			if (gemFound) {
				delete wantedGem;
				wantedGem = NPCFactory::GetInstance()->createNPC((NPCTypes)(rand() % 6), 0, 0); //picks random gem
				gotoXY(51, 1);
				cout << "                   ";
				gotoXY(51 + (int)((19 - wantedGem->m_name.length() - 4) / 2), 1); //goes to a location (centres the text)
				textColour(wantedGem->m_colour);
				cout << (char)wantedGem->m_ascii << " " << wantedGem->m_name << " " << (char)wantedGem->m_ascii; //displays the wanted gem
				gemFound = false;
			}
		}

	} while (key != 27 && player1->m_score < 50000 && player2->m_score < 50000);

	
	//if a player has won the game
	if (player1->m_score >= 50000 || player2->m_score >= 50000) {

		Sleep(2000); //program sleeps for a few seconds
		system("cls");
		textColour(15); //sets the text colour to white

		//displays final scores
		gotoXY(40, 7);
		cout << "*  *  *  FINAL SCORES  *  *  *";

		//displays player1's score
		gotoXY(40, 9);
		textColour(player1->m_colour);
		cout << setw(20) << left << player1->m_name << "     ";
		cout << player1->m_score;

		//displays player2's score
		gotoXY(40, 10);
		textColour(player2->m_colour);
		cout << setw(20) << left << player2->m_name << "     ";
		cout << player2->m_score;

		//displays horizontal line
		gotoXY(30, 12);
		textColour(7); //sets the text colour to a pale white
		cout << "- - - - - - - - - - - - - - - - - - - - - - - - - -";


		//displays winner
		gotoXY(40, 14);
		textColour(15); //sets the text colour to white
		if (player1->m_score >= 50000) { //if player 1 wins
			cout << "Great work " << player1->m_name << ",";
			
		}
		else if (player2->m_score >= 50000) { //if player 2 wins
			cout << "Great work " << player2->m_name << ",";
		}

		gotoXY(40, 15);
		cout << "you are America's next top robber!";

		//pauses until user hits the spacebar
		gotoXY(40, 18);
		cout << "Press the spacebar to continue...";
		while (key != 32) {
			if (_kbhit()) {
				key = _getch();
			}
		}
	}

	//deletes the wanted gem
	delete wantedGem;

	//deletes the players
	delete player1;
	player1 = nullptr;
	delete player2;
	player2 = nullptr;

	//deletes the input managers
	delete inputMgr1;
	inputMgr1 = nullptr;
	delete inputMgr2;
	inputMgr2 = nullptr;

	//deletes the remaining NPCs
	for (int i = 0; i < gems.size(); i++) {
		if (gems[i] != nullptr) {
			delete gems[i];
			gems.erase(gems.begin() + i);
			i--;
		}
	}

	//deletes the timers (the ones that did not finish)
	for (int i = 0; i < TimerMgr::GetInstance()->m_timers.size(); i++) {
		delete TimerMgr::GetInstance()->m_timers[i];
		TimerMgr::GetInstance()->m_timers.erase(TimerMgr::GetInstance()->m_timers.begin() + i);
		i--;
	}
}


//this function dispays the rules of the game
void instructions() {

	system("cls");
	textColour(15); //sets the text colour to white

	//variables
	int x = 11;
	int y = 1;

	//displays the rules
	gotoXY(x, y);
	cout << "*  *  *  *  *  *  *  *  *  *  *  *  *  *   HOW TO PLAY   *  *  *  *  *  *  *  *  *  *  *  *  *  *";

	gotoXY(x, y + 3);
	cout << "                                            Objective";
	gotoXY(x, y + 5);
	cout << "Mr. Banks is hosting America's Next Top Robber! Two robbers will compete to win this edition of ";
	gotoXY(x, y + 6);
	cout << "the competition. Gems will appear throughout the city and each player must run to capture as ";
	gotoXY(x, y + 7);
	cout << "many as possible to be crowned America's Next Top Robber. ";

	gotoXY(x, y + 10);
	cout << "                                            Gameplay";
	gotoXY(x, y + 12);
	cout << "Mr. Banks will request a certain type of gem for the robbers to capture. The requested gem type ";
	gotoXY(x, y + 13);
	cout << "will be displayed at the top of the console window. When a robber grabs a correct gem, Mr. Banks ";
	gotoXY(x, y + 14);
	cout << "will reward the robber with 5,000 points and he will request another gem. If a robber captures ";
	gotoXY(x, y + 15);
	cout << "the wrong gem, they will lose 1,050 points. The first robber to reach 50,000 points will be ";
	gotoXY(x, y + 16);
	cout << "crowned America's Next Top Robber.";

	gotoXY(x, y + 19);
	cout << "                                            Controls";
	gotoXY(x, y + 21);
	cout << "                        - Player 1 moves using the WASD keys.";
	gotoXY(x, y + 22);
	cout << "                        - Player 2 moves using the arrow keys.";
	gotoXY(x, y + 23);
	cout << "                        - Press escape at any time to exit the current game.";



	//displays the system pause
	gotoXY(x + 35, y + 27);
	system("pause");
}

#pragma endregion


#pragma region OTHER FUNCTIONS

//this function moves the cursor to a specific coordinate
void gotoXY(int x, int y)
{
	HANDLE hStdout = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD position = { x, y };
	SetConsoleCursorPosition(hStdout, position);
	CONSOLE_CURSOR_INFO cursorInfo;
	cursorInfo.bVisible = false;
	cursorInfo.dwSize = 10;
	SetConsoleCursorInfo(hStdout, &cursorInfo);
}

//this function changes the colour of the text
void textColour(int colour) {
	HANDLE ConsoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(ConsoleHandle, colour);
}

#pragma endregion