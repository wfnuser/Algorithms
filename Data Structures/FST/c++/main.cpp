#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<vector>

#include "fst.h"

using namespace std;

int main() {
    auto SM = StateMachine();
    
    SM.add("mox", 10);
    SM.add("moxr", 5);
    SM.add("yox", 2);
    SM.add("yoxr", 8);
    SM.add("zox", 6);
    SM.add("uox", 1);
    vector<State*> v = vector<State*>();
    SM.print(SM.source, v);
    
    cout << SM.get("mox") << endl;
    cout << SM.get("moxr") << endl;
    cout << SM.get("yox") << endl;
    cout << SM.get("yoxr") << endl;

    return 0;
}