#include "nfa.h"
#include "regex_parser.h"
#include "graph_generator.h"
#include "test.h"

#include <iostream>
#include <cassert>

using namespace std;

void GraphGeneratorTest() {
    RegexParser parser;
    Nfa *nfa = parser.ParseToNfa("([0-9]*)a");
    graph_generator::GenerateGraph("graph/example", nfa);
}

void RegexMatchTest() {
    RegexParser parser;
    const string pr = "xvvx-regex> ";
    string regex;
    string str;

    while (true) {
        cout << pr;
        cin >> regex;
        Nfa *nfa = parser.ParseToNfa(regex);

        cout << "string to match: ";
        cin >> str;
        if (nfa -> match(str)) {
            cout << "match!\n";
        }
        else {
            cout << "failed!\n";
        }
    }
}

int main() {
    //GraphGeneratorTest();
    RegexMatchTest();
    return 0;
}