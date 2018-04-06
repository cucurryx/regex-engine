//
// Created by xvvx on 18-4-4.
//

#ifndef REGEXENGINE_DFA_H
#define REGEXENGINE_DFA_H

#include  <unordered_map>
#include <vector>
#include <set>

#include "nfa.h"

using std::unordered_map;
using std::vector;
using std::set;
/**
 * pre-declaration of classes
 */
class DfaNode;
class Dfa;

/*-----------------------------------------------------------------------------------------------*/
namespace dfa_constructor {
    vector<NfaNode*> EpsilonClosure(NfaNode *node);
    vector<NfaNode*> EpsilonClosure(vector<NfaNode*> nodes);
    vector<NfaNode*> MoveFromNode(NfaNode *node, char a);
    vector<NfaNode*> MoveFromNode(vector<NfaNode*> nodes, char a);
    void EpsilonClosure_(NfaNode *node, vector<NfaNode*> &result);
    DfaNode *ConvertNfaToDfa(Nfa *nfa)
    DfaNode *ConstructDfaFromSet(const set<set<DfaNode*>> &node_set);
    Dfa *MinimizeDfa(Dfa *dfa);
    set<set<DfaNode*>> Split(const set<set<DfaNode*>> &node_set, set<DfaNode*> &nodes);
    set<set<DfaNode*>> Split(char c, const set<set<DfaNode*>> &node_set, set<DfaNode*> &nodes);
    NfaEdge::CharMasks CollectEdgesCharMasks(const vector<NfaNode*> &nodes);
    bool CharCanSplitSet(char c, const set<set<DfaNode*>> &node_set, const set<DfaNode*> &nodes);
    bool ExistEndNode(const vector<NfaNode*> &nodes);
}

vector<DfaNode*> CollectNodes(Dfa *dfa);
void CollectNodes(DfaNode *node, vector<DfaNode*> &nodes);
/*-----------------------------------------------------------------------------------------------*/

class DfaNode {
public:
    DfaNode(bool is_begin=false, bool is_end=false):
            is_begin_(is_begin),
            is_end_(is_end) { }

    void add_edge(char c, DfaNode *node) {
        assert(edges_.count(c) == 0);
        edges_[c] = node;
    }

    void set_begin(bool begin) {
        is_begin_ = begin;
    }

    void set_end(bool end) {
        is_end_ = end;
    }

    bool is_in(char c) {
        return edges_.count(c) != 0;
    }

    bool is_begin() {
        return is_begin_;
    }

    bool is_end() {
        return is_end_;
    }

    bool match(const std::string &regex) {
        if (regex.empty()) {
            return is_end();
        }
        auto c = regex.front();
        std::string tail = std::string(regex.begin()+1, regex.end());
        if (edges_.find(c) != edges_.end()) {
            return edges_[c] -> match(tail);
        }
        else {
            return false;
        }
    }

    unordered_map<char, DfaNode*> edges() {
        return edges_;
    };

private:
    bool is_begin_;
    bool is_end_;
    unordered_map<char, DfaNode*> edges_;
};

class Dfa {
public:
    Dfa(DfaNode *begin = nullptr):
            begin_(begin) {
     //   ConstructFromBegin(begin_);
    }

    bool match(const std::string &regex) {
        if (begin_ == nullptr) {
            return false;
        }
        return begin_ -> match(regex);
    }

    DfaNode *begin() {
        return begin_;
    }

private:
    DfaNode *begin_;
};


#endif //REGEXENGINE_DFA_H
