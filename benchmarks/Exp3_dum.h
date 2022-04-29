
static void benchmark_exp3_defer(benchmark::State &state)
{
    auto k = state.range(0);
    Exp3_deferred b(k, 0.1, 128);
    for (auto _ : state)
    {
        int rounds = 100;
        for (int i = 0; i < rounds; i++)
        {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}

static void benchmark_exp3_average(benchmark::State &state)
{
    auto k = state.range(0);
    int rounds = 100;
    double gap = 3.2;
    double delta = 0.9;
    auto dataset = StochasticallyConstrainedDataset(k, rounds, gap, delta);
    auto d = dataset.generate();
    // auto d = mod_2(k, rounds, gap);
    Exp3_average b(k, 0.1, 0.2);
    for (auto _ : state)
    {
        for (int i = 0; i < rounds; i++)
        {
            int choice = b.choose();
            b.give_reward(choice, d[choice][i]);
        }
    }
}

static void benchmark_exp3_defer_xi(benchmark::State &state)
{
    auto k = 100;
    int xi = state.range(0);
    Exp3_deferred b(k, 0.1, xi);
    for (auto _ : state)
    {
        int rounds = 10000;
        for (int i = 0; i < rounds; i++)
        {
            int choice = b.choose();
            b.give_reward(0, 0);
        }
    }
}