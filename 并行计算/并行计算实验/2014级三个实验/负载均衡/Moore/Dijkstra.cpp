//
// Created by leeshun on 6/6/17.
//

#include "Dijkstra.h"

Dijkstra::Dijkstra() {}

bool Dijkstra::add(const AdjacencyTable &item_) {
    graph.add(item_);
    return true;
}

const Graph& Dijkstra::getGraph() {
    return graph;
}

std::vector<int> Dijkstra::solve(const int source_) {
    std::vector<int> _result;
    std::list<int> _vertex_list = graph.getVertexList();
    std::vector<int> _previous;
    std::vector<int> _visited;

    for(auto each : _vertex_list) {
        _result.push_back(INT_MAX);
        _previous.push_back(-1);
        _visited.push_back(0);
    }
    if(source_ > _vertex_list.size()) {
        //
    }
    _result[source_] = 0;

    int _index = 0,_value;
    while (!_vertex_list.empty()) {
        _value = INT_MAX;
        _index = -1;
        for(auto each : _result) {
            if (each < _value) {
                _value = each;
                _index += 1;
                if(_visited[_index] == 1) {
                    _value = INT_MAX;
                }
            }
        }

        if(_result[_index] == INT_MAX) {
            break;
        }

        for(auto each : graph.getAdjacencyItem(_index).getNodeList()) {
            if(_result[_index] + each.getWeight() < _result[each.getNextNodeName()]) {
                _result[each.getNextNodeName()] = _result[_index] + each.getWeight();
                _previous[each.getNextNodeName()] = _index;
            }

        }
        _visited[_index] = 1;
        _vertex_list.remove(_index);
    }

    return _result;
}

std::vector<int> Dijkstra::moore_solve(const int source_) {
    std::vector<int> _result;
    std::list<int> _vertex_list = graph.getVertexList();
    std::queue<int> _vertex_queue;
    std::vector<int> _vertex_in_queue_list;

    for(auto each : _vertex_list) {
        _result.push_back(INT_MAX);
        _vertex_in_queue_list.push_back(0);
    }

    _result[source_] = 0;
    _vertex_queue.push(source_);
    _vertex_in_queue_list[source_] = 1;

    while(!_vertex_queue.empty()) {
        int _vertex = _vertex_queue.front();
        _vertex_in_queue_list[_vertex] = 0;
        _vertex_queue.pop();
        for(auto each : graph.getAdjacencyItem(_vertex).getNodeList()) {
            if(_result[_vertex] + each.getWeight() < _result[each.getNextNodeName()]) {
                _result[each.getNextNodeName()] = _result[_vertex] + each.getWeight();
                if(_vertex_in_queue_list[each.getNextNodeName()] == 0) {
                    _vertex_queue.push(each.getNextNodeName());
                }
            }
        }
    }

    return _result;
}