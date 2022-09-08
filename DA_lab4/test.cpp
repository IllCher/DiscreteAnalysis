#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <queue>
#include <memory>
#include <chrono>
typedef unsigned long long ull;
struct TNode{
    TNode() = default;
    ull symb = 0;
    int level = 0;
    int id = 0;
    bool terminate = false;
    std::weak_ptr<TNode> parent;
    std::weak_ptr<TNode>  suffLink;
    std::weak_ptr<TNode>  up;
    std::map<ull, std::shared_ptr<TNode>> links;
};

class TTrie{
public:
    TTrie() = default;
    std::shared_ptr<TNode> root = std::make_shared<TNode>();
    void MakeStep(std::shared_ptr<TNode>& v, ull& symb) {
        v->links[symb] =  std::make_shared<TNode>();
        v->links[symb]->parent = v;
        v->links[symb]->level = v->level + 1;
        v->links[symb]->symb = symb;
    }
    void AddString(std::vector<ull>& word){
        static int counter = 0;
        std::shared_ptr<TNode> curr = root;
        ull symb;
        for (ull i : word) {
            symb = i;
            if(curr->links.count(symb) == 0) {
                MakeStep(curr, symb);
            }
            curr = curr->links[symb];
        }
        counter++;
        curr->id = counter;
        curr->terminate = true;
    }
    void GetSuffLink(std::shared_ptr<TNode>& v){
        if(v == root || v->parent.lock() == root) {
            v->suffLink = root;
        } else {
            std::shared_ptr<TNode> p(v->parent.lock()->suffLink);
            while (p != root && p->links.count(v->symb) == 0) {
                p = p->suffLink.lock();
            }
            if (p->links.count(v->symb) == 0) {
                v->suffLink = root;
            } else {
                v->suffLink = p->links[v->symb];
            }
        }
    }
    void GetUp(std::shared_ptr<TNode>& v) {
        if (v == root || v->parent.lock() == root) {
            v->up.lock() = nullptr;
        } else if (v->suffLink.lock()->terminate) {
            v->up = v->suffLink;
        } else {
            v->up = v->suffLink.lock()->up;
        }
    }
    std::shared_ptr<TNode>& Step(std::shared_ptr<TNode>& state, ull symb){
        if(state->links.count(symb) > 0) {
            return state->links[symb];
        } else {
            for (; state->links.count(symb) == 0 && state != root; state = state->suffLink.lock())
                ;
            if(state->links.count(symb) > 0) {
                return state->links[symb];
            } else {
                return root;
            }
        }
    }
};

void Init(TTrie& trie) {
    std::queue<std::shared_ptr<TNode>> q;
    q.push(trie.root);

    while(!q.empty()){
        std::shared_ptr<TNode> temp =  q.front();
        q.pop();
        trie.GetSuffLink(temp);
        trie.GetUp(temp);

        for(std::pair<const ull, std::shared_ptr<TNode>>& elem: temp->links){
            q.push(elem.second);
        }
    }
}

int main() {
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    TTrie trie;
    std::string input, token;
    while (std::getline(std::cin, input)) {
        if (input.empty()) {break;}
        std::stringstream patternSS(input);
        std::vector<ull> pattern;
        while (patternSS >> token) {
            pattern.push_back(stol(token));
        }
        trie.AddString(pattern);
    }
    Init(trie);

    std::shared_ptr<TNode> state = trie.root;
    int wordCnt,lineCnt = 0;
    ull symb;
    std::vector<int> lengths;
    std::stringstream ss;
    std::string s;
    while(std::getline(std::cin,s)){
        ++lineCnt;
        ss.clear();
        ss << s;
        wordCnt = 0;
        while(ss >> symb){
            ++wordCnt;
            state = trie.Step(state, symb);
            if(state->terminate) {
                int line = lineCnt;
                int pos = state->level - wordCnt;
                while (pos > 0) {
                    line--;
                    pos -= lengths[line - 1];
                }
            }
            if(state->up.lock()){
                std::shared_ptr<TNode> up = state->up.lock();
                while(up){
                    int line = lineCnt;
                    int pos = up->level - wordCnt;
                    while (pos > 0) {
                        --line;
                        pos -= lengths[line - 1];
                    }
                    up = up->up.lock();
                }
            }

        }
        lengths.push_back(wordCnt);
    }
    end = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << "\n";
    return 0;
}