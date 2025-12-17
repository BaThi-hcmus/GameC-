#pragma once

#include <stack>
#include "State.h"

using namespace std;

class State;

class StateManager {
private:
    bool m_IsRunning;
    stack <State*> m_StateStack;
    State* m_CurrentState;
    State* m_NextState;
    static StateManager* m_Instance;
    StateManager();

public:

    static StateManager* getInstance();
    
    ~StateManager();

    void ChangeState(unsigned int stateType); 
    void PushState(unsigned int stateType);
    void PopState(); 
    void Quit();

    void RunStateChange();

    State* currentState() const;
    State* nextState() const;
    
    bool NeedToChangeState();
    bool HasState();
    bool IsRunning();
};