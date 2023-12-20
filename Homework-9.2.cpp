#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class big_integer {
private:
    static const int BASE = 1;
    static const int SIZE = 10;
    std::vector<int> digits;

public:

    big_integer() {
        for (int i = 0; i < SIZE; i++) {
            digits[i] = 0;
        }
    }

    big_integer(int x) {
        for (int i = 0; i < SIZE; i++) {
            digits[i] = 0;
        }

        int next = 0;
        while (x) {
            digits[next++] = x % BASE;
            x /= BASE;
        }
    }

    big_integer(const std::string& number) {
        for (char c : number) {
            //digits.push_back(c);
            digits.insert(digits.begin(), c);
        }
    }

    big_integer(const big_integer& other) {
        for (int i = 0; i < SIZE; i++) {
            digits[i] = other.digits[i];
        }
    }

    big_integer(big_integer&& other) {
        digits = std::move(other.digits);
    }

    big_integer& operator=(big_integer&& other) {
        digits = std::move(other.digits);
        return *this;
    }

    void operator+=(const big_integer& other) {
        for (int i = 0; i < SIZE; i++) {  
            digits[i] += other.digits[i];   
        }

        for (int i = 0; i < SIZE - 1; i++) { 
            if (digits[i] >= BASE) {  
                digits[i] -= BASE;
                digits[i + 1]++;
            }
        }
    }

    big_integer operator+(const big_integer& other) {
        big_integer n(*this);
        n += other;
        return n;
        //big_integer result;
        //int carry = 0;
        //size_t len = std::max(digits.size(), other.digits.size());
        //for (size_t i = 0; i < len || carry; i++) {
        //    if (i == result.digits.size()) result.digits.push_back(0);
        //    int sum = carry + (i < digits.size() ? digits[i] : 0) + (i < other.digits.size() ? other.digits[i] : 0);
        //    result.digits[i] = sum % 10;
        //    carry = sum / 10;
        //}
        //return result;
    }

    big_integer& operator++() {
        *this += 1;
        return *this;
    }

    void operator*=(const big_integer& other) {
        *this = *this * other;
    }

    big_integer operator*(const big_integer& other) {
        big_integer result;

        for (int i = 0; i < SIZE; i++) {           
            for (int j = 0; j < SIZE - i; j++) {     
                result.digits[i + j] += digits[i] * other.digits[j];
            }
        }

        for (int i = 0; i < SIZE - 1; i++) {
            result.digits[i + 1] += result.digits[i] / BASE;
            result.digits[i] %= BASE;
        }

        return result;
    }
    //big_integer operator*(int num) const {
    //    big_integer result;
    //    int carry = 0;
    //    for (int digit : digits) {
    //        int prod = digit * num + carry;
    //        result.digits.push_back(prod % 10);
    //        carry = prod / 10;
    //   }
    //    while (carry) {
    //        result.digits.push_back(carry % 10);
    //       carry /= 10;
    //    }
    //    return result;
    //}

    friend std::ostream& operator<<(std::ostream& os, const big_integer& num) {
       // for (int digit : num.digits) {
       //     os << digit;
       // }
        for (size_t i = num.digits.size() - 1; i >= 0; i--) {
            os << num.digits[i] << " ";
        }
        return os;
    }
    //friend std::ostream& operator<<(std::ostream& out, const big_integer& num) {
    //    std::string result;
    //
    //    char buffer[10];
    //
    //    for (int i = big_integer::SIZE - 1; i >= 0; i--) {
    //        sprintf(buffer, "%d", num.digits[i]);
    //        result += buffer;
    //    }
        //for (int i = big_integer::SIZE - 1; i >= 0; i--) {
        //    result += std::to_string(num.digits[i]);
        //}
    
    //    int first_idx = result.find_first_not_of('0');
    //    if (first_idx == std::string::npos) {
    //        out << "0";
    //   }
    //    else {
    //        out << result.substr(first_idx);
    //    }
    //
    //    return out;
    //}
};

int main() {
    auto number1 = big_integer("114575");
    auto number2 = big_integer("78524");
    auto result = number1 + number2;
    std::cout << result << std::endl;
    auto result2 = number1 * 2;
    std::cout << result2 << std::endl;

    return 0;
}