#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>
#include <random>
#include <chrono>
#include <algorithm>

#include <interval_tree.h>

typedef interval_tree<int, std::string> itree;
typedef itree::value_type               value_type;
typedef itree::key_type                 key_type;
typedef itree::iterator                 iterator;

TEST_CASE("Constructors and assignment", "[test]")
{
    SECTION("Default Constructor")
    {
        itree tree;
        REQUIRE(tree.empty());
        REQUIRE(tree.size() == 0);
        REQUIRE(tree.begin() == tree.end());
    }

    SECTION("Initializer list Constructor")
    {
        itree tree{{{0, 1}, "value0"}};
        REQUIRE_FALSE(tree.empty());
        REQUIRE(tree.size() == 1);
        auto it = tree.begin();
        REQUIRE(it != tree.end());
        REQUIRE(it->first.first  == 0);
        REQUIRE(it->first.second == 1);
        REQUIRE(it->second == "value0");
    }

    SECTION("Copy constructor")
    {
        itree tree{{{0, 1}, "value0"}};
        itree copy(tree);

        REQUIRE(*copy.begin() == *tree.begin());
    }

    SECTION("Move constructor")
    {
        itree tree(itree{{{0, 1}, "value0"}});

        auto it = tree.begin();

        REQUIRE(it->first == key_type(0, 1));
        REQUIRE(it->second == "value0");
    }
}

TEST_CASE("Insertion", "[test]")
{
    itree tree;
    REQUIRE(tree.empty());

    SECTION("Insert 1")
    {
        auto it = tree.insert({{0, 1}, "value0"});

        REQUIRE(std::is_sorted(tree.begin(), tree.end(), tree.value_comp()));
        REQUIRE(it == tree.begin());
        REQUIRE(it->first == key_type(0, 1));
        REQUIRE(it->second == "value0");
        REQUIRE(tree.size() == 1);
        REQUIRE(++it == tree.end());
    }

    SECTION("Insert 3 balanced")
    {
        auto it1 = tree.insert({{-1, 1}, "value1"});
        auto it0 = tree.insert({{-2, 0}, "value0"});
        auto it2 = tree.insert({{0, 2}, "value2"});

        REQUIRE(std::is_sorted(tree.begin(), tree.end(), tree.value_comp()));
        REQUIRE(it0 == tree.begin());
        REQUIRE(it0->first == key_type(-2, 0));
        REQUIRE(it0->second == "value0");
        REQUIRE(it1->first == key_type(-1, 1));
        REQUIRE(it1->second == "value1");
        REQUIRE(it2->first == key_type(0, 2));
        REQUIRE(it2->second == "value2");
        REQUIRE(tree.size() == 3);
        REQUIRE(++it0 == it1);
        REQUIRE(++it0 == it2);
        REQUIRE(++it0 == tree.end());
    }

    SECTION("Insert 3 LL")
    {
        auto it2 = tree.insert({{0, 2}, "value2"});
        auto it1 = tree.insert({{-1, 1}, "value1"});
        auto it0 = tree.insert({{-2, 0}, "value0"});

        REQUIRE(std::is_sorted(tree.begin(), tree.end(), tree.value_comp()));
        REQUIRE(it0 == tree.begin());
        REQUIRE(it0->first == key_type(-2, 0));
        REQUIRE(it0->second == "value0");
        REQUIRE(it1->first == key_type(-1, 1));
        REQUIRE(it1->second == "value1");
        REQUIRE(it2->first == key_type(0, 2));
        REQUIRE(it2->second == "value2");
        REQUIRE(tree.size() == 3);
        REQUIRE(++it0 == it1);
        REQUIRE(++it0 == it2);
        REQUIRE(++it0 == tree.end());
    }

    SECTION("Insert 3 LR")
    {
        auto it2 = tree.insert({{0, 2}, "value2"});
        auto it0 = tree.insert({{-2, 0}, "value0"});
        auto it1 = tree.insert({{-1, 1}, "value1"});

        REQUIRE(std::is_sorted(tree.begin(), tree.end(), tree.value_comp()));
        REQUIRE(it0 == tree.begin());
        REQUIRE(it0->first == key_type(-2, 0));
        REQUIRE(it0->second == "value0");
        REQUIRE(it1->first == key_type(-1, 1));
        REQUIRE(it1->second == "value1");
        REQUIRE(it2->first == key_type(0, 2));
        REQUIRE(it2->second == "value2");
        REQUIRE(tree.size() == 3);
        REQUIRE(++it0 == it1);
        REQUIRE(++it0 == it2);
        REQUIRE(++it0 == tree.end());
    }

    SECTION("Insert 3 RR")
    {
        auto it0 = tree.insert({{-2, 0}, "value0"});
        auto it1 = tree.insert({{-1, 1}, "value1"});
        auto it2 = tree.insert({{0, 2}, "value2"});

        REQUIRE(std::is_sorted(tree.begin(), tree.end(), tree.value_comp()));
        REQUIRE(it0 == tree.begin());
        REQUIRE(it0->first == key_type(-2, 0));
        REQUIRE(it0->second == "value0");
        REQUIRE(it1->first == key_type(-1, 1));
        REQUIRE(it1->second == "value1");
        REQUIRE(it2->first == key_type(0, 2));
        REQUIRE(it2->second == "value2");
        REQUIRE(tree.size() == 3);
        REQUIRE(++it0 == it1);
        REQUIRE(++it0 == it2);
        REQUIRE(++it0 == tree.end());
    }

    SECTION("Insert 3 RL")
    {
        auto it0 = tree.insert({{-2, 0}, "value0"});
        auto it2 = tree.insert({{0, 2}, "value2"});
        auto it1 = tree.insert({{-1, 1}, "value1"});

        REQUIRE(std::is_sorted(tree.begin(), tree.end(), tree.value_comp()));
        REQUIRE(it0 == tree.begin());
        REQUIRE(it0->first == key_type(-2, 0));
        REQUIRE(it0->second == "value0");
        REQUIRE(it1->first == key_type(-1, 1));
        REQUIRE(it1->second == "value1");
        REQUIRE(it2->first == key_type(0, 2));
        REQUIRE(it2->second == "value2");
        REQUIRE(tree.size() == 3);
        REQUIRE(++it0 == it1);
        REQUIRE(++it0 == it2);
        REQUIRE(++it0 == tree.end());
    }

    SECTION("Emplace 3 RL")
    {
        auto it0 = tree.emplace(key_type{-2, 0}, "value0");
        auto it2 = tree.emplace(key_type{0, 2}, "value2");
        auto it1 = tree.emplace(key_type{-1, 1}, "value1");

        REQUIRE(std::is_sorted(tree.begin(), tree.end(), tree.value_comp()));
        REQUIRE(it0 == tree.begin());
        REQUIRE(it0->first == key_type(-2, 0));
        REQUIRE(it0->second == "value0");
        REQUIRE(it1->first == key_type(-1, 1));
        REQUIRE(it1->second == "value1");
        REQUIRE(it2->first == key_type(0, 2));
        REQUIRE(it2->second == "value2");
        REQUIRE(tree.size() == 3);
        REQUIRE(++it0 == it1);
        REQUIRE(++it0 == it2);
        REQUIRE(++it0 == tree.end());
    }
}

