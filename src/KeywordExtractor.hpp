#ifndef _HAS_KEYWORDEXTRACTOR_HPP
#define _HAS_KEYWORDEXTRACTOR_HPP

#include <map>
#include <string>
#include <unordered_map>

#include "Sentence.hpp"

#include "config.h"

/**
 * The KeywordExtractor `consume`s sentences or words and attempts to determine
 * which are keywords. It relies on a combination of a 'blacklist' of 'ignorable'
 * words (eg, 'the' will probably never be a good keyword choice) and frequency
 * analysis.
 *
 */
class KeywordExtractor {
public:
        explicit KeywordExtractor(double pct_keywords);

        /* Percentage of words appearing suspected to be keywords */
        double                     pct_keywords;

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
        /* Count of numeric word id -> times seen */
        unordered_map<unsigned int, unsigned int> counts;
        /* Next numeric word id */
        unsigned int                              next_index;
        /* Mapping relating words to their numeric ids */
        unordered_map<string, unsigned int>       string_table;
        /* Mapping relating numeric ids to their words */
        unordered_map<unsigned int, string>       inverse_table;

        /* Keywords found */
        vector<string>                            keyword_list;
        /* Keyword IDs found */
        vector<unsigned int>                      keyword_id_list;
        /* Whether or not words have been added since we last found keywords */
        bool                                      words_added;

        void         recompute_keywords(void);
        bool         is_ignorable_id(unsigned int id);
        static bool  is_ignorable_word(const string &word);

        unsigned int lookup_or_add_word(const string &word);

};


#undef _HAS_KEYWORDEXTRACTOR_HPP
#endif
