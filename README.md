# Báo cáo Bài tập lớn: Hệ điều hành (Operating Systems)

## 📌 Chủ đề: Tìm hiểu một số thuật toán đồng bộ tài nguyên găng (Critical Resource Synchronization)

### 📖 Giới thiệu
Kho lưu trữ này chứa tài liệu báo cáo và mã nguồn mô phỏng cho bài tập lớn môn Hệ điều hành.
Nội dung tập trung phân tích các vấn đề tranh chấp tài nguyên (Race Condition) và các giải pháp đồng bộ hóa.

### 📂 Cấu trúc thư mục
- `/OS_project`: Tài liệu báo cáo (LaTeX).
- `/Code`: Mã nguồn demo (C/C++).
  - `peterson.c`: Giải thuật Peterson.
  - `Lamport's Bakery.cpp`: Tiệm bánh của Lamport.

### ⚙️ Nội dung chính

### 1. Lý thuyết
- Khái niệm Miền găng (Critical Section).
- Yêu cầu của giải pháp đồng bộ: Mutual Exclusion, Progress, Bounded Waiting.

### 2. Giải pháp nghiên cứu
#### a. Công cụ cấp thấp (Low-level mechanisms)
- *Không có sự trợ giúp phần cứng:* Các giải pháp phần mềm (Software solutions - Peterson, Lamport's Bakery...).
- *Có sự trợ giúp phần cứng:* Các chỉ thị máy (Hardware instructions - Cigarette Smokers Problem, Santa Claus...).

#### b. Công cụ cấp cao (High-level mechanisms)
- Traffic Light Intersection Problem.
- Readers - Writers.
- Elevator Problem.

### 🛠 Công cụ sử dụng
- Ngôn ngữ: C/C++
- Môi trường: Windows/Linux
- Compiler: GCC/G++