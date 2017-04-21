
#include "BinaryHeap.h"
#include "Vertex.h"
#include "Edge.h"
#include "MinimumSpanningTree.h"

int main() {
    Vertex<char> a('A');
    Vertex<char> b('B');
    Vertex<char> c('C');
    Vertex<char> d('D');
    Vertex<char> e('E');
    Vertex<char> f('F');
    Edge ab(a, b, 4);
    Edge ac(a, c, 1);
    Edge bc(b, c, 3);
    Edge bd(b, d, 6);
    Edge be(b, e, 5);
    Edge bf(b, f, 4);
    Edge cd(c, d, 4);
    Edge de(d, e, 2);
    Edge df(d, f, 3);
    Edge ef(e, f, 2);
    std::vector<Vertex<char>> vertices { a, b, c, d, e, f };
    std::vector<Edge> edges { ab, ac, bc, bd, be, bf, cd, de, df, ef };
    BinaryHeap<Edge> sorted_edges(edges);
    MinimumSpanningTree<char> tree(6, sorted_edges);
    tree.print();
}