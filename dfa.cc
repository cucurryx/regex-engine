//
// Created by xvvx on 18-4-4.
//

#include "dfa.h"

#include <algorithm>
#include <queue>
#include <set>
#include <map>


DfaNode *dfa_constructor::ConvertNfaToDfa(Nfa *nfa) {
    assert(nfa != nullptr);

    std::map<vector<NfaNode*>, DfaNode*> set_dfa_node_map;
    DfaNode *begin_node = new DfaNode(true, false);

    auto all_nodes = CollectNodes(nfa);
    auto begin_set = EpsilonClosure(nfa -> begin());
    std::sort(begin_set.begin(), begin_set.end());
    set_dfa_node_map.insert({begin_set, begin_node});

    std::queue<vector<NfaNode*>> work_list;
    work_list.push(begin_set);

    while (!work_list.empty()) {
        auto curr_set = work_list.front();
        auto *curr_dfa_node = set_dfa_node_map[curr_set];
        auto chars = CollectEdgesCharMasks(curr_set);
        
        for (char c = 0; c < CHAR_MAX; ++c) {
            if (chars.test(c)) {
                auto next_nodes = EpsilonClosure(MoveFromNode(curr_set, c));
                std::sort(next_nodes.begin(), next_nodes.end());
                auto iter = set_dfa_node_map.find(next_nodes);

                if (iter == set_dfa_node_map.end()) {
                    iter = set_dfa_node_map.insert(
                            {next_nodes, new DfaNode(false, false)}).first;
                    work_list.push(next_nodes);
                }

                DfaNode *new_dfa_node = iter -> second;
                if (ExistEndNode(next_nodes)) {
                    new_dfa_node -> set_end(true);
                }
                curr_dfa_node -> add_edge(c, new_dfa_node);
            }
        }
        work_list.pop();
    }
    return begin_node;
}

vector<NfaNode*> dfa_constructor::EpsilonClosure(NfaNode *node) {
    vector<NfaNode*> result;
    EpsilonClosure_(node, result);
    return result;
}

vector<NfaNode*> dfa_constructor::EpsilonClosure(vector<NfaNode*> nodes) {
    vector<NfaNode*> result;
    for (auto each_node : nodes) {
        EpsilonClosure_(each_node, result);
    }
    return result;
}

vector<NfaNode*> dfa_constructor::MoveFromNode(NfaNode *node, char a) {
    vector<NfaNode*> result;
    for (auto each_edge : node -> edges()) {
        if (each_edge -> is_in(a)) {
            auto beg = result.begin();
            auto end = result.end();
            if (find(beg, end, each_edge -> next_node()) == end) {
                result.push_back(each_edge -> next_node());
            }
        }
    }
    return result;
}

vector<NfaNode*> dfa_constructor::MoveFromNode(vector<NfaNode*> nodes, char a) {
    vector<NfaNode*> result;

    for (auto node : nodes) {
        for (auto each_edge : node -> edges()) {
            if (each_edge -> is_in(a)) {
                auto beg = result.begin();
                auto end = result.end();
                if (find(beg, end, each_edge -> next_node()) == end) {
                    result.push_back(each_edge -> next_node());
                }
            }
        }
    }
    return result;
}

void dfa_constructor::EpsilonClosure_(NfaNode *node, vector<NfaNode*> &result) {
    if (node == nullptr || find(result.begin(), result.end(), node) != result.end()) {
        return ;
    }
    result.push_back(node);
    for (auto each_edge : node -> edges()) {
        if (each_edge -> is_epsilon()) {
            EpsilonClosure_(each_edge -> next_node(), result);
        }
    }
}

NfaEdge::CharMasks dfa_constructor::CollectEdgesCharMasks(const vector<NfaNode*> &nodes) {
    NfaEdge::CharMasks char_masks;
    for (auto each : nodes) {
        for (auto each_edge : each -> edges()) {
            auto this_char_masks = each_edge -> char_masks();
            char_masks |= this_char_masks;
        }
    }
    return char_masks;
}

bool dfa_constructor::ExistEndNode(const vector<NfaNode*> &nodes) {
    bool result = false;
    for (auto each : nodes) {
        result |= each -> is_end();
    }
    return result;
}

/*-----------------------------------------------------------------------------------------------*/

vector<DfaNode*> CollectNodes(Dfa *dfa) {
    vector<DfaNode*> nodes;
    if (dfa == nullptr) {
        return nodes;
    }
    auto begin = dfa -> begin();
    CollectNodes(begin, nodes);
    return nodes;
}

void CollectNodes(DfaNode *node, vector<DfaNode*> &nodes) {
    if (node == nullptr) {
        return;
    }

    nodes.push_back(node);
    auto edges = node -> edges();
    auto iter = edges.begin();
    while (iter != edges.end()) {
        CollectNodes(iter->second, nodes);
        ++iter;
    }
}

/*-----------------------------------------------------------------------------------------------*/

