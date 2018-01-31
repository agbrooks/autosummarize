#include <algorithm>
#include <cmath>
#include <memory>
#include <set>
#include <string>

#include "KeywordExtractor.hpp"

KeywordExtractor::KeywordExtractor(double pct_keywords)
        : pct_keywords(pct_keywords)
{
        next_index  = 0;
        words_added = true;
}

void
KeywordExtractor::consume(const Sentence &s)
{
        for (auto &word : s.words)
        {
                consume(word);
        }
}

void
KeywordExtractor::consume(const string &word)
{
        unsigned int id = lookup_or_add_word(word);

        /* If the word isn't present, add it to the count map. */
        if (!counts.count(id))
        {
                counts[id] = 1;
        } else {
                counts[id]++;
        }

        words_added = true;
}

unsigned int
KeywordExtractor::lookup_id(const string &word)
{
        return string_table[word];
}

const string
KeywordExtractor::lookup_word(unsigned int id)
{
        return inverse_table[id];
}

const vector<unsigned int>
KeywordExtractor::keyword_ids()
{
        if (words_added)
        {
                recompute_keywords();
        }
        return keyword_id_list;
}

const vector<string>
KeywordExtractor::keywords()
{
        if (words_added)
        {
                recompute_keywords();
        }
        return keyword_list;
}

bool
KeywordExtractor::is_keyword(const string &word)
{
        const vector<string> kws = keywords();
        return std::find(kws.begin(), kws.end(), word) != kws.end();
}

bool
KeywordExtractor::is_keyword_id(unsigned int id)
{
        const vector<unsigned int> ids = keyword_ids();
        return std::find(ids.begin(), ids.end(), id) != ids.end();
}

unsigned int
KeywordExtractor::unique_words()
{
        return next_index;
}

/* Private methods */

bool
KeywordExtractor::is_ignorable_id(unsigned int id)
{
        return is_ignorable_word(inverse_table[id]);
}

unsigned int
KeywordExtractor::lookup_or_add_word(const string &word)
{
        if (!string_table.count(word))
        {
                string_table[word] = next_index;
                inverse_table[next_index] = word;
                next_index++;
        }
        return string_table[word];
}

bool
KeywordExtractor::is_ignorable_word(const string &word)
{
        /*
         * Several words may appear in significant numbers, but will not
         * actually be keywords that we're concerned with. For this reason,
         * we make a blacklist of 'faux amis' ('false friends') to prevent
         * common English words from being erroneously recognized as keywords.
         */
        static const set<string> faux_amis
        {
                "a",         /* articles */
                "an",
                "the",
                "and",       /* conjunctions */
                "but",
                "for",
                "nor",
                "or",
                "so",
                "yet",
                "i",         /* pronouns */
                "me",
                "you",
                "he",
                "him",
                "she",
                "her"
                "they",
                "we",
                "us",
                "that",
                "these",
                "those",
                "some",
                "although",  /* miscellania */
                "despite",
                "however",
                "such"
        };
        /* If the word is in the set, it should be ignored. */
        return faux_amis.count(word) > 0;
}

void
KeywordExtractor::recompute_keywords()
{
        using Count = unsigned int;
        using IdVec = vector<unsigned int>;
        using Id    = unsigned int;

        unsigned int num_keywords = std::floor(unique_words() * pct_keywords);

        /* Reset any keyword-related lists. */
        keyword_id_list.clear();
        keyword_list.clear();

        /* 'Inverse' of count map. */
        unique_ptr<map<Count, IdVec>> inv_counts;

        /* Populate inv_counts with inverse of counts. */
        for (pair<const Id, Count> p : counts)
        {
                unsigned int id        = p.first;
                unsigned int frequency = p.second;

                if (!inv_counts->count(p.second))
                {
                        vector<Id> singleton{id};
                        inv_counts->emplace(frequency, singleton);
                } else {
                        inv_counts->at(frequency).push_back(id);
                }
        }

        /*
         * Generate the keyword ID list by selecting the most frequent keyword
         * ids from the inverse frequency map.
         */
        for (auto rit = inv_counts->rbegin(); rit != inv_counts->rend(); ++rit)
        {
                for (Id i : rit->second)
                {
                        if (keyword_id_list.size() < num_keywords
                            && !is_ignorable_id(i))
                        {
                                keyword_id_list.push_back(i);
                        }
                }
        }

        /*
         * Regenerate the keyword list too.
         */
        for (auto kw_id : keyword_id_list)
        {
                keyword_list.push_back(lookup_word(kw_id));
        }

        /* No new words added since last keyword recompute. */
        words_added = false;
}
