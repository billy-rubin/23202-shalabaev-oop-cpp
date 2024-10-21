#include "FileReader.h"
#include <gtest/gtest.h>
#include <list>
#include <string>
#include <fstream>

TEST(FileReaderTest, ReadFromFile) {
    std::string filename = "test_input.txt";

    std::ofstream testFile(filename);
    testFile << "hello world hello\n";
    testFile.close();

    FileReader fileReader(filename);
    fileReader.open();
    auto content = fileReader.next();
    std::string expectedContent = "hello world hello";
    EXPECT_EQ(content, expectedContent);
    remove(filename.c_str());
}

TEST(FileReaderTest, ReadEmptyFile) {
    std::string filename = "empty_file_test";

    std::ofstream testFile(filename);
    testFile << "\n";
    testFile.close();

    FileReader fileReader(filename);
    fileReader.open();
    auto content = fileReader.next();
    EXPECT_TRUE(content.empty());
    remove(filename.c_str());
}