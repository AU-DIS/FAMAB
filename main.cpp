#include "experiments/AdversarialExperimentRunner.h"
#include "datasets/data_generators.h"
#include "experiments/Exp3ComparisonRunner.h"
#include "experiments/FPLComparisonRunner.h"
#include "experiments/TsallisComparisonRunner.h"
#include "experiments/ExploreNoMoreRunner.h"
#include "datastructures/Incremental_sum_heap.h"
#include "algorithms/Exp3Bandit/Exp3_heap.h"
#include "datasets/Dataset_movielens.h"
#include <map>
#include "experiments/TheoreticalBoundRunner.h"
#include "datasets/dataset.h"

using namespace csv;

enum StringValue { adversarial_weights,
    adversarial,
    specific_adversarial,
    adversarial_exp3m,
    explore_no_more,
    generic_bandit_runner,
    theoretical};

//Enum init, so static
static std::map<std::string, StringValue> s_mapStringValues;
static void Initialize() {
    s_mapStringValues["adversarial_weights"] = adversarial_weights;
    s_mapStringValues["adversarial"] = adversarial;
    s_mapStringValues["exp3_adversarial"] = specific_adversarial;
    s_mapStringValues["fpl_adversarial"] = specific_adversarial;
    s_mapStringValues["tsallis_adversarial"] = specific_adversarial;
    s_mapStringValues["adversarial_exp3m"] = adversarial_exp3m;
    s_mapStringValues["ExploreNoMore"] = explore_no_more;
    s_mapStringValues["GenericBanditRunner"] = generic_bandit_runner;
    s_mapStringValues["Theoretical"] = theoretical;
}

int main(int argc, char *argv[]) {
    Initialize();
    std::string path(argv[1]);
    CSVReader reader(path);
    for (auto &row: reader) {
        //Handle variables
        //This is ugly but so are you
        int rounds, k, K, averages;
        double gap, delta;
        std::string dataset, regret_out, plot_out, algorithm, out_path;
        std::string runner(row["runner"].get());
        for (auto &var_name: row.get_col_names()) {
            //This is ugly but so are you
            if (var_name == "rounds") rounds = row[var_name].get<int>();
            else if (var_name == "k") k = row[var_name].get<int>();
            else if (var_name == "K") K = row[var_name].get<int>();
            else if (var_name == "averages") averages = row[var_name].get<int>();
            else if (var_name == "gap") gap = row[var_name].get<double>();
            else if (var_name == "delta") delta = row[var_name].get<double>();
            else if (var_name == "dataset") dataset = row[var_name].get<std::string>();
            else if (var_name == "regret_out") regret_out = row[var_name].get();
            else if (var_name == "plot_out") plot_out = row[var_name].get();
            else if (var_name == "algorithm") algorithm = row[var_name].get();
            else if (var_name == "output_path") out_path = row[var_name].get();
        }


        //Handle datasets
        Dataset *d;
        Mod2Dataset mod2dataset; StochasticallyConstrainedDataset sCD; StochasticDataset stochasticDataset;

        if (dataset == "stochastically_constrained_adversarial") {sCD = StochasticallyConstrainedDataset(k, rounds, gap, delta); d = &sCD;}
        else if (dataset == "mod2") {mod2dataset = Mod2Dataset(k, rounds, gap); d = &mod2dataset;}
        else if (dataset == "stochastic") {stochasticDataset = StochasticDataset(k, rounds, delta); d = &stochasticDataset;}


        switch (s_mapStringValues[runner]) {
            case adversarial_weights:
                run_adversarial_weight_experiment(*d, k, rounds, gap, averages, regret_out, plot_out, algorithm);
                break;
            case adversarial:
                run_adversarial_experiment(*d, k, rounds, averages, gap, out_path);
                break;
            case specific_adversarial:
                if (runner == "exp3_adversarial") run_exp3_adversarial_experiment(*d, k, rounds, averages, gap, out_path);
                if (runner == "fpl_adversarial") run_fpl_adversarial_experiment(*d, k, rounds, averages, gap, out_path);
                if (runner == "tsallis_adversarial") run_tsallis_adversarial_experiment(*d, k, rounds, averages, gap, out_path);
                break;
            case adversarial_exp3m:
                run_adversarial_exp3m_experiment(*d, k, K, rounds, averages, gap, out_path);
                break;
            case explore_no_more:
                run_explore_no_more_experiment();
                break;
            case generic_bandit_runner:
                if (dataset == "adversarial") {
                    int K = row["K"].get<int>();
                    //auto d = dataset_simple_adversarial(K, rounds);
                    //run_generic_experiment(d, K, rounds, averages, out_path);
                }
                if (dataset == "movielens") {
                    //auto d = Dataset_movielens("datasets/data_directory/movielens.csv", 4);
                    //run_generic_experiment(d, d.K, rounds, averages, out_path);
                }
                break;
            case theoretical:
                run_theoretical_bound_experiment_Exp3_varying_k();
                run_theoretical_bound_experiment_Exp3_varying_T();
                run_theoretical_bound_experiment_Exp3ix_varying_k();
                run_theoretical_bound_experiment_Exp3ix_varying_T();
                run_theoretical_bound_experiment_FPL_varying_k();
                run_theoretical_bound_experiment_FPL_varying_T();
                run_theoretical_bound_experiment_Exp3m_varying_small_k();
                run_theoretical_bound_experiment_Exp3m_varying_big_k();
                run_theoretical_bound_experiment_Exp3m_varying_T();
                break;
            default:
                std::cout << "The Requested runner was not found" << std::endl;
                abort();
        }
    }
}



