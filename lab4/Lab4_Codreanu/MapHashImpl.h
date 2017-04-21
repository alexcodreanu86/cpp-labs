#ifndef LAB4_MAPHASHIMPL_H
#define LAB4_MAPHASHIMPL_H

#include "MapHash.h"


template <class K, class V>
MapHash<K,V>::MapHash(V notFound) :
  table(), notFoundValue(notFound) {};

template <class K, class V>
bool MapHash<K,V>::isEmpty() const {
    return table.isEmpty();
}

template <class K, class V>
bool MapHash<K,V>::contains(const K &key) const {
    const Pair<K, V> pair(key);
    return table.contains(pair);
}

template <class K, class V>
bool MapHash<K,V>::put(const K &key, const V &value) {
    const Pair<K,V> pair(key, value);
    return table.insert(pair);
}

template <class K, class V>
const V MapHash<K,V>::get(const K &key) const {
    Pair<K,V> temp(key, notFoundValue);
    const Pair<K,V> & pair = table.get(temp);
    return pair.value;
}

template <class K, class V>
void MapHash<K,V>::makeEmpty() {
    table.makeEmpty();
};

template <class K, class V>
class hash<Pair<K, V> > {
public:
    size_t operator() (const Pair<K, V> &pair) {
        static hash<K> hs;
        return hs(pair.key);
    }
};

#endif
