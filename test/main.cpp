#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>
#include <random>
#include <chrono>

#include <interval_tree.h>

TEST_CASE("Constructors and assignment")
{
    SECTION("Default Constructor")
    {
        interval_tree<int, std::string> tree;
        REQUIRE(tree.size() == 0);
    }

    SECTION("Initializer list Constructor")
    {
        interval_tree<int, std::string> tree{{{0, 1}, "value0"}};
        REQUIRE(tree.size() == 1);
    }

    SECTION("Copy constructor")
    {
        interval_tree<int, std::string> tree{{{0, 1}, "value0"}};
        interval_tree<int, std::string> copy(tree);

        REQUIRE(*copy.begin() == *tree.begin());
    }

    SECTION("Copy assignment")
    {
        interval_tree<int, std::string> tree{{{0, 1}, "value0"}};
        interval_tree<int, std::string> copy;
        copy = tree;

        REQUIRE(*copy.begin() == *tree.begin());
    }

    SECTION("Move constructor")
    {
        interval_tree<int, std::string> tree(interval_tree<int, std::string>{{{0, 1}, "value0"}});

        auto it = tree.begin();

        REQUIRE(it->first == std::pair<int, int>(0, 1));
        REQUIRE(it->second == "value0");
    }

    SECTION("Move assignment")
    {
        interval_tree<int, std::string> tree = {{{0, 1}, "value0"}};

        auto it = tree.begin();

        REQUIRE(it->first == std::pair<int, int>(0, 1));
        REQUIRE(it->second == "value0");
    }
}

TEST_CASE("Insertion")
{
    interval_tree<int, std::string> tree;

    SECTION("Insert 1")
    {
        auto it = tree.insert({{0, 1}, "value0"});

        REQUIRE(it == tree.begin());
        REQUIRE(it->first == std::pair<int, int>(0, 1));
        REQUIRE(it->second == "value0");
        REQUIRE(tree.size() == 1);
        REQUIRE(++it == tree.end());
    }

    SECTION("Insert 3 balanced")
    {
        auto it1 = tree.insert({{-1, 1}, "value1"});
        auto it0 = tree.insert({{-2, 0}, "value0"});
        auto it2 = tree.insert({{0, 2}, "value2"});

        REQUIRE(it0 == tree.begin());
        REQUIRE(it0->first == std::pair<int, int>(-2, 0));
        REQUIRE(it0->second == "value0");
        REQUIRE(it1->first == std::pair<int, int>(-1, 1));
        REQUIRE(it1->second == "value1");
        REQUIRE(it2->first == std::pair<int, int>(0, 2));
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

        REQUIRE(it0 == tree.begin());
        REQUIRE(it0->first == std::pair<int, int>(-2, 0));
        REQUIRE(it0->second == "value0");
        REQUIRE(it1->first == std::pair<int, int>(-1, 1));
        REQUIRE(it1->second == "value1");
        REQUIRE(it2->first == std::pair<int, int>(0, 2));
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

        REQUIRE(it0 == tree.begin());
        REQUIRE(it0->first == std::pair<int, int>(-2, 0));
        REQUIRE(it0->second == "value0");
        REQUIRE(it1->first == std::pair<int, int>(-1, 1));
        REQUIRE(it1->second == "value1");
        REQUIRE(it2->first == std::pair<int, int>(0, 2));
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

        REQUIRE(it0 == tree.begin());
        REQUIRE(it0->first == std::pair<int, int>(-2, 0));
        REQUIRE(it0->second == "value0");
        REQUIRE(it1->first == std::pair<int, int>(-1, 1));
        REQUIRE(it1->second == "value1");
        REQUIRE(it2->first == std::pair<int, int>(0, 2));
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

        REQUIRE(it0 == tree.begin());
        REQUIRE(it0->first == std::pair<int, int>(-2, 0));
        REQUIRE(it0->second == "value0");
        REQUIRE(it1->first == std::pair<int, int>(-1, 1));
        REQUIRE(it1->second == "value1");
        REQUIRE(it2->first == std::pair<int, int>(0, 2));
        REQUIRE(it2->second == "value2");
        REQUIRE(tree.size() == 3);
        REQUIRE(++it0 == it1);
        REQUIRE(++it0 == it2);
        REQUIRE(++it0 == tree.end());
    }

    SECTION("Emplace 3 RL")
    {
        auto it0 = tree.emplace(std::pair<int, int>{-2, 0}, "value0");
        auto it2 = tree.emplace(std::pair<int, int>{0, 2}, "value2");
        auto it1 = tree.emplace(std::pair<int, int>{-1, 1}, "value1");

        REQUIRE(it0 == tree.begin());
        REQUIRE(it0->first == std::pair<int, int>(-2, 0));
        REQUIRE(it0->second == "value0");
        REQUIRE(it1->first == std::pair<int, int>(-1, 1));
        REQUIRE(it1->second == "value1");
        REQUIRE(it2->first == std::pair<int, int>(0, 2));
        REQUIRE(it2->second == "value2");
        REQUIRE(tree.size() == 3);
        REQUIRE(++it0 == it1);
        REQUIRE(++it0 == it2);
        REQUIRE(++it0 == tree.end());
    }
}

