//
// Created by leeshun on 6/6/17.
//

#include "Graph.h"

Graph::Graph() {
}

std::list<int> Graph::getVertexList() {
    std::list<int> _result;

    for(auto each : table_list) {
        _result.push_back(each.getVertexName());
    }

    return _result;
}

const AdjacencyTable& Graph::getAdjacencyItem(const int index_) {
    return table_list[index_];
}
const int Graph::distance(const int first_, const int second_) {
    if(table_list.size() < first_) {
        Node _node = table_list[first_].getNode(second_);
        if(_node.isNull()) {
            return -1;
        }
        return _node.getWeight();
    }
    return -1;
}

bool Graph::add(const AdjacencyTable &table_) {
    if(_hasTableItem(table_)) {
        return false;
    }

    table_list.push_back(table_);
    return true;
}

bool Graph::_hasTableItem(const AdjacencyTable &table_) {
    for(auto each : table_list) {
        if (each == table_) {
            return true;
        }
    }

    return false;
}