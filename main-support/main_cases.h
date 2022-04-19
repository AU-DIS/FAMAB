//
// Created by Kasper Overgaard Mortensen on 19-04-2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_MAIN_CASES_H
#define EFFICIENT_MULTI_ARMED_BANDITS_MAIN_CASES_H
#include "../csv-parser/include/csv.hpp"
#include "../experiments/GenericBanditRunner.h"
#include "../csv-parser/include/csv.hpp"
#include "../experiments/TsallisExperimentRunner.h"
#include "../datasets/data_generators.h"
#include "../experiments/Exp3ComparisonRunner.h"
#include "../experiments/FPLComparisonRunner.h"
#include "../experiments/ExploreNoMoreRunner.h"
#include "../datastructures/Incremental_sum_heap.h"
#include "../algorithms/Exp3Bandit/Exp3_heap.h"
#include "../datasets/Dataset_movielens.h"

enum StringValue { tsallis_weights,
    tsallis,
    exp3_tsallis,
    fpl_tsallis,
    tsallis_exp3m,
    explore_no_more,
    generic_bandit_runner};

//Enum init, so static
static std::map<std::string, StringValue> s_mapStringValues;
static void Initialize();
void Initialize() {
    s_mapStringValues["tsallis_weights"] = tsallis_weights;
    s_mapStringValues["tsallis"] = tsallis;
    s_mapStringValues["exp3_tsallis"] = exp3_tsallis;
    s_mapStringValues["fpl_tsallis"] = fpl_tsallis;
    s_mapStringValues["tsallis_exp3m"] = tsallis_exp3m;
    s_mapStringValues["ExploreNoMore"] = explore_no_more;
    s_mapStringValues["GenericBanditRunner"] = generic_bandit_runner;
}

void main_case_tsallis_weight(csv::CSVRow &row) {
    int rounds = row["rounds"].get<int>();
    int k = row["k"].get<int>();
    int averages = row["averages"].get<int>();
    double gap = row["gap"].get<double>();
    auto delta = row["delta"].get<double>();

    std::string dataset = row["dataset"].get();
    std::string regret_out = row["regret_out"].get();
    std::string plot_out = row["plot_out"].get();
    std::string algorithm = row["algorithm"].get();

    if (dataset == "stochastically_constrained_adversarial") {
        auto d = StochasticallyConstrainedDataset(k, rounds, gap, delta);
        run_tsallis_weight_experiment(d, k, rounds, gap, averages, regret_out, plot_out, algorithm);
    }
    if (dataset == "mod2") {
        auto d = Mod2Dataset(k, rounds, gap);
        run_tsallis_weight_experiment(d, k, rounds, gap, averages, regret_out, plot_out, algorithm);
    }
}

void main_case_tsallis(csv::CSVRow &row) {
    int rounds = row["rounds"].get<int>();
    int averages = row["averages"].get<int>();
    int k = row["k"].get<int>();
    double gap = row["gap"].get<double>();
    auto delta = row["delta"].get<double>();
    std::string out_path = row["output_path"].get();
    std::string dataset = row["dataset"].get();
    if (dataset == "stochastically_constrained_adversarial") {
        auto d = StochasticallyConstrainedDataset(k, rounds, gap, delta);
        run_tsallis_experiment(d, k, rounds, averages, gap, out_path);
    }
    if (dataset == "mod2") {
        auto d = Mod2Dataset(k, rounds, gap);
        run_tsallis_experiment(d, k, rounds, averages, gap, out_path);
    }
}

void main_case_exp3_tsallis(csv::CSVRow &row) {
    int rounds = row["rounds"].get<int>();
    int averages = row["averages"].get<int>();
    int k = row["k"].get<int>();
    double gap = row["gap"].get<double>();
    auto delta = row["delta"].get<double>();
    std::string out_path = row["output_path"].get();
    std::string dataset = row["dataset"].get();
    if (dataset == "stochastically_constrained_adversarial") {
        auto d = StochasticallyConstrainedDataset(k, rounds, gap, delta);
        run_exp3_tsallis_experiment(d, k, rounds, averages, gap, out_path);
    }
    if (dataset == "mod2") {
        auto d = Mod2Dataset(k, rounds, gap);
        run_exp3_tsallis_experiment(d, k, rounds, averages, gap, out_path);
    }
}

void main_case_fpl_tsallis(csv::CSVRow &row) {
    int rounds = row["rounds"].get<int>();
    int averages = row["averages"].get<int>();
    int k = row["k"].get<int>();
    double gap = row["gap"].get<double>();
    auto delta = row["delta"].get<double>();
    std::string out_path = row["output_path"].get();
    std::string dataset = row["dataset"].get();
    if (dataset == "stochastically_constrained_adversarial") {
        auto d = StochasticallyConstrainedDataset(k, rounds, gap, delta);
        run_fpl_tsallis_experiment(d, k, rounds, averages, gap, out_path);

    }
    if (dataset == "mod2") {
        auto d = Mod2Dataset(k, rounds, gap);
        run_fpl_tsallis_experiment(d, k, rounds, averages, gap, out_path);
    }
}

void main_case_tsallis_exp3m(csv::CSVRow &row) {
    int rounds = row["rounds"].get<int>();
    int averages = row["averages"].get<int>();
    int k = row["k"].get<int>();
    int K = row["K"].get<int>();
    double gap = row["gap"].get<double>();
    auto delta = row["delta"].get<double>();
    std::string out_path = row["output_path"].get();
    std::string dataset = row["dataset"].get();
    if (dataset == "stochastically_constrained_adversarial") {
        auto d = StochasticallyConstrainedDataset(k, rounds, gap, delta);
        run_tsallis_exp3m_experiment(d, k, K, rounds, averages, gap, out_path);
    }
    if (dataset == "mod2") {
        auto d = Mod2Dataset(k, rounds, gap);
        run_tsallis_exp3m_experiment(d, k, K, rounds, averages, gap, out_path);
    }
}

void main_case_explore_no_more(csv::CSVRow &row) {
    run_explore_no_more_experiment();
}

void main_case_generic_bandit_runner(csv::CSVRow &row) {
    int rounds = row["rounds"].get<int>();
    int averages = row["averages"].get<int>();
    std::string out_path = row["output_path"].get();
    std::string dataset = row["dataset"].get();
    if (dataset == "adversarial") {
        int K = row["K"].get<int>();
        auto d = dataset_simple_adversarial(K, rounds);
        run_generic_experiment(d, K, rounds, averages, out_path);
    }
    if (dataset == "movielens") {
        auto d = Dataset_movielens("datasets/data_directory/movielens.csv", 4);
        run_generic_experiment(d, d.K, rounds, averages, out_path);
    }
}

#endif //EFFICIENT_MULTI_ARMED_BANDITS_MAIN_CASES_H