TEST_CASE("Deletion")
{
    interval_tree<int, std::string> tree{
        {{0, 1}, "value0"},
        {{1, 2}, "value1"},
        {{2, 3}, "value2"},
        {{3, 4}, "value3"},
        {{4, 5}, "value4"},
        {{5, 6}, "value5"},
        {{6, 7}, "value6"}
    };

    SECTION("Delete leaf")
    {
        auto it = tree.erase(tree.begin());

        REQUIRE(tree.size() == 6);
        REQUIRE(it->first == std::pair<int, int>(1, 2));
        REQUIRE(it->second == "value1");

    }

    SECTION("Delete middle")
    {
        auto it = tree.erase(++tree.begin());

        REQUIRE(tree.size() == 6);
        REQUIRE(it->first == std::pair<int, int>(2, 3));
        REQUIRE(it->second == "value2");

    }

    SECTION("Delete root")
    {
        auto it  = ++tree.begin();
        it++;
        it++;
        it = tree.erase(it);

        REQUIRE(tree.size() == 6);
        REQUIRE(it->first == std::pair<int, int>(4, 5));
        REQUIRE(it->second == "value4");

    }
}

TEST_CASE("Ordering")
{
    interval_tree<int, int> tree;

    std::srand(0); // Always the same seed. It's just to fill the container

    for(std::size_t i = 0; i < 100; i++)
        tree.emplace(std::pair<int, int>{std::rand(), std::rand()}, i);


    SECTION("Base")
    {
        auto k = tree.begin()->first;
        auto s = tree.size();

        for(auto& p : tree)
        {
            REQUIRE(k <= p.first);
            k = p.first;
            s--;
        }

        REQUIRE(s == 0);
    }

    SECTION("With insert")
    {
        for(std::size_t i = 0; i < 10; i++)
            tree.emplace(std::pair<int, int>{std::rand(), std::rand()}, i);

        auto k = tree.begin()->first;
        auto s = tree.size();

        for(auto& p : tree)
        {
            REQUIRE(k <= p.first);
            k = p.first;
            s--;
        }

        REQUIRE(s == 0);
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

        auto k = tree.begin()->first;
        auto s = tree.size();

        for(auto& p : tree)
        {
            REQUIRE(k <= p.first);
            k = p.first;
            s--;
        }

        REQUIRE(s == 0);
    }

    SECTION("reverse Base")
    {
        auto k = tree.rbegin()->first;
        auto s = tree.size();

        for(auto it = tree.rbegin(); it != tree.rend(); it++)
        {
            auto o = it->first;
            REQUIRE(k >= o);
            k = o;
            s--;
        }

        REQUIRE(s == 0);
    }

    SECTION("reverse With insert")
    {
        for(std::size_t i = 0; i < 10; i++)
            tree.emplace(std::pair<int, int>{std::rand(), std::rand()}, i);

        auto k = tree.rbegin()->first;
        auto s = tree.size();

        for(auto it = tree.rbegin(); it != tree.rend(); it++)
        {
            REQUIRE(k >= it->first);
            k = it->first;
            s--;
        }

        REQUIRE(s == 0);
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

        auto k = tree.rbegin()->first;
        auto s = tree.size();

        for(auto it = tree.rbegin(); it != tree.rend(); it++)
        {
            REQUIRE(k >= it->first);
            k = it->first;
            s--;
        }

        REQUIRE(s == 0);
    }
}

TEST_CASE("Find point")
{
    interval_tree<int, int> tree;

    std::srand(0); // Always the same seed. It's just to fill the container

    for(int i = 0; i < 10000; i++)
        tree.emplace(std::pair<int, int>{std::rand()%1000, std::rand()%1000}, i);

    int point = 250; // Let's get all events at 250;

    // Get the point naivly;

    std::vector<interval_tree<int, int>::value_type> naive;

    for(auto& v : tree)
    {
        auto& k = v.first;

        if(point <= k.second && point >= k.first)
            naive.push_back(v);
    }

    REQUIRE(!naive.empty());

    std::vector<interval_tree<int, int>::iterator> find;

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
}

