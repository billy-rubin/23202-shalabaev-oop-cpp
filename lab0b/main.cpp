#include "src/FileReader.h"
#include "src/FileWriter.h"
#include "src/Parser.h"
#include "src/Statistics.h"

int main(int argc, char* argv[]) {
    FileReader fileReader(argv[1]);
    fileReader.open();
    Parser parser;
    Statistics stats;
    while (fileReader.hasNext()) {
        string line = fileReader.next();
        const list<string> words = parser.Parse(line);
        stats.addWordsToTable(words);
    }
    fileReader.close();
    vector<pair<string, int>> sortedWords = stats.Calculate(stats.getWordFrequency());
    FileWriter fileWriter(argv[2]);
    fileWriter.open();
    vector <string> outputStrings(sortedWords.size());
    stats.ConvertInfoIntoString(outputStrings, sortedWords, stats.getTotalWords());
    fileWriter.write(outputStrings);
    fileWriter.close();
    return 0;
}
