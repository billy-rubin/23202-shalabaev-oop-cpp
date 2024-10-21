#include "FileWriter.h"
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <fstream>

TEST(FileWriterTest, WriteToFile) {
    std::string filename = "test_output.txt";

    FileWriter fileWriter(filename);
    fileWriter.open();

    std::vector<std::pair<std::string, int>> sortedWords = {
            {"hello", 2},
            {"world", 1}
    };
    int totalWords = 3;
    fileWriter.write(sortedWords, totalWords);

    fileWriter.close();

    std::ifstream file(filename);
    std::string line;
    std::getline(file, line);
    EXPECT_EQ(line, "hello,2,66.67%");
    std::getline(file, line);
    EXPECT_EQ(line, "world,1,33.33%");
    file.close();
    remove(filename.c_str());
}

TEST(FileWriterTest, WriteEmptyToFile) {
    std::string filename = "test_empty_output.txt";

    FileWriter fileWriter(filename);
    fileWriter.open();

    std::vector<std::pair<std::string, int>> sortedWords = {};
    int totalWords = 0;
    fileWriter.write(sortedWords, totalWords);

    fileWriter.close();

    std::ifstream file(filename);
    std::string line;
    std::getline(file, line);
    EXPECT_EQ(line, "");
    file.close();
    remove(filename.c_str());
}

TEST(FileWriterTest, WriteLargeToFile) {
    std::string filename = "test_large_output.txt";

    FileWriter fileWriter(filename);
    fileWriter.open();

    std::vector<std::pair<std::string, int>> sortedWords(10000, {"word", 10000});
    int totalWords = 10000;
    fileWriter.write(sortedWords, totalWords);
    fileWriter.close();

    std::ifstream file(filename);
    std::string line;
    std::getline(file, line);
    EXPECT_EQ(line, "word,10000,100.00%");
    file.close();
    remove(filename.c_str());
}