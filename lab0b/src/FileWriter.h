#ifndef OOP_CPP_FILEWRITER_H
#define OOP_CPP_FILEWRITER_H

#include "string"
#include "fstream"
#include "vector"
#include "utility"

using std::string;
using std::ofstream;
using std::vector;
using std::pair;

class FileWriter {
private:
    string filename;
    ofstream* output_file;
public:
    FileWriter(string filename);
    void open();
    void write(const vector<pair<string, int>>& wordFrequency, int totalWords);
    void close();
};

#endif // OOP_CPP_FILEWRITER_H