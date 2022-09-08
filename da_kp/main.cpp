#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <sstream>
#include <iterator>
#include <unordered_map>
#include <unordered_set>

struct document {
    std::vector<std::string> text_vec;
    int class_n;
};

struct category {
    std::unordered_map<std::string, long double> cond_prob;
    std::unordered_map<std::string, size_t> word_count;
    long double prob_word_not_found;
    long double prior_prob;
    size_t total_words = 0;
    size_t total_docs = 0;
};

class NaiveBayesClassifier {
public:
    NaiveBayesClassifier()= default;;
    void Train(size_t train_docs_number);
    int Test(const std::vector<std::string>& test_doc);
private:
    std::vector<document> train_docs;
    std::unordered_map<int, category> categories;
};

std::vector<std::string> Parse(std::string& text);
void NaiveBayesClassifier::Train(const size_t train_docs_number) {
    for (size_t i = 0; i < train_docs_number; i++) {
        document doc;
        std::string input_text;
        std::cin >> doc.class_n;
        std::cin.ignore();
        std::getline(std::cin, input_text);
        doc.text_vec = Parse(input_text);
        train_docs.push_back(doc);
        categories[doc.class_n].total_docs++;
        categories[doc.class_n].total_words += doc.text_vec.size();
        for (const auto& word : doc.text_vec) {
            categories[doc.class_n].word_count[word]++;
        }
    }

    std::unordered_set<std::string> unique_words;
    for (int i = 0; i <= 1; i++) {
        for (auto & iter : categories[i].word_count) {
            unique_words.insert(iter.first);
        }
    }
    size_t unique_words_number = unique_words.size();

    for (int i = 0; i <= 1; i++) {
        categories[i].prior_prob = (long double)categories[i].total_docs / train_docs_number;
        categories[i].prob_word_not_found = 1.0 / 
               (long double)(categories[i].total_words + unique_words_number);
    }

    for (const auto & unique_word : unique_words) {
        for (auto i = 0; i <= 1; i++) {
            auto iter = categories[i].word_count.find(unique_word);
            if (iter == categories[i].word_count.end()) {
                categories[i].cond_prob[unique_word] = categories[i].prob_word_not_found;
            } else {
                categories[i].cond_prob[unique_word] =
                                 (long double)(1.0 + categories[i].word_count[unique_word])
                                 / (categories[i].total_words + unique_words_number);
            }
        }
    }
}

int NaiveBayesClassifier::Test(const std::vector<std::string>& test_doc) {
    long double predicted_prob_for_class[2];
    for (int i = 0; i <= 1; i++) {
        predicted_prob_for_class[i] = std::log(categories[i].prior_prob);
        for (auto word : test_doc) {
            auto iter = categories[i].cond_prob.find(word);
            if (iter == categories[i].cond_prob.end()) {
                predicted_prob_for_class[i] += std::log(categories[i].prob_word_not_found);
            } else {
                predicted_prob_for_class[i] += std::log(categories[i].cond_prob[word]);
            }
        }
    }
    if (predicted_prob_for_class[0] >= predicted_prob_for_class[1]) {
        return 0;
    } else {
        return 1;
    }
}
 
std::vector<std::string> Parse(std::string& text) {
    for (char & i : text) {
        if (std::isupper(i)) {
            i = std::tolower(i);
        } else if (std::ispunct(i) && i != '\'') {
            i = ' ';
        }
    }
    std::istringstream ss{text};
    using string_iteratir = std::istream_iterator<std::string>;
    std::vector<std::string> container{string_iteratir{ss}, string_iteratir{}};
    return container;
}
 
int main() {
    size_t train_docs_number, test_docs_number;
    std::cin >> train_docs_number;
    std::cin >> test_docs_number;
    NaiveBayesClassifier nbc;
    nbc.Train(train_docs_number);
    std::vector<std::string> test_doc;
    std::string input_text;
    for (size_t i = 0; i < test_docs_number; i++) {
        if (!std::getline(std::cin, input_text)) {
            return 0;
        }
        test_doc = Parse(input_text);
        std::cout << nbc.Test(test_doc) << std::endl;
    }

    return 0;
}
