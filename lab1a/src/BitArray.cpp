#include "BitArray.h"

using namespace std;

BitArray::BitArray() :  bit_array(nullptr), num_of_bits(0), num_elements(0) {}

BitArray::BitArray(int num_bits, unsigned long value) : num_of_bits(num_bits) {
    if (num_of_bits < 0)
        throw std::invalid_argument("Number of bits can't be negative");

    num_elements = (num_of_bits + BITS_PER_ELEMENT - 1) / BITS_PER_ELEMENT;
    bit_array = new uint64_t[num_elements];

    for (int i = 0; i < num_elements; ++i)
        bit_array[i] = 0;

    int bits_to_set = std::min(num_of_bits, (int)(sizeof(unsigned long) * BITS_IN_BYTE));
    for (int i = 0; i < bits_to_set; ++i) {
        if ((value >> i) & 1)
            set(i);
    }
}

BitArray::BitArray(const BitArray& b) : num_of_bits(b.num_of_bits), num_elements(b.num_elements) {
    if (num_elements > 0) {
        bit_array = new uint64_t[num_elements];
        for (int i = 0; i < num_elements; ++i)
            bit_array[i] = b.bit_array[i];
    } else {
        bit_array = nullptr;
    }
}

BitArray:: ~BitArray(){
    delete[] bit_array;
}

BitArray::BitProxy::BitProxy(uint64_t &byte, size_t pos) : byte(byte), bit_pos(pos){}

BitArray::BitProxy& BitArray::BitProxy:: operator=(bool value) {
    if (value)
        byte |= (1ULL << bit_pos);
    else
        byte &= ~(1ULL << bit_pos);
    return *this;
}

BitArray:: BitProxy:: operator bool() const {
    return (byte & (1ULL << bit_pos)) != 0;
}

BitArray::BitProxy BitArray::operator[](size_t bit) {
    if (bit >= num_of_bits)
        throw std::out_of_range("Index of bit is out of range");
    size_t index = bit / 64;
    size_t pos = bit % 64;
    return BitProxy(bit_array[index], pos);
}

void BitArray:: HideBits() {
    if (num_of_bits % BITS_PER_ELEMENT != 0) {
        int extra_bits = BITS_PER_ELEMENT - (num_of_bits % BITS_PER_ELEMENT);
        bit_array[num_elements - 1] &= (~0ULL >> extra_bits);
    }
}

void BitArray:: swap(BitArray& b){
    std::swap(bit_array, b.bit_array);
    std::swap(num_of_bits, b.num_of_bits);
    std::swap(num_elements, b.num_elements);
}

void BitArray::resize(int num_bits, bool value) {
    int new_num_elements = (num_bits + BITS_PER_ELEMENT - 1) / BITS_PER_ELEMENT;
    uint64_t* new_array = new uint64_t[new_num_elements];

    uint64_t fill_value = value ? ~0ULL : 0ULL;
    for (int i = 0; i < new_num_elements; ++i)
        new_array[i] = fill_value;

    size_t bits_to_copy = (num_bits < num_of_bits) ? num_bits : num_of_bits;

    for (int i = 0 ; i < bits_to_copy; i++){
        if (bit_array[i / BITS_PER_ELEMENT] >> (i % BITS_PER_ELEMENT) & 1ULL){
            new_array[i / BITS_PER_ELEMENT] |= (1ULL << (i % BITS_PER_ELEMENT));
        } else {
            new_array[i / BITS_PER_ELEMENT] &= ~(1ULL << (i % BITS_PER_ELEMENT));
        }
    }

    delete[] bit_array;
    bit_array = new_array;
    num_of_bits = num_bits;
    num_elements = new_num_elements;
    HideBits();
}

bool BitArray:: operator[](int i) const {
    return (bit_array[i / BITS_PER_ELEMENT] >> (i % BITS_PER_ELEMENT)) & 1ULL;
}

string BitArray:: to_string() const {
    std::ostringstream bit_string;
    for (int i = 0; i < num_of_bits; i++){
        bit_string << ((*this)[i] ? 1 : 0);
    }
    return bit_string.str();
}


void BitArray::push_back(bool bit) {
    resize(num_of_bits + 1);
    set(num_of_bits - 1, bit);
}

void BitArray::clear() {
    delete[] bit_array;
    bit_array = nullptr;
    num_of_bits = 0;
    num_elements = 0;
}

BitArray& BitArray::operator&=(const BitArray& b) {
    if (this->num_of_bits != b.num_of_bits) {
        throw std::invalid_argument("BitArrays must be of the same size");
    }
    for (int i = 0; i < num_elements; i++) {
        bit_array[i] &= b.bit_array[i];
    }
    return *this;
}

BitArray& BitArray::operator|=(const BitArray& b) {
    if (this->num_of_bits != b.num_of_bits) {
        throw std::invalid_argument("BitArrays must be of the same size");
    }
    for (int i = 0; i < num_elements; i++) {
        bit_array[i] |= b.bit_array[i];
    }
    return *this;
}

