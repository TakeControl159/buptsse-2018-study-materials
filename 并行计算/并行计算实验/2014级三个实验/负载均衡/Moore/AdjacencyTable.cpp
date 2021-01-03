//
// Created by leeshun on 6/6/17.
//

#include "AdjacencyTable.h"

AdjacencyTable::AdjacencyTable(const int vertex_name_) :
    vertex_name(vertex_name_){
    node_list.resize(0);
}

const std::vector<Node>& AdjacencyTable::getNodeList() const{
    return node_list;
}

const Node& AdjacencyTable::getNode(const int next_vertex_name_) {
    for(auto each : node_list) {
        if(each.getNextNodeName() == next_vertex_name_) {
            return each;
        }
    }

    return Node();
}

const int AdjacencyTable::getVertexName() {
    return vertex_name;
}

bool AdjacencyTable::add(const Node &next_vertex_) {
    if(_hasNode(next_vertex_)) {
        return false;
    }
    node_list.push_back(next_vertex_);
    return true;
}

bool AdjacencyTable::operator==(const AdjacencyTable &other_) {
    return vertex_name == other_.vertex_name;
}

bool AdjacencyTable::_hasNode(const Node &other_) {
    if(node_list.size() == 0) {
        return false;
    }
    for(auto each : node_list) {
        if(each == other_) {
            return true;
        }
    }

    return false;
}