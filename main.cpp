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

enum StringValue
{
    adversarial_weights,
    adversarial,
    specific_adversarial,
    adversarial_exp3m,
    explore_no_more,
    generic_bandit_runner,
    theoretical
};

// Enum init, so static
static std::map<std::string, StringValue> s_mapStringValues;
static void Initialize()
{
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

static void run_theoretical_bound_experiment_threaded(std::string& algorithm, std::string& variant, double theta, int lambda) {
    if(algorithm == "Exp3Gamma") {
        if (variant == "base") {
            Exp3 exp3(1,1);
            run_theoretical_bound_experiment_Exp3Gamma_varying_k(exp3, 200, "/tmp/Exp3_base_k.csv");
            run_theoretical_bound_experiment_Exp3Gamma_varying_T(exp3, 200, "/tmp/Exp3_base_T.csv");
        }
        else if (variant == "heap") {
            Exp3_heap exp3(1,1);
            run_theoretical_bound_experiment_Exp3Gamma_varying_k(exp3, 200, "/tmp/Exp3_heap_k.csv");
            run_theoretical_bound_experiment_Exp3Gamma_varying_T(exp3, 200, "/tmp/Exp3_heap_T.csv");
        }
        else if (variant == "fid") {
            Exp3_fid exp3(1,1, lambda);
            run_theoretical_bound_experiment_Exp3Gamma_varying_k(exp3, 200, "/tmp/Exp3_fid_k_lambda_" + std::to_string(lambda) + ".csv");
            run_theoretical_bound_experiment_Exp3Gamma_varying_T(exp3, 200, "/tmp/Exp3_fid_T_lambda_" + std::to_string(lambda) + ".csv");
        }
        else if (variant == "lad") {
            Exp3_lad exp3(1,1,theta);
            run_theoretical_bound_experiment_Exp3Gamma_varying_k(exp3, 200, "/tmp/Exp3_lad_k_theta_" + std::to_string(theta) + ".csv");
            run_theoretical_bound_experiment_Exp3Gamma_varying_T(exp3, 200, "/tmp/Exp3_lad_T_theta_" + std::to_string(theta) + ".csv");
        }
    }
    else if(algorithm == "Exp31") {
        run_theoretical_bound_experiment_Exp31_varying_k();
        run_theoretical_bound_experiment_Exp31_varying_T();
    }
    else if(algorithm == "Exp3IX") {
        run_theoretical_bound_experiment_Exp3ix_varying_k();
        run_theoretical_bound_experiment_Exp3ix_varying_T();
    }
    else if(algorithm == "FPL") {
        run_theoretical_bound_experiment_FPL_varying_k();
        run_theoretical_bound_experiment_FPL_varying_T();
    }
    else if(algorithm == "QBL") {
        run_theoretical_bound_experiment_QBL_varying_k();
        run_theoretical_bound_experiment_QBL_varying_T();
    }
    else if(algorithm == "Exp3M") {
        run_theoretical_bound_experiment_Exp3m_varying_m();
        run_theoretical_bound_experiment_Exp3m_varying_k();
        run_theoretical_bound_experiment_Exp3m_varying_T();
    }
    else if(algorithm == "Tsallis") {
        if (variant == "RV") {
            run_theoretical_bound_experiment_Tsallis_varying_k();
            run_theoretical_bound_experiment_Tsallis_varying_T();
        }
    }
}

int main(int argc, char *argv[])
{
    Initialize();
    std::string path(argv[1]);
    CSVReader reader(path);
    for (auto &row : reader)
    {
        // Handle variables
        // This is Græm but so are you
        int rounds, k, m, averages, lambda;
        double gap, delta, optimal_proportion, optimal_probability, theta;
        std::string dataset, regret_out, plot_out, algorithm, variant, out_path;
        std::string runner(row["runner"].get());
        for (auto &var_name : row.get_col_names())
        {
            // This is ugly but so are you
            if (var_name == "rounds")
                rounds = row[var_name].get<int>();
            else if (var_name == "k")
                k = row[var_name].get<int>();
            else if (var_name == "m")
                m = row[var_name].get<int>();
            else if (var_name == "averages")
                averages = row[var_name].get<int>();
            else if (var_name == "gap")
                gap = row[var_name].get<double>();
            else if (var_name == "delta")
                delta = row[var_name].get<double>();
            else if (var_name == "dataset")
                dataset = row[var_name].get<std::string>();
            else if (var_name == "regret_out")
                regret_out = row[var_name].get();
            else if (var_name == "plot_out")
                plot_out = row[var_name].get();
            else if (var_name == "algorithm")
                algorithm = row[var_name].get();
            else if (var_name == "variant")
                variant = row[var_name].get();
            else if (var_name == "output_path")
                out_path = row[var_name].get();
            else if (var_name == "optimal_probability")
                optimal_probability = row[var_name].get<double>();
            else if (var_name == "optimal_proportion")
                optimal_proportion = row[var_name].get<double>();
            else if (var_name == "theta")
                theta = row[var_name].get<double>();
            else if (var_name == "lambda")
                lambda = row[var_name].get<int>();
        }

        // Handle datasets
        Dataset *d;
        Mod2Dataset mod2dataset;
        StochasticallyConstrainedDataset sCD;
        StochasticDataset stochasticDataset;
        BernoulliOptimalDataset bernoulliDS;
        SinusDataset sDS;
        TentMapDataset tentDS;

        if (dataset == "DuellingDataset")
        {
            if (runner.find("exp3") != std::string::npos)
            {
                auto b = Exp3(k, 0.1);
                auto Dds = DuellingDataset<Exp3>(b, k, rounds);
                d = &Dds;
            }
            if (runner.find("fpl") != std::string::npos)
            {
                auto b = FPL(k, 10);
                auto Dds = DuellingDataset<FPL>(b, k, rounds);
                d = &Dds;
            }
            if (runner.find("tsallis") != std::string::npos)
            {
                auto b = Tsallis_IW(k);
                auto Dds = DuellingDataset<Tsallis_IW>(b, k, rounds);
                d = &Dds;
            }
        }

        if (dataset == "BernoulliOptimalDataset")
        {
            bernoulliDS = BernoulliOptimalDataset(k, rounds, gap, optimal_probability, optimal_proportion, delta);
            d = &bernoulliDS;
        }
        if (dataset == "SinusDataset")
        {
            sDS = SinusDataset(k, rounds);
            d = &sDS;
        }
        if (dataset == "TentMapDataset")
        {
            tentDS = TentMapDataset(k, rounds, gap);
            d = &tentDS;
        }
        if (dataset == "stochastically_constrained_adversarial")
        {
            sCD = StochasticallyConstrainedDataset(k, rounds, gap, delta);
            d = &sCD;
        }
        else if (dataset == "mod2")
        {
            mod2dataset = Mod2Dataset(k, rounds, gap);
            d = &mod2dataset;
        }
        else if (dataset == "stochastic")
        {
            stochasticDataset = StochasticDataset(k, rounds, delta);
            d = &stochasticDataset;
        }

        switch (s_mapStringValues[runner])
        {
        case adversarial_weights:
            run_adversarial_weight_experiment(*d, k, rounds, gap, averages, regret_out, plot_out, algorithm);
            break;
        case adversarial:
            run_adversarial_experiment(*d, k, rounds, averages, gap, out_path);
            break;
        case specific_adversarial:
            if (runner == "exp3_adversarial")
                run_exp3_adversarial_experiment(*d, k, rounds, averages, gap, out_path);
            if (runner == "fpl_adversarial")
                run_fpl_adversarial_experiment(*d, k, rounds, averages, gap, out_path);
            if (runner == "tsallis_adversarial")
                run_tsallis_adversarial_experiment(*d, k, rounds, averages, gap, out_path);
            break;
        case adversarial_exp3m:
            run_adversarial_exp3m_experiment(*d, m, k, rounds, averages, gap, out_path);
            break;
        case explore_no_more:
            run_explore_no_more_experiment();
            break;
        case generic_bandit_runner:
            if (dataset == "adversarial")
            {
                int K = row["K"].get<int>();
                // auto d = dataset_simple_adversarial(K, rounds);
                // run_generic_experiment(d, K, rounds, averages, out_path);
            }
            if (dataset == "movielens")
            {
                // auto d = Dataset_movielens("datasets/data_directory/movielens.csv", 4);
                // run_generic_experiment(d, d.K, rounds, averages, out_path);
            }
            break;
        case theoretical:
            run_theoretical_bound_experiment_threaded(algorithm, variant, theta, lambda);
            break;
        default:
            std::cout << "The Requested runner was not found" << std::endl;
            abort();
        }
    }
}