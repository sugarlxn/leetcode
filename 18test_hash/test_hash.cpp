#include <iostream>
#include <hash_set>
#include <hash_map>
#include <unordered_map>
// hashtable decleared in this header file, c style  
#include <hashtable.h>

using namespace std;


int main(int argc, char * argv[]){

    cout<< "hello hash_set!" << endl;
    //BUG: hashtable is not decleared in this scope
    //hashtable<int,int,hash<int>,identity<int>,equal_to<int>,alloc> iht(50,hash<int>(),equal_to<int>());

    //#FIXME reference to  hashtable.h 
    _Hashtable<int,int,hash<int>,identity<int>,equal_to<int>,alloc> iht(50,hash<int>(),equal_to<int>());

    return 0;
}