# -Project_OOP

# Mã nguồn lựa chọn

## Game cờ vua

🔗 [Video Demo trên YouTube](https://www.youtube.com/watch?v=_4EuZI8Q8cs)

---

### 1. Thành viên nhóm

- Trần Hà Lê Hân - 22120092
- Phạm Phúc An Khang - 20120303

---

### 2. Các công việc các thành viên đã thực hiện

**An Khang:**

- Cấu trúc dự án git, viết file markdown
- Cài đặt lại tính năng cơ bản của ứng dụng theo phương pháp hướng đối tượng với coding convention
  - Cài đặt logic cơ bản các quân cờ, bàn cờ
  - Cài đặt các logic bổ sung:
    - Nhập thành (Castling)
    - Bắt quân qua đường (En Passant)
    - Phong cấp (Pawn Promotion)
    - Chiếu và Chiếu hết (Check & Checkmate)
    - Hòa cờ (Stalemate)
  - Cài đặt chức năng hàm main, vòng lặp chính của chương trình
- Triển khai chức năng chơi với máy (AI Opponent)
- Ghi chép biên bản họp nhóm

**Lê Hân:**

- Cấu trúc dự án git

---

### 3. Tỉ lệ đóng góp của các thành viên vào dự án (tổng 100%)

_(Nội dung cần bổ sung cụ thể)_

---

### 4. Tỉ lệ điểm của các thành viên

_(Nội dung cần bổ sung cụ thể)_

---

### 5. Cách thức đánh giá

Mô tả cụ thể cho các yêu cầu

#### 🧑‍🤝‍🧑 Teamwork: thực hiện tốt

- Phân công và theo dõi tiến độ công việc
- Ghi chép biên bản họp nhóm

#### 🎨 UI/UX: chưa hoàn thành

- Giao diện chương trình thân thiện, rõ ràng
- Cung cấp trải nghiệm người dùng mượt mà

#### 🧱 Cài đặt lại chức năng của mã nguồn mẫu theo hướng đối tượng

#### 🔧 Các chức năng thêm và cải tiến

##### ✅ Cải thiện gameplay: đã hoàn thiện

- **Nhập thành (Castling)**: Kiểm tra đầy đủ các điều kiện nhập thành:
  - Không có quân cản
  - Vua và xe chưa từng di chuyển
  - Vua không bị chiếu hoặc đi qua ô bị chiếu
- **Bắt quân qua đường (En Passant)**
- **Phong cấp (Pawn Promotion)**
- **Chiếu và Chiếu hết (Check & Checkmate)**
- **Hòa cờ (Stalemate)**

##### 📜 Ghi lại lịch sử ván cờ (Move History): chưa hoàn thành

- Lưu danh sách các nước đi đã thực hiện

##### ⏱️ Hẹn giờ (Timers): chưa hoàn thành

- Đồng hồ đếm ngược với các chế độ: blitz, rapid, classical

##### 🤖 Chơi với máy (AI Opponent): đã hoàn thiện

- Đối thủ AI có nhiều cấp độ khó

##### 🧩 Cải thiện giao diện người dùng: chưa hoàn thành

- Hiển thị nước đi hợp lệ
- Thông báo và phản hồi các sự kiện: nước đi sai, chiếu, chiếu hết...
- Thêm chức năng đầu hàng, restart trận đấu
- Thêm màn hình Home
- Thêm menu setting bao gồm: chỉnh độ khó, chọn chế độ, credit, nút thoát ứng dụng (exit),
- Ngôn ngữ: Lựa chọn ngôn ngữ hiển thị trong trò chơi, tiếng Anh và Tiếng Việt
- Thống kê: Số ván đã chơi, số ván thắng, thua, hòa.
- Hướng dẫn/Luật chơi (Tutorial/Rules - tùy chọn):cung cấp thông tin về luật chơi cờ vua cho người mới bắt đầu.

#### 🧭 Giao diện bố trí hợp lý

#### 🏗️ Kiến trúc phần mềm + Design Pattern

#### ✅ Đảm bảo chất lượng

##### 🔣 Coding Convention

###### 1. Quy tắc đặt tên (Naming Conventions)

| Đối tượng      | Quy tắc                       | Ví dụ                       |
| -------------- | ----------------------------- | --------------------------- |
| Biến           | `camelCase`                   | `playerScore`, `maxSpeed`   |
| Hằng số        | `UPPER_CASE_WITH_UNDERSCORES` | `MAX_BUFFER_SIZE`, `PI`     |
| Hàm            | `camelCase`                   | `calculateDistance()`       |
| Lớp            | `PascalCase`                  | `GameObject`, `UserManager` |
| Thành viên lớp | `_camelCase`                  | `_position`                 |
| Tên file       | `snake_case`                  | `game_engine.cpp`           |

###### 2. Quy tắc định dạng (Formatting)

- `{` mở ở cùng dòng hoặc dòng mới (nhất quán theo style đã chọn)
- Có dấu cách sau: `,`, `if`, `for`, `while`, `switch`
- Thụt lề: 4 spaces, **không dùng tab**

###### 3. Cấu trúc chương trình

- Dùng include guard
- Tách `.h` (khai báo) và `.cpp` (định nghĩa)
- Dùng forward declaration nếu có thể

###### 4. Quy tắc lập trình (Best Practices)

- Không dùng `using namespace std;` trong header
- Sử dụng `const`, `constexpr`, `noexcept` đúng chỗ
- Dùng `unique_ptr`, `shared_ptr` thay cho con trỏ raw (C++11+)
- Dùng `nullptr` thay `NULL`
- Kiểm tra `nullptr` trước khi dùng
- Tránh lặp code — viết hàm hỗ trợ
- Gom nhóm hàm liên quan
- Ưu tiên `enum class` thay vì `enum`

###### 5. Quy tắc comment

- `//` cho ghi chú thông thường
- `/** */` hoặc `///` cho documentation (Doxygen)

###### 6. Tổ chức file

**Trong file `.h`:**

```cpp
// 1. Include guard hoặc #pragma once
// 2. Includes cần thiết
// 3. Forward declaration
// 4. Khai báo class, typedef, enum
```

**Trong file `.cpp`:**

```cpp
/// 1. Include chính (.h tương ứng)
// 2. Các include còn lại
// 3. Implementation
```

### 🧪 Kiểm thử bằng Unit Test

Xây dựng Test Plan
Viết Test Case
Tạo Test Report

### 📄 Tài liệu mô tả kiến trúc phần mềm và các module

Vẽ Class Diagram
Tạo tài liệu mô tả:
Các lớp trong hệ thống
Ý nghĩa các hàm chính

### 6 Link video demo

🔗 Link video demo
