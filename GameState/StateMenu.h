#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "../GameManager/StateManager.h"
#include <iostream>

using namespace std;

class StateMenu : public State {
private:
	bool isStop;
	int _selectedOption; //lựa chọn của user
	// các biến liên quan đến UI
public:

	StateMenu();
	~StateMenu();

	void Exit();
	void Pause();
	void Resume();

	void Init();
	void Handle();
	void Render();
	int getSelectedOption();
};
