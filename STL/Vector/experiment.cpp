#include<iostream>
#include<cstdio>
#include<vector>

using namespace std;

int main() {

    vector<int> v;

    for (int i = 0; i < 20; i++) {
        cout << "size: " << v.size() << " capacity " << v.capacity() << endl;
        v.push_back(i);
    }

    return 0;
}