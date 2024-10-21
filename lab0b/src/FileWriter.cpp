#include "FileWriter.h"
#include <iomanip>

FileWriter::FileWriter(string filename) : filename(filename), output_file(nullptr) {}

void FileWriter::open() {
    output_file = new ofstream(filename);
}

void FileWriter::write(const vector<pair<string, int>>& wordFrequency, int totalWords) {
    for (const auto& [word, frequency] : wordFrequency) {
        double percentage = (frequency * 100.0) / totalWords;
       *FileWriter::output_file << word << "," << frequency << "," << std::fixed << std::setprecision(2) << percentage << "%\n";
    }
}

void FileWriter::close() {
    if (output_file) {
        output_file->close();
        delete output_file;
        output_file = nullptr;
    }
}