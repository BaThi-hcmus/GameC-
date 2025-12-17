#pragma once

//#include "ResourceManager.h"
#include "StateManager.h"
//#include "StepManager.h"

class State {
public:
	State() {}
	virtual ~State() {}

	virtual void Exit() = 0;
	virtual void Pause() = 0;
	virtual void Resume() = 0;

	virtual void Init() = 0;
	virtual void Handle() = 0;
	virtual void Render() = 0;

	static State* CreateState(unsigned int state);
};

