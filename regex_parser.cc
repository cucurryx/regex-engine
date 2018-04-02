//
// Created by xvvx on 18-4-1.
//

#include "regex_parser.h"

/**
 * @brief  <RE> ::= <union> | <simple-RE>
 * @param regex_stream
 * @return
 */
NfaComponent *RegexParser::ParseRegex(stringstream &regex_stream){
    if (regex_stream.eof()) {
        return nullptr;
    }

    NfaComponent *result = nullptr;
    result = ParseUnion(regex_stream);
    if (result == nullptr) {
        return ParseSimpleRegex(regex_stream);
    }
    return result;
}

/**
 * @brief  <union> ::= <RE> "|" <simple-RE>
 * @param regex_stream
 * @return
 */
NfaComponent *RegexParser::ParseUnion(stringstream &regex_stream){
    if (regex_stream.eof()) {
        return nullptr;
    }

    NfaComponent *result = nullptr;
    while(!regex_stream.eof()) {
        NfaComponent *left = ParseRegex(regex_stream);
        if (result && left) {
            result = ConstructAlternate(left, result);
        }
        else if(!result && left) {
            result = left;
        }
        else {
            return nullptr;
        }

        if (regex_stream.eof()) {
            break;
        }

        auto c = char(regex_stream.get());
        if (c == '|') {
            NfaComponent *right = ParseSimpleRegex(regex_stream);
            result = ConstructAlternate(result, right);
            return result;
        }
    }
    return result;
}

/**
 * @brief <concatenation> ::= <simpe-RE> | <basic-RE>
 * @param regex_stream
 * @return
 */
NfaComponent *RegexParser::ParseConcatenate(stringstream &regex_stream){
    if (regex_stream.eof()) {
        return nullptr;
    }

    NfaComponent *result = nullptr;
    result = ParseSimpleRegex(regex_stream);
    if (!result) {
        return ParseBasicRegex(regex_stream);
    }
    return result;
}

/**
 * @brief <simple-RE> ::= <concatenation> | <basic-RE>
 * @param regex_stream
 * @return
 */
NfaComponent *RegexParser::ParseSimpleRegex(stringstream &regex_stream){
    if (regex_stream.eof()) {
        return nullptr;
    }

    NfaComponent *result = nullptr;
    result = ParseConcatenate(regex_stream);
    if (result == nullptr) {
        return ParseBasicRegex(regex_stream);
    }
    return result;
}

/**
 * @brief <basic-RE> :: <star> | <plus> | <elementary-RE>
 * @param regex_stream
 * @return
 */
NfaComponent *RegexParser::ParseBasicRegex(stringstream &regex_stream){
    if (regex_stream.eof()) {
        return nullptr;
    }

    NfaComponent *result = nullptr;
    result = ParseElementary(regex_stream);

    if (!regex_stream.eof()) {
        auto c = char(regex_stream.get());
        if (c == '*') {
            result = ConstructClosure(result);
        }
        else if (c == '+') {
            NfaComponent *start = ConstructClosure(result);
            result = ConstructConcatenate(result, start);
        }
        else {
            regex_stream.unget();
        }
    }
    return result;
}

/**
 * @brief <elementary-RE> ::= <group> | <any> | <eos> | <char> | <set>
 * @param regex_stream
 * @return
 */
NfaComponent *RegexParser::ParseElementary(stringstream &regex_stream) {
    if (regex_stream.eof()) {
        return nullptr;
    }

    NfaComponent *result = nullptr;
    result = ParseGroup(regex_stream);
    if (!result) {
        return result;
    }
    result = ParseSet(regex_stream);
    if (!result) {
        return result;
    }

    if (!regex_stream.eof()) {
        auto c = char(regex_stream.get());
        if (c == '.') {
            result = ConstructAny();
            return result;
        }
        else {
            result = ConstructAtom(c);
        }
        return result;
    }
}

/**
 * @brief <group> ::= "(" <RE> ")"
 * @param regex_stream
 * @return
 */
NfaComponent *RegexParser::ParseGroup(stringstream &regex_stream){
    if (regex_stream.eof()) {
        return nullptr;
    }

    NfaComponent *result = nullptr;
    auto c = char(regex_stream.get());
    if (c == '(') {
        result = ParseRegex(regex_stream);
    }
    c = char(regex_stream.get());
    if (c == ')') {
        return result;
    }
    return nullptr;
}

/**
 * @brief <set> ::= <positive-set> | <negative-set>
 * @param regex_stream
 * @return
 */
// TODO (negative-set is implemented yet.)
NfaComponent *RegexParser::ParseSet(stringstream &regex_stream){
    if (regex_stream.eof()) {
        return nullptr;
    }

    NfaComponent *result = nullptr;
    auto c = char(regex_stream.get());
    if (c == '[') {
        result = ParseSetItems(regex_stream);
    }
    if (!regex_stream.eof()) {
        c = char(regex_stream.get());
        if (c == ']') {
            return result;
        }
    }
    return nullptr;
}

/**
 * @brief <set-items> ::= <set-item> | <set-item> <set-items>
 * @param regex_stream
 * @return
 */
NfaComponent *RegexParser::ParseSetItems(stringstream &regex_stream) {
    if (regex_stream.eof()) {
        return nullptr;
    }

    NfaComponent *result = nullptr;
    while (!regex_stream.eof()) {
        auto left = ParseSetItem(regex_stream);
        if (left && result) {
            result = ConstructConcatenate(left, result);
        }
        else if (left && !result) {
            result = left;
        }
        else {
            return nullptr;
        }

        if (regex_stream.eof()) {
            return result;
        }
        auto c = char(regex_stream.get());
        if (c == ']') {
            regex_stream.unget();
            return result;
        }
    }
    return result;
}

/**
 * @brief <set-item> ::= <range> | <char>
 * @param regex_stream
 * @return
 */
NfaComponent *RegexParser::ParseSetItem(stringstream &regex_stream) {
    if (regex_stream.eof()) {
        return nullptr;
    }

    NfaComponent *result = nullptr;
    auto c = char(regex_stream.get());
    if (!regex_stream.eof()) {
        auto mid = char(regex_stream.get());
        if (mid == '-' && !regex_stream.eof()) {
            auto e = char(regex_stream.get());
            result = ConstructAtom(c, e);
        }
        else {
            regex_stream.unget();
            result = ConstructAtom(c);
        }
    }
    return result;
}

NfaComponent *RegexParser::ParseEscape(stringstream &regex_stream){
    //TODO
    return nullptr;
}
