#include <mpi.h>
#include <gmpxx.h>
#include <iostream>
#include <chrono>
#include "prng_engine.hpp"

const int LIMIT = 1e4;

int main(int argc,char** argv) {
    int size = 0,rank = 0;
    long cal_amount = 3e6;
    mpz_class in_circle_amount(0);
    double start = 0.0,end = 0.0;
    MPI::Init(argc,argv);
    rank = MPI::COMM_WORLD.Get_rank();
    size = MPI::COMM_WORLD.Get_size();

    sitmo::prng_engine eng;
    eng.seed(rank * time(0));
    int x = 0,y = 0;

    if(rank == 0) {
        start = MPI::Wtime();
    }

    for(int i = 0;i < cal_amount;++i) {
        x = eng() % LIMIT + 1;
        y = eng() % LIMIT + 1;
        if ((x * x + y * y) <= LIMIT * LIMIT) {
            in_circle_amount += 1;
        }
    }

    if(rank != 0) {
        unsigned long m_in_circle_amount = in_circle_amount.get_ui();
        MPI::COMM_WORLD.Send(&m_in_circle_amount,1,MPI::UNSIGNED_LONG,0,0);
    }

    if(rank == 0) {
        unsigned long recv_amount = 0,total_amount = in_circle_amount.get_ui();
        for(int i = 0;i < size - 1;++i) {
            MPI::COMM_WORLD.Recv(&recv_amount,1,MPI::UNSIGNED_LONG,MPI::ANY_SOURCE,MPI::ANY_TAG);
            total_amount += recv_amount;
            recv_amount = 0;
        }

        mpq_class m_pi(total_amount,size * cal_amount);
        m_pi *= 4;
        end = MPI::Wtime();
        std::cout << "Total random number is " << size * cal_amount << std::endl;
        std::cout << "The PI is " << m_pi.get_d() << std::endl;
        std::cout << "It spent " << end - start << " ms" << std::endl;
    }


    MPI::Finalize();
    return 0;
}