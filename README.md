# BÁO CÁO DỰ ÁN CUỐI KỲ - MÔN LẬP TRÌNH HƯỚNG ĐỐI TƯỢNG (OOP)

## Game Cờ Vua

🔗 [Video ứng dụng gốc](https://www.youtube.com/watch?v=_4EuZI8Q8cs)

---

### 1. Thành viên nhóm

- Trần Hà Lê Hân - 22120092
- Phạm Phúc An Khang - 20120303

---

### 2. Các công việc thành viên đã thực hiện

**An Khang:**

- Cấu trúc dự án Git, viết file Markdown.
- Cài đặt lại tính năng cơ bản của ứng dụng theo phương pháp hướng đối tượng với coding convention:
  - Cài đặt logic cơ bản các quân cờ, bàn cờ.
  - Cài đặt các logic bổ sung:
    - Nhập thành (Castling)
    - Bắt quân qua đường (En Passant)
    - Phong cấp (Pawn Promotion)
    - Chiếu và Chiếu hết (Check & Checkmate)
    - Hòa cờ (Stalemate)
  - Cài đặt chức năng hàm main, vòng lặp chính của chương trình.
- Triển khai chức năng chơi với máy (AI Opponent).
- Ghi chép biên bản họp nhóm.

**Lê Hân:**

- Xây dựng chức năng, giao diện UI của chương trình.
- Vẽ Class Diagram.
- Thực hiện demo ứng dụng.
- Đóng gói các thư mục và nộp bài.

---

### 3. Tỉ lệ đóng góp của các thành viên vào dự án (tổng 100%)

- Phạm Phúc An Khang: 55%
- Trần Hà Lê Hân: 45%

---

### 4. Tỉ lệ điểm của các thành viên

- Chia 10 - 9

---

### 5. Cách thức đánh giá và tính năng nổi bật

#### 🧑‍🤝‍🧑 Teamwork: Đã thực hiện tốt

- Phân công và theo dõi tiến độ công việc.
- Ghi chép biên bản họp nhóm.

#### 🎨 UI/UX:

- Giao diện chương trình thân thiện, rõ ràng.
- Cung cấp trải nghiệm người dùng mượt mà.

#### 🧱 Cài đặt lại chức năng của mã nguồn mẫu theo hướng đối tượng: Đã hoàn thành

#### 🔧 Các chức năng thêm và cải tiến

##### ✅ Cải thiện Gameplay: Đã hoàn thiện

- **Nhập thành (Castling)**: Kiểm tra đầy đủ các điều kiện nhập thành:
  - Không có quân cản.
  - Vua và xe chưa từng di chuyển.
  - Vua không bị chiếu hoặc đi qua ô bị chiếu.
- **Bắt quân qua đường (En Passant)**
- **Phong cấp (Pawn Promotion)**
- **Chiếu và Chiếu hết (Check & Checkmate)**
- **Hòa cờ (Stalemate)**

##### 📜 Ghi lại lịch sử ván cờ (Move History): Đã hoàn thành

##### 🤖 Chơi với máy (AI Opponent): Đã hoàn thiện

##### 🧩 Cải thiện giao diện người dùng: Đã hoàn thành

- Hiển thị nước đi hợp lệ.
- Thông báo và phản hồi các sự kiện: nước đi sai, chiếu, chiếu hết...
- Thêm chức năng đầu hàng, restart trận đấu.
- Thêm màn hình Home.
- Thêm menu cài đặt bao gồm: chỉnh độ khó, chọn chế độ chơi, credit, nút thoát ứng dụng.
- Ngôn ngữ: Lựa chọn ngôn ngữ hiển thị trong trò chơi (tiếng Anh và Tiếng Việt).
- Thống kê: Số ván đã chơi, số ván thắng, thua, hòa.
- Hướng dẫn/Luật chơi (Tutorial/Rules - tùy chọn): Cung cấp thông tin về luật chơi cờ vua cho người mới bắt đầu.

#### 🧭 Giao diện bố trí hợp lý

#### 🏗️ Kiến trúc phần mềm + Design Pattern

#### ✅ Đảm bảo chất lượng

##### 🔣 Coding Convention

###### 1. Quy tắc đặt tên (Naming Conventions)

| Đối tượng      | Quy tắc                       | Ví dụ                       |
| :------------- | :---------------------------- | :-------------------------- |
| Biến           | `camelCase`                   | `playerScore`, `maxSpeed`   |
| Hằng số        | `UPPER_CASE_WITH_UNDERSCORES` | `MAX_BUFFER_SIZE`, `PI`     |
| Hàm            | `camelCase`                   | `calculateDistance()`       |
| Lớp            | `PascalCase`                  | `GameObject`, `UserManager` |
| Thành viên lớp | `_camelCase`                  | `_position`                 |
| Tên file       | `snake_case`                  | `game_engine.cpp`           |

###### 2. Quy tắc định dạng (Formatting)

- `{` mở ở cùng dòng hoặc dòng mới (nhất quán theo style đã chọn).
- Có dấu cách sau: `,`, `if`, `for`, `while`, `switch`.
- Thụt lề: 4 spaces, **không dùng tab**.

###### 3. Cấu trúc chương trình

- Dùng include guard.
- Tách `.h` (khai báo) và `.cpp` (định nghĩa).
- Dùng forward declaration nếu có thể.

###### 4. Quy tắc lập trình (Best Practices)

- Không dùng `using namespace std;` trong header.
- Sử dụng `const`, `constexpr`, `noexcept` đúng chỗ.
- Dùng `unique_ptr`, `shared_ptr` thay cho con trỏ raw (C++11+).
- Dùng `nullptr` thay `NULL`.
- Kiểm tra `nullptr` trước khi dùng.
- Tránh lặp code — viết hàm hỗ trợ.
- Gom nhóm hàm liên quan.
- Ưu tiên `enum class` thay vì `enum`.

###### 5. Quy tắc comment

- `//` cho ghi chú thông thường.
- `/** */` hoặc `///` cho documentation (Doxygen).

### 📄 Tài liệu mô tả kiến trúc phần mềm và các module

- Vẽ Class Diagram bằng Mermaid: Đã hoàn thành.
- Thư viện SFML cho giao diện đồ họa.

---

### 6. Link video demo

🔗 [Link video demo trên YouTube]
