// Dán toàn bộ nội dung của file test_runner.cpp của bạn vào đây
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <algorithm>
#include <iomanip>

// --- Dán mã hàm solveQuartic của đề bài vào đây ---
int solveQuartic(double a, double b, double c, double x[]) {
    if (a == 0 && b == 0 && c == 0) {
        return -1;
    }
    if (a == 0 && b == 0) {
        return 0;
    }
    if (a == 0) {
        double y = -c / b;
        if (y < 8) return 0; // BUG is here: should be y < 0
        x[0] = sqrt(y);
        x[1] = -sqrt(y);
        return 2;
    }
    double delta = b * b - 4 * a * c;
    if (delta < 0) return 0;
    double y1 = (-b + sqrt(delta)) / (2 * a);
    double y2 = (-b - sqrt(delta)) / (2 * a);
    int count = 0;
    if (y1 >= 0) {
        if (y1 == 0) { // BUG is here: this block adds 0 and -0
             x[count++] = 0.0;
        } else {
             x[count++] = sqrt(y1);
             x[count++] = -sqrt(y1);
        }
    }
    if (y2 >= 0 && y2 != y1) {
        if (y2 == 0) { // BUG is also here
            x[count++] = 0.0;
        } else {
            x[count++] = sqrt(y2);
            x[count++] = -sqrt(y2);
        }
    }
    return count;
}


// --- Phần mã kiểm thử tự động ---

struct TestCase {
    std::string name;
    double a, b, c;
    int expected_n;
    std::vector<double> expected_x;
};

bool areClose(double a, double b, double epsilon = 1e-9) {
    return std::fabs(a - b) < epsilon;
}

void runTest(const TestCase& tc) {
    double actual_x[4];
    int actual_n = solveQuartic(tc.a, tc.b, tc.c, actual_x);

    bool passed = true;
    if (actual_n != tc.expected_n) {
        passed = false;
    } else if (actual_n > 0) {
        std::vector<double> actual_x_vec(actual_x, actual_x + actual_n);
        std::vector<double> expected_x_vec = tc.expected_x;

        std::sort(actual_x_vec.begin(), actual_x_vec.end());
        std::sort(expected_x_vec.begin(), expected_x_vec.end());

        if (actual_x_vec.size() != expected_x_vec.size()) {
             passed = false;
        } else {
            for (size_t i = 0; i < actual_x_vec.size(); ++i) {
                if (!areClose(actual_x_vec[i], expected_x_vec[i])) {
                    passed = false;
                    break;
                }
            }
        }
    }

    std::cout << "[ " << (passed ? "PASS" : "FAIL") << " ] " << tc.name << std::endl;
    if (!passed) {
        std::cout << "       Input: a=" << tc.a << ", b=" << tc.b << ", c=" << tc.c << std::endl;
        std::cout << "       Expected n: " << tc.expected_n << ", Got n: " << actual_n << std::endl;
        if (tc.expected_n > 0) {
            std::cout << "       Expected x: [ ";
            for(double val : tc.expected_x) std::cout << val << " ";
            std::cout << "]" << std::endl;
        }
        if (actual_n > 0) {
            std::cout << "       Got x:      [ ";
            std::vector<double> sorted_actual(actual_x, actual_x + actual_n);
            std::sort(sorted_actual.begin(), sorted_actual.end());
            for(double val : sorted_actual) std::cout << val << " ";
            std::cout << "]" << std::endl;
        }
        std::cout << "-----------------------------------------------------" << std::endl;
    }
}

int main() {
    std::vector<TestCase> test_cases = {
        {"Detects typo bug (y<8)", 0, 1, -4, 2, {-2.0, 2.0}},
        {"Detects logic bug (y=0)", 1, -4, 0, 3, {-2.0, 0.0, 2.0}},
        {"4 distinct roots", 1, -5, 4, 4, {-2.0, 2.0, -1.0, 1.0}},
        {"2 distinct roots", 1, 2, -8, 2, {-sqrt(2.0), sqrt(2.0)}},
        {"No real roots (delta < 0)", 1, 4, 5, 0, {}},
        {"No real roots (y values are negative)", 1, 3, 2, 0, {}},
        {"Infinite solutions", 0, 0, 0, -1, {}},
        {"No solution (constant)", 0, 0, 5, 0, {}}
    };

    std::cout << std::fixed << std::setprecision(3);

    for (const auto& tc : test_cases) {
        runTest(tc);
    }

    return 0;
}