TEST_CASE("Find interval")
{
    interval_tree<int, int> tree;

    std::srand(0); // Always the same seed. It's just to fill the container

    for(std::size_t i = 0; i < 100; i++)
        tree.emplace(std::pair<int, int>{std::rand()%1000, std::rand()%1000}, i);

    int low = 250;
    int high = 750; // Let's get all events in [250, 750];

    // Get the point naivly;

    std::vector<interval_tree<int, int>::value_type> naive;

    for(auto& v : tree)
    {
        auto& k = v.first;

        if(low <= k.second && high >= k.first)
            naive.push_back(v);
    }

    REQUIRE(!naive.empty());

    std::vector<interval_tree<int, int>::iterator> find;

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
}

class Chrono
{
public:
    typedef std::chrono::high_resolution_clock       clock;
    typedef clock::time_point                        time_point;
    typedef std::chrono::duration<double, std::micro> duration;

public:
    Chrono() : tp(now()) {}

    void start() { tp = now(); }

    static time_point now() { return clock::now(); }

    duration ellapsed() { return now() - tp; }

private:
    time_point tp;
};

void stats(const std::vector<Chrono::duration>& v, double& mean, double& stddev)
{
    mean = std::accumulate(v.begin(), v.end(), 0,
    [](const double& a, const Chrono::duration& b)
    {
        return a + b.count();
    });

    mean /= v.size();

    stddev = std::accumulate(v.begin(), v.end(), 0,
    [=](const double& a, const Chrono::duration& b)
    {
        const double c = (b.count() - mean);
        return a + (c * c);
    });

    stddev = std::sqrt(stddev/v.size());
}

TEST_CASE("Benchmark")
{
    interval_tree<int, int> tree;

    std::srand(0); // Always the same seed. It's just to fill the container

    for(int i = 0; i < 100000; i++)
        tree.emplace(std::pair<int, int>{std::rand()%1000, std::rand()%1000}, i);

    Chrono timer;
    Chrono total;
    std::vector<Chrono::duration> v(100);
    double mean;
    double stddev;

    total.start();
    for(int i = 0; i < 100; i++)
    {
        timer.start();
        tree.emplace(std::pair<int, int>{std::rand()%1000, std::rand()%1000}, 101);
        v[i] = timer.ellapsed();
    }

    std::cout << "Emplace 100 items. total: " << total.ellapsed().count() << "us" << std::endl;
    stats(v, mean, stddev);
    std::cout << " -> Mean: " << mean << "us, StdDev: " << stddev << "us" << std::endl;

    total.start();
    for(int i = 0; i < 100; i++)
    {
        timer.start();
        tree.insert({{std::rand()%1000, std::rand()%1000}, 102});
        v[i] = timer.ellapsed();
    }

    std::cout << "Insert 100 items. total: " << total.ellapsed().count() << "us" << std::endl;
    stats(v, mean, stddev);
    std::cout << " -> Mean: " << mean << "us, StdDev: " << stddev << "us" << std::endl;

    std::vector<interval_tree<int, int>::iterator> find;
    find.reserve(1000);

    total.start();
    for(int i = 0; i < 100; i++)
    {
        timer.start();
        tree.at(std::rand()%1000, find);
        v[i] = timer.ellapsed();
        find.clear();
    }

    std::cout << "Find 100 times points. total: " << total.ellapsed().count() << "us" << std::endl;
    stats(v, mean, stddev);
    std::cout << " -> Mean: " << mean << "us, StdDev: " << stddev << "us" << std::endl;

    total.start();
    for(int i = 0; i < 100; i++)
    {
        timer.start();
        tree.in(std::rand()%1000, std::rand()%1000, find);
        v[i] = timer.ellapsed();
        find.clear();
    }

    std::cout << "Find 100 times interval. total: " << total.ellapsed().count() << "us" << std::endl;
    stats(v, mean, stddev);
    std::cout << " -> Mean: " << mean << "us, StdDev: " << stddev << "us" << std::endl;
}

// TEST_CASE("Benchmark 2")
// {
//     interval_tree<int, int> tree;

//     std::srand(0); // Always the same seed. It's just to fill the container

//     for(int i = 0; i < 15000; i++)
//         tree.emplace(std::pair<int, int>{std::rand()%1000, std::rand()%1000}, i);

//     std::vector<interval_tree<int, int>::iterator> find;

//     BENCHMARK("Emplace")
//     {
//         return tree.emplace(std::pair<int, int>{std::rand()%1000, std::rand()%1000}, 101);
//     };

//     BENCHMARK("Insert")
//     {
//         return tree.insert({{std::rand()%1000, std::rand()%1000}, 101});
//     };

//     BENCHMARK("Find point")
//     {

//         tree.at(250, find);
//         return;
//     };

//     BENCHMARK("Find interval")
//     {
//         tree.in(250, 750, find);
//         return;
//     };
// }
