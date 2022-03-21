#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<unordered_map>
#include<vector>

#define INT_MIN -2147483648;

using namespace std;

class State {
public:
    // pointers to next state
    unordered_map<char, pair<State*, int> > nextStates;
    // pointers back to prev state | tagged by char
    unordered_map<char, vector<State*> > prevStates;

    char tag;
    int weight;
    
    State(char tag, int weight) : tag(tag), weight(weight) {
        nextStates = unordered_map<char, pair<State*, int> >();
    }
};

class StateMachine {
public:
    State* source;
    State* sink;

    StateMachine() {
        source = new State(' ', 0);
        sink = new State(' ', 0);
    }

    // TODO: should bind weight in the edges
    void add(string s, int w) {
        State* cur = source;
        vector<State*> curStates;
        curStates.push_back(cur);

        // create linked list of states for each character of added key.
        for (auto c: s) {
            if (cur->nextStates.find(c) != cur->nextStates.end()) {
                (cur->nextStates)[c].first->prevStates[cur->tag].push_back(cur);
                w -= (cur->nextStates)[c].second;
                cur = (cur->nextStates)[c].first;
                w -= cur->weight;
            } else {
                State* s = new State(c, w);
                cur->nextStates[c] = make_pair(s, 0);
                (cur->nextStates)[c].first->prevStates[cur->tag].push_back(cur);
                w -= (cur->nextStates)[c].second;
                cur = (cur->nextStates)[c].first;
                w -= cur->weight;
            }
            curStates.push_back(cur);
        }
        cur->nextStates[' '] = make_pair(sink, 0);
        if (cur != source) sink->prevStates[cur->tag].push_back(cur);
        
        State* p = sink;
        // compare suffix and try to combine redundant states
        for (int i = curStates.size() - 1; i >= 0; i--) {
            bool combined = false;
            for (auto s: p->prevStates[curStates[i]->tag]) {
                if (s == curStates[i]) continue;
                if (s->nextStates.size() != curStates[i]->nextStates.size()) continue;

                bool flag = true;
                
                // We can combine two states if they are duplicated.
                // Which means all of both states' next states are strictly equal.
                for (auto p: s->nextStates) {
                    if (curStates[i]->nextStates[p.first] != s->nextStates[p.first]) {
                        flag = false;
                        break;
                    }
                }
                 
                // Ff there is common suffix; we should combine the vertex. It works just like zipper.
                /**
                 * From:
                 * y -> o -> x -> SINK 
                 * z -> o -> x -> SINK 
                 * 
                 * To:
                 * y -> o -> x -> SINK
                 *   /
                 * z
                 */
                // TODO: should deal with the memory leak problem here.
                if (flag) {
                    curStates[i-1]->nextStates[s->tag] = make_pair(s, curStates[i]->weight - s->weight);
                    s->prevStates[curStates[i-1]->tag].push_back(curStates[i-1]);
                    p->prevStates[s->tag].pop_back();
                    p = s;
                    combined = true;
                    break;
                }
            }
            if (!combined) break;
        }
    }

    int get(string key) {
        State* p = source;
        int w = 0;
        for (auto c: key) {
            if (p->nextStates.find(c) == p->nextStates.end()) return INT_MIN;
            w += p->nextStates[c].second;
            p = p->nextStates[c].first;
            w += p->weight;
        }

        return w;
    }

    void print(State* begin, vector<State*>& path) {
        if (begin == sink) {
            for (auto s: path) {
                cout << s->tag << "(" << s << ") -> ";
            }
            cout << endl;
            return;
        }
        for (auto s: begin->nextStates) {
            path.push_back(s.second.first);
            print(s.second.first, path);
            path.pop_back();
        }
    }
};

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