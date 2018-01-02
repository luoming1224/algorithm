#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <zconf.h>

/**
*  写一个完整的命令行项目，实现单文件词频统计的功能。
*
*  输入是一个文件（文件名），每行由空格分隔的多个单词组成，如：
*  hello world
*  world is flat
*
*          输出按单词出现频率从低到高排列，如：
*  world 2
*  flat 1
*  hello 1
*  is 1
*  world 1
*  其中第一列是单词，第二列是改单词出现次数。
*  并输出到文件
*  注意点：
*  - 必须是完整的实现，代码符合生产标准的
*  - 文件中只会出现字母，数字，空格
**/
using namespace std;
typedef pair<string, int> PAIR;

struct CmpByValue {
    bool operator()(const PAIR& lhs, const PAIR& rhs) {
        return lhs.second > rhs.second;
    }
};

bool isWord(string str, int len) {
    if (len == 0) {
        return false;
    }
    for (int i = 0; i < len; ++i) {
        if ( !isalpha(str[i]) )
        {
            return false;
        }
    }
    return true;
}

int main(int argc, char **argv) {

    if (argc < 2) {
        std::cout << "please input a file name!" << std::endl;
        return 0;
    }

    std::map<std::string, int> mapOfWords;
    ifstream infile;
    infile.open(argv[1], ios::in);
    string line;
    while (!infile.eof()) {
        std::getline(infile, line);
        cout << line << endl;
        
        istringstream is(line);
        string word;
        while (is >> word) {
            if (isWord(word, word.length())) {
                mapOfWords[word]++;
            }
        }
   /*     
        int i, pos1 = -1;
        bool invalidWord = false;
        char c;
        for (i = 0; (c = line[i]) != '\0'; ++i) {
            if (c == ' ') {
                if (pos1 != -1) {
                    if (invalidWord) {
                        pos1 = -1;
                        invalidWord = false;
                        continue;
                    }
                    string word = line.substr((size_t)pos1, (size_t)(i - pos1));
                    mapOfWords[word]++;
                    pos1 = -1;
                }
                continue;
            } else {
                if (invalidWord) continue;
                if (pos1 == -1) {
                    pos1 = i;
                }
                if (!isalpha(c)) {
                    invalidWord = true;
                }
            }
        }
        if (pos1 != -1 && !invalidWord && pos1 != i) {
            string word = line.substr((size_t)pos1, (size_t)(i - pos1));
            mapOfWords[word]++;
        }
*/
        /*
        std::string::size_type pos1, pos2;
        pos2 = line.find(" ");
        pos1 = 0;
        while (std::string::npos != pos2) {
            string word = line.substr(pos1, pos2 - pos1);
            if (isWord(word, (int) (pos2 - pos1))) {
                mapOfWords[word]++;
            }
            pos1 = pos2 + 1;
            pos2 = line.find(" ", pos1);
        }
        if (pos1 != line.length()) {
            string word = line.substr(pos1);
            if (isWord(word, (int) (line.length() - pos1))) {
                mapOfWords[word]++;
            }
        }
        */

    }
    infile.close();

    vector<PAIR> vecOfWords(mapOfWords.begin(), mapOfWords.end());
    sort(vecOfWords.begin(), vecOfWords.end(), CmpByValue());

    for (int i = 0; i != vecOfWords.size(); ++i) {
        cout << vecOfWords[i].first << " " << vecOfWords[i].second << endl;
    }

    ofstream outfile("out.txt", ios::out);
    for (int i = 0; i != vecOfWords.size(); ++i) {
        outfile << vecOfWords[i].first << " " << vecOfWords[i].second << endl;
    }
    outfile.close();

    return 0;
}
