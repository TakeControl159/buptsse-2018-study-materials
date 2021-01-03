#include <mpi.h>
#include <gmpxx.h>
#include <cmath>
#include <string>
#include <iostream>

const mpf_class PI25DT("3.141592653589793238462643");


int main(int argc,char** argv) {
    MPI::Init(argc,argv);
    long cal_amount = 4e6;

    int rank = MPI::COMM_WORLD.Get_rank();
    int size = MPI::COMM_WORLD.Get_size();

    mpq_class m_pi(0);
    double _start,_end;

    if(rank == 0) {
        _start = MPI::Wtime();
    }

	mpq_class i;
	int step = 0;
	if (size > 1) {
		i = rank + mpq_class(1,2);
		step = size;
 	}   
	else {
		i = mpq_class(1,2);
		step = 1;
	}
	const mpz_class& nIntervals = cal_amount;
	mpq_class width(1,cal_amount);
	mpq_class sum(0);
	mpq_class x(0);
	while(i < nIntervals) {
		x = width * i;
		sum += (4 / (1 + x*x));
		i += step;	
	}
	m_pi = sum;


    if(rank != 0) {
        m_pi /= cal_amount;
        m_pi.canonicalize();
        std::string _ration_string = m_pi.get_str(10);

        int _length = _ration_string.length() + 1;

        char* _c_ration_string = new char[_length];
        std::strcpy(_c_ration_string,_ration_string.c_str());
        MPI::COMM_WORLD.Send(&_length,1,MPI::INT,0,0);
        MPI::COMM_WORLD.Send(_c_ration_string,_length,MPI::CHAR,0,0);

        delete[] _c_ration_string;
    }

    if(rank == 0) {
        m_pi /= cal_amount;
        for(int i = 1;i < size;i++) {
            int _length = 0,_tag = 0;
            MPI::COMM_WORLD.Recv(&_length,1,MPI::INT,i,_tag);
            char* _c_recv_string = new char[_length];
            MPI::COMM_WORLD.Recv(_c_recv_string,_length,MPI::CHAR,i,_tag);
            mpq_class _recv_ration(_c_recv_string);
            m_pi += _recv_ration;
            delete[] _c_recv_string;
        }
        m_pi.canonicalize();

        _end = MPI::Wtime();
        printf("pi is approximately %.25f ",m_pi.get_d());
        mpq_class error(m_pi - PI25DT);
        std::cout << ",Error is " 
            << error.get_d() << std::endl;
        std::cout << "wall clock time = " << _end - _start << std::endl;
    }

    MPI::Finalize();
}
