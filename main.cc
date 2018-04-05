/**************************************************************************************************
 * Author: xvvx
 * Email:  xiebei1108@outlook.com
 * Github: https://github.com/xiebei1108
 *************************************************************************************************/

#include <iostream>
#include <cassert>

#include "nfa.h"
#include "dfa.h"
#include "regex_parser.h"
#include "graph_generator.h"

using namespace std;

void GraphGeneratorTest() {
    RegexParser parser;
    Nfa *nfa = parser.ParseToNfa(".*");
    graph_generator::GenerateGraph("example3", nfa);
}

void RegexMatchTest() {
    RegexParser parser;
    const string pr = "xvvx-regex> ";
    string regex;
    string str;

    while (regex != "**quit**") {
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
 //   GraphGeneratorTest();
//    RegexMatchTest();

    RegexParser parser;

    Nfa *nfa1 = parser.ParseToNfa("abc");
    Nfa *nfa2 = parser.ParseToNfa("a|b|c*");
    Nfa *nfa3 = parser.ParseToNfa("a*");

    graph_generator::GenerateGraph("example1", nfa1);
    graph_generator::GenerateGraph("example", nfa2);
    graph_generator::GenerateGraph("test3", nfa3);

    Dfa *dfa1 = parser.ParseToDfa("abc");
    Dfa *dfa2 = parser.ParseToDfa("a|b|c");
    Dfa *dfa3 = parser.ParseToDfa("a*");

    graph_generator::GenerateGraph("test1", dfa1);
    graph_generator::GenerateGraph("example", dfa2);
   // cout << CollectNodes(dfa3).size() << endl;
    //graph_generator::GenerateGraph("test3", dfa3);

    cout << dfa1 -> match("abc") << endl;
    cout << dfa2 -> match("b") << endl;
    //cout << dfa3 -> match("a") << endl;

    return 0;
}