#include "experiments/GenericBanditRunner.h"
#include "csv-parser/include/csv.hpp"
using namespace csv;

int main(int argc, char *argv[]) {
    if (argc <= 1) {
        run_generic_experiment();
    }
    else {
        std::string path(argv[1]);

        CSVReader reader(path);
        for (auto& row : reader) {
            std::string runner(row["runner"].get());
            if (runner == "GenericBanditRunner") {
                int K = row["K"].get<int>();
                int rounds = row["rounds"].get<int>();
                int averages = row["averages"].get<int>();
                std::string out_path = row["output_path"].get();
                run_generic_experiment(K, rounds,  averages, out_path);
            }
        }
    }
}