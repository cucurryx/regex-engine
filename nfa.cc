//
// Created by xvvx on 18-3-31.
//

#include "nfa.h"

#include <stack>

NfaComponent *ConstructAny() {
    auto *start = new NfaNode(true, false);
    auto *end = new NfaNode(false, true);
    auto *edge = new NfaEdge();
    edge -> set();
    start -> add_edge(edge);
    edge -> set_next_node(end);
    auto *component = new NfaComponent(start, end);
    return component;
}

/**
 * s0 -- c --> |s1|
 */
NfaComponent *ConstructAtom(char c) {
    auto *start = new NfaNode(true, false);
    auto *end = new NfaNode(false, true);
    auto *edge = new NfaEdge();
    edge -> set(c);
    start -> add_edge(edge);
    edge -> set_next_node(end);

    auto *component = new NfaComponent(start, end);
    return component;
}

NfaComponent *ConstructAtom(char l, char h) {
    auto *start = new NfaNode(true, false);
    auto *end = new NfaNode(false, true);
    auto *edge = new NfaEdge();
    edge -> set_range(l, h);
    start -> add_edge(edge);
    edge -> set_next_node(end);

    auto *component = new NfaComponent(start, end);
    return component;
}

/**
 *     s1 -- a --> s2
 *   /               \
 * s0                 |s5|
 *   \               /
 *     s3 -- b --> s4
 */
NfaComponent *ConstructAlternate(NfaComponent *n1, NfaComponent *n2) {
    if (n1 && !n2) {
        return n1;
    }
    if (n2 && !n1) {
        return n2;
    }
    if (!n1) {
        return nullptr;
    }

    auto *n1_start = n1 -> start();
    auto *n1_end = n1 -> end();
    auto *n2_start  = n2 -> start();
    auto *n2_end = n2 -> end();

    auto *new_start = new NfaNode(true, false);
    auto *new_end = new NfaNode(false, true);

    auto *edge1 = new NfaEdge();
    auto *edge2 = new NfaEdge();
    auto *edge3 = new NfaEdge();
    auto *edge4 = new NfaEdge();

    new_start -> add_edge(edge1);
    new_start -> add_edge(edge2);
    edge1 -> set_next_node(n1_start);
    edge2 -> set_next_node(n2_start);

    n1_end -> add_edge(edge3);
    n2_end -> add_edge(edge4);
    edge3 -> set_next_node(new_end);
    edge4 -> set_next_node(new_end);

    n1_start -> set_begin(false);
    n2_start -> set_begin(false);
    n1_end -> set_end(false);
    n2_end -> set_end(false);

    auto *component = new NfaComponent(new_start, new_end);
    return component;
}

/**
 * s0 -- a --> s1 -->  s2 -- b --> |s3|
 */
NfaComponent *ConstructConcatenate(NfaComponent *n1, NfaComponent *n2) {
    if (n1 && !n2) {
        return n1;
    }
    if (n2 && !n1) {
        return n2;
    }
    if (!n1) {
        return nullptr;
    }

    auto *n1_start = n1 -> start();
    auto *n1_end = n1 -> end();
    auto *n2_start  = n2 -> start();
    auto *n2_end = n2 -> end();

    auto *edge = new NfaEdge();
    edge -> set_next_node(n2_start);
    n1_end -> add_edge(edge);

    n1_end -> set_end(false);
    n2_start -> set_begin(false);

    auto *component = new NfaComponent(n1_start, n2_end);
    return component;
}

/**
 *          ----------
 *         /          \
 *        \/          \
 * s0 --> s1 -- a --> s2 --> |s3|
 *  \                         ^
 *  \                         /
 *   -----------------------
 */
NfaComponent *ConstructClosure(NfaComponent *n) {
    if (n == nullptr) {
        return nullptr;
    }

    auto *n_start = n -> start();
    auto *n_end = n -> end();

    auto *new_start = new NfaNode(true, false);
    auto *new_end = new NfaNode(false, true);

    auto *edge1 = new NfaEdge();
    auto *edge2 = new NfaEdge();
    auto *edge3 = new NfaEdge();
    auto *edge4 = new NfaEdge();

    edge1 -> set_next_node(n_start);
    edge2 -> set_next_node(new_end);
    edge3 -> set_next_node(n_start);
    edge4 -> set_next_node(new_end);

    new_start -> add_edge(edge1);
    new_start -> add_edge(edge4);
    n_end -> add_edge(edge3);
    n_end -> add_edge(edge2);

    n_start -> set_begin(false);
    n_end -> set_end(false);

    auto *component = new NfaComponent(new_start, new_end);
    return component;
}

NfaComponent *ConstructMoreOne(NfaComponent *n) {
    if (n == nullptr) {
        return nullptr;
    }

    auto *n_start = n -> start();
    auto *n_end = n -> end();

    auto *new_start = new NfaNode(true, false);
    auto *new_end = new NfaNode(false, true);

    auto *edge1 = new NfaEdge();
    auto *edge2 = new NfaEdge();
    auto *edge3 = new NfaEdge();

    edge1 -> set_next_node(n_start);
    edge2 -> set_next_node(new_end);
    edge3 -> set_next_node(n_start);

    new_start -> add_edge(edge1);
    n_end -> add_edge(edge3);
    n_end -> add_edge(edge2);

    n_start -> set_begin(false);
    n_end -> set_end(false);

    auto *component = new NfaComponent(new_start, new_end);
    return component;
}

NfaComponent *ConstructMaybe(NfaComponent *n) {
    if (n == nullptr) {
        return nullptr;
    }

    auto *n_start = n -> start();
    auto *n_end = n -> end();

    auto *new_start = new NfaNode(true, false);
    auto *new_end = new NfaNode(false, true);

    auto *edge1 = new NfaEdge();
    auto *edge2 = new NfaEdge();
    auto *edge3 = new NfaEdge();

    edge1 -> set_next_node(n_start);
    edge2 -> set_next_node(new_end);
    edge3 -> set_next_node(new_end);

    new_start -> add_edge(edge1);
    n_end -> add_edge(edge2);
    new_start -> add_edge(edge3);

    n_start -> set_begin(false);
    n_end -> set_end(false);

    auto *component = new NfaComponent(new_start, new_end);
    return component;
}

/*-----------------------------------------------------------------------------------------------*/
// TODO(make this functor more clean)
bool NfaNode::match(std::string s) {
    bool res = false;

    if (s.empty()) {
        if (is_end()) {
            return true;
        }
        for (auto edge : edges_) {
            if (edge -> is_epsilon()) {
                auto next_node = edge -> next_node();
                if (next_node != nullptr) {
                    res =  next_node -> match("") || res;
                }
            }
        }
        return res;
    }

    char c = s.front();
    s.erase(s.begin());

    for (auto edge : edges_) {
        if (edge -> is_in(c) || edge -> is_epsilon()) {
            std::string pre;
            if (edge -> is_epsilon()) {
                pre = std::string(1, c);
            }
            else {
                pre = "";
            }
            auto next_node = edge -> next_node();
            if (next_node != nullptr) {
                res = next_node -> match(pre+s) || res;
            }
        }
    }
    return res;
}

/*-----------------------------------------------------------------------------------------------*/