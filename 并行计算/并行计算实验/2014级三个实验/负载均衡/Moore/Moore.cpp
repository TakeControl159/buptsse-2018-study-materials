//
// Created by leeshun on 6/6/17.
//

#include "Moore.h"

Moore::Moore(int agrc_, char **argv_) :
    MPIBase(agrc_,argv_){
    vertex_amount = 0;
}

std::vector<int> Moore::getDistances() {
    return distances;
}

void Moore::setSource(int source_) {
    source = source_;
}

void Moore::task() {
    vertex_list = graph.getVertexList();
    for(auto each : vertex_list) {
        distances.push_back(INT_MAX);
        vertex_in_queue.push_back(0);
    }

    distances[source] = 0;
    vertex_queue.push(source);
    vertex_in_queue[source] = 1;
    vertex_amount = vertex_list.size();
    m_busy.resize(getSize(), false);

    if(getRank() == 0) {
        _masterTask();
    }
    else {
        _slaveTask();
    }
}



bool Moore::add(const AdjacencyTable &item_) {
    graph.add(item_);
    return true;
}

void Moore::_masterTask() {
    std::cout << "node[" << getRank() << "] working..." << std::endl;
    auto start = MPI::Wtime();

    while(!vertex_queue.empty()) {
        for (auto i = 1u;i < getSize() && !vertex_queue.empty();++i) {
            if(!m_busy[i]) {
                int vertex_id = vertex_queue.front();
                vertex_queue.pop();
                vertex_in_queue[vertex_id] = 0;
                MPI::COMM_WORLD.Send(&vertex_id,1,MPI::INT,i,TASK_FLAG);
                MPI::COMM_WORLD.Send(distances.data(),distances.size(),MPI::INT,i,TASK_FLAG);
                m_busy[i] = true;
            }
        }
        for (auto i = 1u;i < getSize();++i) {
            if(!m_busy[i]) { continue; }
            int ret_size = 0;
            MPI::COMM_WORLD.Recv(&ret_size,1,MPI::INT,i,RETURN_LEN_FLAG);
            m_busy[i] = false;
            if(0 < ret_size) {
                std::vector <int> rets;
                rets.resize(ret_size);
                MPI::COMM_WORLD.Recv(rets.data(),ret_size, MPI::INT, i, RETURN_FLAG);
                for(int i = 0;i < rets.size();i += 2) {
                    if(rets[i + 1] < distances[rets[i]]) { distances[rets[i]] = rets[i + 1]; }
                    if (vertex_in_queue[rets[i]] == 0) {
                        vertex_queue.push(rets[i]);
                        vertex_in_queue[rets[i]] == 1;
                    }
                }
            }
        }
    }
    int padding = 0;
    for (auto i = 1u;i < getSize();++i) {
        MPI::COMM_WORLD.Send(&padding,1,MPI::INT,i,TERMINATE_FLAG);
    }

    auto end = MPI::Wtime();
    for (auto i = 0u; i < distances.size(); ++i) {
        std::cout << "[" << source << "]-->[" << i << "]: " << distances[i] << std::endl;
    }
    std::cout << "wall clock time = " << end - start << std::endl;

}


void Moore::_slaveTask() {
    std::cout << "node[" << getRank() << "] working..." << std::endl;
    while (true) {
        int vertex_id;
        MPI::Status status;
        MPI::COMM_WORLD.Recv(&vertex_id, 1, MPI::INT, 0, MPI::ANY_TAG, status);
        auto tag = status.Get_tag();
        if (TERMINATE_FLAG == tag) {
            break;
        }
        else if (TASK_FLAG == tag) {
            MPI::COMM_WORLD.Recv(distances.data(),distances.size(),MPI::INT,0,TASK_FLAG);
            std::vector<int> rets;
            for(auto each : graph.getAdjacencyItem(vertex_id).getNodeList()) {
                int dis = distances[vertex_id] + each.getWeight();
                if(dis < distances[each.getNextNodeName()]) {
                    distances[each.getNextNodeName()] = dis;
                    rets.push_back(each.getNextNodeName());
                    rets.push_back(dis);
                }
            }
            int ret_size = rets.size();
            MPI::COMM_WORLD.Send(&ret_size, 1, MPI::INT, 0, RETURN_LEN_FLAG);
            MPI::COMM_WORLD.Send(rets.data(), ret_size, MPI::INT, 0, RETURN_FLAG);
        }
    }
    //std::cout << "node[" << getRank() << "] finished..." << std::endl;
}