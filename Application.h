#pragma once
#include <iostream>
#include "GameManager/StateManager.h"

using namespace std;

class Application {
public:
	void Run();
	~Application();
private:
	void Init(); //khởi tạo cửa sổ và trạng thái game
	void Update();// cập nhật logic
	void Handle();//xử lí input 
	void Render();//vẽ frame
};