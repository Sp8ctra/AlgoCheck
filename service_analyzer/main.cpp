#include <chrono>
#include <vector>
#include <string>
#include <sstream>
#include <algorithm>
#define CPPHTTP_SUPPORT
#include "httplib.h"

// Пузырьковая сортировка O(N^2)
void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

int main() {
    httplib::Server svr;

    svr.Post("/analyze", [](const httplib::Request& req, httplib::Response& res) {
        std::vector<int> data;
        
        // Быстрый ручной парсинг чисел из JSON строки вида {"data":[1,2,3]}
        std::string body = req.body;
        size_t start_pos = body.find("[");
        size_t end_pos = body.find("]");
        
        if (start_pos != std::string::npos && end_pos != std::string::npos) {
            std::string array_str = body.substr(start_pos + 1, end_pos - start_pos - 1);
            std::stringstream ss(array_str);
            std::string token;
            while (std::getline(ss, token, ',')) {
                if (!token.empty()) {
                    data.push_back(std::stoi(token));
                }
            }
        }

        // Замер времени алгоритма
        auto start = std::chrono::high_resolution_clock::now();
        bubbleSort(data); 
        auto end = std::chrono::high_resolution_clock::now();
        
        auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();

        // Формируем JSON ответ вручную
        std::string json_res = "{\"array_size\":" + std::to_string(data.size()) + 
                               ",\"execution_time_us\":" + std::to_string(duration) + "}";
        
        res.set_content(json_res, "application/json");
    });

    svr.listen("0.0.0.0", 8080);
    return 0;
}
