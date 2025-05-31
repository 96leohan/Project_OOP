# BÁO CÁO DỰ ÁN CUỐI KỲ - MÔN LẬP TRÌNH HƯỚNG ĐỐI TƯỢNG (OOP)

## Game Cờ Vua

🔗 [Video ứng dụng gốc](https://www.youtube.com/watch?v=_4EuZI8Q8cs)

---

### 1. Thành viên nhóm

- Trần Hà Lê Hân - 22120092
- Phạm Phúc An Khang - 20120303 - Nhóm trưởng

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

---

### 3. Tỉ lệ đóng góp của các thành viên vào dự án (tổng 100%)

- Phạm Phúc An Khang: 60%
- Trần Hà Lê Hân: 40%

---

### 4. Tỉ lệ điểm của các thành viên

- Chia 10 - 9

---

### 5. Cách thức đánh giá và tính năng nổi bật

#### 🧑‍🤝‍🧑 Teamwork:

- Phân công và theo dõi tiến độ công việc: Nhóm trưởng thực hiện, đã nhắc nhở thành viên đều đặn làm đồ án hằng tuần.
- Ghi chép biên bản họp nhóm: Nhóm trưởng thực hiện.
- Mức độ commit: [https://github.com/96leohan/Project_OOP/graphs/contributors](https://github.com/96leohan/Project_OOP/graphs/contributors)
  - Phạm Phúc An Khang: 29 commits, thêm 7,951 dòng, xóa 4,110 dòng.
  - Trần Hà Lê Hân: 116 commits, thêm 1,534 dòng, xóa 1,286 dòng.

#### 🎨 UI/UX:

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

- Vẽ Class Diagram bằng Mermaid:
  https://www.mermaidchart.com/play?utm_source=mermaid_live_editor&utm_medium=toggle#pako:eNq9WFFv2zYQ_iuEgQLyEj_sbRCCAEuKrca6Lkva7aEpDEZibCIyKZB0Mq_Lf9-RFKWjRNle5yQIEon38Xh3_Hh31NdJIUs2ySdFRbV-y-lS0fWtuBUEft68IZcrpjW5osUDXTKS_UzXjLyXS15MPcRNI1dSc8OlIF_9qP2ZcWGIkk-9kUJW3cjJkplr-ZRNCYji4UtZDYaNvDGKiyUItHvwsudgrzcGZkqFLTk7Y2KzZopaE8_PO8GfK25Y93pRgZtJlVecFezjtmYHqb2iT6J7-0Xw5Qp5ccH1Stbd-7WUD93b7xvG8OQxJ51FsTX0DoJCC4NNmflgFPbvAg3_Kh_ZH7TiJTUgfgxPCHLSDDILze6VXOftNp8SI_HbnaSqzMmF_TeFt_4WOyNg09x_JCoqKRiMO2fiKTfb9Z1jwI6NtnHGIfi_-vxOHVOj3-tjarRsOaY-x7ejBhEEx9QXM3Uv4U-4duhvZGyCYcnFR87VcVf3fEyuf9yFPE1fYSHL3ldYxpH6FdaxXH-N7bHyiH1LxcvPP3yB38GxqqGIMTeY1fZv7hGnpJa6W3uKZqzhhPkJu6wd5PXGxb3lIVUQGvsiiwaecAECWOJv5gKQTaPFoTEpHtZQnzJ3CHNfXBJWOuAoKFVWf4KcItU2zmKKwVrebgONQN71BKckVo78eMadlFyvqSghpxjDVK9j8aL92Y39xYoN-IxjsRGlDAOJ5JlQPvOMcvTDXUHbxtn9TAqMjIZdE1LQ2mwUKxeOb0O55ddQeLgrELsbA8FPRc72o164P3YriELFsiVMyd3Eaa8aWT0fYHxP11HRLcgGqx5Lv-Pry2q3x-YFVoCN-u1OM_XIVGqvPs0_SMPvOeuVcejxmbqHrBXtlrDY7f7skvTSXVMOIPw1EyVTYJBqHrBwLuqNeeeCouAiAi8LH6II1Xn1-QsRzaNeRK2CO4AgLvzTYsW1TTAY1BFZ27-LYauxUWCk-bhRYhHvy1zAFFHYbbFakhk0Cw7mJPh8GvuUE-wv3npalsHFLDiYo93EWLBEmehIN8e8CULWhCAPOa9_-t9TbdymR1ob8mUuNnl36nsMvexilLhtAKApJL6iDtn7aR5uulHTEkhyAGt9mLOosOMjBg1dZZu6b-T1pRRaVixl0Usv_S7MZ2Vq-e4oPSla15DwU0eqrSOg0ixGq4yTxqXGVmyyonrhZLakLF7P9-DbeGMQEE1v4NPjtJ2Y1BrllwO4Bfz1J6OzPTzsIsvYMv9BHxyNa1a57xx6xWvdjs7Fiinuso8f8xX_7J_ZDH0FQYP4Ywgaxt9E0HD3aQQNoi8kWHFbjuILY2tKOzSK6l23RnG929IoLrrsjKLiu8q4cfiq4VGhsXNy1Ol5aVdQfAhQ15IEdG3HuLjtGzykPfIeEeemFCSRQzws4ijWhgWIjT9qLQvuCUlsDN6y2ioUBWcac-O72eyc3E6-v530gpqTjY6hFulLbW4TjRf5vqHRAsHdgiIPz6GaC0O5iJAW2KYxvIbrSJA1Hp4T0AnlZgTURm-Xpih2Y8DGdNSC5aFZGUcHguWkKeIjFnRUQZFzIBxT25A_6I7gQbvFtNGQJTKpj0oGNlWX0iEsWSEVbb1oJdgAX0hSCLR4W050gr09rGJwNxKYaKGIOGCgkisiO1Hu6_OAtRgWAm0hk-d_AYRZbBc

- Thư viện SFML cho giao diện đồ họa.
