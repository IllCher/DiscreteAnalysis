#include <iostream>
#include <string>
typedef unsigned long long ull;
ull matrix[101][101];
std::string string;
ull DoCount(int i, int j) {
    if (i > j) {
        return 0;
    }
    if (i == j) {
        return 1;
    }
    if (matrix[i][j] == 0) {
         if (string[i] == string[j]) {
             matrix[i][j] = DoCount(i + 1, j) + DoCount(i, j - 1) + 1;
         } else {
             matrix[i][j] = DoCount(i + 1, j) + DoCount(i, j - 1) - DoCount(i + 1, j - 1);
         }
         return matrix[i][j];
    } else {
        return matrix[i][j];
    }
}
 int main() {
    std::cin >> string;
    std::cout << DoCount(0, string.length() - 1) << std::endl;
    return 0;
}