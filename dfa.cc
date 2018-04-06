//
// Created by xvvx on 18-4-4.
//

#include "dfa.h"

#include <algorithm>
#include <queue>
#include <set>
#include <map>

/*-----------------------------------------------------------------------------------------------*/
/**
 * namespace dfa_constructor
 */

/**
 * @brief Use subset construction to convert a nfa to dfa
 * @param nfa
 * @return
 */
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

/**
 * @brief Use Hopcroft Algorithm to minimize a dfa
 * @param dfa
 * @return
 */
Dfa *dfa_constructor::MinimizeDfa(Dfa *dfa) {
    assert (dfa != nullptr);

    auto all_nodes = CollectNodes(dfa);
    set<DfaNode*> terminal_nodes;
    set<DfaNode*> nonterminal_nodes;
    for (auto each_node : all_nodes) {
        if (each_node -> is_end()) {
            terminal_nodes.insert(each_node);
        }
        else {
            nonterminal_nodes.insert(each_node);
        }
    }

    set<set<DfaNode*>> set_t{ terminal_nodes, nonterminal_nodes };
    set<set<DfaNode*>> set_p;

    while (set_p != set_t) {
        set_p = set_t;
        set_t = set<set<DfaNode*>>();

        // T = T union Split(p)
        for (auto each_set : set_p) {
            auto each_set_split = Split(set_p, each_set);
            for (const auto &each : each_set_split) {
                set_t.insert(each);
            }
        }
    }

    auto dfa_begin = ConstructDfaFromSet(set_p);
    auto minimal_dfa = new Dfa(dfa_begin);
    return minimal_dfa;
}

set<set<DfaNode*>>
dfa_constructor::Split(const set<set<DfaNode*>> &node_set, set<DfaNode*> &nodes) {
    set<set<DfaNode*>> result;
    std::map<char, set<DfaNode*>> char_set_map;
    for (char c = 0; c != CHAR_MAX; ++c) {
        result = Split(c, node_set, nodes);
        if (result.size() > 1) {
            return result;
        }
    }
    return result;
}

set<set<DfaNode*>> dfa_constructor::Split(char c, const set<set<DfaNode*>> &node_set,
                                          set<DfaNode*> &nodes) {
    auto set_num = node_set.size();
    vector<set<DfaNode*>> next_set(set_num, set<DfaNode*>());
    int count = 0;
    auto iter = nodes.begin();
    while (iter != nodes.end()) {
        auto node = *iter;
        auto edges = node -> edges();
        auto next_node = node;
        auto edge_iter= edges.find(c);
        if (edge_iter != edges.end()) {
            next_node = edge_iter -> second;
        }

        auto node_set_iter= node_set.begin();
        for (int i = 0; i != set_num; ++i) {
            if (node_set_iter -> find(next_node) != node_set_iter -> end()) {
                next_set[i].insert(node);
            }
            ++node_set_iter;
        }
        ++iter;
    }

    set<set<DfaNode*>> result;
    for (const auto &each : next_set) {
        if (!each.empty()) {
            result.insert(each);
        }
    }
    return result;
}

DfaNode *dfa_constructor::ConstructDfaFromSet(const set<set<DfaNode *>> &node_set) {
    //TODO
    return nullptr;
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
/**
 * tool functions
 */

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
        auto node = iter -> second;
        if (find(nodes.begin(), nodes.end(), node) == nodes.end()) {
            CollectNodes(iter->second, nodes);
        }
        ++iter;
    }
}

/*-----------------------------------------------------------------------------------------------*/

