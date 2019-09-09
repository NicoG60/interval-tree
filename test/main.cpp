#define CATCH_CONFIG_MAIN
#define CATCH_CONFIG_ENABLE_BENCHMARKING
#include <catch2/catch.hpp>
#include <random>

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
        auto it0 = tree.emplace({-2, 0}, "value0");
        auto it2 = tree.emplace({0, 2}, "value2");
        auto it1 = tree.emplace({-1, 1}, "value1");

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

        REQUIRE(it->first == std::pair<int, int>(1, 2));
        REQUIRE(it->second == "value1");
        REQUIRE(tree.size() == 6);
    }

    SECTION("Delete middle")
    {
        auto it = tree.erase(++tree.begin());

        REQUIRE(it->first == std::pair<int, int>(2, 3));
        REQUIRE(it->second == "value2");
        REQUIRE(tree.size() == 6);
    }

    SECTION("Delete root")
    {
        auto it  = ++tree.begin();
        it++;
        it++;
        it = tree.erase(it);

        REQUIRE(it->first == std::pair<int, int>(4, 5));
        REQUIRE(it->second == "value4");
        REQUIRE(tree.size() == 6);
    }
}

TEST_CASE("Ordering")
{
    interval_tree<int, int> tree;

    std::srand(0); // Always the same seed. It's just to fill the container

    for(int i = 0; i < 100; i++)
        tree.emplace({std::rand(), std::rand()}, i);


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
        for(int i = 0; i < 10; i++)
            tree.emplace({std::rand(), std::rand()}, i);

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
        for(int i = 0; i < 10; i++)
        {
            auto it = tree.begin();

            for(int j = 0; j < (std::rand() % tree.size()); j++)
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
            REQUIRE(k >= it->first);
            k = it->first;
            s--;
        }

        REQUIRE(s == 0);
    }

    SECTION("reverse With insert")
    {
        for(int i = 0; i < 10; i++)
            tree.emplace({std::rand(), std::rand()}, i);

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
        for(int i = 0; i < 10; i++)
        {
            auto it = tree.begin();

            for(int j = 0; j < (std::rand() % tree.size()); j++)
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

    for(int i = 0; i < 100; i++)
        tree.emplace({std::rand()%1000, std::rand()%1000}, i);

    int point = 250; // Let's get all events at 250;

    // Get the point naivly;

    std::vector<interval_tree<int, int>::value_type> naive;

    for(auto& v : tree)
    {
        auto& k = v.first;

        if(point <= k.second && point >= k.first)
            naive.push_back(v);
    }

    std::vector<interval_tree<int, int>::value_type> find;

    tree.at(point, find);

    REQUIRE(naive == find);
}

TEST_CASE("Find interval")
{
    interval_tree<int, int> tree;

    std::srand(0); // Always the same seed. It's just to fill the container

    for(int i = 0; i < 100; i++)
        tree.emplace({std::rand()%1000, std::rand()%1000}, i);

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

    std::vector<interval_tree<int, int>::value_type> find;

    tree.in(low, high, find);

    REQUIRE(naive == find);
}

// TEST_CASE("Benchmark")
// {
//     interval_tree<int, int> tree;

//     std::srand(0); // Always the same seed. It's just to fill the container

//     for(int i = 0; i < 150000; i++)
//         tree.emplace({std::rand()%1000, std::rand()%1000}, i);

//     BENCHMARK("Emplace")
//     {
//         return tree.emplace({std::rand()%1000, std::rand()%1000}, 101);
//     };

//     BENCHMARK("Insert")
//     {
//         return tree.insert({{std::rand()%1000, std::rand()%1000}, 101});
//     };

//     BENCHMARK("Find point")
//     {
//         std::vector<interval_tree<int, int>::value_type> find;
//         tree.at(250, find);
//         return;
//     };

//     BENCHMARK("Find interval")
//     {
//         std::vector<interval_tree<int, int>::value_type> find;
//         tree.in(250, 750, find);
//         return;
//     };
// }
