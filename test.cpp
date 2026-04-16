#include <iostream>
#include <vector>
#include <cassert>
#include "json.hpp"

// Тестування серіалізації JSON
void test_json_serialization() {
    nlohmann::json j;
    j["S2"] = 10;
    std::vector<int> v = {1, 2, 3};
    j["V1"] = v;

    std::string output = j.dump(4);
    
    // Перевіряємо, чи містить рядок ключі та значення
    assert(output.find("\"S2\": 10") != std::string::npos);
    assert(output.find("\"V1\": [1,2,3]") != std::string::npos);
    std::cout << "JSON Test Passed!" << std::endl;
}

// Тестування логіки групування (аналог того, що у вас в main)
void test_grouping_logic() {
    std::vector<int> V = {1, 2, 3, 4};
    int n = 2;
    std::vector<int> sums;

    for (size_t i = 0; i < V.size(); i += n) {
        int currentSum = 0;
        for (size_t j = i; j < i + n && j < V.size(); j++) {
            currentSum += V[j];
        }
        sums.push_back(currentSum);
    }

    assert(sums.size() == 2);
    assert(sums[0] == 3); // 1+2
    assert(sums[1] == 7); // 3+4
    std::cout << "Grouping Logic Test Passed!" << std::endl;
}

// Тестування обчислення різниці векторів
void test_vector_diff() {
    std::vector<int> V1 = {10, 20};
    std::vector<int> V2 = {5, 8};
    std::vector<int> V_diff;

    for (size_t i = 0; i < V1.size() && i < V2.size(); i++) {
        V_diff.push_back(V1[i] - V2[i]);
    }

    assert(V_diff.size() == 2);
    assert(V_diff[0] == 5);
    assert(V_diff[1] == 12);
    std::cout << "Vector Difference Test Passed!" << std::endl;
}

int main() {
    try {
        test_json_serialization();
        test_grouping_logic();
        test_vector_diff();
        std::cout << "\nAll tests passed successfully!" << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Test failed: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}
