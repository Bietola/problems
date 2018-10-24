#include <iostream>
#include <type_traits>

template <class Ta, class Tb> 
std::common_type_t<Ta, Tb> gcd(Ta a, Tb b) {
    return b == 0 ? a : gcd(b, a % b);
}

bool solve(int potw, int tomw, int pota, int toma) {
    auto weightGcd = gcd(potw, tomw);
    return pota >= potw / weightGcd || toma >= tomw / weightGcd;
}

int main() {
    size_t problemsNum;
    std::cin >> problemsNum;
    for(size_t j = 0; j < problemsNum; ++j) {
        int potw, tomw, pota, toma;
        std::cin >> potw >> tomw >> pota >> toma;
        std::cout << (solve(potw, tomw, pota, toma) ? "YES" : "NO") << "\n";
    }

    return 0;
}
