#include <iostream>
#include <thread>
#include <chrono>

//Libraries that help avoid race condition (data races)
#include <mutex> //"mutual exclusion" library - for concurrent execution, prevents access to shared resources
#include <atomic> //"atomic" library - for shared variable, lockless


using namespace std;

bool DidQuit = false;
bool ShouldDecrementLife = false;
mutex Mutex;

//Methods that ensure that Lives does not get past 0 will be commented

struct Character {
	float Position = 0.0f;

	int Score = 0;
	//Method: Atomic Declaration
	//atomic<int> Lives = 1;
	int Lives = 1;

	void DisplayStats() {
		cout << "Lives: " << Lives << endl;
	}
};

Character Player;

void UpdateCharacter() {
	while(!DidQuit) {
		if(ShouldDecrementLife) {

			//Method: Mutex Locking
			//lock_guard<mutex> Guard(Mutex);

			if(Player.Lives > 0) {
				//this_thread::sleep_for(chrono::milliseconds(500));
				std::this_thread::yield();
				Player.Lives--;
			}
			ShouldDecrementLife = false;
		}
	}
}

void ProcessInput() {
	while(!DidQuit) {
		cout << "'a' to decrement player life" << endl;
		cout << "'d' to display player stats" << endl;
		cout << "'q' to quit" << endl;

		char UserInput;
		cin >> UserInput;

		switch(UserInput) {
			case 'a':
				ShouldDecrementLife = true;
				break;
			case 'd':
				Player.DisplayStats();
				break;
			case 'q':
				DidQuit = true;
				break;
			default:
				break;
		}
		DidQuit = (UserInput == 'q');
	}
}

int main() {
	thread InputHandler(ProcessInput);
	thread CharacterUpdate1(UpdateCharacter);
	thread CharacterUpdate2(UpdateCharacter);

	InputHandler.join();
	CharacterUpdate1.join();
	CharacterUpdate2.join();

	return 0;
}