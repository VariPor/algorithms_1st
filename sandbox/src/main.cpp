#include <iostream>
<<<<<<< HEAD
#include <math.h>
=======
#include <vector>
>>>>>>> ccdf496ec5018f0db7f3af688634a35ad2d83c2a

int divCount (int n) {
    for (int j = 2; j <= n / 5 + 1; ++j) {
        if (n % static_cast<int>(pow(5, j)) != 0) return j - 1;
    }
    return n / 5;
}

int main() {
    int n;
    std::cin >> n;
    int res = 0;
    for (int i = 5; i <= n; i += 5) {
        res += divCount(i);
    } 
    std::cout << res;
    return 0;
}
