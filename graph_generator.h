//
// Created by xvvx on 18-4-3.
//

#ifndef REGEXENGINE_GRAPH_GENERATOR_H
#define REGEXENGINE_GRAPH_GENERATOR_H

#include <vector>
#include <algorithm>
#include <unordered_map>

#include <cstdlib>
#include <fstream>

#include "nfa.h"

using std::vector;
using std::unordered_map;


namespace graph_generator {
    void CollectNodes(NfaNode *nfa_node, vector<NfaNode*> &nodes) {
        if (nfa_node == nullptr) {
            return ;
        }

        if (std::find(nodes.begin(), nodes.end(), nfa_node) == nodes.end()) {
            nodes.push_back(nfa_node);
        }
        else {
            return ;
        }

        for (auto each_edge : nfa_node->edges()) {
            auto next_node = each_edge -> next_node();
            CollectNodes(next_node, nodes);
        }
    }

    vector<NfaNode*> CollectNodes(Nfa *nfa) {
        if (nfa == nullptr) {
            return vector<NfaNode*>();
        }
        auto begin = nfa -> begin();
        vector<NfaNode*> nodes;
        CollectNodes(begin, nodes);
        return nodes;
    }

    void WriteToFile(const string &graphname, const vector<NfaNode*> &nodes) {
        string path = "../graphs/" + graphname + ".dot";
        FILE *fp = fopen(path.c_str(), "wt+");

        unordered_map<NfaNode*, int> node_index_map;
        int nodes_size = nodes.size();
        for (int i = 0; i != nodes_size; ++i) {
            node_index_map[nodes[i]] = i;
        }

        fprintf(fp, "digraph %s {\n", graphname.c_str());
        for (auto each_node : nodes) {
            for (auto each_edge : each_node->edges()) {
                auto next_node = each_edge->next_node();
                auto this_node_index = node_index_map[each_node];
                auto next_node_index = node_index_map[next_node];
                auto edge_charmask   = each_edge -> to_string();

                if (edge_charmask.empty()) {
                    edge_charmask = "ϵ";
                }
                fprintf(fp, "\t%d -> %d [label=\"%s\"]\n", this_node_index,
                        next_node_index, edge_charmask.c_str());
            }
        }
        fprintf(fp, "}");
        fclose(fp);
    }

    void GenerateGraph(const string &graphname, Nfa *nfa) {
        auto nodes = CollectNodes(nfa);
        WriteToFile(graphname, nodes);
    }
}

#endif //REGEXENGINE_GRAPH_GENERATOR_H
