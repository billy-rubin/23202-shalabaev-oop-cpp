#include "FileWriter.h"
#include "iostream"

FileWriter::FileWriter(string filename) : filename(filename) {}

void FileWriter::open() {
    output_file.open(filename);
}

void FileWriter::write(const vector<string>& outputStrings) {
    if (output_file && output_file.is_open()) {
        for (string const& line: outputStrings) {
            output_file << line << "\n";
        }
    }
}

void FileWriter::close() {
    output_file.close();
}