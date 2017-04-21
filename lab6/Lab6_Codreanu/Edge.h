//
// Created by Alexandru Codreanu on 4/17/17.
//

#ifndef LAB6_EDGE_H
#define LAB6_EDGE_H

#include <algorithm>

class Edge {
public:
    int u, v, weight;
    Edge() : u(-1), v(-1), weight(-1) {}
    Edge(int u, int v, int weight): u(u), v(v), weight(weight) {}
    Edge(const Edge &other) {
        u = other.u;
        v = other.v;
        weight = other.weight;
    }


    bool operator<(const Edge &other) {
        return weight < other.weight;
    }
};

#endif //LAB6_EDGE_H
