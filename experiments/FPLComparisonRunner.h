//
// Created by Mathias Ravn Tversted on 05/04/2022.
//

#ifndef EFFICIENT_MULTI_ARMED_BANDITS_FPLCOMPARISONRUNNER_H
#define EFFICIENT_MULTI_ARMED_BANDITS_FPLCOMPARISONRUNNER_H

#include <thread>
#include "../algorithms/FPL/FPL.h"
#include "../algorithms/FPL/FPL_toplog.h"
#include "../algorithms/FPL/FPL_unnormalized.h"
#include "../algorithms/FPL/FPL_hash.h"
#include "../algorithms/FPL/QBL.h"
#include "../algorithms/Exp3Bandit/exp3r.h"
#include "../datasets/dataset.h"

template <typename Dataset>
void run_fpl_adversarial_experiment(Dataset &d, int k, int rounds, int averages, double gap,
                                    const std::string &out_path = "/tmp/out")
{

    std::vector<double> fpl_original_regrets(rounds);
    std::vector<double> fpl_new_regrets(rounds);
    std::vector<double> exp3_regrets(rounds);
    //std::vector<double> exp3r_regrets(rounds);
    std::vector<double> uniform_regrets(rounds);

    auto baseline = "FPL";
    auto uniform = "Uniform";
    auto compared = "QBL";
    //auto exp3r_comp = "Exp3r";
    auto exp3_comp = "Exp3";

    for (int i = 0; i < averages; i++)
    {
        std::vector<std::vector<double>> data_matrix = d.generate();
        double eta = 10;
        FPL fpl(k, eta);
        // FPL_hash fpl_new(k, 0.9, rounds);
        // FPL_toplog fpl_new(k, eta);

        QBL fpl_new(k, 5);
        double gamma = 0.006;
        Exp3 exp3(k, gamma);
        //Exp3r exp3r(k,gamma,0.0001, 100000);



        Uniformbandit uni(k);
        // FPL_hash fpl_new(k, eta, rounds);
        // QBL fpl_new(k, eta);

        std::vector<double> fpl_original_run;
        std::thread t1(basic_runner<FPL>, std::ref(fpl), std::ref(data_matrix), rounds, std::ref(fpl_original_run));

        std::vector<double> fpl_new_run;
        std::thread t2(basic_runner<QBL>, std::ref(fpl_new), std::ref(data_matrix), rounds, std::ref(fpl_new_run));

        std::vector<double> exp3_run;
        std::thread t3(basic_runner<Exp3>, std::ref(exp3), std::ref(data_matrix), rounds, std::ref(exp3_run));

        std::vector<double> uniform_run;
        std::thread t4(basic_runner<Uniformbandit>, std::ref(uni), std::ref(data_matrix), rounds,
                       std::ref(uniform_run));

        //std::vector<double> exp3r_run;
        //std::thread t5(basic_runner<Exp3r>, std::ref(exp3r), std::ref(data_matrix), rounds,
        //               std::ref(exp3r_run));

        t1.join();
        t2.join();
        t3.join();
        t4.join();
        //t5.join();

        for (int round = 0; round < rounds; round++)
        {
            fpl_original_regrets[round] += fpl_original_run[round];
            fpl_new_regrets[round] += fpl_new_run[round];
            exp3_regrets[round] += exp3_run[round];
            uniform_regrets[round] += uniform_run[round];
            //exp3r_regrets[round] += exp3r_run[round];
        }
    }
    for (auto &v : fpl_original_regrets)
        v /= averages;

    for (auto &v : fpl_new_regrets)
        v /= averages;
    for (auto &v : exp3_regrets)
        v /= averages;
    for (auto &v : uniform_regrets)
        v /= averages;
    //for (auto &v : exp3r_regrets)
    //    v /= averages;
    std::vector<std::vector<double>> result_matrix;
    result_matrix.push_back(fpl_original_regrets);

    result_matrix.push_back(fpl_new_regrets);

    result_matrix.push_back(exp3_regrets);
    result_matrix.push_back(uniform_regrets);

   // result_matrix.push_back(exp3r_regrets);
    // MUST CONTAIN ENDING COMMA
    auto description = ",";
    auto metadata =
        description +
        std::to_string(k) + "," + std::to_string(rounds) + "," + std::to_string(gap) + "," +
        baseline + "," +
        compared + "," +
        exp3_comp + ","+
        uniform; // + "," +
        //exp3r_comp;
    auto descriptions = std::vector<string>{
        baseline,
        compared,
        exp3_comp,
        uniform};
        //exp3r_comp};
    write_results(result_matrix, metadata, descriptions, out_path);
}

#endif // EFFICIENT_MULTI_ARMED_BANDITS_FPLCOMPARISONRUNNER_H
