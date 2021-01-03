#include <mpi.h>
#include <gmpxx.h>
#include <iostream>

const mpf_class PI25DT ("3.141592653589793238462643");

int main(int argc,char** argv) {
    int size = 0, rank = 0;
    long cal_amount = 30;
    double start = 0,end = 0;
    mpq_class m_pi(0);
    MPI::Init(argc,argv);
    rank = MPI::COMM_WORLD.Get_rank();
    size = MPI::COMM_WORLD.Get_size();

    if(rank == 0) {
        start = MPI::Wtime();
    }
    mpz_class i;
	int step;
	mpq_class num(0);
    if (size > 1) {
        i = rank;
        step = size;
        if (rank % 2 == 0) {
            num = 1;
        }
        else {
            num = -1;
        }
    }
    else {
        i = 1;
        step = 1;
        num = 1;
    }
    mpz_class power5Factor;
    mpz_class power239Factor;
    const mpz_class cal_end = cal_amount;
    while (i < cal_end) {
        mpz_ui_pow_ui(power5Factor.get_mpz_t(),5,2 * i.get_ui() + 1);
        mpz_ui_pow_ui(power239Factor.get_mpz_t(),239,2 * i.get_ui() + 1);
        m_pi += (4 * num / ((2 * i + 1) * power5Factor)) - (num / ((2 * i + 1) * power239Factor));
        i += step;
    }

    if(rank != 0) {
        m_pi.canonicalize();
        std::string _ration_string = m_pi.get_str(10);

        int _length = _ration_string.length() + 1;

        char* _c_ration_string = new char[_length];
        std::strcpy(_c_ration_string,_ration_string.c_str());
        MPI::COMM_WORLD.Send(&_length,1,MPI::INT,0,0);
        MPI::COMM_WORLD.Send(_c_ration_string,_length,MPI::CHAR,0,0);

        delete[] _c_ration_string;
    }

    if (rank == 0) {
        for(int i = 1;i < size;i++) {
            int _length = 0,_tag = 0;
            MPI::COMM_WORLD.Recv(&_length,1,MPI::INT,i,_tag);
            char* _c_recv_string = new char[_length];
            MPI::COMM_WORLD.Recv(_c_recv_string,_length,MPI::CHAR,i,_tag);
            mpq_class _recv_ration(_c_recv_string);
            m_pi += _recv_ration;
            delete[] _c_recv_string;
        }
        m_pi *= 4;
        m_pi.canonicalize();

        end = MPI::Wtime();
        printf("pi is approximately %.25f ",m_pi.get_d());
        mpq_class error(m_pi - PI25DT);
        std::cout << ",Error is " 
            << error.get_d() << std::endl;
        std::cout << "wall clock time = " << end - start << std::endl;
    }

    MPI::Finalize();
}