#include <algorithm>

#include "SparsetenceFactory.hpp"

SparsetenceFactory::SparsetenceFactory(double pct_keywords)
        : KeywordExtractor(pct_keywords)
{ }

/**
 * From a `Sentence`, construct a `Sparsetence`.
 *
 * This function assumes that this `Sentence`, and all others that way include
 * related keywords, have already been `consume`d by the `KeywordExtractor`.
 */
const Sparsetence
SparsetenceFactory::sparsify(const Sentence &sentence)
{
        /* Extract keyword IDs from the sentence. */
        vector<unsigned int> word_ids;
        for (auto word : sentence.words)
        {
                const unsigned int keyword_id = lookup_id(word);
                if (is_keyword_id(keyword_id))
                {
                        word_ids.push_back(keyword_id);
                }
        }

        return Sparsetence(word_ids);
}

/**
 * From a vector of `Sentences`, construct several `Sparsetence`s.
 *
 * This function assumes that all `Sentences` of interest have already been
 * `consume`d by the underlying `KeywordExtractor`.
 */
const vector<Sparsetence>
SparsetenceFactory::sparsify(const vector<Sentence> &sentences)
{
        vector<Sparsetence> sparsetences;
        for (Sentence s : sentences)
        {
                sparsetences.push_back(sparsify(s));
        }
        return sparsetences;
}
