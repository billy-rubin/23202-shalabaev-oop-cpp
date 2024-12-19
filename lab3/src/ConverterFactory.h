#ifndef LAB3_CONVERTERFACTORY_H
#define LAB3_CONVERTERFACTORY_H
#include "Converter.h"
#include <map>
#include <memory>
#include <string>
#include "regex"

class ConverterFactory {
public:
    virtual ~ConverterFactory() = default;
    virtual Converter* create(const std::smatch& line) const = 0;
};

class MuterFactory : public ConverterFactory{
public:
    Converter* create(const std::smatch& line) const override;
};

class MixerFactory : public ConverterFactory{
public:
    Converter* create(const std::smatch& line) const override;

};

class EchoerFactory : public ConverterFactory{
public:
    Converter* create(const std::smatch& line) const override;
};

#endif //LAB3_CONVERTERFACTORY_H
