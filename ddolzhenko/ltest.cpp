#include <iostream>
#include <vector>
#include <map>
#include <functional>
#include <string>


using namespace std;

struct Run
{
    std::string what;
    bool failed;

};

std::ostream& operator<<(std::ostream& o, const Run& run)
{
    if(run.failed)
        o << "FAILED: " << run.what;
    else
        o << "OK: " << run.what;

    return o;
};

class RunInfo
{
public:

    std::vector<Run> db;

    template <class T1, class T2>
    void __expect_eq(string line1, string line2, const T1& e1, const T2& e2)
    {
        Run run;
        run.what = "expect: " + line1 + " == " + line2;
        run.failed = !(e1 == e2);

        std::cout << "    " << run << std::endl;

        db.push_back(run);
    }
};

class TestSuite
{
public:
    // TestSuite();
    

    typedef std::string Name;
    typedef std::function<void (TestSuite&, RunInfo&)> TestFunction;
    typedef std::map<Name, TestFunction> Tests;

    void add(Name name, TestFunction test)
    {
        m_tests[name] = test;
    }

  

    void run(std::string basename="")
    {
        for(const auto& test : m_tests)
        {
            std::string fullname = basename + test.first;
            TestSuite internal_suite;
            std::cout << "testing: " << fullname << std::endl;
            
            RunInfo info;
            test.second(internal_suite, info);
            results[fullname] = info;

            
            internal_suite.run(test.first + "::");
        }
    }


    Tests m_tests;
    std::map<std::string, RunInfo> results;
};

TestSuite globalTests;

using namespace std;

struct Wrapper
{
    typedef TestSuite::TestFunction TestFunction;
    typedef std::string TestName;
    
    Wrapper(string name, TestFunction test=TestFunction())
    : m_name(name), m_test(test) {}
    
    Wrapper operator+(TestFunction test)
    {
        return Wrapper(m_name, test);
    }

    TestName        m_name;
    TestFunction    m_test;
};


struct Registrator
{
    Registrator(const Wrapper& w)
    {
        globalTests.add(w.m_name, w.m_test);
    }
};


// #define STR(x) #x
// #define CAT(x, y) x ## y
// #define TEST_FUNC_NAME(name) STR(CAT(test_, name))


#define ITEST(test_name) \
    Registrator ltest_ ## test_name = \
        Wrapper(#test_name) + \
        [](TestSuite& __ltests, RunInfo& __info)

// #define ITEST(test_name) \
//     TestSuite::TestFunction TEST_FUNC_NAME(test_name) = 
// __ltests(#test_name) = [](TestSuite& __ltests, RunInfo& __info)

#define EXPECT_EQ(expr1, expr2) __info.__expect_eq(#expr1, #expr2, expr1, expr2)





int foo(int x)
{
    return x*x;
}


ITEST(foo) {

    EXPECT_EQ(1, 1);

    ITEST(degenarated) {
        EXPECT_EQ(0, foo(0));
    };
    ITEST(trivial) {
        EXPECT_EQ(1, foo(1));
    };
};


int main()
{
    globalTests.run();
    return 0;
}