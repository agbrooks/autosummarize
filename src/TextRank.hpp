#ifndef _HAS_TEXTRANK_HPP
#define _HAS_TEXTRANK_HPP

#include "SparsetenceFactory.hpp"

#include "config.h"

/**
 * A `TextRank` performs the actual TextRank algorithm over a vector of
 * sentences.
 *
 * The resulting `TextRank::order` provides the ranked importance of the
 * sentences, by index.
 */
class TextRank {
public:
        TextRank(
                const vector<Sentence> &sentences,
                double                 pct_keywords,
                double                 dee,
                unsigned long          max_iter,
                double                 tolerance
                );

        /* Indexes of sentences, from most to least important. */
        vector<unsigned int> order;
        /* Maximum number of iterations performed for scoring. */
        const unsigned long  max_iter;
        /* Percentage of words expected to be keywords. */
        const double         pct_keywords;
        /*
         * PageRank / TextRank 'd' parameter. Higher values mean that important
         * sentences more readily disperse their influence amongst related
         * sentences.
         */
        const double         dee;
        /*
         * Tolerance threshold used to declare convergence of the scoring loop.
         */
        const double         tolerance;

private:
        vector<Sparsetence>     sparsetences;
        SparsetenceFactory      sparsetence_factory;
        vector<vector<double>>  similarities;
        vector<double>          sum_similarities;
        vector<double>          scores;
        vector<double>          old_scores;

        void compute_order();
        void compute_similarities();
        void compute_sparsetences(const vector<Sentence> &sentences);

        bool has_converged() const;
        void update_scores();

};

#undef _HAS_TEXTRANK_HPP
#endif
