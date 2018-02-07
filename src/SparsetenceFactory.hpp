#ifndef _HAS_SPARSETENCEFACTORY_HPP
#define _HAS_SPARSETENCEFACTORY_HPP

#include "KeywordExtractor.hpp"
#include "Sparsetence.hpp"

#include "config.h"


/**
 * A `SparsetenceFactory` constructs `Sparsetence`s using keywords extracted
 * by the `KeywordExtractor` that it inherits from.
 *
 * Because keyword extraction must be performed first, sentences should be
 * `consume`d prior to attempting the construction of any `Sparsetence`s.
 */
class SparsetenceFactory : public KeywordExtractor {
public:
        explicit SparsetenceFactory(double pct_keywords);

        const Sparsetence         sparsify(const Sentence &sentence);
        const vector<Sparsetence> sparsify(const vector<Sentence> &sentences);

};

#undef _HAS_SPARSETENCEFACTORY_HPP
#endif
