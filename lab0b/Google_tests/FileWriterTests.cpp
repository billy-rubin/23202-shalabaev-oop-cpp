#include "FileWriter.h"
#include <gtest/gtest.h>
#include <vector>
#include <string>
#include <fstream>

TEST(FileWriterTest, WriteToFile) {
    std::string filename = "test_output.txt";

    FileWriter fileWriter(filename);
    fileWriter.open();

    std::vector<std::string> outputStrings = {
            {"hello,2,66.666667"},
            {"world,1,33.333333%"}
    };
    fileWriter.write(outputStrings);

    fileWriter.close();

    std::ifstream file(filename);
    std::string line;
    std::getline(file, line);
    EXPECT_EQ(line, "hello,2,66.666667");
    std::getline(file, line);
    EXPECT_EQ(line, "world,1,33.333333%");
    file.close();
    remove(filename.c_str());
}

TEST(FileWriterTest, WriteEmptyToFile) {
    std::string filename = "test_empty_output.txt";

    FileWriter fileWriter(filename);
    fileWriter.open();

    vector<std::string> outputStrings = {};
    fileWriter.write(outputStrings);

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

    vector<std::string> outputStrings = {"word,1000000,100.00%"};
    fileWriter.write(outputStrings);
    fileWriter.close();

    std::ifstream file(filename);
    std::string line;
    std::getline(file, line);
    EXPECT_EQ(line, "word,1000000,100.00%");
    file.close();
    remove(filename.c_str());
}