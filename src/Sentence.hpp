#ifndef _HAS_SENTENCE_HPP
#define _HAS_SENTENCE_HPP

#include <string>
#include <vector>

#include "config.h"

using namespace std;

/**
 * A Sentence associates a sentence text with its normalized constituent words.
 */
class Sentence {
public:
        explicit Sentence(const string &text);

        const string text;
        vector<string> words;

        static const vector<Sentence> to_sentences(const string &text);

private:
        void extract_words();
        static const string normalize_word(const string &str);

};

#undef _HAS_SENTENCE_HPP
#endif
