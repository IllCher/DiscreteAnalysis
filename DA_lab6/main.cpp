#include <iostream>
#include <cmath>
#include <iomanip>
#include <cstdlib>
#include <algorithm>
#include <exception>
#include <vector>

class TLongNumb {
    std::vector<unsigned long long> longNumber;
    const unsigned long base = 1000*1000*1000;

public:
    TLongNumb() = default;
    TLongNumb(const std::string &str);
    TLongNumb(const TLongNumb &ln);
    TLongNumb &operator=(const TLongNumb &second);
    bool operator<(const TLongNumb &second);
    bool operator>(const TLongNumb &second);
    bool operator==(const TLongNumb &second);
    bool operator<=(const TLongNumb &second);
    bool operator>=(const TLongNumb &second);

    friend TLongNumb Pow(TLongNumb &n, const TLongNumb &exp);
    friend TLongNumb operator+(const TLongNumb &first, const TLongNumb &second);
    friend TLongNumb operator-(const TLongNumb &first, const TLongNumb &second);
    friend TLongNumb operator*(const TLongNumb &first, const TLongNumb &second);
    friend TLongNumb operator/(const TLongNumb &first, const TLongNumb &second);
    friend std::ostream &operator<<(std::ostream &out, const TLongNumb &num);

private:
    friend int Compare(const TLongNumb &first, const TLongNumb &second);
    friend TLongNumb PowAssist(TLongNumb &n, const TLongNumb &exp);
    void DltLeadZero();
    friend TLongNumb ColumnMult(const TLongNumb &first, const TLongNumb &second);
    friend TLongNumb SmallMult(const TLongNumb &first, const TLongNumb &second);
    void RightShift();
    friend TLongNumb Div(const TLongNumb &first, const TLongNumb &second);
};

TLongNumb::TLongNumb(const std::string &str) {
    int power = static_cast<int>(log10(static_cast<double>(base)));
    for (int i = static_cast<int>((str.size() - 1)); i >= 0; i -= power) {
        if (i < power) {
            longNumber.push_back(std::atoll(str.substr(0, i + 1).c_str()));
        } else {
            longNumber.push_back(std::atoll(str.substr(i - power + 1, power).c_str()));
        }
    }
    DltLeadZero();
}

TLongNumb::TLongNumb(const TLongNumb &ln) {
    longNumber = ln.longNumber;
}

TLongNumb &TLongNumb::operator=(const TLongNumb &second) {
    this->longNumber = second.longNumber;
    return *this;
}

bool TLongNumb::operator<(const TLongNumb &second) {
    return (Compare(*this, second) == 1 ? true : false);
}

bool TLongNumb::operator>(const TLongNumb &second) {
    return (Compare(*this, second) == -1 ? true : false);
}

bool TLongNumb::operator==(const TLongNumb &second) {
    return (Compare(*this, second) == 0 ? true : false);
}

bool TLongNumb::operator<=(const TLongNumb &second) {
    int res = Compare(*this, second);
    if (res == 1 || res == 0)
        return true;
    return false;
}

bool TLongNumb::operator>=(const TLongNumb &second) {
    int res = Compare(*this, second);
    if (res == -1 || res == 0)
        return true;
    return false;
}

TLongNumb Pow(TLongNumb &n, const TLongNumb &exp) {
    if (TLongNumb("0") == exp) {
        if (n == TLongNumb("0")) {
            throw std::logic_error("Error");
        } else {
            return TLongNumb("1");
        }
    }
    if (n == TLongNumb("1") || TLongNumb("1") == exp) {
        return n;
    }
    return PowAssist(n, exp);
}

TLongNumb operator+(const TLongNumb &first, const TLongNumb &second) {
    unsigned long carryOver = 0;
    unsigned long maxSize = std::max(first.longNumber.size(), second.longNumber.size());
    unsigned long sumInDigit = 0;
    TLongNumb res;
    for (int i = 0; i < maxSize; i++) {
        if (first.longNumber.size() <= i) {
            sumInDigit = second.longNumber[i] + carryOver;
        } else if (second.longNumber.size() <= i) {
            sumInDigit = first.longNumber[i] + carryOver;
        } else {
            sumInDigit = first.longNumber[i] + second.longNumber[i] + carryOver;
        }
        res.longNumber.push_back(sumInDigit % first.base);
        carryOver = sumInDigit / first.base;
    }
    if (carryOver != 0) {
        res.longNumber.push_back(carryOver);
    }
    return res;
}

TLongNumb operator-(const TLongNumb &first, const TLongNumb &second) {
    if (first.longNumber.size() < second.longNumber.size()) {
        throw std::logic_error("Error");
    }
    unsigned long carryOver = 0;
    unsigned long size = first.longNumber.size();
    long long differenceInDigit = 0;
    TLongNumb res;
    for (int i = 0; i < size; i++) {
        if (i >= second.longNumber.size()) {
            differenceInDigit = first.longNumber[i] - carryOver;
        } else {
            differenceInDigit = first.longNumber[i] - second.longNumber[i] - carryOver;
        }
        carryOver = 0;
        if (differenceInDigit < 0) {
            differenceInDigit += first.base;
            carryOver = 1;
        }
        res.longNumber.push_back(differenceInDigit);
    }
    if (carryOver == 1) {
        throw std::logic_error("Error");
    }
    res.DltLeadZero();
    return res;
}

TLongNumb operator*(const TLongNumb &first, const TLongNumb &second) {
    if (second.longNumber.size() == 1) {
        return SmallMult(first, second);
    } else if (first.longNumber.size() == 1) {
        return SmallMult(second, first);
    }
    TLongNumb res = ColumnMult(first, second);
    res.DltLeadZero();
    return res;
}

