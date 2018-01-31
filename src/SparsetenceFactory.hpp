#ifndef _HAS_SPARSETENCEFACTORY_HPP
#define _HAS_SPARSETENCEFACTORY_HPP

#include "KeywordExtractor.hpp"
#include "Sparsetence.hpp"

class SparsetenceFactory : public KeywordExtractor {
public:
        explicit SparsetenceFactory(unsigned int num_keywords);

        vector<unsigned int> keyword_ids;

        const Sparsetence         sparsify(const Sentence &sentence);
        const vector<Sparsetence> sparsify(const vector<Sentence> &sentences);

};

#undef _HAS_SPARSETENCEFACTORY_HPP
#endif