TEST_CASE("Insert overloads", "[test]")
{
    itree tree{
        {{0, 1}, "value0"},
        {{1, 2}, "value1"},
        {{2, 3}, "value2"},
        //{{3, 4}, "value3"}, // this is the one we'll insert
        {{4, 5}, "value4"},
        {{5, 6}, "value5"},
        {{6, 7}, "value6"}
    };

    SECTION("Insert copy")
    {
        value_type v{{3, 4}, "value3"};

        auto it = tree.insert(v);

        REQUIRE(std::is_sorted(tree.begin(), tree.end(), tree.value_comp()));
        REQUIRE(it->first == v.first);
        REQUIRE(it->second == v.second);
        --it;
        REQUIRE(it->first == key_type(2, 3));
        REQUIRE(it->second == "value2");
        ++it;
        ++it;
        REQUIRE(it->first == key_type(4, 5));
        REQUIRE(it->second == "value4");
    }

    SECTION("Insert move")
    {
        auto it = tree.insert(value_type{{3, 4}, "value3"});

        REQUIRE(std::is_sorted(tree.begin(), tree.end(), tree.value_comp()));
        REQUIRE(it->first == key_type(3, 4));
        REQUIRE(it->second == "value3");
        --it;
        REQUIRE(it->first == key_type(2, 3));
        REQUIRE(it->second == "value2");
        ++it;
        ++it;
        REQUIRE(it->first == key_type(4, 5));
        REQUIRE(it->second == "value4");
    }

    SECTION("Insert hint")
    {
        value_type v{{3, 4}, "value3"};

        auto it = tree.begin();
        ++it;
        ++it;

        it = tree.insert(it, v);

        REQUIRE(it->first == v.first);
        REQUIRE(it->second == v.second);
        --it;
        REQUIRE(it->first == std::pair<int, int>(2, 3));
        REQUIRE(it->second == "value2");
        ++it;
        ++it;
        REQUIRE(it->first == std::pair<int, int>(4, 5));
        REQUIRE(it->second == "value4");
    }

    SECTION("Insert iterators")
    {
        itree tree2(tree);

        tree.insert(tree2.begin(), tree2.end());

        REQUIRE(std::is_sorted(tree.begin(), tree.end(), tree.value_comp()));
    }

    SECTION("Insert ilist")
    {
        tree.insert({
                        {{0, 1}, "value0"},
                        {{1, 2}, "value1"},
                        {{2, 3}, "value2"},
                        {{4, 5}, "value4"},
                        {{5, 6}, "value5"},
                        {{6, 7}, "value6"}
                    });

        REQUIRE(std::is_sorted(tree.begin(), tree.end(), tree.value_comp()));
    }
}

