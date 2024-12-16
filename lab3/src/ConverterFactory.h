#ifndef LAB3_CONVERTERFACTORY_H
#define LAB3_CONVERTERFACTORY_H
#include "Converter.h"
#include <map>
#include <memory>
#include <string>

class ConverterFactory {
private:
    std::map<std::string, Converter*> converterTypes;
public:
    ConverterFactory();
    ~ConverterFactory();
    Converter* createFromLine(const std::string& line) const;
};

#endif //LAB3_CONVERTERFACTORY_H
