#ifndef _HAS_KEYWORDEXTRACTOR_HPP
#define _HAS_KEYWORDEXTRACTOR_HPP

#include <map>
#include <string>
#include <unordered_map>

#include "Sentence.hpp"

class KeywordExtractor {
public:
        KeywordExtractor();

        void                       consume(Sentence &s);
        void                       consume(string &word);
        unsigned int               lookup_id(const string &word);
        const string               lookup_word(unsigned int id);
        const vector<unsigned int> keyword_ids(unsigned int howmany);
        const vector<string>       keywords(unsigned int howmany);
        unsigned int               unique_words();

private:
        unordered_map<unsigned int, unsigned int> counts;
        unsigned int                              next_index;
        unordered_map<string, unsigned int>       string_table;
        unordered_map<unsigned int, string>       inverse_table;

        bool         is_ignorable_id(unsigned int id);
        unsigned int lookup_or_add_word(const string &word);

        static bool is_ignorable_word(const string &word);

};


#undef _HAS_KEYWORDEXTRACTOR_HPP
#endif
