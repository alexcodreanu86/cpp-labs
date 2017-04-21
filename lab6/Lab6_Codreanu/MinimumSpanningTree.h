#ifndef LAB6_MINIMUMSPANNINGTREE_H
#define LAB6_MINIMUMSPANNINGTREE_H

#include <vector>
#include "Vertex.h"
#include "Edge.h"
#include "BinaryHeap.h"
#include "DisjSets.h"

template <class T>
class MinimumSpanningTree {
    std::vector<Edge> * treeEdges;
    int weight;

public:
    MinimumSpanningTree(int verticesNum, BinaryHeap<Edge> & sortedEdges) :
            treeEdges (new std::vector<Edge>()),
            weight(0)
    {
        kruskalMSP(verticesNum, sortedEdges);
    }

    ~MinimumSpanningTree() {
        delete(treeEdges);
    }

    void print() {
        std::cout << "Weight: " << weight << "\n";
        printEdges();

    }

private:
    void kruskalMSP(int verticesNum , BinaryHeap<Edge> & sortedEdges) {
        DisjSets ds { verticesNum };
        while(treeEdges->size() != verticesNum - 1) {
            Edge e = sortedEdges.findMin();
            sortedEdges.deleteMin();
            Vertex<char> uset = ds.find(e.u);
            Vertex<char> vset = ds.find(e.v);
            if (uset != vset) {
                treeEdges->push_back(e);
                weight += e.weight;
                ds.unionSets(uset, vset);
            }
        }
    }

    void printEdges() {
        for (auto edge : *(treeEdges)) {
            Vertex<char> u(edge.u);
            Vertex<char> v(edge.v);
            std::cout << "Edge u: " << u.identifier << " | v: " << v.identifier << " | weight: " << edge.weight << '\n';
        }
    }
};

#endif
