//
// Created by vikas on 12/19/20.
//

#include <cstdlib>
#include "iostream"
#include <string>

#ifndef UNTITLED1_HASHMAP_H
#define UNTITLED1_HASHMAP_H

namespace krank {
#define MINIMUM_TABLE_SIZE 1000

    typedef struct HashTableEntry {
        long int key;
        std::string value;
        HashTableEntry *next;
    } hashTableEntry;

    class HashTable {
    private:
        hashTableEntry **table;
        unsigned long size;
        unsigned long used;

        void fillNull() {
            if (this->table == NULL) return;
            for (int i = 0; i < this->size; ++i) {
                this->table[i] = NULL;
            }
        }

        void printTable() {
            for (int i = 0; i < this->size; ++i) {
                if(this->table[i]!=NULL){
                    hashTableEntry *entry = this->table[i];
                    std::cout << "( i : "<<i ;
                    while (entry!=NULL) {
                        std::cout<< " -> " << entry->value;
                        entry = entry->next;
                    }
                    std::cout <<" ), ";
                }
            }
            std::cout<<std::endl<<std::endl;
        }

    public:
        HashTable() {
            this->table = NULL;
            this->used = 0;
            this->size = 0;
        }

        bool isEmpty() {
            return (table == NULL);
        }

        long int getSize() {
            return this->size;
        }

        void init(long int size) {
            this->size = size;
            this->used = 0;
            this->table = static_cast<hashTableEntry **>(calloc(this->size, sizeof(hashTableEntry *)));
            fillNull();
        }

        void init() {
            this->size = MINIMUM_TABLE_SIZE;
            this->used = 0;
            this->table = static_cast<hashTableEntry **>(calloc(this->size, sizeof(hashTableEntry *)));
            fillNull();
        }

        int freeTableDangrously() {
            this->size = 0;
            this->used = 0;
            free(this->table);
        }

//
//        void freeTableAndValues() {
//
//        }
//
        hashTableEntry *getPtrToIdx(long int idx) {
//            if(this->table!=NULL) printTable();
            if (this->size > idx) return this->table[idx];
            return NULL;
        }

        long int setPtrToIdx(long int idx, hashTableEntry *nodePtr) {
            this->table[idx] = nodePtr;
//            if(this->table!=NULL) printTable();
        }

        double getBalanceFactor() {
            if (isEmpty()) return -1;
            return (this->used / this->size);
        }

    };

    class HashMap {
    private:
        HashTable *ht[2];
//        long int rehashIdx;

        long int getHashedValue(long int key) {
            return key % (this->ht[0]->getSize());
        }

    public:

        HashMap() {
            this->ht[0] = new HashTable();
            this->ht[0]->init();
        }

        HashMap(long int size) {
            this->ht[0] = new HashTable();
            this->ht[0]->init(size);
        }

        void add(long int key, std::string value) {
            long int idx = getHashedValue(key);
            hashTableEntry *head = this->ht[0]->getPtrToIdx(getHashedValue(key));
            hashTableEntry *newEntry = static_cast<hashTableEntry *>(malloc(sizeof(hashTableEntry)));
            newEntry->key = key;
            newEntry->value = value;
            newEntry->next = head;
            this->ht[0]->setPtrToIdx(idx,newEntry);
        }


        std::string get(long int key) {
            long int idx = getHashedValue(key);
            hashTableEntry *entry = this->ht[0]->getPtrToIdx(idx);
            if(entry == NULL)
                return "";

            while (entry!=NULL) {
                if(entry->key == key) {
//                    std::cout<< "value passed : " << entry->key << std::endl;
                    return entry->value;
                }
                entry = entry->next;
            }

            return "";
        }

        void remove(long int key) {
            long int idx = getHashedValue(key);
            hashTableEntry *entry = this->ht[0]->getPtrToIdx(idx);
            if (entry == NULL) return;

            if(entry->key == key) {
                this->ht[0]->setPtrToIdx(idx , entry->next);
                entry->next = NULL;
                free(entry);
                return;
            }

            hashTableEntry *prevEntry = NULL;

            while (entry != NULL) {
//                std::cout<< "value passed : " << entry->key << std::endl;
                if (entry->key == key) {
                    if(prevEntry!=NULL)
                        prevEntry->next = entry->next;

                    entry->next = NULL;
                    free(entry);
                    return;
                }
                prevEntry = entry;
                entry = entry->next;
            }
        }
    };
}


#endif //UNTITLED1_HASHMAP_H