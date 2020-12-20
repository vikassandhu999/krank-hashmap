#include <iostream>
#include <vector>
#include <unordered_map>
#include "chrono"
#include "HashMap.h"

#define MAX_TABLE_SIZE 5000000
#define MAX_BENCH_VALUE 3000000


//load factor 0.65 = 50000 / 100000
auto startTime = std::chrono::high_resolution_clock::now();

#define startBench() startTime = std::chrono::high_resolution_clock::now()
#define endBench(msg) if(true) { \
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds> (std::chrono::high_resolution_clock::now() - startTime); \
    std::cout << "Operation : " << msg << " time : " << elapsed.count() << " nanoseconds" << std::endl; }

int main() {
    krank::HashMap map =  krank::HashMap(MAX_TABLE_SIZE);
    std::unordered_map<long int, std::string> smap;
    std::vector<long int> list(MAX_BENCH_VALUE);

    for(int i=0;i<MAX_BENCH_VALUE;i++) {
        srand(time(0));
        list.push_back(rand());
    }

    startBench();
        for(auto i = list.begin();i < list.end();i++) {
           map.add(*i , "r");
        }
    endBench("Adding random keys")

    startBench();
        for(auto i = list.begin();i < list.end();i++) {
            smap.insert(std::make_pair(*i , "r"));
        }
    endBench("Std::Adding random keys")
//
//    startBench();
//    map.add(304343,"344345");
//    endBench("Inserting a single value for a Value")
//
//
//
//
//
//    startBench();
//        for(auto i = list.begin();i < list.end();i++) {
//            map.remove(*i);
//        }
//    endBench("Deleting all random keys")
//
//
//
    startBench();
        std::cout << "Value Search for : " << map.get(list.at(500)) << std::endl;
    endBench("Searching for a Value")

    startBench();

    std::cout << "Value Search for : " << smap.find(list.at(500))->first << std::endl;
    endBench("Std::Searching for a Value")

    //    smap.erase()
    return 0;
}