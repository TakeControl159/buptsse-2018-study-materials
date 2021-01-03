//
// Created by leeshun on 6/6/17.
//

#ifndef MOORE_GRAPH_H
#define MOORE_GRAPH_H

#include <vector>
#include <list>
#include "AdjacencyTable.h"
class Graph {
public:
    Graph();
    std::list<int> getVertexList();
    const AdjacencyTable& getAdjacencyItem(const int index_);
    const int distance(const int first_,const int second_);
    bool add(const AdjacencyTable& table_);
private:
    bool _hasTableItem(const AdjacencyTable& table_);
    std::vector<AdjacencyTable> table_list;
};


#endif //MOORE_GRAPH_H
