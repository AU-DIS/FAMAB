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

void run_theoretical_bound_experiment_Exp3Eta_varying_k(int averages=50, const std::string& out_path="/tmp") {
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
    vector<string> comments {"#Theoretical Bound Experiment for Exp3 (eta) with varying K's"};
    vector<string> header {"k","T","average","average_divided_by_promise","number_of_average_runs"};
    write_results(data_matrix, comments, header, out_path + "/Theoretical_Bound_Experiment_Exp3Eta_with_varying_k.csv");
}

void run_theoretical_bound_experiment_Exp3Eta_varying_T(int averages=50, const std::string& out_path="/tmp") {
    vector<vector<double>> data_matrix;
    for (int i = 1; i < 6; i++) {
        int k = 1000;
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
    vector<string> comments {"#Theoretical Bound Experiment for Exp3 (eta) with varying T's"};
    vector<string> header {"k","T","average","average_divided_by_promise","number_of_average_runs"};
    write_results(data_matrix, comments, header, out_path + "/Theoretical_Bound_Experiment_Exp3Eta_with_varying_T.csv");
}

void run_theoretical_bound_experiment_Exp3Gamma_varying_k(int averages=50, const std::string& out_path="/tmp") {
    vector<vector<double>> data_matrix;
    for (int i = 1; i < 8; i++) {
        int k = pow(2, i);
        int T = 10000;
        double g = T * 10;
        double gamma = min(1.0, sqrt(k*log(k)/((exp(1)-1)*g)));
        double average_weak_regret = 0;
        Mod2Dataset d(k, T, 3.2);
        for (int run = 0; run < averages; run++) {
            Exp3 exp3(k, gamma);
            std::vector<std::vector<double>> data = d.generate();
            std::vector<double> regrets;
            basic_runner_returning_reward(exp3, data, T, regrets);
            auto E_Exp3 = sum_of_range(regrets, 0, T);
            double local_GMax = 0;
            for (int arm = 0; arm < k; arm++) {
                double local_best_GMax = 0;
                for (int round = 0; round < T; round++) {
                    local_best_GMax += data[arm][round];
                }
                if (local_best_GMax > local_GMax) {
                    local_GMax = local_best_GMax;
                }
            }
            average_weak_regret += (local_GMax - E_Exp3) / (double)averages;
        }
        // The divided part is the O-time that we are promised so we would expect these different averages to be the
        // same i.e. a flat line when plotted
        double promise = 2.0*sqrt(exp(1)-1)*sqrt((double)g*(double)k*log((double)k));
        double average_divided_by_promise = average_weak_regret / promise;
        vector<double> run { (double)k, (double)T, average_weak_regret, (double) promise, average_divided_by_promise, (double)averages, (double)g, (double)gamma };
        data_matrix.push_back(run);
    }
    vector<string> comments {"#Theoretical Bound Experiment for Exp3 (gamma) with varying k's"};
    vector<string> header {"k","T","average_weak_regret","promise","average_divided_by_promise","number_of_average_runs","g","gamma"};
    write_results(data_matrix, comments, header, out_path + "/Theoretical_Bound_Experiment_Exp3Gamma_with_varying_k.csv");
}

void run_theoretical_bound_experiment_Exp3Gamma_varying_T(int averages=50, const std::string& out_path="/tmp") {
    vector<vector<double>> data_matrix;
    for (int i = 1; i < 7; i++) {
        int k = 10;
        int T = pow(10, i);
        double g = T * 10;
        double gamma = min(1.0, sqrt(k*log(k)/((exp(1)-1)*g)));
        double average_weak_regret = 0;
        Mod2Dataset d(k, T, 3.2);
        for (int run = 0; run < averages; run++) {
            Exp3 exp3(k, gamma);
            std::vector<std::vector<double>> data = d.generate();
            std::vector<double> regrets;
            basic_runner_returning_reward(exp3, data, T, regrets);
            auto EExp3 = sum_of_range(regrets, 0, T);
            double local_GMax = 0;
            for (int arm = 0; arm < k; arm++) {
                double local_best_GMax = 0;
                for (int round = 0; round < T; round++) {
                    local_best_GMax += data[arm][round];
                }
                if (local_best_GMax > local_GMax) {
                    local_GMax = local_best_GMax;
                }
            }
            average_weak_regret += (local_GMax - EExp3) / (double)averages;
        }
        // The divided part is the O-time that we are promised so we would expect these different averages to be the
        // same i.e. a flat line when plotted
        double promise = 2.0*sqrt(exp(1)-1)*sqrt((double)g*(double)k*log((double)k));
        double average_divided_by_promise = average_weak_regret / promise;
        vector<double> run { (double)k, (double)T, average_weak_regret, (double) promise, average_divided_by_promise, (double)averages, (double)g, (double)gamma };
        data_matrix.push_back(run);
    }
    vector<string> comments {"#Theoretical Bound Experiment for Exp3 (gamma) with varying T's"};
    vector<string> header {"k","T","average_weak_regret","promise","average_divided_by_promise","number_of_average_runs","g","gamma"};
    write_results(data_matrix, comments, header, out_path + "/Theoretical_Bound_Experiment_Exp3Gamma_with_varying_T.csv");
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

void run_theoretical_bound_experiment_Exp3m_varying_m(int averages=50, const std::string& out_path="/tmp") {
    vector<vector<double>> data_matrix;
    for (int i = 1; i < 10; i++) {
        int m = pow(2, i);
        int k = 10000;
        int T = 1000000;
        double average = 0;
        Mod2Dataset d(k, T, 3.2);
        for (int run = 0; run < averages; run++) {
            double gamma = min(1.0, sqrt(k*log(k/m)/((exp(1)-1)*m*T)));
            Exp3m exp3m(m, k, gamma);
            std::vector<std::vector<double>> data = d.generate();
            std::vector<double> regrets;
            top_k_runner(exp3m, data, T,k, m, regrets);
            auto Rn = sum_of_range(regrets, 0, T);
            average += Rn / (double)averages;
        }
        // The divided part is the O-time that we are promised so we would expect these different averages to be the
        // same i.e. a flat line when plotted
        double average_divided_by_promise = average / sqrt((double)m*(double)T*(double)k*log((double)k/(double)m));
        vector<double> run { (double)k, (double)m, (double)T, average, average_divided_by_promise, (double)averages };
        data_matrix.push_back(run);
    }
    vector<string> comments {"#Theoretical Bound Experiment for Exp3.M with varying small k's"};
    vector<string> header {"K", "k", "T","average","average_divided_by_promise","number_of_average_runs"};
    write_results(data_matrix, comments, header, out_path + "/Theoretical_Bound_Experiment_Exp3M_with_varying_small_k.csv");
}

void run_theoretical_bound_experiment_Exp3m_k(int averages=50, const std::string& out_path="/tmp") {
    vector<vector<double>> data_matrix;
    for (int i = 1; i < 10; i++) {
        int m = 10;
        int k = 10 * pow(2, i);
        int T = 1000000;
        double average = 0;
        Mod2Dataset d(k, T, 3.2);
        for (int run = 0; run < averages; run++) {
            double gamma = min(1.0, sqrt(k*log(k/m)/((exp(1)-1)*m*T)));
            Exp3m exp3m(m, k, gamma);
            std::vector<std::vector<double>> data = d.generate();
            std::vector<double> regrets;
            top_k_runner(exp3m, data, T, k, m, regrets);
            auto Rn = sum_of_range(regrets, 0, T);
            average += Rn / (double)averages;
        }
        // The divided part is the O-time that we are promised so we would expect these different averages to be the
        // same i.e. a flat line when plotted
        double average_divided_by_promise = average / sqrt((double)m*(double)T*(double)k*log((double)k/(double)m));
        vector<double> run { (double)k, (double)m, (double)T, average, average_divided_by_promise, (double)averages };
        data_matrix.push_back(run);
    }
    vector<string> comments {"#Theoretical Bound Experiment for Exp3.M with varying big k's"};
    vector<string> header {"K", "k", "T","average","average_divided_by_promise","number_of_average_runs"};
    write_results(data_matrix, comments, header, out_path + "/Theoretical_Bound_Experiment_Exp3M_with_varying_big_k.csv");
}

void run_theoretical_bound_experiment_Exp3m_varying_T(int averages=50, const std::string& out_path="/tmp") {
    vector<vector<double>> data_matrix;
    for (int i = 1; i < 6; i++) {
        int m = 100;
        int k = 10000;
        int T = pow(10, i);
        double average = 0;
        Mod2Dataset d(k, T, 3.2);
        for (int run = 0; run < averages; run++) {
            double gamma = min(1.0, sqrt(k*log(k/m)/((exp(1)-1)*m*T)));
            Exp3m exp3m(m, k, gamma);
            std::vector<std::vector<double>> data = d.generate();
            std::vector<double> regrets;
            top_k_runner(exp3m, data, T, k, m, regrets);
            auto Rn = sum_of_range(regrets, 0, T);
            average += Rn / (double)averages;
        }
        // The divided part is the O-time that we are promised so we would expect these different averages to be the
        // same i.e. a flat line when plotted
        double average_divided_by_promise = average / sqrt((double)m*(double)T*(double)k*log((double)k/(double)m));
        vector<double> run { (double)k, (double)m, (double)T, average, average_divided_by_promise, (double)averages };
        data_matrix.push_back(run);
    }
    vector<string> comments {"#Theoretical Bound Experiment for Exp3.M with varying T's"};
    vector<string> header {"k", "m", "T","average","average_divided_by_promise","number_of_average_runs"};
    write_results(data_matrix, comments, header, out_path + "/Theoretical_Bound_Experiment_Exp3M_with_varying_T.csv");
}


#endif //EFFICIENT_MULTI_ARMED_BANDITS_THEORETICALBOUNDRUNNER_H
