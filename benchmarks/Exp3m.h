

static void benchmark_exp3m_1(benchmark::State &state)
{
    auto k = state.range(0);
    int rounds = 100;
    int K = 1;
    std::vector<double> reward(K, 1);
    std::vector<int> index(K, 1);
    DepRoundALIASStrategy a;
    Exp3m b(k, K, 0.1, a);

    for (auto _ : state)
    {
        for (int i = 0; i < rounds; i++)
        {
            auto choices = b.choose();
            b.give_reward(index, reward);
        }
    }
}

static void benchmark_exp3m_1_sample(benchmark::State &state)
{
    auto k = state.range(0);
    int rounds = 100;
    int K = 1;
    std::vector<double> reward(K, 1);
    std::vector<int> index(K, 1);
    DepRoundALIASStrategy a;
    Exp3m b(k, K, 0.1, a);
    for (auto _ : state)
    {
        for (int i = 0; i < rounds; i++)
        {
            auto choices = b.choose();
        }
    }
}

static void benchmark_exp3m_1_update(benchmark::State &state)
{
    auto k = state.range(0);
    int rounds = 100;
    int K = 1;
    std::vector<double> reward(K, 0);
    std::vector<int> index(K, 0);
    DepRoundALIASStrategy a;
    Exp3m b(k, K, 0.1, a);
    b.choose();
    for (auto _ : state)
    {
        for (int i = 0; i < rounds; i++)
        {
            b.give_reward(index, reward);
        }
    }
}