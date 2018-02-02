#ifndef _HAS_TEXTRANK_HPP
#define _HAS_TEXTRANK_HPP

#include "SparsetenceFactory.hpp"

#include "config.h"

class TextRank {
public:
        TextRank(
                const vector<Sentence> &sentences,
                double                 pct_keywords,
                double                 dee,
                unsigned long          max_iter,
                double                 tolerance
                );

        vector<unsigned int> order;
        const unsigned long  max_iter;
        const double         pct_keywords;
        const double         dee;
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
