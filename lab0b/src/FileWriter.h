#ifndef OOP_CPP_FILEWRITER_H
#define OOP_CPP_FILEWRITER_H

#include "string"
#include "fstream"
#include "vector"

using std::string;
using std::ofstream;
using std::vector;

class FileWriter {
private:
    string filename;
    ofstream output_file;
public:
    FileWriter(string filename);
    void open();
    void write(const vector<string>& outputStrings);
    void close();
};

#endif // OOP_CPP_FILEWRITER_H
