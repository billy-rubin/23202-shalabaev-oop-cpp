#include "TransferToTable.h"
#include <gtest/gtest.h>
#include <list>
#include <string>
#include <map>

TEST(TransferToTableTest, AddWordsToTable) {
    TransferToTable table;
    std::list<std::string> words = {"hello", "world", "hello"};
    table.addWordsToTable(words);

    EXPECT_EQ(table.getTotalWords(), 3);
    std::map<std::string, int> expectedFrequency = {
        {"hello", 2},
        {"world", 1}
    };
    EXPECT_EQ(table.getWordFrequency(), expectedFrequency);
}

TEST(TransferToTableTest, GetTotalWords) {
    TransferToTable table;
    std::list<std::string> words = {"apple", "banana", "apple", "cherry"};
    table.addWordsToTable(words);
    EXPECT_EQ(table.getTotalWords(), 4);
}

TEST(TransferToTableTest, GetWordFrequency) {
    TransferToTable table;
    std::list<std::string> words = {"dog", "cat", "dog", "dog", "cat"};
    table.addWordsToTable(words);
    std::map<std::string, int> expectedFrequency = {
        {"dog", 3},
        {"cat", 2}
    };
    EXPECT_EQ(table.getWordFrequency(), expectedFrequency);
}

TEST(TransferToTableTest, AddEmptyList) {
    TransferToTable table;
    std::list<std::string> words = {};
    table.addWordsToTable(words);
    EXPECT_EQ(table.getTotalWords(), 0);
    EXPECT_TRUE(table.getWordFrequency().empty());
}

TEST(TransferToTableTest, AddLargeNumberOfWords) {
    TransferToTable table;
    std::list<std::string> words(10000, "test");
    table.addWordsToTable(words);
    EXPECT_EQ(table.getTotalWords(), 10000);
    EXPECT_EQ(table.getWordFrequency().at("test"), 10000);
}