//
// Created by xvvx on 18-3-31.
//

#ifndef REGEXENGINE_NFA_H
#define REGEXENGINE_NFA_H

#include <vector>
#include <bitset>

#include <climits>
#include <cassert>

/**
 * classes
 */
class NfaEdge;
class NfaNode;
class NfaComponent;
class Nfa;

/*-----------------------------------------------------------------------------------------------*/
/**
 * @brief construct basic nfa from a single letter
 * @param c
 * @return
 */
NfaComponent *ConstructAtom(char c);
NfaComponent *ConstructAtom(char l, char h);

/**
 * @brief trainsformation on NFAs that models the effects of each basic RE operator
 * @param n1
 * @param n2
 * @return
 */
NfaComponent *ConstructAlternate(NfaComponent *n1, NfaComponent *n2);
NfaComponent *ConstructConcatenate(NfaComponent *n1, NfaComponent *n2);
NfaComponent *ConstructClosure(NfaComponent *n);

/*-----------------------------------------------------------------------------------------------*/
class NfaEdge {
public:
    typedef std::bitset<CHAR_MAX+1> CharMasks;
public:
    NfaEdge (CharMasks char_masks, NfaNode *next_to):
            char_masks_(char_masks),
            next_to_(next_to) { }

    NfaEdge () = default;

    void set(char c) {
        char_masks_.set(size_t(c));
    }

    void set() {
        char_masks_.set();
    }

    void reset() {
        char_masks_.reset();
    }

    void set_range(char l, char h) {
        while (l <= h) {
            char_masks_.set(size_t(l));
            ++l;
        }
    }

    void set_next_node(NfaNode *new_next) {
        next_to_ = new_next;
    }

    void flip() {
        char_masks_.flip();
    }

    void set_except(char c) {
        char_masks_.set(size_t(c));
        char_masks_.flip();
    }

    bool is_epsilon() {
        return char_masks_.none();
    }

    bool is_in(char c) {
        return char_masks_[c];
    }

    NfaNode *next_node() {
        return next_to_;
    }
private:
    CharMasks char_masks_;
    NfaNode *next_to_ { nullptr };
};

class NfaNode {
public:
    NfaNode (bool is_begin = false, bool is_end = false):
        is_begin_(is_begin),
        is_end_(is_end) { }

    void add_edge(NfaEdge *e) {
        edges_.push_back(e);
    }

    void set_end(bool end) {
        is_end_ = end;
    }

    void set_begin(bool begin) {
        is_begin_ = begin;
    }

    bool is_end() {
        return is_end_;
    }

    bool is_begin() {
        return is_begin_;
    }

    /**
     *
     * @param s
     * @return
     */
    // TODO (this function is to ugly)
    bool match(std::string s);

private:
    std::vector<NfaEdge*> edges_;
    bool is_end_;
    bool is_begin_;
};

class NfaComponent {
public:
    NfaComponent(NfaNode *start = nullptr, NfaNode *end = nullptr):
            start_ (start),
            end_ (end) {
        assert(start -> is_begin());
        assert(end -> is_end());
    }

    NfaNode *start() {
        return start_;
    }

    NfaNode *end() {
        return end_;
    }

private:
    NfaNode *start_;
    NfaNode *end_;
};

class Nfa {
public:
    Nfa(NfaComponent *component = nullptr):
        component_(component) {
        begin_ = component -> start();
    }

    bool match(const std::string &s) {
        if (begin_ == nullptr) {
            return false;
        }
        return begin_ -> match(s);
    }

    NfaNode *begin() {
        return begin_;
    }

private:
    NfaComponent *component_;
    NfaNode *begin_;
};


#endif //REGEXENGINE_NFA_H
