#include <algorithm>
#include <math.h>

#include "Sparsetence.hpp"

Sparsetence::Sparsetence(const std::vector<unsigned int> &kw_ids)
        : keywords(kw_ids)
{}
/*
Sparsetence::Sparsetence(const Sparsetence &&other)
        : keywords(std::move(other.keywords))
{ }

Sparsetence&
Sparsetence::operator=(const Sparsetence &&other)
{
        if (this != &other)
        {
                keywords = std::move(other.keywords);
        }
        return *this;
}
*/

double
Sparsetence::similarity(const Sparsetence &other) const
{
        /*
         * 0 length can't be similar to anything (and may divide by zero anyway)
         */
        if (length() == 0 || other.length() == 0)
        {
                return 0.0;
        }
        // Compute similarity metric
        unsigned int n_shared = shared_keywords(other);
        double normalizing_factor = log(length()) + log(other.length());

        return n_shared / normalizing_factor;

}

bool
Sparsetence::has_kw(unsigned int kw) const
{
        return std::find(keywords.begin(), keywords.end(), kw) != keywords.end();
}

unsigned int
Sparsetence::length() const
{
        return keywords.size();
}

/* Private methods */

unsigned int
Sparsetence::shared_keywords(const Sparsetence &other) const
{
        unsigned int count = 0;
        for (unsigned int each_kw : keywords)
        {
                if (other.has_kw(each_kw))
                {
                        count++;
                }
        }
        return count;
}
