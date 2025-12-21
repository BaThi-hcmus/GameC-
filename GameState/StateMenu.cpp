#include "StateMenu.h"
//#include "ResourceManager.h"

/**
 * @file StateMenu.cpp
 * @brief Triển khai StateMenu - trạng thái menu chính của game CARO.
 *
 * StateMenu là trạng thái đầu tiên được hiển thị khi game khởi động.
 * Cung cấp giao diện menu với 4 lựa chọn chính:
 * 1. New Game - Bắt đầu trò chơi mới
 * 2. Load Game - Tải game đã lưu
 * 3. Setting - Cài đặt game
 * 4. About Us - Thông tin về game
 *
 * Các tính năng chính:
 * - Hiệu ứng animation cho logo CARO (30 frame)
 * - Xử lý di chuyển chuột để highlight nút menu
 * - Xử lý click chuột để chọn tùy chọn
 * - Phát nhạc nền và âm thanh khi tương tác
 * - Zoom button khi di chuột vào (visual feedback)
 *
 * @note Sử dụng ResourceManager để tải tài nguyên (font, texture, âm thanh, nhạc)
 * @note Kế thừa từ class State (abstract base class)
 */

/**
 * @brief Constructor của StateMenu.
 *
 * Khởi tạo tất cả các thành viên dữ liệu:
 * - currentWidthLogoTitleRect: bề rộng frame logo animation (43px)
 * - currentLogoTitleFrameCout: số frame animation hiện tại (0-29)
 * - currentFrame, currentScreen: biến theo dõi frame/screen hiện tại
 * - isStop: cờ dừng animation sau khi chạy xong
 * - Các vị trí chuột (m_PositionMouseX, m_PositionMouseY)
 * - m_SelectedOption: tùy chọn được chọn (0-3 tương ứng với 4 nút menu)
 * - Con trỏ tài nguyên: Font, Sound, Music (nullptr ban đầu)
 * - Vector lưu Sprite nút menu (4 nút)
 * - Vector lưu Text tùy chọn (4 tùy chọn)
 * - Vector lưu vị trí zoom button
 *
 * @note Constructor không tải tài nguyên; việc tải được thực hiện trong Init()
 */
StateMenu::StateMenu()
{
	// khởi tạo các biến thành viên liên quan đến UI
}

/**
 * @brief Destructor của StateMenu.
 *
 * Giải phóng bộ nhớ của các tài nguyên:
 * - m_Font: font Minecraft.ttf
 * - m_ChooseOptionSound: âm thanh khi click tùy chọn
 * - m_MovedIntoSpriteSound: âm thanh khi di chuột vào nút
 * - m_MenuBackgroundMusic: nhạc nền menu
 *
 * @note Vector m_ButtonSprite, m_OptionText, m_ZoomButtonPosition tự động giải phóng
 *       vì là member variable của class
 * @note Sprite background và animation sử dụng texture từ ResourceManager
 *       nên không cần delete
 */
StateMenu::~StateMenu()
{
	// xóa con trỏ tài nguyên
}

void StateMenu::Exit()
{
}

/**
 * @brief Thoát khỏi StateMenu (được gọi khi chuyển sang state khác).
 *
 * Hiện tại hàm này trống - có thể được sử dụng để dừng âm thanh
 * hoặc làm sạch các tài nguyên tạm thời nếu cần.
 */
void StateMenu::Pause()
{
}

/**
 * @brief Tạm dừng StateMenu (hiện tại không được sử dụng).
 *
 * Hàm này trống - có thể được sử dụng trong tương lai nếu cần
 * tạm dừng logic menu (ví dụ: tạm dừng nhạc nền).
 */
void StateMenu::Resume()
{
}

