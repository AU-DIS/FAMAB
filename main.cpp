#include "experiments/AdversarialExperimentRunner.h"
#include "datasets/data_generators.h"
#include "experiments/Exp3ComparisonRunner.h"
#include "experiments/FPLComparisonRunner.h"
#include "experiments/ExploreNoMoreRunner.h"
#include "datastructures/Incremental_sum_heap.h"
#include "algorithms/Exp3Bandit/Exp3_heap.h"

using namespace csv;

int main(int argc, char *argv[]) {
    std::string path(argv[1]);
    CSVReader reader(path);
    for (auto &row: reader) {
        std::string runner(row["runner"].get());

        if (runner == "adversarial_weights") {
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
                run_adversarial_weight_experiment(d, k, rounds, gap, averages, regret_out, plot_out, algorithm);
            }
            if (dataset == "mod2") {
                auto d = Mod2Dataset(k, rounds, gap);
                run_adversarial_weight_experiment(d, k, rounds, gap, averages, regret_out, plot_out, algorithm);
            }

        }

        if (runner == "adversarial") {
            int rounds = row["rounds"].get<int>();
            int averages = row["averages"].get<int>();
            int k = row["k"].get<int>();
            double gap = row["gap"].get<double>();
            auto delta = row["delta"].get<double>();
            std::string out_path = row["output_path"].get();
            std::string dataset = row["dataset"].get();
            if (dataset == "stochastically_constrained_adversarial") {
                auto d = StochasticallyConstrainedDataset(k, rounds, gap, delta);
                run_adversarial_experiment(d, k, rounds, averages, gap, out_path);
            }
            if (dataset == "mod2") {
                auto d = Mod2Dataset(k, rounds, gap);
                run_adversarial_experiment(d, k, rounds, averages, gap, out_path);
            }
            if (dataset == "stochastic") {
                auto d = StochasticDataset(k, rounds, delta);
                if (runner == "exp3_adversarial") run_exp3_adversarial_experiment(d, k, rounds, averages, gap, out_path);
                if (runner == "fpl_adversarial") run_fpl_adversarial_experiment(d, k, rounds, averages, gap, out_path);
            }
        }
        if (runner == "exp3_adversarial" || runner == "fpl_adversarial") {
            int rounds = row["rounds"].get<int>();
            int averages = row["averages"].get<int>();
            int k = row["k"].get<int>();
            double gap = row["gap"].get<double>();
            auto delta = row["delta"].get<double>();
            std::string out_path = row["output_path"].get();
            std::string dataset = row["dataset"].get();
            if (dataset == "stochastically_constrained_adversarial") {
                auto d = StochasticallyConstrainedDataset(k, rounds, gap, delta);
                if (runner == "exp3_adversarial") run_exp3_adversarial_experiment(d, k, rounds, averages, gap, out_path);
                if (runner == "fpl_adversarial") run_fpl_adversarial_experiment(d, k, rounds, averages, gap, out_path);

            }
            if (dataset == "mod2") {
                auto d = Mod2Dataset(k, rounds, gap);
                if (runner == "exp3_adversarial") run_exp3_adversarial_experiment(d, k, rounds, averages, gap, out_path);
                if (runner == "fpl_adversarial") run_fpl_adversarial_experiment(d, k, rounds, averages, gap, out_path);
            }
            if (dataset == "stochastic") {
                auto d = StochasticDataset(k, rounds, delta);
                if (runner == "exp3_adversarial") run_exp3_adversarial_experiment(d, k, rounds, averages, gap, out_path);
                if (runner == "fpl_adversarial") run_fpl_adversarial_experiment(d, k, rounds, averages, gap, out_path);
            }
        }

        if (runner == "adversarial_exp3m") {
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
                run_adversarial_exp3m_experiment(d, k, K, rounds, averages, gap, out_path);
            }
            if (dataset == "mod2") {
                auto d = Mod2Dataset(k, rounds, gap);
                run_adversarial_exp3m_experiment(d, k, K, rounds, averages, gap, out_path);
            }
            if (dataset == "stochastic") {
                auto d = StochasticDataset(k, rounds, delta);
                if (runner == "exp3_adversarial") run_exp3_adversarial_experiment(d, k, rounds, averages, gap, out_path);
                if (runner == "fpl_adversarial") run_fpl_adversarial_experiment(d, k, rounds, averages, gap, out_path);
            }
        }


        if (runner == "ExploreNoMore") {
            run_explore_no_more_experiment();
        }

        if (runner == "GenericBanditRunner") {
            int rounds = row["rounds"].get<int>();
            int averages = row["averages"].get<int>();
            std::string out_path = row["output_path"].get();
            std::string dataset = row["dataset"].get();
            if (dataset == "adversarial") {
                int K = row["K"].get<int>();
                //auto d = dataset_simple_adversarial(K, rounds);
                //run_generic_experiment(d, K, rounds, averages, out_path);
            }
            if (dataset == "movielens") {
                //auto d = Dataset_movielens("datasets/data_directory/movielens.csv", 4);
                //run_generic_experiment(d, d.K, rounds, averages, out_path);
            }

        }
    }
}