TLongNumb operator/(const TLongNumb &first, const TLongNumb &second) {
    return Div(first, second);
}

std::ostream &operator<<(std::ostream &out, const TLongNumb &num) {
    out << (num.longNumber.empty() ? 0 : num.longNumber.back());
    int power = static_cast<int>(log10(static_cast<double>(num.base)));
    for (int i = static_cast<int>((num.longNumber.size() - 2)); i >= 0; i--) {
        out << std::setw(power) << std::setfill('0') << num.longNumber[i];
    }

    return out;
}

int Compare(const TLongNumb &first, const TLongNumb &second) {
    if (first.longNumber.size() < second.longNumber.size()) {
        return 1;
    } else if (first.longNumber.size() > second.longNumber.size()) {
        return -1;
    }
    for (int i = first.longNumber.size(); i > 0; i--) {
        if (first.longNumber[i - 1] < second.longNumber[i - 1]) {
            return 1;
        } else if (first.longNumber[i - 1] > second.longNumber[i - 1]) {
            return -1;
        }
    }
    return 0;
}

TLongNumb PowAssist(TLongNumb &n, const TLongNumb &exp) {
    if (TLongNumb{"1"} == exp) {
        return n;
    }
    if (exp.longNumber[0] % 2 == 0) {
        TLongNumb x = PowAssist(n, exp / TLongNumb{"2"});
        return x * x;
    } else {
        return PowAssist(n, exp - TLongNumb{"1"}) * n;
    }
}

void TLongNumb::DltLeadZero() {
    while (longNumber.size() > 1 && longNumber.back() == 0) {
        longNumber.pop_back();
    }
}

TLongNumb ColumnMult(const TLongNumb &first, const TLongNumb &second) {
    TLongNumb res;
    res.longNumber.resize(first.longNumber.size() + second.longNumber.size());

    for (int i = 0; i < second.longNumber.size(); i++) {
        long carryOver = 0;
        for (int j = 0; j < first.longNumber.size() || carryOver != 0; j++) {
            long long cur = res.longNumber[i + j] + second.longNumber[i] * 1ll * (j < first.longNumber.size() ? first.longNumber[j] : 0) + carryOver;
            res.longNumber[i + j] = cur % first.base;
            carryOver = cur / first.base;
        }
    }
    res.DltLeadZero();
    return res;
}

TLongNumb SmallMult(const TLongNumb &first, const TLongNumb &second) {
    unsigned long long carryOver = 0;
    unsigned long long multInDigit = 0;
    int size = first.longNumber.size();
    TLongNumb res;
    for (int i = 0; i < size; i++) {
        multInDigit = first.longNumber[i] * second.longNumber[0] + carryOver;
        res.longNumber.push_back(multInDigit % first.base);
        carryOver = multInDigit / first.base;
    }
    if (carryOver != 0) {
        res.longNumber.push_back(carryOver);
    }
    res.DltLeadZero();
    return res;
}

void TLongNumb::RightShift() {
    if (this->longNumber.size() == 0) {
        this->longNumber.push_back(0);
        return;
    }
    this->longNumber.push_back(this->longNumber[this->longNumber.size() - 1]);
    for (int i = this->longNumber.size() - 2; i > 0; i--) {
        this->longNumber[i] = this->longNumber[i - 1];
    }
    this->longNumber[0] = 0;
}

TLongNumb Div(const TLongNumb &first, const TLongNumb &second) {
    if (TLongNumb("0") == second) {
        throw std::logic_error("Error");
    }
    TLongNumb b = second;
    TLongNumb result, current;
    result.longNumber.resize(first.longNumber.size());
    for (long i = static_cast<long>(first.longNumber.size()) - 1; i >= 0; i--) {
        current.RightShift();
        current.longNumber[0] = first.longNumber[i];
        current.DltLeadZero();
        long long x = 0, l = 0, r = static_cast<long long>(first.base);
        while (l <= r) {
            long long m = (l + r) / 2;
            TLongNumb t = SmallMult(b, TLongNumb(std::to_string(m)));
            if (t <= current) {
                x = m;
                l = m + 1;
            } else {
                r = m - 1;
            }
        }
        result.longNumber[i] = x;
        current = current - b * TLongNumb(std::to_string(x));
    }
    result.DltLeadZero();
    return result;
}
int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::string firstOper, secondOper;
    char operation;
    while (std::cin >> firstOper >> secondOper >> operation)  {
        TLongNumb left(firstOper), right(secondOper);
        if (operation == '+') {
            std::cout << left + right << "\n";
        } else if (operation == '-') {
            try {
                std::cout << left - right << "\n";
            } catch (std::logic_error &e) {
                std::cout << e.what() << "\n";
            }
        } else if (operation == '*') {
            std::cout << left * right << "\n";
        } else if (operation == '^') {
            try {
                std::cout << Pow(left, right) << "\n";
            } catch (std::logic_error &e) {
                std::cout << e.what() << "\n";
            }
        } else if (operation == '/') {
            try {
                std::cout << left / right << "\n";
            } catch (std::logic_error &e) {
                std::cout << e.what() << "\n";
            }
        } else if (operation == '<') {
            bool res = left < right;
            if (res) {
                std::cout << "true\n";
            } else {
                std::cout << "false\n";
            }
        } else if (operation == '=') {
            bool res = left == right;
            if (res) {
                std::cout << "true\n";
            } else {
                std::cout << "false\n";
            }
        } else if (operation == '>') {
            bool res = left > right;
            if (res) {
                std::cout << "true\n";
            } else {
                std::cout << "false\n";
            }
        }
    }

    return 0;
}