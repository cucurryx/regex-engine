//
// Created by xvvx on 18-3-31.
//

#include "nfa.h"

/**
 * s0 -- c --> |s1|
 */
NfaComponent *ConstructAtom(char c) {
    NfaNode *start = new NfaNode(true, false);
    NfaNode *end = new NfaNode(false, true);
    NfaEdge *edge = new NfaEdge();
    edge -> set(c);
    start -> add_edge(edge);
    edge -> set_next_node(end);

    NfaComponent *component = new NfaComponent(start, end);
    return component;
}

NfaComponent *ConstructAtom(char l, char h) {
    NfaNode *start = new NfaNode(true, false);
    NfaNode *end = new NfaNode(true, false);
    NfaEdge *edge = new NfaEdge();
    edge -> set_range(l, h);
    start -> add_edge(edge);
    edge -> set_next_node(end);

    NfaComponent *component = new NfaComponent(start, end);
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
    NfaNode *n1_start = n1 -> start();
    NfaNode *n1_end = n1 -> end();
    NfaNode *n2_start  = n2 -> start();
    NfaNode *n2_end = n2 -> end();

    NfaNode *new_start = new NfaNode(true, false);
    NfaNode *new_end = new NfaNode(false, true);

    NfaEdge *edge1 = new NfaEdge();
    NfaEdge *edge2 = new NfaEdge();
    NfaEdge *edge3 = new NfaEdge();
    NfaEdge *edge4 = new NfaEdge();

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

    NfaComponent *component = new NfaComponent(new_start, new_end);
    return component;
}

/**
 * s0 -- a --> s1 -->  s2 -- b --> |s3|
 */
NfaComponent *ConstructConcatenate(NfaComponent *n1, NfaComponent *n2) {
    NfaNode *n1_start = n1 -> start();
    NfaNode *n1_end = n1 -> end();
    NfaNode *n2_start  = n2 -> start();
    NfaNode *n2_end = n2 -> end();

    NfaEdge *edge = new NfaEdge();
    edge -> set_next_node(n2_start);
    n1_end -> add_edge(edge);

    n1_end -> set_end(false);
    n2_start -> set_begin(false);

    NfaComponent *component = new NfaComponent(n1_start, n2_end);
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
    NfaNode *n_start = n -> start();
    NfaNode *n_end = n -> end();

    NfaNode *new_start = new NfaNode(true, false);
    NfaNode *new_end = new NfaNode(false, true);

    NfaEdge *edge1 = new NfaEdge();
    NfaEdge *edge2 = new NfaEdge();
    NfaEdge *edge3 = new NfaEdge();
    NfaEdge *edge4 = new NfaEdge();

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

    NfaComponent *component = new NfaComponent(new_start, new_end);
    return component;
}

/*-----------------------------------------------------------------------------------------------*/
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
        if (edge -> is_in(c)) {
            auto next_node = edge -> next_node();
            if (next_node != nullptr) {
                res = next_node -> match(s) || res;
            }
        }
        else if (edge -> is_epsilon()) {
            auto next_node = edge -> next_node();
            if (next_node != nullptr) {
                res = next_node -> match(c+s) || res;
            }
        }
    }
    return res;
}