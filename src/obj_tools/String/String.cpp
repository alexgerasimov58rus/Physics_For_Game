
#include "String.hpp"

using namespace obj_tools;
using namespace std;

vector<string> String::split(string s, char separator) {
    vector<string> vec;

    int i;

    while((i = s.find(separator)) != string::npos) {
        vec.push_back(s.substr(0, i));
        s = s.substr(i + 1);
    }

    vec.push_back(s);

    return vec;
}