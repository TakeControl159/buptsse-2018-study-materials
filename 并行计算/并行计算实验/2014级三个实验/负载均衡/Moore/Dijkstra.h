//
// Created by leeshun on 6/6/17.
//

#ifndef MOORE_DIJKSTRA_H
#define MOORE_DIJKSTRA_H

#include <iostream>
#include <vector>
#include <climits>
#include <queue>
#include "Graph.h"

class Dijkstra {
public:
    Dijkstra();

    bool add(const AdjacencyTable& item_);

    const Graph& getGraph();

    std::vector<int> moore_solve(const int source_);

    std::vector<int> solve(const int source_);

private:
    Graph graph;
};


#endif //MOORE_DIJKSTRA_H
