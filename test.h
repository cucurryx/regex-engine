//
// Created by xvvx on 18-4-2.
//

#ifndef REGEXENGINE_TEST_H
#define REGEXENGINE_TEST_H

#include "regex_parser.h"
#include <functional>
#define TEST_PASSED(info) printf("TEST:  %s\n", info);

namespace regex_parser_test {

    void TestParseSetItem() {
        RegexParser parser;
        stringstream regex_stream1("a");
        stringstream regex_stream2("a-z");
        auto comp1 = parser.ParseSetItems(regex_stream1);
        auto comp2 = parser.ParseSetItems(regex_stream2);

        Nfa *nfa1 = new Nfa(comp1);
        assert(nfa1 -> match("a"));
        TEST_PASSED("ParseSetItem <char> succeed");

        Nfa *nfa2 = new Nfa(comp2);
        for (auto c = 'a'; c <= 'z'; ++c) {
            assert(nfa2 -> match(string(1, c)));
        }

        // printf("%s", nfa2 -> to_string().c_str()); // for debug
        TEST_PASSED("ParseSetItem <range> succeed");
    }

    void TestParseSetItems() {
        RegexParser parser;
        stringstream regex_stream1("a");
        stringstream regex_stream2("abcdefghijklmnopqrst");
        auto comp1 = parser.ParseSetItems(regex_stream1);
        auto comp2 = parser.ParseSetItems(regex_stream2);

        Nfa *nfa1 = new Nfa(comp1);
        assert(nfa1 -> match("a"));
        TEST_PASSED("ParseSetItems  <set-item> succeed");

        Nfa *nfa2 = new Nfa(comp2);
        for (auto c = 'a'; c <= 't'; ++c) {
            assert(nfa2 -> match(string(1, c)));
        }

       // printf("%s", nfa2 -> to_string().c_str()); // for debug
        TEST_PASSED("ParseSetItems <set-item> <set-items> succeed");
    }

    void TestParsePositiveSet() {
        RegexParser parser;
        stringstream regex_stream1("[a-z]");
        stringstream regex_stream2("[abcde]");
        auto comp1 = parser.ParseSetItems(regex_stream1);
        auto comp2 = parser.ParseSetItems(regex_stream2);

        Nfa *nfa1 = new Nfa(comp1);
        assert(nfa1 -> match("a"));
        TEST_PASSED("ParsePositiveSet  <positive-set1> succeed");

        Nfa *nfa2 = new Nfa(comp2);
        for (auto c = 'a'; c <= 'e'; ++c) {
            assert(nfa2 -> match(string(1, c)));
        }
       // printf("%s", nfa2 -> to_string().c_str()); // for debug
        TEST_PASSED("ParsePositiveSet <positive-set2> succeed");
    }

    void TestParseNegativeSet() {
        // TODO
    }

    void TestParseElementary() {
        RegexParser parser;
        stringstream regex_stream1("([a-z])");
        stringstream regex_stream2(".");
        stringstream regex_stream3("");
        stringstream regex_stream4("a");
        stringstream regex_stream5("[a-z]");

        auto comp1 = parser.ParseElementary(regex_stream1);
        auto comp2 = parser.ParseElementary(regex_stream2);
        auto comp3 = parser.ParseElementary(regex_stream3);
        auto comp4 = parser.ParseElementary(regex_stream4);
        auto comp5 = parser.ParseElementary(regex_stream5);

        Nfa *nfa1 = new Nfa(comp1);
        for (auto c = 'a'; c <= 'z'; ++c) {
            assert(nfa1 -> match(string(1, c)));
        }
        TEST_PASSED("ParseElementory <group> succeed");

        Nfa *nfa2 = new Nfa(comp2);
       // puts(nfa2 -> to_string().c_str());
        for (auto c = '!'; c <= ']'; ++c) {
            assert(nfa2 -> match(string(1, char(c))));
        }
        TEST_PASSED("ParseElementory <any> succeed");

        assert(comp3 == nullptr);
        TEST_PASSED("ParseElementory <eos> succeed");

        Nfa *nfa4 = new Nfa(comp4);
        assert(nfa2 -> match("a"));
        TEST_PASSED("ParseElementory <char> succeed");

        Nfa *nfa5 = new Nfa(comp5);
        for (auto c = 'a'; c <= 'z'; ++c) {
            assert(nfa2 -> match(string(1, c)));
        }
        TEST_PASSED("ParseElementory <set> succeed");
    }


    void TestParseBasic() {
        RegexParser parser;
        stringstream regex_stream1("([a-z])");
        stringstream regex_stream2(".*");
        stringstream regex_stream3("[abc]+");

        auto comp1 = parser.ParseBasicRegex(regex_stream1);
        auto comp2 = parser.ParseBasicRegex(regex_stream2);
        auto comp3 = parser.ParseBasicRegex(regex_stream3);

        Nfa *nfa1 = new Nfa(comp1);
        for (auto c = 'a'; c <= 'z'; ++c) {
            assert(nfa1 -> match(string(1, c)));
        }
        TEST_PASSED("ParseBasic <elementory-re> succeed");

        Nfa *nfa2 = new Nfa(comp2);
        assert(nfa2 -> match("fuck you"));
        TEST_PASSED("ParseBasic <elementory-re>* succeed");

        Nfa *nfa3 = new Nfa(comp3);
        assert(!nfa3 -> match(""));
        assert(nfa3 -> match("aabccaa"));
        TEST_PASSED("ParseBasic <elementory-re>+ succeed");
    }

    void TestParseSimpleRegex() {
        RegexParser parser;
        stringstream regex_stream1("([a-z])xxxxx");
        stringstream regex_stream2("[0-9]+(.*)you");

        auto comp1 = parser.ParseSimpleRegex(regex_stream1);
        auto comp2 = parser.ParseSimpleRegex(regex_stream2);

        Nfa *nfa1 = new Nfa(comp1);
      //  puts(nfa1 -> to_string().c_str());
        for (auto c = 'a'; c <= 'z'; ++c) {
            assert(nfa1 -> match(string(1, c) + "xxxxx"));
        }
        TEST_PASSED("ParseSimpleRegex <basic-RE> succeed");

        Nfa *nfa2 = new Nfa(comp2);
        assert(nfa2 -> match("211fuck you"));
        TEST_PASSED("ParseSimpleRegex <basic-RE><simple-RE> succeed");
    }

    void TestParseRegex() {
        RegexParser parser;
        stringstream regex_stream1("(.*)(cc|h|cpp)");
        stringstream regex_stream2("(.*)you\\*");
        stringstream regex_stream3("bool [a-z]+( )*=( )*((true)|(false))");

        auto comp1 = parser.ParseSimpleRegex(regex_stream1);
        auto comp2 = parser.ParseSimpleRegex(regex_stream2);
        auto comp3 = parser.ParseSimpleRegex(regex_stream3);

        Nfa *nfa1 = new Nfa(comp1);
     //   puts(nfa1 -> to_string().c_str());
        assert(nfa1 -> match("hello.cc"));
        assert(nfa1 -> match("test.h"));
        TEST_PASSED("ParseRegex <simple-RE> \"|\" <simple-RE> succeed");

        Nfa *nfa2 = new Nfa(comp2);
        assert(nfa2 -> match("fuck you*"));
        TEST_PASSED("ParseRegex <SimpleRegex> succeed");

        Nfa *nfa3 = new Nfa(comp3);

        assert(nfa3 -> match("bool x = true"));
        TEST_PASSED("ParseRegex <SimpleRegex> succeed");
    }

    void TestParseEscape() {
        // TODO
    }
}


#endif //REGEXENGINE_TEST_H
