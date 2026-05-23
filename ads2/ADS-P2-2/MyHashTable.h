#pragma once
#include <string>
#include <vector>

struct Account {
    std::string username;
    std::string passwordHash;
    std::string website;
};

class MyHashTable {
private:
    struct Entry {
        Account acc;
        bool occupied = false;
    };
    std::vector<Entry> table;
    int mNumElements;
    int mHashMethod;
    double mMaxLoadFactor = 0.6;
    int collisionCount = 0;

    unsigned int hash(const std::string& key) const;
    void rehash();
public:
    MyHashTable(int size = 8, int hashMethod = 1) : table(size), mNumElements(0), mHashMethod(hashMethod) {}
    void insert(const Account& acc);
    bool login(const std::string& website, const std::string& username, const std::string& passwordHash) const;
    void listEntries() const;
    //void SaveToFile(const std::string& filename) const;
    //void LoadFromFile(const std::string& filename);
	int getNextPrime(int x) const;
    int getLastPrime(int x) const;
    int getNumElements() { return mNumElements; }
    Entry at(int x) { return table.at(x); }
    int getSize() { return table.size(); }
    int getCollisionCount() { return collisionCount; }
};