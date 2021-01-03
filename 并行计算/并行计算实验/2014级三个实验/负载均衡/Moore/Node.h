//
// Created by leeshun on 6/5/17.
//

#ifndef MOORE_NODE_H
#define MOORE_NODE_H

#include <string>

class Node {
public:
    Node();
    Node(const int next_node_name_,const int weight_);
    int getNextNodeName() const;
    int getWeight() const;
    bool operator==(const Node& other_) const;
    const Node&operator=(const Node& other_);
    bool isNull() const;
private:
    int next_node_name;
    int weight;
    bool is_null_node;
};


#endif //MOORE_NODE_H
