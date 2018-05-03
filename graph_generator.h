//
// Created by xvvx on 18-4-3.
//

#ifndef REGEXENGINE_GRAPH_GENERATOR_H
#define REGEXENGINE_GRAPH_GENERATOR_H

#include <vector>
#include <algorithm>
#include <unordered_map>
#include <map>

#include <cstdlib>
#include <fstream>

#include "nfa.h"

using std::vector;
using std::unordered_map;
using std::map;

namespace graph_generator {

    void WriteToFile(const string &graphname, const vector<NfaNode*> &nodes) {
        string path = "./graphs/" + graphname + "_nfa.dot";
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

    // copy from nfa
    string BitsetToString(const std::bitset<CHAR_MAX> &char_masks) {
        std::string s;
        int beg = 0;
        int end = 0;
        if (char_masks.all()) {
            return "all";
        }
        for (int i = 1; i <= CHAR_MAX; ++i) {
            if (char_masks[i]) {
                if (beg == 0) {
                    beg = i;
                    end = i;
                }
                ++end;
            }
            else {
                if (beg != end) {
                    if (beg + 1 == end) {
                        s += char(beg);
                    }
                    else {
                        s += char(beg);
                        s += "-";
                        s += char(--end);
                    }
                    beg = 0;
                    end = 0;
                }
            }
        }
        return s;
    }

    void WriteToFile(const string &graphname, const vector<DfaNode*> &nodes) {
        string path = "./graphs/" + graphname + "_dfa.dot";
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

        map<std::pair<int, int>, std::bitset<CHAR_MAX>> edge_charmasks;
        for (auto each_node : nodes) {
            auto edges = each_node->edges();
            auto iter = edges.cbegin();
            while (iter != edges.cend()) {
                auto next_node = iter->second;
                auto this_node_index = node_index_map[each_node];
                auto next_node_index = node_index_map[next_node];
                auto index_pair = std::pair<int, int>(this_node_index, next_node_index);
                edge_charmasks[index_pair].set(int(iter -> first));
                ++iter;
            }
        }

        auto iter = edge_charmasks.cbegin();
        while (iter != edge_charmasks.cend()) {
            auto index_pair = iter -> first;
            auto edge_charmask_str = BitsetToString(iter -> second);
            fprintf(fp, "\tshape%d -> shape%d [label=\"%s\"]\n", index_pair.first,
                    index_pair.second, edge_charmask_str.c_str());
            ++iter;
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
