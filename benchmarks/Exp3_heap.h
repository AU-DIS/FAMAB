

static void benchmark_exp3_heap(benchmark::State &state)
{
    auto k = state.range(0);
    Exp3_heap b(k, 0.1);
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

static void benchmark_exp3_heap_sample(benchmark::State &state)
{
    auto k = state.range(0);
    Exp3_heap b(k, 0.1);
    for (auto _ : state)
    {
        int rounds = 100;
        for (int i = 0; i < rounds; i++)
        {
            int choice = b.choose();
        }
    }
}
static void benchmark_exp3_heap_update(benchmark::State &state)
{
    auto k = state.range(0);
    Exp3_heap b(k, 0.1);
    for (auto _ : state)
    {
        int rounds = 100;
        for (int i = 0; i < rounds; i++)
        {
            b.give_reward(0, 0);
        }
    }
}