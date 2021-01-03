//
// Created by leeshun on 6/6/17.
//

#ifndef MOORE_MPIBASE_H
#define MOORE_MPIBASE_H


#include <mpi.h>
#include <iostream>

class MPIBase {
public:
    MPIBase(int argc, char** argv);
    ~MPIBase();

    int getRank() const;
    int getSize() const;

    virtual void task();

private:
    int num_process;
    int num_size;
};



#endif //MOORE_MPIBASE_H
