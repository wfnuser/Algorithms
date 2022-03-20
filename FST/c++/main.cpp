#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<unordered_map>
#include<vector>

using namespace std;

class State {
public:
    // pointers to next state
    unordered_map<char, State*> nextStates;
    // pointers back to prev state | tagged by char
    unordered_map<char, vector<State*> > prevStates;

    char tag;
    int weight;
    
    State(char tag) {
        nextStates = unordered_map<char, State*>();
        this->tag = tag;
    }
};

class StateMachine {
public:
    State* source;
    State* sink;

    StateMachine() {
        source = new State(' ');
        sink = new State(' ');
    }

    // TODO: should bind weight in the edges
    void add(string s) {
        State* cur = source;
        vector<State*> curStates;
        curStates.push_back(cur);

        // create linked list of states for each character of added key.
        for (auto c: s) {
            if (cur->nextStates.find(c) != cur->nextStates.end()) {
                (cur->nextStates)[c]->prevStates[cur->tag].push_back(cur);
                cur = (cur->nextStates)[c];
            } else {
                cur->nextStates[c] = new State(c);
                (cur->nextStates)[c]->prevStates[cur->tag].push_back(cur);
                cur = (cur->nextStates)[c];
            }
            curStates.push_back(cur);
        }
        cur->nextStates[' '] = sink;
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
                // Which means all of both states' next states are the strictly equal.
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
                    curStates[i-1]->nextStates[s->tag] = s;
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

    bool get(string key) {
        State* p = source;

        for (auto c: key) {
            if (p->nextStates.find(c) == p->nextStates.end()) return false;
            p = p->nextStates[c];
        }

        return true;
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
            path.push_back(s.second);
            print(s.second, path);
            path.pop_back();
        }
    }
};

int main() {

    auto SM = StateMachine();
    
    SM.add("mox");
    SM.add("moxr");
    SM.add("yox");
    SM.add("yoxr");
    SM.add("zox");
    SM.add("uox");
    vector<State*> v = vector<State*>();
    SM.print(SM.source, v);
    
    cout << SM.get("mox") << endl;
    cout << SM.get("ypx") << endl;
    cout << SM.get("yz") << endl;
    cout << SM.get("zx") << endl;

    return 0;
}