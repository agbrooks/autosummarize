#include <memory>
#include <set>
#include <string>

#include "KeywordExtractor.hpp"

KeywordExtractor::KeywordExtractor()
{
        next_index = 0;
}

void
KeywordExtractor::consume(Sentence &s)
{
        for (string &word : s.words)
        {
                consume(word);
        }
}

void
KeywordExtractor::consume(string &word)
{
        unsigned int id = lookup_or_add_word(word);

        /* If the word isn't present, add it to the count map. */
        if (!counts.count(id))
        {
                counts[id] = 1;
        } else {
                counts[id]++;
        }
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
KeywordExtractor::keyword_ids(unsigned int howmany)
{
        using Count = unsigned int;
        using IdVec = vector<unsigned int>;
        using Id    = unsigned int;

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

        /* Now, select the top 'howmany' keyword ids from the inverse freq map. */
        vector<Id> ids;
        for (auto rit = inv_counts->rbegin(); rit != inv_counts->rend(); ++rit)
        {
                for (Id i : rit->second)
                {
                        if (ids.size() < howmany && !is_ignorable_id(i))
                        {
                                ids.push_back(i);
                        }
                }
        }
        return ids;
}

const vector<string>
KeywordExtractor::keywords(unsigned int howmany)
{
        const vector<unsigned int> ids = keyword_ids(howmany);
        vector<string> kw_strings;
        for (unsigned int id : ids)
        {
                kw_strings.push_back(lookup_word(id));
        }
        return kw_strings;
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
