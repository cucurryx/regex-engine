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

    void WriteToFile(const string &graphname, const vector<NfaNode*> &nodes) {
        string path = "../graphs/" + graphname + "_nfa.dot";
        FILE *fp = fopen(path.c_str(), "wt+");

        unordered_map<NfaNode*, int> node_index_map;
        int nodes_size = nodes.size();
        for (int i = 0; i != nodes_size; ++i) {
            node_index_map[nodes[i]] = i;
        }

        fprintf(fp, "digraph %s {\n", graphname.c_str());

        for (auto each_node : nodes) {
            string shape = "circle";
            if (each_node -> is_end()) {
                shape = "doublecircle";
            }
            fprintf(fp, "\tshape%d [label=\"%d\", shape=%s];\n",
                    node_index_map[each_node], node_index_map[each_node], shape.c_str());
        }

        fprintf(fp, "\n\n");
        for (auto each_node : nodes) {
            for (auto each_edge : each_node->edges()) {
                auto next_node = each_edge->next_node();
                auto this_node_index = node_index_map[each_node];
                auto next_node_index = node_index_map[next_node];
                auto edge_charmask   = each_edge -> to_string();

                if (edge_charmask.empty()) {
                    edge_charmask = "ϵ";
                }
                fprintf(fp, "\tshape%d -> shape%d [label=\"%s\"]\n", this_node_index,
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

    void WriteToFile(const string &graphname, const vector<DfaNode*> &nodes) {
        string path = "../graphs/" + graphname + "_dfa.dot";
        FILE *fp = fopen(path.c_str(), "wt+");

        unordered_map<DfaNode*, int> node_index_map;
        int nodes_size = nodes.size();
        for (int i = 0; i != nodes_size; ++i) {
            node_index_map[nodes[i]] = i;
        }

        fprintf(fp, "digraph %s {\n", graphname.c_str());
        for (auto each_node : nodes) {
            string shape = "circle";
            if (each_node -> is_end()) {
                shape = "doublecircle";
            }
            fprintf(fp, "\tshape%d [label=\"%d\", shape=%s];\n",
                    node_index_map[each_node], node_index_map[each_node], shape.c_str());
        }

        fprintf(fp, "\n\n");
        for (auto each_node : nodes) {
            auto edges = each_node->edges();
            auto iter = edges.cbegin();
            while (iter != edges.cend()) {
                auto next_node = iter->second;
                auto this_node_index = node_index_map[each_node];
                auto next_node_index = node_index_map[next_node];
                auto edge_charmask = string(1, iter->first);
                fprintf(fp, "\tshape%d -> shape%d [label=\"%s\"]\n", this_node_index,
                        next_node_index, edge_charmask.c_str());
                ++iter;
            }
        }
        fprintf(fp, "}");
        fclose(fp);
    }

    void GenerateGraph(const string &graphname, Dfa *dfa) {
        auto nodes = CollectNodes(dfa);
        WriteToFile(graphname, nodes);
    }
}

#endif //REGEXENGINE_GRAPH_GENERATOR_H
