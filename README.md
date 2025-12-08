\# Báo cáo Bài tập lớn: Hệ điều hành (Operating Systems)



\## 📌 Chủ đề: Tìm hiệu một số thuật toán đồng bộ tài nguyên găng (Critical Resource Synchronization)



\### 📖 Giới thiệu

Kho lưu trữ này chứa tài liệu báo cáo và mã nguồn mô phỏng cho bài tập lớn môn Hệ điều hành.

Nội dung tập trung phân tích các vấn đề tranh chấp tài nguyên (Race Condition) và các giải pháp đồng bộ hóa.



\### 📂 Cấu trúc thư mục

\* `/OS\_project`: Tài liệu báo cáo (Latex).

\* `/src`: Mã nguồn demo (C/C++).

&nbsp;   \* `peterson.cpp`: Giải thuật Peterson.

&nbsp;   \* `producer\_consumer.c`: Bài toán Nhà sản xuất - Người tiêu dùng.



\### ⚙️ Nội dung chính

1\. \*\*Lý thuyết:\*\*

&nbsp;  - Khái niệm Miền găng (Critical Section).

&nbsp;  - Yêu cầu của giải pháp đồng bộ: Mutual Exclusion, Progress, Bounded Waiting.

2\. \*\*Giải pháp nghiên cứu:\*\*

&nbsp;  - \*\*Công cụ cấp thấp (Low-level mechanisms):\*\*

&nbsp;    - \*Không có sự trợ giúp phần cứng:\* Các giải pháp phần mềm (Software solutions - Peterson, Lamport's Bakery...).

&nbsp;    - \*Có sự trợ giúp phần cứng:\* Các chỉ thị máy (Hardware instructions - Cigarette Smokers, Santa claus ...).

&nbsp;  - \*\*Công cụ cấp cao (High-level mechanisms):\*\*

&nbsp;    - Traffic Light Intersection Problem.

&nbsp;    - Readers - Writers.

&nbsp;    - Elevator Problem.

\### 🛠 Công cụ sử dụng

\- Ngôn ngữ: C/C++

\- Môi trường: Windows

\- Compiler: GCC/G++



---

