#include "experiments/GenericBanditRunner.h"
#include "csv-parser/include/csv.hpp"
#include "experiments/ExploreNoMoreRunner.h"

using namespace csv;

int main(int argc, char *argv[]) {
    std::string path(argv[1]);
    std::cout << path;
    CSVReader reader(path);
    for (auto &row: reader) {
        std::string runner(row["runner"].get());
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
    }*/
}