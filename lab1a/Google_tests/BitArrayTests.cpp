#include "gtest/gtest.h"
#include "BitArray.h"

// Test default constructor
TEST(BitArrayTest, DefaultConstructor) {
    BitArray b;
    EXPECT_EQ(b.size(), 0);
    EXPECT_TRUE(b.empty());
}

// Test constructor with specified number of bits and initial value
TEST(BitArrayTest, ConstructorWithNumBitsAndValue) {
    BitArray b(64, 0b1111);
    EXPECT_EQ(b.size(), 64);
    EXPECT_EQ(b.count(), 4);

    BitArray b_zero(64, 0);
    EXPECT_EQ(b_zero.size(), 64);
    EXPECT_EQ(b_zero.count(), 0);

// Boundary test for very large bit count
    EXPECT_THROW(BitArray(-1), std::invalid_argument);
}

// Test copy constructor
TEST(BitArrayTest, CopyConstructor) {
    BitArray b1(64, 0b0001);
    BitArray b2(b1);
    EXPECT_EQ(b1.size(), b2.size());
    EXPECT_EQ(b1.count(), b2.count());
    EXPECT_EQ(b1, b2);
}

// Test swap
TEST(BitArrayTest, Swap) {
    BitArray b1(64, 0ULL);
    BitArray b2(64, 1ULL);
    b1.swap(b2);
    EXPECT_EQ(b1.count(), 1);
    EXPECT_EQ(b2.count(), 0);
}

// Test resize
TEST(BitArrayTest, ResizeToTopNewByte) {
    BitArray b(64, ~0UL);
    b.resize(128, false);
    EXPECT_EQ(b.size(), 128);
    EXPECT_EQ(b.count(), 32);

    b.resize(32);
    EXPECT_EQ(b.size(), 32);
    EXPECT_EQ(b.count(), 32);
}

TEST(BitArrayTest, ResizeToTop) {
    BitArray b(46, ~0UL);
    b.resize(55, true);
    EXPECT_EQ(b.size(), 55);
    EXPECT_EQ(b.count(), 41);
}

TEST(BitArrayTest, ResizeToFloorNewByte) {
    BitArray b(150, ~0UL);
    b.resize(111, false);
    EXPECT_EQ(b.size(), 111);
    EXPECT_EQ(b.count(), 32);

    b.resize(32);
    EXPECT_EQ(b.size(), 32);
    EXPECT_EQ(b.count(), 32);
}

TEST(BitArrayTest, ResizeToFloor) {
    BitArray b(64, ~0UL);
    b.resize(2, false);
    EXPECT_EQ(b.size(), 2);
    EXPECT_EQ(b.count(), 2);

    b.resize(32);
    EXPECT_EQ(b.size(), 32);
    EXPECT_EQ(b.count(), 2);
}

// Test push_back
TEST(BitArrayTest, PushBack) {
    BitArray b(64, 0);
    b.push_back(true);
    EXPECT_EQ(b.size(), 65);
    EXPECT_TRUE(b[64]);
}

// Test clear
TEST(BitArrayTest, Clear) {
    BitArray b(64, ~0ULL);
    b.clear();
    EXPECT_EQ(b.size(), 0);
    EXPECT_TRUE(b.empty());
}

// Test bitwise AND operation
TEST(BitArrayTest, BitwiseAndOperation) {
    BitArray b1(64, ~0ULL);
    BitArray b2(64, 0ULL);
    b1 &= b2;
    EXPECT_EQ(b1.count(), 0);

    EXPECT_THROW(b1 &= BitArray(32, 0), std::invalid_argument);
}

// Test bitwise OR operation
TEST(BitArrayTest, BitwiseOrOperation) {
    BitArray b1(64, ~0ULL);
    BitArray b2(64, 0ULL);
    b1 |= b2;
    EXPECT_EQ(b1.count(), 32);

    EXPECT_THROW(b1 |= BitArray(32, 0), std::invalid_argument);
}

// Test bitwise XOR operation
TEST(BitArrayTest, BitwiseXorOperation) {
    BitArray b1(64, 0b1010);
    BitArray b2(64, 0b0101);
    b1 ^= b2;
    EXPECT_EQ(b1.count(), 4);

    EXPECT_THROW(b1 ^= BitArray(32, 0), std::invalid_argument);
}

TEST(BitArrayTest, LeftShift) {
    BitArray b(64, 0b1000011);
    b <<= 5;

    EXPECT_EQ(b[0], true);
    EXPECT_EQ(b[4], true);
}

TEST(BitArrayTest, RightShift) {
    BitArray b(64, 0b1000101);
    b >>= 5;

    EXPECT_EQ(b[63], false);
    EXPECT_EQ(b[59], false);
}

// Test set and reset methods
TEST(BitArrayTest, SetAndReset) {
    BitArray b(64);
    b.set(0);
    b.set(63);
    EXPECT_TRUE(b[0]);
    EXPECT_TRUE(b[63]);
    b.reset(63);
    EXPECT_FALSE(b[63]);

    EXPECT_THROW(b.set(64), std::out_of_range);
    EXPECT_THROW(b.reset(64), std::out_of_range);
}

// Test set all and reset all
TEST(BitArrayTest, SetAllAndResetAll) {
    BitArray b(64);
    b.set();
    EXPECT_EQ(b.count(), 64);
    b.reset();
    EXPECT_EQ(b.count(), 0);
}

// Test any and none
TEST(BitArrayTest, AnyAndNone) {
    BitArray b(64, 0);
    EXPECT_FALSE(b.any());
    EXPECT_TRUE(b.none());

    b.set(0);
    EXPECT_TRUE(b.any());
    EXPECT_FALSE(b.none());
}

// Test count
TEST(BitArrayTest, Count) {
    BitArray b(64, 0xFFFFFFFFFFFFFFFF);
    EXPECT_EQ(b.count(), 32);
    b.reset(0);
    EXPECT_EQ(b.count(), 31);
}

// Test to_string
TEST(BitArrayTest, ToString) {
    BitArray b(4, 0b1010);
    EXPECT_EQ(b.to_string(), "0101");

    BitArray empty_b;
    EXPECT_EQ(empty_b.to_string(), "");
}

// Test equality and inequality operators
TEST(BitArrayTest, EqualityOperators) {
    BitArray b1(64, 0xFFFFFFFFFFFFFFFF);
    BitArray b2(64, 0xFFFFFFFFFFFFFFFF);
    BitArray b3(64, 0);

    EXPECT_TRUE(b1 == b2);
    EXPECT_FALSE(b1 == b3);
    EXPECT_TRUE(b1 != b3);
    EXPECT_FALSE(b1 != b2);
}

// Test bitwise operators & | ^
TEST(BitArrayTest, BitwiseOperators) {
    BitArray b1(64, 0xAAAAAAAAAAAAAAAA);
    BitArray b2(64, 0x5555555555555555);

    BitArray and_result = b1 & b2;
    BitArray or_result = b1 | b2;
    BitArray xor_result = b1 ^ b2;

    EXPECT_EQ(and_result.count(), 0);
    EXPECT_EQ(or_result.count(), 32);
    EXPECT_EQ(xor_result.count(), 32);

    EXPECT_THROW(BitArray(32, 0) & BitArray(64, 0), std::invalid_argument);
    EXPECT_THROW(BitArray(32, 0) | BitArray(64, 0), std::invalid_argument);
    EXPECT_THROW(BitArray(32, 0) ^ BitArray(64, 0), std::invalid_argument);
}
