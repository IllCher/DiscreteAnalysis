#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <chrono>
typedef unsigned long long ull;

class TSuffixArray;

class TNode {
public:
    std::map<char, TNode*> links;
    std::string::iterator begin, end;
    TNode* suffLink;
    TNode(std::string::iterator begin, std::string::iterator end);
};

class TSuffixTree {
public:
    TSuffixTree(std::string str);
    friend TSuffixArray;

private:
    std::string text;
    TNode* root;
    int remainder;
    TNode* tmpSuffLink;
    TNode* curNode;
    int curLength;
    std::string::iterator curEdge;
    int EdgeLength(TNode* node, std::string::iterator pos);
    void TreeDestroy(TNode* node);
    bool WalkDown(std::string::iterator curPos, TNode* node);
    void SuffLinkAdd(TNode* node);
    void TreeExtend(std::string::iterator add);
    void DFS(TNode* node, std::vector<int> &result, int deepness);
};

class TSuffixArray {
public:
    TSuffixArray(TSuffixTree tree);
    std::vector<int> Find(const std::string& pattern);
    int CompareStrings(int index, const std::string &pattern);
private:
    std::string text;
    std::vector<int> array;
};

TSuffixTree::TSuffixTree(std::string str):text(str),root(new TNode(text.end(), text.end())), remainder(0) {
    curEdge = text.begin();
    curNode = tmpSuffLink;
    curNode = root->suffLink;
    curNode = root;
    curLength = 0;
    for (std::string::iterator it = text.begin(); it != text.end(); it++) {
        TreeExtend(it);
    }
}

TNode::TNode(std::string::iterator begin, std::string::iterator end) : begin(begin), end(end), suffLink(nullptr){}


void TSuffixTree::TreeDestroy(TNode* node) {
    for (std::map<char, TNode* >::iterator it = node->links.begin(); it != node->links.end(); it++) {
        TreeDestroy(it->second);
    }
    delete node;
}

void TSuffixTree::TreeExtend(std::string::iterator add) {
    tmpSuffLink = root;
    remainder++;
    while (remainder) {
        if (!curLength) {
            curEdge = add;
        }
        std::map<char, TNode* >::iterator it = curNode->links.find(*curEdge);
        TNode* next = (it == curNode->links.end()) ? nullptr : it->second;
        if (next == nullptr) {
            TNode* leaf = new TNode(add, text.end());
            curNode->links[*curEdge] = leaf;
            SuffLinkAdd(curNode);
        } else {
            if (WalkDown(add, next)) {
                continue;
            }
            if (*(next->begin + curLength) == *add) {
                curLength++;
                SuffLinkAdd(curNode);
                break;
            }
            TNode* split = new TNode(next->begin, next->begin + curLength);
            TNode* leaf = new TNode(add, text.end());
            curNode->links[*curEdge] = split;
            split->links[*add] = leaf;
            next->begin += curLength;
            split->links[*next->begin] = next;
            SuffLinkAdd(split);
        }
        remainder--;
        if (curNode == root && curLength) {
            curLength--;
            curEdge = add - remainder + 1;
        } else {
            curNode = (curNode->suffLink) ? curNode->suffLink : root;
        }
    }
}

int TSuffixTree::EdgeLength(TNode* node, std::string::iterator pos) {
    return min(node->end, pos + 1) - node->begin;
}

bool TSuffixTree::WalkDown(std::string::iterator cur_pos, TNode* node) {
    if (curLength >= EdgeLength(node, cur_pos)) {
        curEdge += EdgeLength(node, cur_pos);
        curLength -= EdgeLength(node, cur_pos);
        curNode = node;
        return true;
    }
    return false;
}

void TSuffixTree::SuffLinkAdd(TNode* node) {
    if (tmpSuffLink != root) {
        tmpSuffLink->suffLink = node;
    }
    tmpSuffLink = node;
}

void TSuffixTree::DFS(TNode* node, std::vector<int> &result, int deepness) {
    if (node->links.empty()) {
        result.push_back(text.size() - deepness);
        return;
    }
    for (std::map<char, TNode* >::iterator it = node->links.begin(); it != node->links.end(); it++) {
        int tmp = deepness;
        tmp += it->second->end - it->second->begin;
        DFS(it->second, result, tmp);
    }
}

TSuffixArray::TSuffixArray(TSuffixTree tree):text(tree.text), array() {
    tree.DFS(tree.root, array, 0);
    tree.TreeDestroy(tree.root);
}

int TSuffixArray::CompareStrings(int index, const std::string &pattern) {
    int minimumSize;
    if (text.size() - index < pattern.size()) {
        minimumSize = text.size();
    } else {
        minimumSize = pattern.size();
    }
    for (int i = 0; i < minimumSize; i++) {
        if (text[index] != pattern[i]) {
            if (text[index] < pattern[i]) {
                return 1;
            } else {
                return -1;
            }
        }
        ++index;
    }
    if (pattern.size() <= minimumSize) {
        return 0;
    }
    return 1;
}


std::vector<int> TSuffixArray::Find(const std::string& pattern) {
    std::vector<int> answer;
    int left = 0, right = array.size() - 1, mid;
    while (left <= right) {
        mid = (left + right) / 2;
        int result = CompareStrings(array[mid], pattern);
        if (result == 1) {
            left = mid + 1;
        } else if (result == -1) {
            right = mid - 1;
        }
        if (result == 0) {
            int leftBound = mid;
            while (leftBound > 0 && CompareStrings(array[leftBound - 1],pattern) == 0) {
                leftBound--;
            }
            int rightBound = mid;
            while (rightBound < array.size() - 1 && CompareStrings(array[rightBound + 1],pattern) == 0 ) {
                rightBound++;
            }
            if (rightBound == leftBound) {
                answer.push_back(array[leftBound]);
            } else {
                for (int i = leftBound; i <= rightBound; ++ i) {
                    answer.push_back(array[i]);
                }
            }
            break;
        }
    }
    std::sort(answer.begin(), answer.end());
    return answer;
}

int main() {
    std::string text, pattern;
    std::cin >> text;
    std::chrono::time_point<std::chrono::system_clock> start, end;
    start = std::chrono::system_clock::now();
    TSuffixTree tree(text + "$");
    TSuffixArray array(tree);
    //int i = 1;
    for (int i = 0; i < 1000000; i++) {
        //while (std::cin >> pattern) {
        std::vector<int> answer = array.Find(pattern);
        /*if (!answer.empty()) {
            std::cout << i << ": ";
            for (int j = 0; j < answer.size(); j++) {
                std::cout << answer[j] + 1;
                if (j < answer.size() - 1) {
                    std::cout << ", ";
                }
            }
            std::cout << "\n";
        }*/
    }
    end = std::chrono::system_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(end-start).count() << "\n";
        //i++;

    //}

    return 0;


}
