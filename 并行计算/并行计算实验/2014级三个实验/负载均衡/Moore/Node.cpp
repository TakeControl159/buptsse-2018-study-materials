//
// Created by leeshun on 6/5/17.
//

#include "Node.h"

Node::Node() {
    is_null_node = true;
}

Node::Node(const int next_node_name_,const int weight_) :
    next_node_name(next_node_name_),weight(weight_){
    is_null_node = false;
}

bool Node::isNull() const {
    return is_null_node;
}

int Node::getNextNodeName() const {
    return next_node_name;
}


int Node::getWeight() const {
    return weight;
}

bool Node::operator==(const Node &other_) const{
    return next_node_name == other_.next_node_name;
}

const Node& Node::operator=(const Node &other_) {
    return Node(other_.next_node_name,other_.weight);
}