TEST_CASE("Emplaces overloads", "[test]")
{
    itree tree{
        {{0, 1}, "value0"},
        {{1, 2}, "value1"},
        {{2, 3}, "value2"},
        //{{3, 4}, "value3"}, // this is the one we'll insert
        {{4, 5}, "value4"},
        {{5, 6}, "value5"},
        {{6, 7}, "value6"}
    };

    SECTION("Emplace")
    {
        auto it = tree.emplace(key_type{3, 4}, "value3");

        REQUIRE(std::is_sorted(tree.begin(), tree.end(), tree.value_comp()));
        REQUIRE(it->first == key_type(3, 4));
        REQUIRE(it->second == "value3");
        --it;
        REQUIRE(it->first == key_type(2, 3));
        REQUIRE(it->second == "value2");
        ++it;
        ++it;
        REQUIRE(it->first == key_type(4, 5));
        REQUIRE(it->second == "value4");
    }

    SECTION("Emplace hint")
    {
        value_type v{{3, 4}, "value3"};

        auto it = tree.begin();
        ++it;
        ++it;

        it = tree.emplace_hint(it, key_type{3, 4}, "value3");

        REQUIRE(it->first == key_type(3, 4));
        REQUIRE(it->second == "value3");
        --it;
        REQUIRE(it->first == std::pair<int, int>(2, 3));
        REQUIRE(it->second == "value2");
        ++it;
        ++it;
        REQUIRE(it->first == std::pair<int, int>(4, 5));
        REQUIRE(it->second == "value4");
    }
}

TEST_CASE("Deletion", "[test]")
{
    itree tree{
        {{0, 1}, "value0"},
        {{1, 2}, "value1"},
        {{2, 3}, "value2"},
        {{3, 4}, "value3"},
        {{4, 5}, "value4"},
        {{5, 6}, "value5"},
        {{6, 7}, "value6"}
    };

    REQUIRE(tree.size() == 7);
    REQUIRE(std::is_sorted(tree.begin(), tree.end(), tree.value_comp()));

    SECTION("Delete leaf")
    {
        auto it = tree.erase(tree.begin());

        REQUIRE(std::is_sorted(tree.begin(), tree.end(), tree.value_comp()));
        REQUIRE(tree.size() == 6);
        REQUIRE(it->first == key_type(1, 2));
        REQUIRE(it->second == "value1");
    }

    SECTION("Delete middle")
    {
        auto it = tree.erase(++tree.begin());

        REQUIRE(std::is_sorted(tree.begin(), tree.end(), tree.value_comp()));
        REQUIRE(tree.size() == 6);
        REQUIRE(it->first == key_type(2, 3));
        REQUIRE(it->second == "value2");
    }

    SECTION("Delete root")
    {
        auto it  = ++tree.begin();
        it++;
        it++;
        it = tree.erase(it);

        REQUIRE(std::is_sorted(tree.begin(), tree.end(), tree.value_comp()));
        REQUIRE(tree.size() == 6);
        REQUIRE(it->first == key_type(4, 5));
        REQUIRE(it->second == "value4");
    }

    SECTION("Clear")
    {
        tree.clear();

        REQUIRE(tree.empty());
        REQUIRE(tree.begin() == tree.end());
    }
}

