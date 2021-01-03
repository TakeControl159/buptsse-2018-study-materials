#include <iostream>
#include <vector>
#include "Dijkstra.h"
#include "Moore.h"

int main(int argc,char**argv) {
    Dijkstra dijkstra;
    Moore moore(argc,argv);

    AdjacencyTable a(0);
    a.add(Node(1,10));
    dijkstra.add(a);
    moore.add(a);

    AdjacencyTable b(1);
    b.add(Node(2,8));
    b.add(Node(3,13));
    b.add(Node(4,24));
    b.add(Node(5,51));
    dijkstra.add(b);
    moore.add(b);

    AdjacencyTable c(2);
    c.add(Node(3,14));
    dijkstra.add(c);
    moore.add(c);

    AdjacencyTable d(3);
    d.add(Node(4,9));
    dijkstra.add(d);
    moore.add(d);

    AdjacencyTable e(4);
    e.add(Node(5,17));
    dijkstra.add(e);
    moore.add(e);

    AdjacencyTable f(5);
    dijkstra.add(f);
    moore.add(f);


    /*Graph graph = dijkstra.getGraph();

    for(auto each : graph.getVertexList()) {
        std::cout << each << " ";
        for (auto item : graph.getAdjacencyItem(each).getNodeList()) {
            std::cout << "xxxx";
            std::cout << item.getNextNodeName() << ":" << item.getWeight() << "  ";
        }
        std::cout << std::endl;
    }

    std::vector<int> _r = dijkstra.solve(0);

    for(auto each : _r) {
        std::cout << each << std::endl;
    }

    std::vector<int> _moore_r = dijkstra.moore_solve(0);

    for(auto each : _moore_r) {
        std::cout << each << std::endl;
    }*/

    moore.setSource(0);
    moore.task();
    return 0;
}