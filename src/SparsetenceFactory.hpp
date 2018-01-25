#ifndef _HAS_SPARSETENCEFACTORY_HPP
#define _HAS_SPARSETENCEFACTORY_HPP

#include "KeywordExtractor.hpp"
#include "Sparsetence.hpp"

class SparsetenceFactory : KeywordExtractor {
public:
        SparsetenceFactory();

        const vector<unsigned int> keywords;

        const Sparsetence         sparsify(const Sentence &sentence);
        const vector<Sparsetence> sparsify(const vector<Sentence> &sentences);

};

#undef _HAS_SPARSETENCEFACTORY_HPP
#endif
