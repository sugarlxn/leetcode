#include <iostream>
#include "nlohmann/json.hpp"

using json = nlohmann::json;
using namespace std;

int main(int argc, char * argv[]){

    cout << "Hello json! (｡･∀･)ﾉﾞ嗨!" << endl;

    json myjob = {
        {"name", "John"},
        {"age", 22},
        {"string", "Hello, json! (｡･∀･)ﾉﾞ嗨!"}
    };

    cout << myjob << endl;

    cout << myjob["name"] << endl;
    cout << myjob["age"] << endl;
    cout << myjob["string"] << endl;

    json j;
    j.push_back("foo");
    cout << j << endl;
    
    
    return 0;
}