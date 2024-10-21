#include "src/FileReader.h"
#include "src/FileWriter.h"
#include "src/Parser.h"
#include "src/TransferToTable.h"
#include "src/Statistics.h"

int main(int argc, char* argv[]) {
    FileReader fileReader(argv[1]);
    fileReader.open();
    TransferToTable transferToTable;
    Parser parser;
    while (fileReader.hasNext()) {
        string line = fileReader.next();
        const list<string> words = parser.Parse(line);
        transferToTable.addWordsToTable(words);
    }
    fileReader.close();
    Statistics stats;
    vector<pair<string, int>> sortedWords = stats.Calculate(transferToTable.getWordFrequency());
    FileWriter fileWriter(argv[2]);
    fileWriter.open();
    fileWriter.write(sortedWords, transferToTable.getTotalWords());
    fileWriter.close();
    return 0;
}
