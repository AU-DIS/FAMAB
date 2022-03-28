#include "experiments/GenericBanditRunner.h"
#include "csv-parser/include/csv.hpp"
#include "experiments/TsallisExperimentRunner.h"
#include "experiments/ExploreNoMoreRunner.h"

using namespace csv;

int main(int argc, char *argv[]) {
    std::string path(argv[1]);
    CSVReader reader(path);
    for (auto &row: reader) {
        std::string runner(row["runner"].get());

        if (runner == "tsallis_weights") {
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
                auto d = adversarial_with_gap(k, rounds, gap, delta);
                run_tsallis_weight_experiment(d, k, rounds, gap, averages, regret_out, plot_out, algorithm);
            }
            if (dataset == "mod2") {
                auto d = mod_2(k, rounds, gap);
                run_tsallis_weight_experiment(d, k, rounds, gap, averages, regret_out, plot_out, algorithm);
            }

        }

        if (runner == "tsallis") {
            int rounds = row["rounds"].get<int>();
            int averages = row["averages"].get<int>();
            int k = row["k"].get<int>();
            double gap = row["gap"].get<double>();
            auto delta = row["delta"].get<double>();
            std::string out_path = row["output_path"].get();
            std::string dataset = row["dataset"].get();
            if (dataset == "stochastically_constrained_adversarial") {
                auto d = adversarial_with_gap(k, rounds, gap, delta);
                run_tsallis_experiment(d, k, rounds, averages, gap, out_path);
            }
            if (dataset == "mod2") {
                auto d = mod_2(k, rounds, gap);
                run_tsallis_experiment(d, k, rounds, averages, gap, out_path);
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
                auto d = dataset_simple_adversarial(K, rounds);
                run_generic_experiment(d, K, rounds, averages, out_path);
            }
            if (dataset == "movielens") {
                auto d = Dataset_movielens("datasets/data_directory/movielens.csv", 4);
                run_generic_experiment(d, d.K, rounds, averages, out_path);
            }
        }
    }
}