//
// Created by leeshun on 6/6/17.
//

#ifndef MOORE_ADJACENCYTABLE_H
#define MOORE_ADJACENCYTABLE_H

#include <vector>
#include "Node.h"

class AdjacencyTable {
public:
    AdjacencyTable(const int vertex_name_);
    const std::vector<Node>& getNodeList() const;
    const Node& getNode(const int next_vertex_name_);
    const int getVertexName();
    bool add(const Node& next_vertex_);
    bool operator==(const AdjacencyTable& other_);
private:
    bool _hasNode(const Node& other_);
    int vertex_name;
    std::vector<Node> node_list;
};


#endif //MOORE_ADJACENCYTABLE_H
