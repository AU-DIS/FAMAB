

static void benchmark_exp3m_1(benchmark::State &state)
{
    auto m = state.range(0);
    int rounds = 100;
    int k = 1;
    std::vector<double> reward(k, 1);
    std::vector<int> index(k, 1);
    Exp3m b(m, k, 0.1);

    for (auto _ : state)
    {
        for (int i = 0; i < rounds; i++)
        {
            auto choices = b.choose(m);
            b.give_reward(index, reward);
        }
    }
}

static void benchmark_exp3m_1_sample(benchmark::State &state)
{
    auto m = state.range(0);
    int rounds = 100;
    int k = 1;
    std::vector<double> reward(k, 1);
    std::vector<int> index(k, 1);
    Exp3m b(m, k, 0.1);
    for (auto _ : state)
    {
        for (int i = 0; i < rounds; i++)
        {
            auto choices = b.choose(m);
        }
    }
}

static void benchmark_exp3m_1_update(benchmark::State &state)
{
    auto m = state.range(0);
    int rounds = 100;
    int k = 1;
    std::vector<double> reward(k, 0);
    std::vector<int> index(k, 0);
    Exp3m b(k, k, 0.1);
    b.choose(m);
    for (auto _ : state)
    {
        for (int i = 0; i < rounds; i++)
        {
            b.give_reward(index, reward);
        }
    }
}