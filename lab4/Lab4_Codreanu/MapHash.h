#ifndef LAB4_MAPHASH_H
#define LAB4_MAPHASH_H

#include "QuadraticProbing.h"

template <class Key, class Value>
class Pair {
private:
public:
    Key key;
    Value value;
    Pair() {}

    Pair(Key k, Value v) :
            key(k), value(v) {}

    Pair(Key &&k, Value &&v) :
            key(std::move(k)), value(std::move(v)) {}

    Pair(Pair<Key, Value> const &other) {
        key = other.key;
        value = other.value;
    }

    Pair(Key k): key(k) {}

    bool operator!=(const Pair<Key, Value> &other) const {
        return !this->operator==(other);
    }

    bool operator==(const Pair<Key, Value> &other) const {
        return key == other.key;
    }
};


template <class Key, class Value>
class MapHash {
private:
    HashTable< Pair<Key, Value> > table;
    // The notFoundValue is to be returned by get when an element is not found
    Value notFoundValue;

public:
    MapHash(Value notFound);
    bool isEmpty() const;
    bool contains(const Key &key) const;
    bool put(const Key &key, const Value &value);
    const Value get(const Key &key) const;
    void makeEmpty();
};

#import "MapHashImpl.h"

#endif
