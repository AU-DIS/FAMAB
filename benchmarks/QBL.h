

static void benchmark_qbl(benchmark::State &state)
{
    auto k = state.range(0);
    QBL b(k, 0.1);
    for (auto _ : state)
    {
        int rounds = 100;
        for (int i = 0; i < rounds; i++)
        {
            int choice = b.choose();
            b.give_reward(i % k, 1);
        }
    }
}

static void benchmark_qbl_sample(benchmark::State &state)
{
    auto k = state.range(0);
    QBL b(k, 0.1);
    for (auto _ : state)
    {
        int rounds = 100;
        for (int i = 0; i < rounds; i++)
        {
            int choice = b.choose();
        }
    }
}
static void benchmark_qbl_update(benchmark::State &state)
{
    auto k = state.range(0);
    QBL b(k, 0.1);
    for (auto _ : state)
    {
        int rounds = 100;
        for (int i = 0; i < rounds; i++)
        {
            b.give_reward(i % k, 1);
        }
    }
}