//
// Created by leeshun on 6/6/17.
//

#include "MPIBase.h"

MPIBase::MPIBase(int argc_, char **argv_) {

    MPI::Init(argc_,argv_);


    num_process = MPI::COMM_WORLD.Get_rank();
    num_size = MPI::COMM_WORLD.Get_size();

    //std::cout << "process " << num_process << "/" << num_size << " begin to run!" << std::endl;
}



int MPIBase::getRank() const {
    return num_process;
}

int MPIBase::getSize() const {
    return num_size;
}

MPIBase::~MPIBase() {
    //std::cout << "process " << num_process << "/" << num_size << " stop!" << std::endl;
    MPI::Finalize();
}

void MPIBase::task() {
    //do nothing
}
