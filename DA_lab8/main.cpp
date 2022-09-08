#include <iostream>
#include <vector>
#include <chrono>
int main() {
    int size;
    std::cin >> size;
    std::vector<int> data(size);
    std::vector<int> frequency(3);
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    for (int i = 0; i < size; i++) {
        std::cin >> data[i];
        if (data[i] == 1) {
            frequency[0]++;
        } else if (data[i] == 2) {
            frequency[1]++;
        } else {
            frequency[2]++;
        }
    }
    int exchange = 0;
    for (int i = 0; i < frequency[0] + frequency[1]; i++) {
        if (i < frequency[0]) {
            if (data[i] == 2) {
                for (int j = frequency[0]; j < size; j++) {
                    if (data[j] == 1) {
                        std::swap(data[i], data[j]);
                        exchange++;
                        break;
                    }
                }
            } else if (data[i] == 3) {
                for (int j = size - 1; j >= frequency[0]; j--) {
                    if (data[j] == 1) {
                        std::swap(data[i], data[j]);
                        exchange++;
                        break;
                    }
                }
            }
        } else {
            if (data[i] == 3) {
                for (int j = frequency[0] + frequency[1]; j < size; j++) {
                    if (data[j] == 2) {
                        std::swap(data[i], data[j]);
                        exchange++;
                        break;
                    }
                }
            }
        }
    }
    end = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << std::endl;
    std::cout << exchange << std::endl;
    return 0;
}