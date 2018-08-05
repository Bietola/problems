#include <iostream>
#include <vector>

// Complete the swapToSort function below.
int swapToSort(const std::vector<int>& v) {
    auto const first = std::is_sorted_until(std::begin(v), std::end(v));
    if (first != std::end(v)) {
        
    }
    else {
        return 0;
    }
}

int main() {

    return 0;
}
