//
// Created by Kristoffer Strube on 30-03-2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_THEORETICALBOUNDRUNNER_H
#define EFFICIENT_MULTI_ARMED_BANDITS_THEORETICALBOUNDRUNNER_H
#include "../utilities/eta_mean_std_writer.h"
#include "../algorithms/Exp3Bandit/Exp31.h"
#include "../algorithms/Exp3Bandit/Exp3.h"
#include "../algorithms/Exp3m/Exp3m.h"
#include "../algorithms/Exp3m/DepRoundALIASStrategy.h"
#include "../algorithms/FPL/FPL.h"
#include "../algorithms/UCB/UCB1.h"
#include "../runner.h"
#include "math.h"

void run_theoretical_bound_experiment_Exp3_varying_k(int averages=50, const std::string& out_path="/tmp") {
    vector<vector<double>> data_matrix;
    for (int i = 1; i < 10; i++) {
        int k = pow(2, i);
        int T = 1000000;
        double average = 0;
        Mod2Dataset d(k, T, 3.2);
        for (int run = 0; run < averages; run++) {
            double eta = sqrt(log(k)/((double)T*(double)k));
            Exp3Tor exp3(k, eta);
            std::vector<std::vector<double>> data = d.generate();
            std::vector<double> regrets;
            basic_runner(exp3, data, T, regrets);
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
        int k = 10000;
        int T = pow(10, i);
        double average = 0;
        Mod2Dataset d(k, T, 3.2);
        for (int run = 0; run < averages; run++) {
            double eta = sqrt(log(k)/((double)T*(double)k));
            Exp3Tor exp3(k, eta);
            std::vector<std::vector<double>> data = d.generate();
            std::vector<double> regrets;
            basic_runner(exp3, data, T, regrets);
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
    for (int i = 1; i < 10; i++) {
        int k = pow(2, i);
        int T = 1000000;
        double average = 0;
        Mod2Dataset d(k, T, 3.2);
        for (int run = 0; run < averages; run++) {
            double eta = sqrt(log(k)/((double)T*(double)k));
            double gamma = eta/2;
            Exp3IXTor exp3IX(k, eta, gamma);
            std::vector<std::vector<double>> data = d.generate();
            std::vector<double> regrets;
            basic_runner(exp3IX, data, T, regrets);
            auto Rn = sum_of_range(regrets, 0, T);
            average += Rn / (double)averages;
        }
        // The divided part is the O-time that we are promised so we would expect these different averages to be the
        // same i.e. a flat line when plotted
        double average_divided_by_promise = average / sqrt((double)T*(double)k*log((double)k));
        vector<double> run { (double)k, (double)T, average, average_divided_by_promise, (double)averages };
        data_matrix.push_back(run);
    }
    vector<string> comments {"#Theoretical Bound Experiment for Exp3-IX with varying K's"};
    vector<string> header {"k","T","average","average_divided_by_promise","number_of_average_runs"};
    write_results(data_matrix, comments, header, out_path + "/Theoretical_Bound_Experiment_Exp3ix_with_varying_k.csv");
}

void run_theoretical_bound_experiment_Exp3ix_varying_T(int averages=50, const std::string& out_path="/tmp") {
    vector<vector<double>> data_matrix;
    for (int i = 1; i < 10; i++) {
        int k = 10000;
        int T = pow(10, i);
        double average = 0;
        Mod2Dataset d(k, T, 3.2);
        for (int run = 0; run < averages; run++) {
            double eta = sqrt(log(k)/((double)T*(double)k));
            double gamma = eta/2;
            Exp3IXTor exp3IX(k, eta, gamma);
            std::vector<std::vector<double>> data = d.generate();
            std::vector<double> regrets;
            basic_runner(exp3IX, data, T, regrets);
            auto Rn = sum_of_range(regrets, 0, T);
            average += Rn / (double)averages;
        }
        // The divided part is the O-time that we are promised so we would expect these different averages to be the
        // same i.e. a flat line when plotted
        double average_divided_by_promise = average / sqrt((double)T*(double)k*log((double)k));
        vector<double> run { (double)k, (double)T, average, average_divided_by_promise, (double)averages };
        data_matrix.push_back(run);
    }
    vector<string> comments {"#Theoretical Bound Experiment for Exp3-IX with varying T's"};
    vector<string> header {"k","T","average","average_divided_by_promise","number_of_average_runs"};
    write_results(data_matrix, comments, header, out_path + "/Theoretical_Bound_Experiment_Exp3ix_with_varying_T.csv");
}

void run_theoretical_bound_experiment_FPL_varying_k(int averages=50, const std::string& out_path="/tmp") {
    vector<vector<double>> data_matrix;
    for (int i = 1; i < 10; i++) {
        int k = pow(2, i);
        int T = 1000000;
        double average = 0;
        Mod2Dataset d(k, T, 3.2);
        for (int run = 0; run < averages; run++) {
            // We have not found the actual eta for the theoretical bounds, but we have found 10 to work for other experiments
            double eta = 10;
            FPL fpl(k, eta);
            std::vector<std::vector<double>> data = d.generate();
            std::vector<double> regrets;
            basic_runner(fpl, data, T, regrets);
            auto Rn = sum_of_range(regrets, 0, T);
            average += Rn / (double)averages;
        }
        // The divided part is the O-time that we are promised so we would expect these different averages to be the
        // same i.e. a flat line when plotted
        double average_divided_by_promise = average / sqrt((double)T*(double)k*log((double)k));
        vector<double> run { (double)k, (double)T, average, average_divided_by_promise, (double)averages };
        data_matrix.push_back(run);
    }
    vector<string> comments {"#Theoretical Bound Experiment for FPL with varying K's"};
    vector<string> header {"k","T","average","average_divided_by_promise","number_of_average_runs"};
    write_results(data_matrix, comments, header, out_path + "/Theoretical_Bound_Experiment_FPL_with_varying_k.csv");
}

void run_theoretical_bound_experiment_FPL_varying_T(int averages=50, const std::string& out_path="/tmp") {
    vector<vector<double>> data_matrix;
    for (int i = 1; i < 10; i++) {
        int k = 10000;
        int T = pow(10, i);
        double average = 0;
        Mod2Dataset d(k, T, 3.2);
        for (int run = 0; run < averages; run++) {
            // We have not found the actual eta for the theoretical bounds, but we have found 10 to work for other experiments
            double eta = 10;
            FPL fpl(k, eta);
            std::vector<std::vector<double>> data = d.generate();
            std::vector<double> regrets;
            basic_runner(fpl, data, T, regrets);
            auto Rn = sum_of_range(regrets, 0, T);
            average += Rn / (double)averages;
        }
        // The divided part is the O-time that we are promised so we would expect these different averages to be the
        // same i.e. a flat line when plotted
        double average_divided_by_promise = average / sqrt((double)T*(double)k*log((double)k));
        vector<double> run { (double)k, (double)T, average, average_divided_by_promise, (double)averages };
        data_matrix.push_back(run);
    }
    vector<string> comments {"#Theoretical Bound Experiment for FPL with varying T's"};
    vector<string> header {"k","T","average","average_divided_by_promise","number_of_average_runs"};
    write_results(data_matrix, comments, header, out_path + "/Theoretical_Bound_Experiment_FPL_with_varying_T.csv");
}

void run_theoretical_bound_experiment_Exp3m_varying_small_k(int averages=50, const std::string& out_path="/tmp") {
    vector<vector<double>> data_matrix;
    for (int i = 1; i < 10; i++) {
        int k = pow(2, i);
        int K = 10000;
        int T = 1000000;
        double average = 0;
        Mod2Dataset d(k, T, 3.2);
        for (int run = 0; run < averages; run++) {
            double gamma = min(1.0, sqrt(K*log(K/k)/((exp(1)-1)*k*T)));
            DepRoundALIASStrategy ALIAS;
            Exp3m exp3m(K, k, gamma, ALIAS);
            std::vector<std::vector<double>> data = d.generate();
            std::vector<double> regrets;
            top_k_runner(exp3m, data, T, k, regrets);
            auto Rn = sum_of_range(regrets, 0, T);
            average += Rn / (double)averages;
        }
        // The divided part is the O-time that we are promised so we would expect these different averages to be the
        // same i.e. a flat line when plotted
        double average_divided_by_promise = average / sqrt((double)k*(double)T*(double)K*log((double)K/(double)k));
        vector<double> run { (double)K, (double)k, (double)T, average, average_divided_by_promise, (double)averages };
        data_matrix.push_back(run);
    }
    vector<string> comments {"#Theoretical Bound Experiment for Exp3.M with varying small k's"};
    vector<string> header {"K", "k", "T","average","average_divided_by_promise","number_of_average_runs"};
    write_results(data_matrix, comments, header, out_path + "/Theoretical_Bound_Experiment_Exp3M_with_varying_small_k.csv");
}

void run_theoretical_bound_experiment_Exp3m_varying_big_k(int averages=50, const std::string& out_path="/tmp") {
    vector<vector<double>> data_matrix;
    for (int i = 1; i < 10; i++) {
        int k = 10;
        int K = 10 * pow(2, i);
        int T = 1000000;
        double average = 0;
        Mod2Dataset d(k, T, 3.2);
        for (int run = 0; run < averages; run++) {
            double gamma = min(1.0, sqrt(K*log(K/k)/((exp(1)-1)*k*T)));
            DepRoundALIASStrategy ALIAS;
            Exp3m exp3m(K, k, gamma, ALIAS);
            std::vector<std::vector<double>> data = d.generate();
            std::vector<double> regrets;
            top_k_runner(exp3m, data, T, k, regrets);
            auto Rn = sum_of_range(regrets, 0, T);
            average += Rn / (double)averages;
        }
        // The divided part is the O-time that we are promised so we would expect these different averages to be the
        // same i.e. a flat line when plotted
        double average_divided_by_promise = average / sqrt((double)k*(double)T*(double)K*log((double)K/(double)k));
        vector<double> run { (double)K, (double)k, (double)T, average, average_divided_by_promise, (double)averages };
        data_matrix.push_back(run);
    }
    vector<string> comments {"#Theoretical Bound Experiment for Exp3.M with varying big k's"};
    vector<string> header {"K", "k", "T","average","average_divided_by_promise","number_of_average_runs"};
    write_results(data_matrix, comments, header, out_path + "/Theoretical_Bound_Experiment_Exp3M_with_varying_big_k.csv");
}

void run_theoretical_bound_experiment_Exp3m_varying_T(int averages=50, const std::string& out_path="/tmp") {
    vector<vector<double>> data_matrix;
    for (int i = 1; i < 6; i++) {
        int k = 100;
        int K = 10000;
        int T = pow(10, i);
        double average = 0;
        Mod2Dataset d(k, T, 3.2);
        for (int run = 0; run < averages; run++) {
            double gamma = min(1.0, sqrt(K*log(K/k)/((exp(1)-1)*k*T)));
            DepRoundALIASStrategy ALIAS;
            Exp3m exp3m(K, k, gamma, ALIAS);
            std::vector<std::vector<double>> data = d.generate();
            std::vector<double> regrets;
            top_k_runner(exp3m, data, T, k, regrets);
            auto Rn = sum_of_range(regrets, 0, T);
            average += Rn / (double)averages;
        }
        // The divided part is the O-time that we are promised so we would expect these different averages to be the
        // same i.e. a flat line when plotted
        double average_divided_by_promise = average / sqrt((double)k*(double)T*(double)K*log((double)K/(double)k));
        vector<double> run { (double)K, (double)k, (double)T, average, average_divided_by_promise, (double)averages };
        data_matrix.push_back(run);
    }
    vector<string> comments {"#Theoretical Bound Experiment for Exp3.M with varying T's"};
    vector<string> header {"K", "k", "T","average","average_divided_by_promise","number_of_average_runs"};
    write_results(data_matrix, comments, header, out_path + "/Theoretical_Bound_Experiment_Exp3M_with_varying_T.csv");
}


#endif //EFFICIENT_MULTI_ARMED_BANDITS_THEORETICALBOUNDRUNNER_H
