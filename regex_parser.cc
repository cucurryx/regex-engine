//
// Created by xvvx on 18-4-1.
//

#include "regex_parser.h"

/**
 * @brief  <RE>    ::= <simple-RE> | <union>
 *         <union> ::= <simple-RE> "|" <simple-RE>
 * @param regex_stream
 * @return
 */
NfaComponent *RegexParser::ParseRegex(stringstream &regex_stream){
    if (regex_stream.peek() == -1) {
        return nullptr;
    }

    NfaComponent *result = nullptr;
    while (!regex_stream.eof()) {
        NfaComponent *now = ParseSimpleRegex(regex_stream);
        if (result && now) {
            result = ConstructAlternate(result, now);
        }
        else if(!result && now) {
            result = now;
        }
        else {
            return nullptr;
        }

        if (regex_stream.eof()) {
            return result;
        }

        auto c = regex_stream.peek();
        if (char(c) == '|') {
            regex_stream.get();
        }
        else if (char(c) == ')' || c == -1) {
            return result;
        }
        else {
            return nullptr;
        }
    }
}

/**
 * @brief <simple-RE> ::= <basic-RE> | <basic-RE> <simple-RE>
 * @param regex_stream
 * @return
 */
NfaComponent *RegexParser::ParseSimpleRegex(stringstream &regex_stream) {
    if (regex_stream.peek() == -1) {
        return nullptr;
    }

    NfaComponent *result = nullptr;
    while (!regex_stream.eof()) {
        NfaComponent *now = ParseBasicRegex(regex_stream);
        if (result && now) {
            result = ConstructConcatenate(result, now);
        } else if (!result && now) {
            result = now;
        } else {
            return nullptr;
        }

        if (regex_stream.eof()) {
            return result;
        }

        auto c = regex_stream.peek();
        if (char(c) == '|' || char(c) == ')' || c == -1) {
            // regex_stream.get();
            return result;
        }
    }
}

/**
 * @brief <basic-RE> :: <star> | <plus> | <elementary-RE>
 * @param regex_stream
 * @return
 */
NfaComponent *RegexParser::ParseBasicRegex(stringstream &regex_stream){
    if (regex_stream.peek() == -1) {
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
            result = ConstructMoreOne(result);
        }
        else if (c == '?') {
            result = ConstructMaybe(result);
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
    if (regex_stream.peek() == -1) {
        return nullptr;
    }

    NfaComponent *result = nullptr;
    auto c = regex_stream.peek();

    if (char(c) == '(') {
        result = ParseGroup(regex_stream);
    }
    else if (char(c) == '.') {
        regex_stream.get();
        result = ConstructAny();
    }
    else if (char(c) == '[') {
        result = ParseSet(regex_stream);
    }
    else if (c == -1) {
        result = nullptr;
    }
    else if (c == '\\') {
        regex_stream.get();
        c = char(regex_stream.peek());
        if (c == '(' || c == '*' || c == ')' || c == '+' || c == '?' || c == '.' ||
                c == '[' || c == ']' || c == '\\') {
            regex_stream.get();
            result = ConstructAtom(c);
        }
        else {
            //TODO (other circumstances)
            assert(false);
        }
    }
    else {
        regex_stream.get();
        result = ConstructAtom(c);
    }

    return result;
}

/**
 * @brief <group> ::= "(" <RE> ")"
 * @param regex_stream
 * @return
 */
NfaComponent *RegexParser::ParseGroup(stringstream &regex_stream){
    if (regex_stream.peek() == -1) {
        return nullptr;
    }

    NfaComponent *result = nullptr;
    auto c = char(regex_stream.peek());
    if (c == '(') {
        regex_stream.get();
        result = ParseRegex(regex_stream);
    }
    else {
        assert (false); // must be '(' here
    }

    if(!regex_stream.eof()) {
        c = char(regex_stream.peek());
        if (c == ')') {
            regex_stream.get();
            return result;
        }
        else {
            return nullptr;
        }
    }
    return result;
}

/**
 * @brief <set> ::= <positive-set> | <negative-set>
 * @param regex_stream
 * @return
 */
// TODO (negative-set is implemented yet.)
NfaComponent *RegexParser::ParseSet(stringstream &regex_stream){
    if (regex_stream.peek() == -1) {
        return nullptr;
    }

    NfaComponent *result = nullptr;
    auto c = char(regex_stream.get());
    if (c == '[') {
        result = ParseSetItems(regex_stream);
    }
    else {
        regex_stream.unget();
        return nullptr;
    }
    if (regex_stream.eof()) {
        return result;
    }
    int x = regex_stream.get();
    if (x == -1 || char(x) == ']') {
        return result;
    }
    else {
        return nullptr;
    }
}

/**
 * @brief <set-items> ::= <set-item> | <set-item> <set-items>
 * @param regex_stream
 * @return
 */
NfaComponent *RegexParser::ParseSetItems(stringstream &regex_stream) {
    if (regex_stream.peek() == -1) {
        return nullptr;
    }

    NfaComponent *result = nullptr;
    while (regex_stream.peek() != -1) {
        auto current = ParseSetItem(regex_stream);

        if (current && result) {
            result = ConstructAlternate(result, current);
        }
        else if (current && !result) {
            result = current;
        }
        else {
            return nullptr;
        }

        auto c = regex_stream.peek();
        if (c == -1 || char(c) == ']') {
            return result;
        }
    }
}

/**
 * @brief <set-item> ::= <range> | <char>
 * @param regex_stream
 * @return
 */
NfaComponent *RegexParser::ParseSetItem(stringstream &regex_stream) {
    if (regex_stream.peek() == -1 || regex_stream.eof()) {
        return nullptr;
    }

    NfaComponent *result = nullptr;
    auto c = char(regex_stream.get());
    if (regex_stream.peek() != -1) {
        auto mid = char(regex_stream.get());
        if (mid == '-' && regex_stream.peek() != -1) {
            auto e = char(regex_stream.get());
            result = ConstructAtom(c, e);
            return result;
        }
        else {
            regex_stream.unget();
        }
    }
    result = ConstructAtom(c);
    return result;
}

NfaComponent *RegexParser::ParseEscape(stringstream &regex_stream){
    //TODO
    return nullptr;
}
