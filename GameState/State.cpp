#include "State.h"

#include "StateNewGame.h"
// #include "StateLoadGame.h"
// #include "StateSetting.h"
// #include "StateAboutUs.h"
#include "StateMenu.h"

/**
 * @file State.cpp
 * @brief Factory pattern cho tạo các trạng thái (State) khác nhau trong game CARO.
 *
 * Các trạng thái được hỗ trợ:
 * - StateMenu (0): Menu chính - lựa chọn các chức năng
 * - StateNewGame (1): Bắt đầu trò chơi mới
 * - StateLoadGame (2): Tải game đã lưu
 * - StateSetting (3): Cài đặt game
 * - StateAboutUs (4): Thông tin về game
 *
 * @note Sử dụng Factory pattern để tạo instances của các State khác nhau,
 *       cho phép quản lý linh hoạt các loại trạng thái mà không cần biết
 *       chi tiết triển khai của từng loại.
 */

/**
 * @brief Factory method - tạo một instance của trạng thái dựa trên loại được yêu cầu.
 *
 * Hàm static này sử dụng Factory pattern để khởi tạo các đối tượng State
 * tương ứng với giá trị state được truyền vào. Mỗi trạng thái được tạo là
 * một instance mới được cấp phát bộ nhớ động (new).
 *
 * Các giá trị state được hỗ trợ:
 * - 0: StateMenu - Menu chính của game
 *   - Hiển thị các nút: New Game, Load Game, Setting, About Us, Quit
 * - 1: StateNewGame - Trò chơi mới
 *   - Khởi tạo bàn cờ rỗng (15x15)
 *   - Chuẩn bị để người chơi bắt đầu
 * - 2: StateLoadGame - Tải trò chơi từ file
 *   - Hiển thị danh sách các file lưu (5 slot)
 *   - Cho phép chọn và tải game đã lưu
 * - 3: StateSetting - Cài đặt game
 *   - Cho phép điều chỉnh các tùy chọn game
 * - 4: StateAboutUs - Thông tin về game
 *   - Hiển thị thông tin tác giả, phiên bản, v.v...
 *
 * @param state Mã số loại trạng thái cần tạo (0-4)
 *
 * @return Con trỏ đến State mới được tạo
 * @return nullptr nếu state không hợp lệ (không nằm trong 0-4)
 *
 * @note Người gọi phải chịu trách nhiệm xóa (delete) đối tượng được tạo
 *       để tránh rò rỉ bộ nhớ. Thường StateManager sẽ quản lý việc này.
 *
 * @warning Nếu state không được hỗ trợ (không trong khoảng 0-4), hàm trả về nullptr.
 *          Cần kiểm tra giá trị trả về trước khi sử dụng.
 *
 * @example
 * // Tạo StateMenu (menu chính)
 * State* menuState = State::CreateState(0);
 * if (menuState != nullptr) {
 *     menuState->Init();  // Khởi tạo trạng thái
 * }
 *
 * @example
 * // Trong StateManager::RunStateChange()
 * State* newState = State::CreateState(stateType);
 * if (newState != nullptr) {
 *     m_StateStack.push(newState);
 *     newState->Init();
 * }
 *
 * @see StateMenu
 * @see StateNewGame
 * @see StateLoadGame
 * @see StateSetting
 * @see StateAboutUs
 */
State* State::CreateState(unsigned int state)
{
	State* gameState = nullptr;
	switch (state) {
	case 0:
		gameState = new StateMenu();
		break;
	case 1: // New Game
		gameState = new StateNewGame();
		break;
	// case 2: // Load Game
	// 	gameState = new StateLoadGame();
	// 	break;
	// case 3: // Setting
	// 	gameState = new StateSetting();
	// 	break;
	// case 4:	// About us
	// 	gameState = new StateAboutUs();
	// 	break;
	default:
		break;
	}
	return gameState;
}
