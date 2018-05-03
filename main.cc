/**************************************************************************************************
 * Author: xvvx
 * Email:  xiebei1108@outlook.com
 * Github: https://github.com/xiebei1108
 *************************************************************************************************/

#include <iostream>

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

    cout << "\t\tWelecom!\n\t\tInput a regular expression and we will generate the nfa graph and dfa graph"
            "for you(int /graphs). \n\t\tThen you can input a string and we will match it for you.\n"
            "\t\tinput **quit** to quit."
         << endl;

    while (true) {
        cout << pr;
        cin >> regex;

        if (regex == "**quit**") {
            break;
        }

        Nfa *nfa = parser.ParseToNfa(regex);
        Dfa *dfa = new Dfa(dfa_constructor::ConvertNfaToDfa(nfa));

        graph_generator::GenerateGraph(regex, nfa);
        graph_generator::GenerateGraph(regex+"_dfa", dfa);

        cout << "string to match: ";
        cin >> str;
        if (nfa -> match(str)) {
            cout << "match!\n";
        }
        else {
            cout << "failed!\n";
        }
    }

    system("python ../generate_graph.py");
}

int main() {
   // GraphGeneratorTest();
    RegexMatchTest();
    return 0;
}