#include "Parser.h"
#include <gtest/gtest.h>
#include <list>
#include <string>

TEST(ParserTest, ParseContent) {
    Parser parser;
    std::string content = "hello, world! Hello.";
    auto words = parser.Parse(content);
    std::list<std::string> expectedWords = {"hello", "world", "hello"};
    EXPECT_EQ(words, expectedWords);
}

TEST(ParserTest, EmptyContent) {
    Parser parser;
    std::string content = "";
    auto words = parser.Parse(content);
    std::list<std::string> expectedWords = {};
    EXPECT_EQ(words, expectedWords);
}

TEST(ParserTest, SpecialCharacters) {
    Parser parser;
    std::string content = "#@$%^&*()_+";
    auto words = parser.Parse(content);
    std::list<std::string> expectedWords = {};
    EXPECT_EQ(words, expectedWords);
}

TEST(ParserTest, SingleWord) {
    Parser parser;
    std::string content = "unique";
    auto words = parser.Parse(content);
    std::list<std::string> expectedWords = {"unique"};
    EXPECT_EQ(words, expectedWords);
}