TEST_CASE("Ordering", "[test]")
{
    itree tree;

    std::srand(0); // Always the same seed. It's just to fill the container

    for(std::size_t i = 0; i < 100; i++)
        tree.emplace(key_type{std::rand(), std::rand()}, std::to_string(i));


    SECTION("Base")
    {
        REQUIRE(std::is_sorted(tree.begin(), tree.end(), tree.value_comp()));
    }

    SECTION("With insert")
    {
        for(std::size_t i = 0; i < 10; i++)
            tree.emplace(key_type{std::rand(), std::rand()}, std::to_string(i));

        REQUIRE(std::is_sorted(tree.begin(), tree.end(), tree.value_comp()));
    }

    SECTION("With deletes")
    {
        for(std::size_t i = 0; i < 10; i++)
        {
            auto it = tree.begin();

            for(std::size_t j = 0; j < (std::rand() % tree.size()); j++)
                it++;
            tree.erase(it);
        }

        REQUIRE(std::is_sorted(tree.begin(), tree.end(), tree.value_comp()));
    }

    SECTION("reverse Base")
    {
        auto comp = tree.value_comp();

        REQUIRE(std::is_sorted(tree.rbegin(), tree.rend(),
        [&](const value_type& a, const value_type& b)
        {
            return !comp(a, b);
        }));
    }

    SECTION("reverse With insert")
    {
        for(std::size_t i = 0; i < 10; i++)
            tree.emplace(key_type{std::rand(), std::rand()}, std::to_string(i));

        auto comp = tree.value_comp();

        REQUIRE(std::is_sorted(tree.rbegin(), tree.rend(),
        [&](const value_type& a, const value_type& b)
        {
            return !comp(a, b);
        }));
    }

    SECTION("reverse With deletes")
    {
        for(std::size_t i = 0; i < 10; i++)
        {
            auto it = tree.begin();

            for(std::size_t j = 0; j < (std::rand() % tree.size()); j++)
                it++;
            tree.erase(it);
        }

        auto comp = tree.value_comp();

        REQUIRE(std::is_sorted(tree.rbegin(), tree.rend(),
        [&](const value_type& a, const value_type& b)
        {
            return !comp(a, b);
        }));
    }
}

TEST_CASE("Swap", "[test]")
{
    itree tree{
        {{0, 1}, "value0"},
        {{1, 2}, "value1"},
        {{2, 3}, "value2"},
        {{3, 4}, "value3"},
        {{4, 5}, "value4"},
        {{5, 6}, "value5"},
        {{6, 7}, "value6"}
    };

    itree tree2;

    tree.swap(tree2);

    REQUIRE(tree.empty());
    REQUIRE(tree2.size() == 7);
}

TEST_CASE("Find point", "[test]")
{
    itree tree;

    std::srand(0); // Always the same seed. It's just to fill the container

    for(int i = 0; i < 10000; i++)
        tree.emplace(std::pair<int, int>{std::rand()%1000, std::rand()%1000}, std::to_string(i));

    int point = 250; // Let's get all events at 250;

    // Get the point naivly;

    std::vector<value_type> naive;

    for(auto& v : tree)
    {
        auto& k = v.first;

        if(point <= k.second && point >= k.first)
            naive.push_back(v);
    }

    REQUIRE(!naive.empty());

    std::vector<iterator> find;

    tree.at(point, find);

    REQUIRE(!find.empty());

    auto bf = find.begin();
    auto bn = naive.begin();

    while(bf != find.end() && bn != naive.end())
    {
        REQUIRE(**bf == *bn);
        ++bf;
        ++bn;
    }

    auto comp = tree.value_comp();

    REQUIRE(std::is_sorted(find.begin(), find.end(),
    [&](const iterator& a, const iterator& b)
    {
        return comp(*a, *b);
    }));
}

