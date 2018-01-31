#include <algorithm>

#include "SparsetenceFactory.hpp"

SparsetenceFactory::SparsetenceFactory(unsigned int num_keywords)
        : KeywordExtractor(num_keywords)
{ }

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
