#ifndef _HAS_SPARSETENCE_HPP
#define _HAS_SPARSETENCE_HPP

#include <vector>

#include "config.h"

class Sparsetence {
public:
        explicit Sparsetence(const std::vector<unsigned int> &kw_ids);

        std::vector<unsigned int> keywords;

        bool         has_kw(unsigned int kw) const;
        unsigned int length() const;
        double       similarity(const Sparsetence &other) const;
private:
        unsigned int shared_keywords(const Sparsetence &other) const;
};

#undef _HAS_SPARSETENCE_HPP
#endif
