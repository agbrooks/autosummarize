#ifndef _HAS_SPARSETENCE_HPP
#define _HAS_SPARSETENCE_HPP

#include <vector>

class Sparsetence {
public:
        explicit Sparsetence(const std::vector<unsigned int> &kw_ids);

        const std::vector<unsigned int> keywords;

        bool         has_kw(unsigned int kw);
        unsigned int length();
        double       similarity(Sparsetence &other);
private:
        unsigned int shared_keywords(Sparsetence &other);
};

#undef _HAS_SPARSETENCE_HPP
#endif
