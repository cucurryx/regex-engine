#include "nfa.h"
#include "regex_parser.h"
#include "test.h"

#include <iostream>
#include <cassert>

using namespace std;


int main() {
    auto *node1 = new NfaNode();
    auto *node2 = new NfaNode();
    auto *node3 = new NfaNode();


    node1 -> set_begin(true);
  //  node1 -> set_end(true);
    node3 -> set_end(true);

    NfaEdge *edge1 = new NfaEdge();
    NfaEdge *edge2 = new NfaEdge();
    NfaEdge *edge3 = new NfaEdge();
    NfaEdge *edge4 = new NfaEdge();
    NfaEdge *edge5 = new NfaEdge();

    edge1 -> set_except('a');
    edge1 -> set_next_node(node1);

    edge2 -> set('a');
    edge2 -> set_next_node(node2);

    edge3 -> set('a');
    edge3 -> set_next_node(node2);

    edge4 -> set('a');
    edge4 -> set('b');
    edge4 -> flip();
    edge1 -> set_next_node(node1);

    edge5 -> set('b');
    edge5 -> set_next_node(node3);

    node1 -> add_edge(edge1);
    node1 -> add_edge(edge2);
    node2 -> add_edge(edge3);
    node2 -> add_edge(edge4);
    node2 -> add_edge(edge5);

    NfaComponent *component1 = ConstructAtom('a', 'z');
    NfaComponent *component2 = ConstructAtom('b');
    NfaComponent *component3 = ConstructAtom('a');
    NfaComponent *component4 = ConstructAtom('b');
  //  NfaComponent *component_1 = ConstructConcatenate(component1, component2);
  //  NfaComponent *component_2 = ConstructConcatenate(component_1, component3);

    //TEST concatenate
  //  Nfa *nfa1 = new Nfa(component1);
  //  Nfa *nfa2 = new Nfa(component2);
   // Nfa *nfa = new Nfa(component_2);

    //cout << nfa -> match("a") << endl;
    //cout << nfa -> match("ab") << endl;
    //cout << nfa -> match("aba") << endl;

    /** TEST alternate
    NfaComponent *component_3 = ConstructAlternate(component1, component2);
    Nfa *nfa_or = new Nfa(component_3);
    cout << nfa_or -> match("a") << endl;
    cout << nfa_or -> match("b") << endl;
    cout << nfa_or -> match("c") << endl;
    */

    // TEST closure
    NfaComponent *component_4 = ConstructClosure(component1);
    Nfa *nfa_closure = new Nfa(component_4);
    assert(nfa_closure -> match(""));
    assert(nfa_closure -> match("aaaaaaaaaaaaaaaaaa"));
    assert(nfa_closure -> match("abbfhjfjfzz"));

   // cout << nfa.match("rthrejhrejrhrehrey") << endl;
  //  cout << node1 -> is_begin() << endl;
   // cout << nfa.match("aaaaab") << endl;
    //cout << nfa.match("baaaa") << endl;
    //cout << nfa.match("2isln0-r
    //NfaEdge *edge = new NfaEdge();
    //cout << edge -> is_epsilon() << endl;
    //edge -> set();
    //cout << edge -> is_in('x');3s09fuoab") << endl;

    //RegexParser parser;
    //Nfa *nfa = parser.ParseToNfa("(a|b)c*");
    //nfa -> match("accccc");
    //nfa -> match("aa");

    //regex_parser_test::TestParseSetItem();
    //regex_parser_test::TestParseSetItems();
    //regex_parser_test::TestParsePositiveSet();
    //regex_parser_test::TestParseElementary();
    //regex_parser_test::TestParseBasic();
    //regex_parser_test::TestParseSimpleRegex();
    //regex_parser_test::TestParseRegex();

    const string pr = "xvvx-regex> ";
    string regex;
    string str;
    RegexParser parser;


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
    return 0;
}