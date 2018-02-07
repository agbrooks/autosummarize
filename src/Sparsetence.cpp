#include <algorithm>
#include <math.h>

#include "Sparsetence.hpp"

Sparsetence::Sparsetence(const std::vector<unsigned int> &kw_ids)
        : keywords(kw_ids)
{}

/**
 * Compute the similarity between this Sparsetence and another.
 * The similarity metric is the one suggested by the original TextRank
 * algorithm.
 *
 * This function assumes that this Sparsetence and the other were created
 * by the same SparsetenceFactory. Otherwise, the keyword IDs are not comparable.
 */
double
Sparsetence::similarity(const Sparsetence &other) const
{
        /*
         * 0 length Sparsetences can't be similar to anything.
         */
        if (length() == 0 || other.length() == 0)
        {
                return 0.0;
        }

        /*
         * To avoid an edge case that divides by zero, we assume that if both
         * sentences have length 1, they are unrelated. Given that length 1
         * sentences probably don't convey a lot of information, this isn't a
         * huge loss.
         */
        if (length() == 1 && other.length() == 1)
        {
                return 0.0;
        }

        /*
         * Compute the similarity metric. Because we'll be sifting through
         * a vector, we'll want to search through the smaller vector more
         * often, so check length before proceeding.
         */
        unsigned int n_shared;
        if (length() > other.length())
        {
                n_shared = shared_keywords(other);
        } else {
                n_shared = other.shared_keywords(*this);
        }
        double normalizing_factor = log(length()) + log(other.length());

        return n_shared / normalizing_factor;

}

/**
 * Determine if the Sparsetence includes a particular keyword ID.
 */
bool
Sparsetence::has_kw(unsigned int kw) const
{
        return std::find(keywords.begin(), keywords.end(), kw) != keywords.end();
}


/**
 * Determine the number of words in the Sparsetence.
 */
unsigned int
Sparsetence::length() const
{
        return keywords.size();
}

/* Private methods */

/**
 * Determine how many keywords are shared amongst this Sparsetence and another.
 * This method assumes that both Sparsetences were created by the same
 * SparsetenceFactory.
 */
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
