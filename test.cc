//
// Created by xvvx on 18-4-2.
//

#include <functional>
#include <gtest/gtest.h>

#include "regex_parser.h"

#define STRING_MATCH(str) do {\
        RegexParser parser;\
        stringstream regex_stream(str);\
        auto comp = parser.ParseSetItems(regex_stream);\
        Nfa *nfa = new Nfa(comp);\
        ASSERT_TRUE(nfa->match(str));\
    } while (0);

TEST(TestParseSetItem, HandleSingleInput) {
    RegexParser parser;
    stringstream regex_stream("a");
    auto comp = parser.ParseSetItems(regex_stream);
    Nfa *nfa = new Nfa(comp);
    ASSERT_TRUE(nfa->match("a"));
}

TEST(TestParseSetItem, HandleMultipleInput) {
    RegexParser parser;
    stringstream regex_stream("a-z");
    auto comp = parser.ParseSetItems(regex_stream);
    Nfa *nfa = new Nfa(comp);
    for (auto c = 'a'; c <= 'z'; ++c) {
        ASSERT_TRUE(nfa->match(string(1, c)));
    }
}

TEST(TestParseSetItems, HandleSimpleInput) {
    RegexParser parser;
    stringstream regex_stream("a");
    auto comp = parser.ParseSetItems(regex_stream);
    Nfa *nfa = new Nfa(comp);
    ASSERT_TRUE(nfa->match("a"));
}

TEST(TestParseSetItems, HandleMultipleInput) {
    RegexParser parser;
    stringstream regex_stream("abcdefghijklmnopqrst");
    auto comp = parser.ParseSetItems(regex_stream);
    Nfa *nfa = new Nfa(comp);
    for (auto c = 'a'; c <= 't'; ++c) {
        ASSERT_TRUE(nfa->match(string(1, c)));
    }
}

TEST(TestParsePositiveSet, HandleRangeInput) {
    RegexParser parser;
    stringstream regex_stream("[a-z]");
    auto comp = parser.ParseSetItems(regex_stream);
    Nfa *nfa = new Nfa(comp);
    ASSERT_TRUE(nfa->match("a"));
}

TEST(TestParsePositiveSet, HandleAtomInput) {
    RegexParser parser;
    stringstream regex_stream("[abcde]");
    auto comp = parser.ParseSetItems(regex_stream);
    Nfa *nfa = new Nfa(comp);
    for (auto c = 'a'; c <= 'e'; ++c) {
        ASSERT_TRUE(nfa->match(string(1, c)));
    }
}

TEST(TestParseNegativeSet, HandleRangeInput) {
    //TODO
}

TEST(TestParseNegativeSet, HandleAtomInput) {
    //TODO
}

TEST(TestParseElementary, HandleParenInput) {
    RegexParser parser;
    stringstream regex_stream("([a-z])");
    auto comp = parser.ParseElementary(regex_stream);
    Nfa *nfa = new Nfa(comp);
    for (auto c = 'a'; c <= 'z'; ++c) {
        ASSERT_TRUE(nfa->match(string(1, c)));
    }
}

TEST(TestParseElementary, HandleDotInput) {
    RegexParser parser;
    stringstream regex_stream(".");
    auto comp = parser.ParseElementary(regex_stream);
    Nfa *nfa = new Nfa(comp);
    for (auto c = '!'; c <= ']'; ++c) {
        ASSERT_TRUE(nfa->match(string(1, c)));
    }
}

TEST(TestParseElementary, HandleEmptyInput) {
    RegexParser parser;
    stringstream regex_stream("");
    auto comp = parser.ParseElementary(regex_stream);
    ASSERT_TRUE(comp == nullptr);
}

TEST(TestParseElementary, HandleCharacterInput) {
    RegexParser parser;
    stringstream regex_stream("a");
    auto comp = parser.ParseElementary(regex_stream);
    Nfa *nfa = new Nfa(comp);
    ASSERT_TRUE(nfa->match("a"));
}

TEST(TestParseElementary, HandleRangeInput) {
    RegexParser parser;
    stringstream regex_stream("[a-z]");
    auto comp = parser.ParseElementary(regex_stream);
    Nfa *nfa = new Nfa(comp);
    for (auto c = 'a'; c <= 'z'; ++c) {
        ASSERT_TRUE(nfa->match(string(1, c)));
    }
}

TEST(TestParseBasic, HandleParenInput) {
    RegexParser parser;
    stringstream regex_stream("([a-z])");
    auto comp = parser.ParseBasicRegex(regex_stream);
    Nfa *nfa = new Nfa(comp);
    for (auto c = 'a'; c <= 'z'; ++c) {
        ASSERT_TRUE(nfa->match(string(1, c)));
    }
}

TEST(TestParseBasic, HandleDotStarInput) {
    RegexParser parser;
    stringstream regex_stream(".*");
    auto comp = parser.ParseBasicRegex(regex_stream);
    Nfa *nfa = new Nfa(comp);
    ASSERT_TRUE(nfa->match("hello world"));
}

TEST(TestParseBasic, HandlePlusInput) {
    RegexParser parser;
    stringstream regex_stream("[abc]+");
    auto comp = parser.ParseBasicRegex(regex_stream);
    Nfa *nfa = new Nfa(comp);
    ASSERT_FALSE(nfa->match(""));
    ASSERT_TRUE(nfa->match("aabccaa"));
}

TEST(TestParseSimpleRegex, HandleComplextInputOne) {
    RegexParser parser;
    stringstream regex_stream("([a-z])xxxxx");
    auto comp = parser.ParseSimpleRegex(regex_stream);
    Nfa *nfa = new Nfa(comp);
    for (auto c = 'a'; c <= 'z'; ++c) {
        ASSERT_TRUE(nfa->match(string(1, c) + "xxxxx"));
    }
}

TEST(TestParseSimpleRegex, HandleComplexInputOne) {
    RegexParser parser;
    stringstream regex_stream("[0-9]+(.*)you");
    auto comp = parser.ParseSimpleRegex(regex_stream);
    Nfa *nfa = new Nfa(comp);
    ASSERT_TRUE(nfa->match("211lscin293 you"));
}

TEST(TestParseRegex, HandleComplexInputOne) {
    RegexParser parser;
    stringstream regex_stream("(.*)(cc|h|cpp)");
    auto comp = parser.ParseSimpleRegex(regex_stream);
    Nfa *nfa = new Nfa(comp);
    ASSERT_TRUE(nfa->match("hello.cc"));
    ASSERT_TRUE(nfa->match("test.h"));
}

TEST(TestParseRegex, HandleComplexInputTwo) {
    RegexParser parser;
    stringstream regex_stream("(.*)you\\*");
    auto comp = parser.ParseSimpleRegex(regex_stream);
    Nfa *nfa = new Nfa(comp);
    ASSERT_TRUE(nfa->match("is you*"));
}

TEST(TestParseRegex, HandleComplexInputThree) {
    RegexParser parser;
    stringstream regex_stream("bool [a-z]+( )*=( )*((true)|(false))");
    auto comp = parser.ParseSimpleRegex(regex_stream);
    Nfa *nfa = new Nfa(comp);
    ASSERT_TRUE(nfa->match("bool x = true"));
}

TEST(TestParseEscape, Handle) {
    //TODO
}

#if 1
int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
#endif