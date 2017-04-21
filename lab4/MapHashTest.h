#ifndef LAB4_MAPHASHTEST_H
#define LAB4_MAPHASHTEST_H

#include <cassert>
#import "MapHash.h"

static void testIsEmpty();
static void testInsertContains();
static void testGet();
static void testMakeEmpty();

void testMapHash() {
    testIsEmpty();
    testInsertContains();
    testGet();
    testMakeEmpty();
}

void testIsEmpty() {
    MapHash<int, int> map(0);

    assert(map.isEmpty());
}

void testInsertContains() {
    MapHash<int, int> map(0);
    assert(!map.contains(1));

    map.put(3, 6);
    assert(map.contains(3));
}

void testGet() {
    MapHash<int, std::string> map("NOT FOUND");
    map.put(3, "Alex");

    std::string name = map.get(3);

    assert("Alex" == name);

    std::string invalid = map.get(4);

    assert("NOT FOUND" == invalid);
}

static void testMakeEmpty() {
    MapHash<std::string, int> map(-100);

    map.put("Alex", 10);

    assert(10 == map.get("Alex"));
    assert(!map.isEmpty());

    map.makeEmpty();
    assert(map.isEmpty());
    assert(-100 == map.get("Alex")) ;
}

#endif