TEST_CASE("Find interval", "[test]")
{
    itree tree;

    std::srand(0); // Always the same seed. It's just to fill the container

    for(std::size_t i = 0; i < 100; i++)
        tree.emplace(key_type{std::rand()%1000, std::rand()%1000}, std::to_string(i));

    int low = 250;
    int high = 750; // Let's get all events in [250, 750];

    // Get the point naively;

    std::vector<value_type> naive;

    for(auto& v : tree)
    {
        auto& k = v.first;

        if(low <= k.second && high >= k.first)
            naive.push_back(v);
    }

    REQUIRE(!naive.empty());

    std::vector<iterator> find;

    tree.in(low, high, find);

    REQUIRE(!find.empty());

    auto bf = find.begin();
    auto bn = naive.begin();

    while(bf != find.end() && bn != naive.end())
    {
        REQUIRE(**bf == *bn);
        ++bf;
        ++bn;
    }

    auto comp = tree.value_comp();

    REQUIRE(std::is_sorted(find.begin(), find.end(),
    [&](const iterator& a, const iterator& b)
    {
        return comp(*a, *b);
    }));
}

void fill(itree& tree, int s)
{
    for(int i = 0; i < s; i++)
        tree.emplace(key_type{std::rand()%1000, std::rand()%1000}, std::to_string(i));
}

int generate_size()
{
    return GENERATE(0, 1,     2,     5,     7,
                       10,    25,    50,    75,
                       100,   250,   500,   750,
                       1000,  2500,  5000,  7500,
                       10000, 25000, 50000, 75000,
                       100000);
}

TEST_CASE("Benchmarks Copy", "[benchmark]")
{
    int size = generate_size();

    BENCHMARK_ADVANCED("Copy " + std::to_string(size))(Catch::Benchmark::Chronometer meter)
    {
        itree tree;
        fill(tree, size);

        meter.measure([&]()
        {
            itree tree2 = tree;
            return tree2;
        });
    };
}

TEST_CASE("Benchmarks Emplace", "[benchmark]")
{
    int size = generate_size();

    BENCHMARK_ADVANCED("Emplace " + std::to_string(size))(Catch::Benchmark::Chronometer meter)
    {
        itree tree;
        fill(tree, size);

        meter.measure([&](int i)
        {
            return tree.emplace(key_type{std::rand()%1000, std::rand()%1000}, std::to_string(i));
        });
    };
}

TEST_CASE("Benchmarks Insert", "[benchmark]")
{
    int size = generate_size();

    BENCHMARK_ADVANCED("Insert " + std::to_string(size))(Catch::Benchmark::Chronometer meter)
    {
        itree tree;
        fill(tree, size);

        meter.measure([&](int i)
        {
            return tree.insert({{std::rand()%1000, std::rand()%1000}, std::to_string(i)});
        });
    };
}

TEST_CASE("Benchmarks Find Point", "[benchmark]")
{
    int size = generate_size();

    BENCHMARK_ADVANCED("Find point " + std::to_string(size))(Catch::Benchmark::Chronometer meter)
    {
        itree tree;
        fill(tree, size);

        std::vector<iterator> find;
        find.reserve(size/10);

        meter.measure([&](){ tree.at(std::rand()%1000, find); return &find; });
    };
}

TEST_CASE("Benchmarks Find Interval", "[benchmark]")
{
    int size = generate_size();


    BENCHMARK_ADVANCED("Find interval " + std::to_string(size))(Catch::Benchmark::Chronometer meter)
    {
        itree tree;
        fill(tree, size);

        std::vector<iterator> find;
        find.reserve(size/10);

        meter.measure([&](){ tree.in(std::rand()%1000, std::rand()%1000, find); return &find; });
    };
}

TEST_CASE("Benchmarks Erase begin", "[benchmark]")
{
    int size = generate_size();

    BENCHMARK_ADVANCED("Erase Begin " + std::to_string(size))(Catch::Benchmark::Chronometer meter)
    {
        itree tree;
        fill(tree, std::max(size, meter.runs()));

        meter.measure([&]()
        {
            return tree.erase(tree.begin());
        });
    };
}

TEST_CASE("Benchmarks Erase middle", "[benchmark]")
{
    int size = generate_size();

    BENCHMARK_ADVANCED("Erase middle " + std::to_string(size))(Catch::Benchmark::Chronometer meter)
    {
        itree tree;
        fill(tree, std::max(size, meter.runs()));

        int m = tree.size() / 2;

        auto it = tree.begin();

        for(int i = 0; i < m; i++)
            ++it;

        meter.measure([&]()
        {
            it = tree.erase(it);
            if(tree.size() > 2 && tree.size()%2 == 1)
                --it;
            return it;
        });
    };
}
