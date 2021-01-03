#include <iostream>
#include <random>
#include <chrono>
#include <set>
#include <vector>
#include <mpi.h>

const int array_size = 1e4;
const int sort_number_limit = 1e4;
const int finish_tag = - 1;

int main(int argc,char** argv) {
    int rank = 0,pro_size = 0,length = array_size,tag = 0;
    MPI::Init(argc,argv);
    rank = MPI::COMM_WORLD.Get_rank();
    pro_size = MPI::COMM_WORLD.Get_size();
    int SET_CAPACITY = length / pro_size + 1;
    if(rank == 0) {
		std::vector<int> m_source;
        m_source.resize(array_size);
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::mt19937 generator(seed);
        for(int i = 1;i <= array_size;i++) {
			m_source.push_back(generator() % sort_number_limit  + 1);
        }

        for(auto each : m_source) {
            std::cout << each << " ";
        }
        std::cout << std::endl;

        double _start = MPI::Wtime();
        std::multiset<int> set;
		for(auto& each : m_source) {
            set.insert(each);
            if(SET_CAPACITY < set.size()) {
                int min = *set.begin();
                set.erase(set.begin());
                MPI::COMM_WORLD.Send(&min,1,MPI::INT,rank + 1,tag);
            }
		}
        
        MPI::COMM_WORLD.Send(&finish_tag,1,MPI::INT,rank + 1,tag);

        std::vector<int> sorted;
        
        for(auto i = 1u;i < pro_size;++i) {
            int len = 0;
            MPI::COMM_WORLD.Recv(&len,1,MPI::INT,pro_size - i,tag);
            for(int j = 0;j < len;++j) {
                int tmp = 0;
                MPI::COMM_WORLD.Recv(&tmp,1,MPI::INT,pro_size - i,tag);
                sorted.push_back(tmp);
            }
        }
        std::copy(set.begin(),set.end(),std::back_inserter(sorted));
        double _end = MPI::Wtime();
		std::cout << "it spend " << _end - _start << "s" << std::endl;
        for(auto each : sorted) {
            std::cout << each << " ";
        }
    }
    else {
        std::multiset<int> set;
        while(true) {
            int recv = 0;
            MPI::COMM_WORLD.Recv(&recv,1,MPI::INT,rank - 1,tag);
            if(recv == finish_tag) {
                if(rank + 1 < pro_size) {
                    MPI::COMM_WORLD.Send(&recv,1,MPI::INT,rank + 1,0);
                }
				int len = set.size();
				MPI::COMM_WORLD.Send(&len, 1, MPI::INT, 0, 0);

				for (auto& each : set) {
					MPI::COMM_WORLD.Send(&each, 1, MPI::INT, 0, 0);
				}

				break;
            }

            set.insert(recv);

            if (SET_CAPACITY < set.size()) {
				int min = *set.begin();
				set.erase(set.begin());
                if(rank + 1 < pro_size) {
				    MPI::COMM_WORLD.Send(&min, 1, MPI::INT, rank + 1, 0);
                }
			}
        }
    }

    MPI::Finalize();
}
