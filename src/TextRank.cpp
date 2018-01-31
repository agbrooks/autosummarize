#include <cmath>

#include "TextRank.hpp"

TextRank::TextRank(
        const vector<Sentence> &sentences,
        double                 pct_keywords,
        double                 dee,
        unsigned long          max_iter,
        double                 tolerance
        )
        : max_iter(max_iter)
        , pct_keywords(pct_keywords)
        , dee(dee)
        , tolerance(tolerance)
        , sparsetence_factory(SparsetenceFactory(pct_keywords))
{
        compute_sparsetences(sentences);
        compute_similarities();
        compute_rank();
}

bool
TextRank::has_converged() const
{
        long double sum_of_abs_diff = 0;
        #pragma omp parallel for
        for (unsigned int i = 0; i < scores.size(); i++)
        {
                sum_of_abs_diff += std::abs(scores[i] - old_scores[i]);
        }

        return (sum_of_abs_diff / scores.size()) < tolerance;
}

void
TextRank::update_scores()
{
        #pragma omp parallel for
        for (unsigned int i = 0; i < scores.size(); i++)
        {
                scores[i] = 0;
                for (unsigned int j = 0; i < scores.size(); j++)
                {
                        if (i == j) continue;
                        scores[i] += similarities[i][j]
                                   / sum_similarities[j]
                                   * old_scores[j];
                }
        }
}

void
TextRank::compute_rank()
{
        unsigned long iter = 0;
        do
        {
                update_scores();
                iter++;
        } while (!has_converged() && iter < max_iter);
}

void
TextRank::compute_similarities()
{
        /* Expand the similarities matrices to the correct size. */
        similarities.resize(sparsetences.size());
        sum_similarities.resize(sparsetences.size());
        for (auto &v : similarities)
        {
                v.resize(sparsetences.size());
        }

        /* Compute inter-sentence similarity. */
        for (unsigned int i = 0; i < sparsetences.size(); i++)
        {
                sum_similarities[i] = 0;
                for (unsigned int j = 0; j < sparsetences.size(); j++)
                {
                        similarities[i][j] =
                                sparsetences[i].similarity(sparsetences[j]);
                        sum_similarities[i] += similarities[i][j];
                }
        }

        /* Remove self-similarity from sums. */
        for (unsigned int i = 0; i < sparsetences.size(); i++)
        {
                sum_similarities[i] -=
                        sparsetences[i].similarity(sparsetences[i]);
        }
}

void
TextRank::compute_sparsetences(const vector<Sentence> &sentences)
{
        /* Consume all sentences. */
        for (auto &s : sentences)
        {
                sparsetence_factory.consume(s);
        }

        /* Convert to sparsetences. */
        sparsetences = sparsetence_factory.sparsify(sentences);
}