BitArray& BitArray::operator^=(const BitArray& b) {
    if (this->num_of_bits != b.num_of_bits) {
        throw std::invalid_argument("BitArrays must be of the same size");
    }
    for (int i = 0; i < num_elements; i++) {
        bit_array[i] ^= b.bit_array[i];
    }
    return *this;
}

BitArray& BitArray::operator<<=(int n) {
    if (n < 0) {
        throw std::invalid_argument("Number of bits can't be negative");
    }
    uint64_t bits_to_shift = n % BITS_PER_ELEMENT;
    uint64_t elements_to_shift = n / BITS_PER_ELEMENT;
    uint64_t* new_bit_array = new uint64_t[num_elements];

    for (int i = num_elements - 1; i >= 0; --i) {

        uint64_t prev_elem = (i - elements_to_shift >= 0) ? bit_array[i - elements_to_shift] : 0;
        uint64_t cur_elem = (i - elements_to_shift - 1 >= 0 && bits_to_shift != 0) ? bit_array[i - elements_to_shift - 1] : 0;

        new_bit_array[i] = (prev_elem << bits_to_shift) | (cur_elem >> (BITS_PER_ELEMENT - bits_to_shift));
    }

    delete[] bit_array;
    bit_array = new_bit_array;
    HideBits();
    return (*this);
}

BitArray& BitArray::operator>>=(int n) {
    if (n < 0) {
        throw std::invalid_argument("Number of bits can't be negative");
    }
    uint64_t bits_to_shift = n % BITS_PER_ELEMENT;
    uint64_t elements_to_shift = n / BITS_PER_ELEMENT;
    uint64_t* new_bit_array = new uint64_t[num_elements];

    for (int i = 0; i < num_elements; i++) {

        uint64_t cur_elem = (i + elements_to_shift < num_elements) ? bit_array[i + elements_to_shift] : 0;
        uint64_t prev_elem = (i + elements_to_shift + 1 < num_elements && bits_to_shift != 0) ? bit_array[i + elements_to_shift + 1] : 0;

        new_bit_array[i] = (cur_elem >> bits_to_shift) | (prev_elem << (BITS_PER_ELEMENT - bits_to_shift));
    }

    delete[] bit_array;
    bit_array = new_bit_array;

    return (*this);
}


BitArray BitArray::operator<<(int n) const {
    if (n < 0){
        throw std::invalid_argument("Number of bits can't be negative");
    }
    BitArray result(*this);
    result <<= n;
    return result;
}

BitArray BitArray::operator>>(int n) const {
    if (n < 0){
        throw std::invalid_argument("Number of bits can't be negative");
    }
    BitArray result(*this);
    result >>= n;
    return result;
}

BitArray& BitArray::set(int n, bool val) {
    if (n < 0 || n >= num_of_bits)
        throw std::out_of_range("Index is out of range");

    if (val)
        bit_array[n / BITS_PER_ELEMENT] |= (1ULL << (n % BITS_PER_ELEMENT));
    else
        bit_array[n / BITS_PER_ELEMENT] &= ~(1ULL << (n % BITS_PER_ELEMENT));

    return *this;
}

BitArray& BitArray::set() {
    for (int i = 0; i < num_elements; ++i)
        bit_array[i] = ~0ULL;
    HideBits();
    return *this;
}

BitArray& BitArray::reset(int n) {
    return set(n, false);
}

BitArray& BitArray::reset() {
    for (int i = 0; i < num_elements; ++i)
        bit_array[i] = 0ULL;
    return *this;
}

int BitArray:: count() const{
    int count_of_bits = 0;
    for (int i = 0; i < num_of_bits; i++){
        if ((bit_array[i / BITS_PER_ELEMENT] >> (i % BITS_PER_ELEMENT)) & 1ULL){
            count_of_bits++;
        }
    }
    return count_of_bits;
}
bool BitArray::any() const {
    if (!BitArray::count()){
        return false;
    }
    return true;
}

bool BitArray::none() const {
    if (BitArray::count()){
        return false;
    }
    return true;
}

int BitArray:: size() const{
    return num_of_bits;
}

int BitArray::byte_size() const {
    return num_elements;
}

bool BitArray:: empty() const{
    return !(num_of_bits);
}


bool operator==(const BitArray& a, const BitArray& b) {
    if (a.size() != b.size()){
        return false;
    }
    for (int i = 0; i < a.size(); ++i) {
        if (a[i] != b[i])
            return false;
    }
    return true;
}

bool operator!=(const BitArray& a, const BitArray& b) {
    if (a == b){
        return false;
    }
    return true;
}

BitArray operator&(const BitArray& b1, const BitArray& b2){
    if (b1.size() != b2.size()){
        throw std::invalid_argument("BitArrays must be of the same size");
    }
    BitArray result(b1);
    result &= b2;
    return result;
}
BitArray operator|(const BitArray& b1, const BitArray& b2){
    if (b1.size() != b2.size()){
        throw std::invalid_argument("BitArrays must be of the same size");
    }
    BitArray result(b1);
    result |= b2;
    return result;
}
BitArray operator^(const BitArray& b1, const BitArray& b2){
    if (b1.size() != b2.size()){
        throw std::invalid_argument("BitArrays must be of the same size");
    }
    BitArray result(b1);
    result ^= b2;
    return result;
}