/**
 * @brief Khởi tạo StateMenu - tải tất cả các tài nguyên.
 *
 * Quy trình khởi tạo chi tiết:
 *
 * 1. **Font**: Tải font Minecraft.ttf từ ResourceManager
 *
 * 2. **Hình nền (Background)**:
 *    - Tải texture "menu-background.png"
 *    - Scale theo kích thước màn hình
 *
 * 3. **Animation Logo CARO**:
 *    - Tải sprite sheet "caro-animation.png" (30 frame, mỗi frame 43x13 pixel)
 *    - Đặt frame đầu tiên (0, 0, 43, 13)
 *    - Scale lên 12x so với kích thước gốc
 *    - Đặt vị trí ở giữa trên cùng (420, 70)
 *
 * 4. **Text tùy chọn** (4 tùy chọn):\n *    - \"New game\" tại (535, 240)
 *    - \"Load game\" tại (520, 360)
 *    - \"Setting\" tại (530, 480)
 *    - \"About Us\" tại (505, 600)
 *    - Font size: 65, màu đen\n *
 * 5. **Nút menu** (4 nút):\n *    - Tải texture "button.png"
 *    - Tạo 4 nút tại các vị trí tương ứng với text\n *    - Scale nút theo kích thước màn hình\n *
 * 6. **Zoom button** (hiệu ứng hover):\n *    - Sử dụng cùng texture \"button.png\" nhưng lớn hơn\n *    - 4 vị trí tương ứng cho 4 nút menu\n *
 * 7. **Âm thanh và nhạc**:\n *    - Tải nhạc nền \"backgroundmusic1.mp3\" và phát nếu bật\n *    - Tải âm thanh click \"click-sound1.ogg\" (50% volume)\n *    - Tải âm thanh hover \"moved-into-sprite2.ogg\" (50% volume)\n *\n * @note Tất cả các tài nguyên được tải từ ResourceManager (Singleton)\n * @note Việc khởi tạo được gọi tự động khi StateManager chuyển sang StateMenu\n * @see ResourceManager\n */
void StateMenu::Init()
{
	cout << "Khoi tao giao dien state menu game" << endl;
}

/**
 * @brief Xử lý sự kiện trong StateMenu.
 *
 * Xử lý 3 loại sự kiện chính:\n *
 * 1. **KeyPressed** (Phím được nhấn):
 *    - ESC: Thoát game bằng cách gọi StateManager::getInstance()->Quit()
 *    - Kết thúc vòng lặp game\n *
 * 2. **MouseMoved** (Chuột di chuyển):
 *    - Cập nhật tọa độ chuột (m_PositionMouseX, m_PositionMouseY)
 *    - Kiểm tra xem chuột có di vào nút nào (hiện tại ghi chú cần fix để chỉ phát âm
 *      thanh khi di chuyển từ ngoài vào, không liên tục)
 *    - Ghi chú: \"!!! chinh lai khi di chuyen tu ngoai vao moi keu\"\n *
 * 3. **MouseButtonPressed** (Click chuột - nút trái):\n *    - Lặp qua 4 nút menu
 *    - Kiểm tra xem click có nằm trong bounds của nút nào không
 *    - Nếu có:
 *      - Đặt m_SelectedOption = i + 1 (1-4 tương ứng với các state 1-4)
 *      - Phát âm thanh click
 *      - Gọi StateManager::getInstance()->ChangeState(i + 1) để chuyển sang state tương ứng\n *
 * @param event Sự kiện SFML cần xử lý\n *
 * @note Chuỗi các state được chuyển:\n *       - Case 0 (New game) -> State 1 (StateNewGame)\n *       - Case 1 (Load game) -> State 2 (StateLoadGame)\n *       - Case 2 (Setting) -> State 3 (StateSetting)\n *       - Case 3 (About us) -> State 4 (StateAboutUs)\n *
 * @example
 * // Người dùng bấm ESC
 * // -> Handle() gọi StateManager::getInstance()->Quit()\n * // -> vòng lặp game kết thúc\n *
 * @example
n * // Người dùng click vào \"Load game\" (nút thứ 2)\n * // -> m_SelectedOption = 2\n * // -> phát âm thanh click\n * // -> chuyển sang StateLoadGame (state 2)\n */
void StateMenu::Handle()
{
	//phần nào thuộc hàm render, gameloop của game đang ở bản demo chưa hoàn thiện nên đặt tạm ở đây cho hợp lí 
	cout << "NEW GAME (1)" <<endl;
	cout << "LOAD GAME (2)" <<endl;
	cout << "SETTING (3)" <<endl;
	cout << "ABOUT US (4)" <<endl;
    //Xu li cac su kien trong StateMenu : click chuot, di chuyen chuot, keypress,...

    cout << "Nhap lua chon cua ban (1-4, 0 de thoat): ";
    cin >> _selectedOption;

    if (_selectedOption >= 1 && _selectedOption <= 4) {
         // 1: New Game, 2: Load Game, 3: Setting, 4: About Us
        StateManager::getInstance()->ChangeState(_selectedOption);
    } else if (_selectedOption == 0) {
        StateManager::getInstance()->Quit();
    } else {
        cout << "Lua chon khong hop le!" << endl;
    }
}

