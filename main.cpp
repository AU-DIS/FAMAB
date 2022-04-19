#include "experiments/GenericBanditRunner.h"
#include "csv-parser/include/csv.hpp"
#include "experiments/TsallisExperimentRunner.h"
#include "datasets/data_generators.h"
#include "experiments/Exp3ComparisonRunner.h"
#include "experiments/FPLComparisonRunner.h"
#include "experiments/ExploreNoMoreRunner.h"
#include "datastructures/Incremental_sum_heap.h"
#include "algorithms/Exp3Bandit/Exp3_heap.h"
#include "datasets/Dataset_movielens.h"
#include "main-support/main_cases.h"
#include <map>

using namespace csv;


int main(int argc, char *argv[]) {
    Initialize();
    std::string path(argv[1]);
    CSVReader reader(path);
    for (auto &row: reader) {
        std::string runner(row["runner"].get());
        switch (s_mapStringValues[runner]) {
            case tsallis_weights:
                main_case_tsallis_weight(row);
                break;
            case tsallis:
                main_case_tsallis(row);
                break;
            case exp3_tsallis:
                main_case_exp3_tsallis(row);
                break;
            case fpl_tsallis:
                main_case_fpl_tsallis(row);
                break;
            case tsallis_exp3m:
                main_case_tsallis_exp3m(row);
                break;
            case explore_no_more:
                main_case_explore_no_more(row);
                break;
            case generic_bandit_runner:
                main_case_generic_bandit_runner(row);
                break;
            default:
                std::cout << "The Requested runner was not found" << std::endl;
                abort();
        }
    }
}

