#ifndef _HAS_SPARSETENCE_HPP
#define _HAS_SPARSETENCE_HPP

#include <vector>

#include "config.h"

/**
 * A Sparsetence is a compact representation of a Sentence.
 * It differs from a Sentence in that:
 *
 * 1. A numeric word identifier is used in place of the actual text of a word.
 *
 * 2. It may omit some words from the sentence which are deemed unimportant.
 *
 * Rather than computing the similarity between Sentences, it's much faster to
 * use Sparsetences instead, since comparing integers should be significantly
 * faster than comparing strings.
 */
class Sparsetence {
public:
        explicit Sparsetence(const std::vector<unsigned int> &kw_ids);

        /* Keyword IDs of the Sparsetence */
        std::vector<unsigned int> keywords;

        bool         has_kw(unsigned int kw) const;
        unsigned int length() const;
        double       similarity(const Sparsetence &other) const;
private:
        unsigned int shared_keywords(const Sparsetence &other) const;
};

#undef _HAS_SPARSETENCE_HPP
#endif
