
#ifndef LAB6_VERTEX_H
#define LAB6_VERTEX_H

template <class T>
class Vertex {
public:
    T identifier;
    Vertex();
    Vertex(T id) : identifier(id) {};
    Vertex(int id);
    operator int();
};

template <>
Vertex<char>::Vertex() : identifier('A') { }
template <>
Vertex<char>::Vertex(int id) : identifier(id + 'A') { }

template <>
Vertex<char>::operator int() { return identifier - 'A'; }

#endif //LAB6_VERTEX_H
