#ifndef _HAS_SENTENCE_HPP
#define _HAS_SENTENCE_HPP

#include <string>
#include <vector>

using namespace std;

class Sentence {
public:
        explicit Sentence(const string &text);

        const string &text;
        vector<string> words;

private:
        void extract_words(const string &text);
        const string normalize_word(string &str);

};

#undef _HAS_SENTENCE_HPP
#endif
