#ifndef OOP_CPP_FILEREADER_H
#define OOP_CPP_FILEREADER_H

#include "string"
#include "iostream"
#include "fstream"

using std::string;
using std::ifstream;
// Чтение файла построчно
class FileReader {
private:
    string filename;
    ifstream* input_file;
public:
    FileReader(string filename);
    // открыть файл
    void open();
    string next();
    // есть ли еще данные для считывания
    bool hasNext();
    // закрыть файл
    void close();
    // вернуть в начало
};


#endif //OOP_CPP_FILEREADER_H
