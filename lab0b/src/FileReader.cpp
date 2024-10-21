#include "FileReader.h"

FileReader::FileReader(string filename) : filename(filename), input_file(nullptr) {}

void FileReader::open() {
    input_file = new ifstream(filename);
}

string FileReader::next() {
    string line;
    std::getline(*input_file, line);
    return line;
}

bool FileReader::hasNext() {
    return !(input_file->eof());
}

void FileReader::close() {
    if (input_file) {
        input_file->close();
        delete input_file;
        input_file = nullptr;
    }
}