# 1. Cấu hình tên file thực thi và trình biên dịch
TARGET = app.exe
CXX = g++
CXXFLAGS = -std=c++17 -Wall

# 2. Tự động tìm tất cả các thư mục con để thêm vào Include Path
# Giúp bạn chỉ cần viết #include "Card.h" thay vì #include "Card/Card.h"
INC_DIRS := $(shell dir /ad /s /b)
INCLUDE_FLAGS := $(foreach dir, $(INC_DIRS), -I"$(dir)") -I.

# 3. Tự động tìm tất cả các file .cpp trong thư mục gốc và các thư mục con
SRCS := $(shell dir /s /b *.cpp)

# 4. Quy tắc biên dịch chính
all: $(TARGET)

$(TARGET): $(SRCS)
	@echo "Dang bien dich du an..."
	$(CXX) $(CXXFLAGS) $(INCLUDE_FLAGS) $(SRCS) -o $(TARGET)
	@echo "Bien dich hoan tat: $(TARGET)"

# 5. Lệnh dọn dẹp file thực thi
clean:
	@if exist $(TARGET) del /f /q $(TARGET)
	@echo "Da don dep file."