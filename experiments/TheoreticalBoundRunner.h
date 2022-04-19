//
// Created by Kristoffer Strube on 30-03-2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_THEORETICALBOUNDRUNNER_H
#define EFFICIENT_MULTI_ARMED_BANDITS_THEORETICALBOUNDRUNNER_H
#include "../datasets/dataset_theoretical_bounds.h"
#include "../utilities/eta_mean_std_writer.h"
#include "../algorithms/Exp3Bandit/Exp31.h"
#include "../algorithms/Exp3Bandit/Exp3.h"
#include "../algorithms/FPL/FPLVectorWeightStrategy.h"
#include "../algorithms/FPL/NaiveRandomGenStrategy.h"
#include "../algorithms/FPL/FPL.h"
#include "../algorithms/UCB/UCB1.h"
#include "../runner.h"
#include "math.h"

void run_theoretical_bound_experiment_Exp3_varying_k(int averages=50, const std::string& out_path="/tmp") {
    vector<vector<double>> data_matrix;
    for (int i = 1; i < 2; i++) {
        std::cout << std::to_string(i) << std::endl;
        int k = pow(16, i);
        int T = 1000000;
        double average = 0;
        for (int run = 0; run < averages; run++) {
            double eta = sqrt(log(k)/((double)T*(double)k));
            Exp3Tor exp3(k, eta);
            dataset_theoretical_bounds d(T, k);
            auto regrets = basic_runner(exp3, d, T);
            auto Rn = sum_of_range(regrets, 0, T);
            average += Rn / (double)averages;
        }
        // The divided part is the O-time that we are promised so we would expect these different averages to be the
        // same i.e. a flat line when plotted
        double average_divided_by_promise = average / sqrt((double)T*(double)k*log((double)k));
        vector<double> run { (double)k, (double)T, average, average_divided_by_promise, (double)averages };
        data_matrix.push_back(run);
    }
    vector<string> comments {"#Theoretical Bound Experiment for Exp3 with varying K's"};
    vector<string> header {"k","T","average","average_divided_by_promise","number_of_average_runs"};
    write_results(data_matrix, comments, header, out_path + "/Theoretical_Bound_Experiment_Exp3_with_varying_k.csv");
}

void run_theoretical_bound_experiment_Exp3_varying_T(int averages=50, const std::string& out_path="/tmp") {
    vector<vector<double>> data_matrix;
    for (int i = 1; i < 10; i++) {
        std::cout << std::to_string(i) << std::endl;
        int k = 10000;
        int T = pow(10, i);
        double average = 0;
        for (int run = 0; run < averages; run++) {
            double eta = sqrt(log(k)/((double)T*(double)k));
            Exp3Tor exp3(k, eta);
            dataset_theoretical_bounds d(T, k);
            auto regrets = basic_runner(exp3, d, T);
            auto Rn = sum_of_range(regrets, 0, T);
            average += Rn / (double)averages;
        }
        // The divided part is the O-time that we are promised so we would expect these different averages to be the
        // same i.e. a flat line when plotted
        double average_divided_by_promise = average / sqrt((double)T*(double)k*log((double)k));
        vector<double> run { (double)k, (double)T, average, average_divided_by_promise, (double)averages };
        data_matrix.push_back(run);
    }
    vector<string> comments {"#Theoretical Bound Experiment for Exp3 with varying T's"};
    vector<string> header {"k","T","average","average_divided_by_promise","number_of_average_runs"};
    write_results(data_matrix, comments, header, out_path + "/Theoretical_Bound_Experiment_Exp3_with_varying_k.csv");
}

void run_theoretical_bound_experiment_Exp3ix_varying_k(int averages=50, const std::string& out_path="/tmp") {
    vector<vector<double>> data_matrix;
    for (int i = 1; i < 2; i++) {
        std::cout << std::to_string(i) << std::endl;
        int k = pow(16, i);
        int T = 1000000;
        double average = 0;
        for (int run = 0; run < averages; run++) {
            double eta = sqrt(log(k)/((double)T*(double)k));
            double gamma = eta/2;
            Exp3IXTor exp3IX(k, eta, gamma);
            dataset_theoretical_bounds d(T, k);
            auto regrets = basic_runner(exp3IX, d, T);
            auto Rn = sum_of_range(regrets, 0, T);
            average += Rn / (double)averages;
        }
        // The divided part is the O-time that we are promised so we would expect these different averages to be the
        // same i.e. a flat line when plotted
        double average_divided_by_promise = average / sqrt((double)T*(double)k*log((double)k));
        vector<double> run { (double)k, (double)T, average, average_divided_by_promise, (double)averages };
        data_matrix.push_back(run);
    }
    vector<string> comments {"#Theoretical Bound Experiment for Exp3ix with varying K's"};
    vector<string> header {"k","T","average","average_divided_by_promise","number_of_average_runs"};
    write_results(data_matrix, comments, header, out_path + "/Theoretical_Bound_Experiment_Exp3ix_with_varying_k.csv");
}

void run_theoretical_bound_experiment_Exp3ix_varying_T(int averages=50, const std::string& out_path="/tmp") {
    vector<vector<double>> data_matrix;
    for (int i = 1; i < 10; i++) {
        std::cout << std::to_string(i) << std::endl;
        int k = 10000;
        int T = pow(10, i);
        double average = 0;
        for (int run = 0; run < averages; run++) {
            double eta = sqrt(log(k)/((double)T*(double)k));
            double gamma = eta/2;
            Exp3IXTor exp3IX(k, eta, gamma);
            dataset_theoretical_bounds d(T, k);
            auto regrets = basic_runner(exp3IX, d, T);
            auto Rn = sum_of_range(regrets, 0, T);
            average += Rn / (double)averages;
        }
        // The divided part is the O-time that we are promised so we would expect these different averages to be the
        // same i.e. a flat line when plotted
        double average_divided_by_promise = average / sqrt((double)T*(double)k*log((double)k));
        vector<double> run { (double)k, (double)T, average, average_divided_by_promise, (double)averages };
        data_matrix.push_back(run);
    }
    vector<string> comments {"#Theoretical Bound Experiment for Exp3 with varying T's"};
    vector<string> header {"k","T","average","average_divided_by_promise","number_of_average_runs"};
    write_results(data_matrix, comments, header, out_path + "/Theoretical_Bound_Experiment_Exp3ix_with_varying_k.csv");
}


#endif //EFFICIENT_MULTI_ARMED_BANDITS_THEORETICALBOUNDRUNNER_H
