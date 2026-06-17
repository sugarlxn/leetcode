#include <iostream>
#include <hash_set>
#include <hash_map>
#include <unordered_map>
// // hashtable decleared in this header file, c style  
// #include <hashtable.h>

using namespace std;


//the implement of hash table 
template<typename K, typename V>
struct Node{
    std::pair<const K, V> kv;
    Node* next;
    size_t cached_hash;
    Node(const K& key, const V& value, size_t hash): kv(key, value), cached_hash(hash), next(nullptr) {}
};

//NOTE: HashTable 
template<typename K, typename V>
struct HashTable{
    std::vector<Node<const K, V>*> buckets;
    size_t bucket_count;
    size_t size;

};

int main(int argc, char * argv[]){

    // //BUG: hashtable is not decleared in this scope
    // //hashtable<int,int,hash<int>,identity<int>,equal_to<int>,alloc> iht(50,hash<int>(),equal_to<int>());

    // //#FIXME reference to  hashtable.h 
    // _Hashtable<int,int,hash<int>,identity<int>,equal_to<int>,alloc> iht(50,hash<int>(),equal_to<int>());

    cout<< "hello hash_set!" << endl;

    return 0;
}