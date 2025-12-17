#pragma once
#include <string>

using namespace std;

// =======================
// PHÂN LOẠI THẺ BÀI
// =======================

/**
 * @brief Enum định nghĩa nhóm thẻ bài trong game Hakari.
 * Game chỉ tập trung vào 3 nhóm chính:
 * - Gây sát thương
 * - Phòng thủ
 * - Hiệu ứng đặc biệt (nộ ii, jackpot)
 */
enum class CardCategory {
    Damage,     // Nhóm gây sát thương
    Defense,    // Nhóm phòng thủ
    Effect      // Nhóm hiệu ứng (nộ ii, jackpot)
};

/**
 * @brief Lớp trừu tượng đại diện cho một lá bài trong game.
 * Mỗi lá bài khi được sử dụng sẽ kích hoạt hiệu ứng tương ứng.
 */
class Card {
public:
    /**
     * @brief Tên lá bài (hiển thị trên console).
     * Ví dụ: "Đấm chí mạng", "Phòng thủ tuyệt đối", "Quay Jackpot"
     */
    string name;

    /**
     * @brief Nhóm thẻ bài (Damage / Defense / Effect).
     * Dùng để hiển thị và debug logic lượt chơi.
     */
    CardCategory category;

    /**
     * @brief Constructor khởi tạo lá bài.
     * @param name Tên lá bài
     * @param category Nhóm lá bài
     */
    Card(const string& name, CardCategory category)
        : name(name), category(category) {}

    /**
     * @brief Destructor ảo để đảm bảo giải phóng đúng bộ nhớ
     */
    virtual ~Card() {}

    /**
     * @brief Thực thi hiệu ứng của lá bài.
     * @param self Người chơi sử dụng lá bài (Hakari)
     * @param target Đối thủ
     *
     * Mỗi lá bài con sẽ override hàm này
     * để xử lý logic riêng và in thông báo ra console.
     */
    virtual void execute(class Player& self, class Player& target) = 0;

    /**
     * @brief In mô tả ngắn gọn lá bài ra console.
     * Dùng khi hiển thị 6 lá rút được để người chơi chọn.
     */
    virtual void printDescription() const = 0;
};
