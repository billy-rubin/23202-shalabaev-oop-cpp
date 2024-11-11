#include "src/BitArray.h"
#include <iostream>

int main() {
    BitArray bits(16, 0b10100);

    std::cout << bits.to_string() << "\n";
    std::cout << bits.count() << "\n";

    BitArray bitsy(bits);
    std::cout << bitsy.to_string() << "\n";

    bits.resize(24, true);
    std::cout << "After resize(24, true):\n";
    std::cout << bits.to_string() << "\n";

    bits.set(1, true);
    std::cout << bits.to_string() << "\n";

    bits.set(1, false);

    std::cout << bits.to_string() << "\n";

    bits.resize(8, false);
    std::cout << "After resize(8, false):\n";
    std::cout << bits.to_string() << "\n";

    std::cout << "Resize Test" << "\n";
    BitArray bits_to_resize(46, ~0ULL);
    std::cout << bits_to_resize.count() << "\n";
    std::cout << bits_to_resize.to_string() << "\n";
    bits_to_resize.resize(55, true);
    std::cout << bits_to_resize.count() << "\n";

    std::cout << bits_to_resize.to_string() << "\n";
    bits_to_resize.resize(32);
    std::cout << bits_to_resize.to_string() << "\n";

    return 0;
}
