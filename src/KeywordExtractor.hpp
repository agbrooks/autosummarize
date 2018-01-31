#ifndef _HAS_KEYWORDEXTRACTOR_HPP
#define _HAS_KEYWORDEXTRACTOR_HPP

#include <map>
#include <string>
#include <unordered_map>

#include "Sentence.hpp"

class KeywordExtractor {
public:
        explicit KeywordExtractor(double pct_keywords);

        unsigned int               pct_keywords;

        void                       consume(const Sentence &s);
        void                       consume(const string &word);
        unsigned int               lookup_id(const string &word);
        const string               lookup_word(unsigned int id);
        const vector<unsigned int> keyword_ids();
        const vector<string>       keywords();
        bool                       is_keyword(const string &word);
        bool                       is_keyword_id(unsigned int id);
        unsigned int               unique_words();

private:
        unordered_map<unsigned int, unsigned int> counts;
        unsigned int                              next_index;
        unordered_map<string, unsigned int>       string_table;
        unordered_map<unsigned int, string>       inverse_table;

        vector<string>                            keyword_list;
        vector<unsigned int>                      keyword_id_list;
        bool                                      words_added;

        void         recompute_keywords(void);
        bool         is_ignorable_id(unsigned int id);
        static bool  is_ignorable_word(const string &word);

        unsigned int lookup_or_add_word(const string &word);

};


#undef _HAS_KEYWORDEXTRACTOR_HPP
#endif
