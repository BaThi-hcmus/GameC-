#include "Application.h"

Application::~Application()
{
	//todo
}

/**
 * @brief Khởi tạo game.
 * 
 * - Tạo cửa sổ SFML toàn màn hình
 * - Giới hạn FPS ở 60
 * - Chuyển về trạng thái ban đầu (state 0)
 */
void Application::Init()
{
	// khởi tạo cửa sổ, thiết lập fps, chuyển về state ban đầu
	StateManager::getInstance()->ChangeState(0);
}

/**
 * @brief Xử lý sự kiện từ người dùng.
 * 
 * Chuyển sự kiện đến trạng thái hiện tại để xử lý
 * (ví dụ: click chuột, phím bấm).
 * 
 * @param event Sự kiện SFML cần xử lý
 */
void Application::Handle() 
{
	//currentState trỏ tới state hiện tại, gọi handle để bắt sự kiện của state tương ứng
	StateManager::getInstance()->currentState()->Handle();
}

/**
 * @brief Cập nhật logic game.
 * 
 * Kiểm tra và thực hiện chuyển đổi trạng thái nếu cần.
 * Được gọi mỗi frame trong game loop.
 */
void Application::Update()
{
	//kiểm tra nextState có khác null không
	// nếu có thì thực hiện chuyển trang (thêm vào stack)
	if (StateManager::getInstance()->NeedToChangeState()) {
		cout << "Co yeu cau chuyen state, bat dau chuyen..." << endl;
		StateManager::getInstance()->RunStateChange();
	}
}

/**
 * @brief Vẽ frame hiện tại.
 * 
 * Quy trình vẽ:
 * 1. Xóa frame cũ (màu nền trắng)
 * 2. Vẽ các thành phần của trạng thái hiện tại
 * 3. Hiển thị frame mới
 */
void Application::Render()
{
	//vẽ giao diện của state hiện tại
	StateManager::getInstance()->currentState()->Render();
}

/**
 * @brief Hàm chạy chính của game.
 * 
 * Triển khai game loop cơ bản:
 * 1. Khởi tạo game (Init)
 * 2. Vòng lặp chính:
 *    - Cập nhật logic (Update)
 *    - Xử lý input (Handle)
 *    - Vẽ frame (Render)
 * 3. Lặp cho đến khi:
 *    - Cửa sổ bị đóng HOẶC
 *    - StateManager báo dừng
 */
void Application::Run()
{
	//changeState : báo hiệu chuẩn bị chuyển trang 
	Init();

	while (StateManager::getInstance()->IsRunning()) {
		//kiểm tra nếu có yêu cầu chuyển trang thì chuyển 
		Update();

		Handle();

		//render giao diện của state tương ứng
		Render();
	}
	return;
}
