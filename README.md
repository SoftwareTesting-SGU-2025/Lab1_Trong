# Lab1_Trong
Bài tập thực hành Lab 1: Verification &amp; Validation - Xây dựng test cases cho hàm giải phương trình trùng phương.
# Lab 1: Verification & Validation - Xây dựng Test Cases

**Sinh viên:** [Tên của bạn]
**MSSV:** [Mã số sinh viên của bạn]

## I. Mô tả bài toán

[cite_start]Chương trình này được viết để giải phương trình trùng phương có dạng **$ax^4 + bx^2 + c = 0$**. [cite: 48]

* [cite_start]**Input:** Ba số thực a, b, c. [cite: 49]
* [cite_start]**Output:** Số lượng nghiệm thực và danh sách các nghiệm của phương trình. [cite: 50]

---

## II. Xây dựng các Test Cases

Dựa trên việc phân tích các trường hợp đặc biệt của phương trình (a=0, delta=0, y<0), các test cases sau đã được xây dựng để kiểm thử hàm `solveQuartic`.

| Tên Test Case | Input (a, b, c) | Kết quả mong đợi (số nghiệm, các nghiệm) | Mục đích |
| :--- | :--- | :--- | :--- |
| Vô số nghiệm | 0, 0, 0 | -1 (Infinite solutions) | Kiểm tra trường hợp a=b=c=0. |
| Vô nghiệm (1) | 0, 0, 5 | 0 (No solution) | Kiểm tra trường hợp phương trình suy biến thành hằng số khác 0. |
| 2 nghiệm phân biệt | 0, 1, -4 | 2 nghiệm: 2.0, -2.0 | Kiểm tra trường hợp a=0, phương trình bậc hai có 2 nghiệm. |
| Vô nghiệm (delta < 0) | 1, 4, 5 | 0 (No solution) | Kiểm tra trường hợp delta < 0. |
| 4 nghiệm phân biệt | 1, -5, 4 | 4 nghiệm: 1.0, -1.0, 2.0, -2.0 | Trường hợp tổng quát, delta > 0, y1 > 0, y2 > 0. |
| **3 nghiệm (phát hiện lỗi)** | 1, -4, 0 | **Mong đợi: 3 nghiệm: 0, 2, -2** | Kiểm tra trường hợp một nghiệm y = 0, phát hiện lỗi logic trong code. |
| 2 nghiệm (y2 < 0) | 1, 2, -8 | 2 nghiệm: 1.414, -1.414 | Kiểm tra trường hợp delta > 0 nhưng chỉ có một giá trị y không âm. |

---

## III. Mã nguồn và Thực thi

### 1. Mã nguồn kiểm thử (`test_runner.cpp`)

Chương trình C++ này chứa hàm `solveQuartic` bị lỗi và một bộ khung kiểm thử tự động (test runner) để so sánh kết quả thực tế với kết quả mong đợi của từng test case.

*(Bạn có thể dán một đoạn code nhỏ để minh họa nếu muốn)*

### 2. Biên dịch và Chạy kiểm thử (`test_cases.ipynb`)

File Jupyter Notebook được sử dụng để biên dịch và chạy chương trình C++ một cách tiện lợi.

**Các lệnh thực thi:**

```bash
# Biên dịch mã nguồn C++
g++ -std=c++11 test_runner.cpp -o test_runner

# Chạy chương trình kiểm thử
./test_runner
```

---

## IV. Kết quả kiểm thử

Sau khi chạy, chương trình đã phát hiện ra các lỗi trong hàm `solveQuartic` như dự kiến.

```
[ FAIL ] Detects typo bug (y<8)
       Input: a=0.000, b=1.000, c=-4.000
       Expected n: 2, Got n: 0
       Expected x: [ -2.000 2.000 ]
-----------------------------------------------------
[ FAIL ] Detects logic bug (y=0)
       Input: a=1.000, b=-4.000, c=0.000
       Expected n: 3, Got n: 2 
       Expected x: [ -2.000 0.000 2.000 ]
       Got x:      [ -2.000 2.000 ]
-----------------------------------------------------
[ PASS ] 4 distinct roots
[ PASS ] 2 distinct roots
[ PASS ] No real roots (delta < 0)
[ PASS ] No real roots (y values are negative)
[ PASS ] Infinite solutions
[ PASS ] No solution (constant)
```

### Phân tích lỗi:
* **Lỗi 1 (Typo `y < 8`):** Test case `{"Detects typo bug (y<8)", 0, 1, -4, 2, {-2.0, 2.0}}` đã thất bại, chứng tỏ điều kiện `if (y < 8)` sai. Lẽ ra phải là `if (y < 0)`.
* **Lỗi 2 (Xử lý `y = 0`):** Test case `{"Detects logic bug (y=0)", 1, -4, 0, 3, {-2.0, 0.0, 2.0}}` cũng thất bại. Code đã xử lý sai khi một trong các nghiệm `y` của phương trình bậc hai bằng 0, dẫn đến thiếu nghiệm `x = 0`.
