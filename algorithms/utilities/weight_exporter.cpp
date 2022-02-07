//
// Created by Mathias Ravn Tversted on 07/02/2022.
//
# include "../../csv-parser/include/csv.hpp"

using namespace csv;

static void write_weights(const std::vector<double>& weights, const std::string& path) {
    std::ofstream of;
    of.open(path, std::ios::out | std::ios::trunc);
    auto writer = make_csv_writer(of);
    writer << weights;
    of.close();
}


