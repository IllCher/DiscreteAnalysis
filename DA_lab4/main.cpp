#include <iostream>
#include <map>
#include <string>
#include <sstream>
#include <queue>
#include <memory>
typedef unsigned long long ull;
struct TNode{
    TNode() = default;
    ull symb = 0;
    int level = 0;
    int id = 0;
    bool flag = false;
    std::weak_ptr<TNode> parent;
    std::weak_ptr<TNode>  suffLink;
    std::weak_ptr<TNode>  up;
    std::map<ull, std::shared_ptr<TNode>> links;
};

class TTrie{
public:
    TTrie() = default;
    std::shared_ptr<TNode> root = std::make_shared<TNode>();
    void MakeStep(std::shared_ptr<TNode>& n, ull& symb) {
        n->links[symb] =  std::make_shared<TNode>();
        n->links[symb]->parent = n;
        n->links[symb]->level = n->level + 1;
        n->links[symb]->symb = symb;
    }
    void AddString(std::vector<ull>& word){
        static int counter = 0;
        std::shared_ptr<TNode> curr = root;
        ull symb;
        for (ull i : word) {
            symb = i;
            if (curr->links.count(symb) == 0) {
                MakeStep(curr, symb);
            }
            curr = curr->links[symb];
        }
        counter++;
        curr->id = counter;
        curr->flag = true;
    }
    void GetSuffLink(std::shared_ptr<TNode>& n){
        if(n == root || n->parent.lock() == root) {
            n->suffLink = root;
        } else {
            std::shared_ptr<TNode> p(n->parent.lock()->suffLink);
            while (p != root && p->links.count(n->symb) == 0) {
                p = p->suffLink.lock();
            }
            if (p->links.count(n->symb) == 0) {
                n->suffLink = root;
            } else {
                n->suffLink = p->links[n->symb];
            }
        }
    }
    void GetUp(std::shared_ptr<TNode>& n) {
        if (n == root || n->parent.lock() == root) {
            n->up.lock() = nullptr;
        } else if (n->suffLink.lock()->flag) {
            n->up = n->suffLink;
        } else {
            n->up = n->suffLink.lock()->up;
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
    std::stringstream textss;
    std::string s;
    while(std::getline(std::cin,s)){
        lineCnt++;
        textss.clear();
        textss << s;
        wordCnt = 0;
        while(textss >> symb) {
            wordCnt++;
            state = trie.Step(state, symb);
            if(state->flag) {
                int line = lineCnt;
                int pos = state->level - wordCnt;
                while (pos > 0) {
                    line--;
                    pos -= lengths[line - 1];
                }
                std::cout << line << ", " << abs(pos) + 1 << ", " << state->id << "\n";
            }
            if(state->up.lock()){
                std::shared_ptr<TNode> up = state->up.lock();
                while(up){
                    int line = lineCnt;
                    int pos = up->level - wordCnt;
                    while (pos > 0) {
                        line--;
                        pos -= lengths[line - 1];
                    }
                    std::cout << line << ", " << abs(pos) + 1 << ", " << up->id << "\n";
                    up = up->up.lock();
                }
            }

        }
        lengths.push_back(wordCnt);
    }
    return 0;
}