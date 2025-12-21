#include "StateManager.h"

StateManager* StateManager::m_Instance = nullptr;

StateManager::StateManager()
{
	m_CurrentState = nullptr;
	m_NextState = nullptr;
	m_IsRunning = true;
}

StateManager* StateManager::getInstance()
{
	if (m_Instance == nullptr) {
		m_Instance = new StateManager();
	}
	return m_Instance;
}

StateManager::~StateManager()
{
	while (!m_StateStack.empty()) {
		delete m_StateStack.top();
		m_StateStack.pop();
	}
	delete m_CurrentState;
	delete m_NextState;
	delete m_Instance;
}

void StateManager::ChangeState(unsigned int stateType)
{
	State* state = State::CreateState(stateType);
	m_NextState = state;
}

void StateManager::PushState(unsigned int stateType)
{
	State* state = State::CreateState(stateType);
	m_NextState = state;
}

void StateManager::PopState()
{
	if (!m_StateStack.empty()) {
		m_StateStack.pop();
	}
	m_CurrentState = m_StateStack.top();
}

void StateManager::Quit()
{
	m_IsRunning = false;
}

void StateManager::RunStateChange()
{
	if (m_NextState != nullptr) {
		m_StateStack.push(m_NextState);
		m_StateStack.top()->Init();
		m_CurrentState = m_NextState;
	}
	m_NextState = nullptr;
}

State* StateManager::currentState() const
{
	return m_CurrentState;
}

State* StateManager::nextState() const
{
	return m_NextState;
}

bool StateManager::NeedToChangeState()
{
	return m_NextState != nullptr;
}

bool StateManager::HasState()
{
	return m_StateStack.size() > 0;
}

bool StateManager::IsRunning()
{
	return m_IsRunning;
}

