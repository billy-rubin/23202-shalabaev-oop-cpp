#include "Statistics.h"
#include <gtest/gtest.h>
#include <map>
#include <vector>
#include <string>

TEST(StatisticsTest, CalculateFrequency) {
    Statistics stats;
    std::map<std::string, int> wordFrequency = {
            {"hello", 2},
            {"world", 1}
    };
    auto sortedWords = stats.Calculate(wordFrequency);
    std::vector<std::pair<std::string, int>> expectedSortedWords = {
            {"hello", 2},
            {"world", 1}
    };
    EXPECT_EQ(sortedWords, expectedSortedWords);
}

TEST(StatisticsTest, EmptyFrequency) {
    Statistics stats;
    std::map<std::string, int> wordFrequency = {};
    auto sortedWords = stats.Calculate(wordFrequency);
    std::vector<std::pair<std::string, int>> expectedSortedWords = {};
    EXPECT_EQ(sortedWords, expectedSortedWords);
}

TEST(StatisticsTest, SingleWordFrequency) {
    Statistics stats;
    std::map<std::string, int> wordFrequency = {
            {"word", 5}
    };
    auto sortedWords = stats.Calculate(wordFrequency);
    std::vector<std::pair<std::string, int>> expectedSortedWords = {
            {"word", 5}
    };
    EXPECT_EQ(sortedWords, expectedSortedWords);
}

TEST(StatisticsTest, IdenticalFrequencies) {
    Statistics stats;
    std::map<std::string, int> wordFrequency = {
            {"a", 1},
            {"b", 1},
            {"c", 1}
    };
    auto sortedWords = stats.Calculate(wordFrequency);
    std::vector<std::pair<std::string, int>> expectedSortedWords = {
            {"a", 1},
            {"b", 1},
            {"c", 1}
    };
    EXPECT_EQ(sortedWords, expectedSortedWords);
}

TEST(StatisticsTest, BasicConverter) {
    Statistics stats;
    vector<pair<std::string, int>> sortedWords = {
            {"hello", 2},
            {"world", 1}
    };
    int totalWords = 3;
    vector<std::string> outputStrings(sortedWords.size());
    stats.ConvertInfoIntoString(outputStrings, sortedWords, totalWords);
    EXPECT_EQ(outputStrings[0], "hello,2,66.666667");
    EXPECT_EQ(outputStrings[1], "world,1,33.333333");
}

TEST(StatisticsTest, LargeInfo) {
    Statistics stats;
    vector<pair<std::string, int>> sortedWords = {
            {"word", 1000000},
    };
    vector<std::string> outputStrings(sortedWords.size());
    int totalWords = 1000000;
    stats.ConvertInfoIntoString(outputStrings, sortedWords, totalWords);
    EXPECT_EQ(outputStrings[0], "word,1000000,100.000000");
}