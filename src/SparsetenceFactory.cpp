#include <algorithm>

#include "SparsetenceFactory.hpp"

SparsetenceFactory::SparsetenceFactory()
        : KeywordExtractor()
{ }

/* FIXME: Need a way to know how many keywords to use in sparsification. */

const Sparsetence
SparsetenceFactory::sparsify(const Sentence &sentence)
{
        vector<unsigned int> keywords_present;
        // turn sentence words -> word ids
        // filter word ids based on whether they're keywords
        // make sparsetence
        return Sparsetence(keywords_present);
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
