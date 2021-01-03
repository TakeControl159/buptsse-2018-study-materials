//
// Created by leeshun on 6/6/17.
//

#ifndef MOORE_MOORE_H
#define MOORE_MOORE_H

#include <mpi.h>
#include <vector>
#include <list>
#include <queue>
#include <climits>
#include "MPIBase.h"
#include "Graph.h"
#include "AdjacencyTable.h"

class Moore :public MPIBase{
public:
    Moore(int agrc_,char** argv_);
    void task();
    bool add(const AdjacencyTable& item_);
    void setSource(int source_);
    std::vector<int> getDistances();

    enum flag_type {
        RETURN_LEN_FLAG,
        RETURN_FLAG,
        TASK_FLAG,
        TERMINATE_FLAG
    };

private:
    void _masterTask();
    void _slaveTask();
    void _sendDistance(int source_);
    std::vector<int> distances;
    std::list<int> vertex_list;
    std::vector<int> vertex_in_queue;
    std::queue<int> vertex_queue;
    std::vector<bool> m_busy;
    int source;
    int vertex_amount;
    int* p_vertex;
    Graph graph;
};


#endif //MOORE_MOORE_H
