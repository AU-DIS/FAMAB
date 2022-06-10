static void benchmark_exp3m(benchmark::State &state)
{
    int k = state.range(0);
    int m = (int)k / 10;
    int rounds = 100;
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

static void benchmark_exp3m_sample(benchmark::State &state)
{
    int k = state.range(0);
    int m = (int)k / 10;
    int rounds = 100;
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

static void benchmark_exp3m_update(benchmark::State &state)
{
    int k = state.range(0);
    int m = (int)k / 10;
    int rounds = 100;
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

static void benchmark_fpltopk(benchmark::State &state)
{
    int k = state.range(0);
    int m = (int)k / 10;
    int rounds = 100;

    std::vector<double> reward(k, 1);
    std::vector<int> index(k, 1);
    FPL b(k, 10);

    for (auto _ : state)
    {
        for (int i = 0; i < rounds; i++)
        {
            auto choices = b.choose(m);
            b.give_reward(index, reward);
        }
    }
}

static void benchmark_fpltopk_sample(benchmark::State &state)
{
    int k = state.range(0);
    int m = (int)k / 10;
    int rounds = 100;
    std::vector<double> reward(k, 1);
    std::vector<int> index(k, 1);
    FPL b(k, 10);
    for (auto _ : state)
    {
        for (int i = 0; i < rounds; i++)
        {
            auto choices = b.choose(m);
        }
    }
}

static void benchmark_fpltopk_update(benchmark::State &state)
{
    int k = state.range(0);
    int m = (int)k / 10;
    int rounds = 100;
    std::vector<double> reward(k, 0);
    std::vector<int> index(k, 0);
    FPL b(k, 10);
    b.choose(m);
    for (auto _ : state)
    {
        for (int i = 0; i < rounds; i++)
        {
            b.give_reward(index, reward);
        }
    }
}


static void benchmark_exp3m_heap(benchmark::State &state)
{
    int k = state.range(0);
    int m = (int)k / 10;
    int rounds = 100;
    std::vector<double> reward(k, 1);
    std::vector<int> index(k, 1);
    Exp3m_heap b(m, k, 0.1);

    for (auto _ : state)
    {
        for (int i = 0; i < rounds; i++)
        {
            auto choices = b.choose(m);
            b.give_reward(index, reward);
        }
    }
}

static void benchmark_exp3m_heap_sample(benchmark::State &state)
{
    int k = state.range(0);
    int m = (int)k / 10;
    int rounds = 100;
    std::vector<double> reward(k, 1);
    std::vector<int> index(k, 1);
    Exp3m_heap b(m, k, 0.1);
    for (auto _ : state)
    {
        for (int i = 0; i < rounds; i++)
        {
            auto choices = b.choose(m);
        }
    }
}

static void benchmark_exp3m_heap_update(benchmark::State &state)
{
    int k = state.range(0);
    int m = (int)k / 10;
    int rounds = 100;
    std::vector<double> reward(k, 0);
    std::vector<int> index(k, 0);
    Exp3m_heap b(k, k, 0.1);
    b.choose(m);
    for (auto _ : state)
    {
        for (int i = 0; i < rounds; i++)
        {
            b.give_reward(index, reward);
        }
    }
}