

static void benchmark_exp3_data(benchmark::State &state)
{
    auto k = state.range(0);
    int rounds = 100;
    double gap = 3.2;
    double delta = 0.9;
    auto dataset = StochasticallyConstrainedDataset(k, rounds, gap, delta);
    auto d = dataset.generate();
    Exp3 b(k, 0.1);
    for (auto _ : state)
    {
        for (int i = 0; i < rounds; i++)
        {
            int choice = b.choose();
            b.give_reward(choice, d[choice][i]);
        }
    }
}


static void benchmark_exp3(benchmark::State &state)
{
    auto k = state.range(0);
    Exp3 b(k, 0.1);
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

static void benchmark_exp3_sample(benchmark::State &state)
{
    auto k = state.range(0);
    Exp3 b(k, 0.1);
    for (auto _ : state)
    {
        int rounds = 100;
        for (int i = 0; i < rounds; i++)
        {
            int choice = b.choose();
        }
    }
}
static void benchmark_exp3_update(benchmark::State &state)
{
    auto k = state.range(0);
    Exp3 b(k, 0.1);
    for (auto _ : state)
    {
        int rounds = 100;
        for (int i = 0; i < rounds; i++)
        {
            b.give_reward(0, 0);
        }
    }
}