/**
 * @brief Vẽ StateMenu lên cửa sổ game.
 *
 * Quy trình vẽ (Render pipeline):\n *
 * 1. **Cập nhật animation logo CARO**:
 *    - Nếu chưa dừng (isStop == false) và thời gian đủ (frameDelay):
 *      - Tăng currentWidthLogoTitleRect += 43 (chuyển sang frame tiếp theo)
 *      - Tăng bộ đếm frame (currentLogoTitleFrameCout từ 0-29)
 *      - Cập nhật texture rect của sprite animation
 *      - Restart clock để tính thời gian cho frame tiếp theo
 *      - Nếu frame == 29 (frame cuối cùng), set isStop = true dừng animation\n *
 * 2. **Vẽ các layer theo thứ tự (Z-order)**:
 *    - Vẽ hình nền (m_BackgroundSprite)
 *    - Vẽ animation logo (m_CaroAnimationSprite)\n *
 * 3. **Vẽ 4 nút menu và text**:\n *    - Lặp 4 lần (mỗi lần cho một nút):\n *      - Vẽ nút menu (m_ButtonSprite[i])\n *      - Kiểm tra xem chuột có nằm trong bounds của nút không\n *        - Nếu có: vẽ zoom button (lớn hơn) để hiệu ứng highlight\n *      - Vẽ text tùy chọn (m_OptionText[i])\n *
 * @param window Con trỏ đến RenderWindow để vẽ\n *
 * @note Vẽ được gọi mỗi frame từ Application::Render()\n *
 * @note Hiệu ứng animation: 30 frame, mỗi frame delay được định bởi frameDelay\n * (Lưu ý: frameDelay được định nghĩa ở đâu?)\n *
 * @note Hiệu ứng zoom button: khi di chuột vào nút, nút lớn hơn (zoom button)\n *       được vẽ để tạo hiệu ứng visual\n */
void StateMenu::Render()
{
	cout << "Ve giao dien state menu game" << endl;
}

/**
 * @brief Lấy tùy chọn đã được chọn bởi người dùng.
 *
 * @return Giá trị m_SelectedOption:\n *         - 0: Chưa chọn gì (trạng thái ban đầu)
 *         - 1: \"New game\" (Trò chơi mới)\n *         - 2: \"Load game\" (Tải game)\n *         - 3: \"Setting\" (Cài đặt)\n *         - 4: \"About us\" (Thông tin)\n *
 * @note Hàm này là hàm const, không thay đổi trạng thái\n *
 * @example\n * // Kiểm tra lựa chọn cuối cùng
 * int selectedOption = stateMenu->getSelectedOption();\n * if (selectedOption == 1) {\n *     // Người dùng chọn \"New game\"\n * }\n */
int StateMenu::getSelectedOption()
{
	// trả về tùy chọn đã chọn
	return _selectedOption;
}
