#include <iostream>

using num = size_t;

// operations
num add(num lhs, num rhs) {
    return lhs + rhs;
}
num digitsum(num n) {
    num s = 0;
    for(s = 0; n > 0; n /= 10) {
        s += (n % 10);
    }
    return s;
}

// solve
pair<num, size_t> solve(num n, num d) {

}

int main() {
    std::cout << "digitsum(10): " << digitsum(10234) << "\n";

    return 0;
}
