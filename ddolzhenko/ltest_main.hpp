#include <string>
#include <vector>
#include <set>
#include <map>

#include <algorithm>
#include <functional>
// #include <utility>

#include <iostream>
#include <iomanip>

namespace ltest {

    class TestContext;
    class RunInfo;

    typedef std::string Name;
    typedef std::function<void (TestContext&, RunInfo&)>    TestFunction;
    typedef std::function<void(void)>                       PrepareFunction;
    typedef std::map<Name, TestFunction> Tests;

    struct Run
    {
        const char* expected;
        const char* recieved;
        const char* file;
        const int line;
        const bool ok;
    };

    std::ostream& operator<<(std::ostream& o, const Run& run)
    {
        const char tab[] = "    ";
        return o    << run.file << ":" << run.line << ":: " 
                    << (run.ok ? "ok" : "failed") << ": "
                    << tab << run.expected << std::endl;
                    // << tab << run.recieved << std::endl;
    };


class RunInfo
{
public:
    RunInfo(Name test_name):m_test_name(test_name) {}

    Name m_test_name;
    std::vector<Run> db;

    void expect_true(const char* file, int line, const char* expected, bool ok)
    {
        Run run = {expected, ok ? "true" : "false", file, line, ok};
        db.push_back(run);
        if(!ok) std::cout << run;
    }
  
};

class TestContext
{
public:
    PrepareFunction m_before;
    PrepareFunction m_after;

    bool m_global;

public:
    TestContext(Name name, bool global=false)
    : m_name(name)
    , m_global(global)
    {
        m_before = [](){};
        m_after  = [](){};

        // if(!m_global && verbose) std::cout << m_name << std::endl;
    }

    void run(Name basename="")
    {
        for(const auto& test : m_tests)
        {
            run_test(test.first, test.second, basename);
        }
    }

    void add(Name name, TestFunction test)
    {
        m_tests[name] = test;

        if(!m_global)
        {
            run_test(name, test, m_name+".");
        }
    }


    void run_test(Name name, TestFunction test, Name basename)
    {
        m_before();
        
        TestContext context(basename + name);
        RunInfo info(context.m_name);
        test(context, info);
        // results[fullname] = info;
        m_after();
        
        // context.run(context.m_name + ".");
    }

private:
    static const bool verbose = true;
    Name  m_name;
    Tests m_tests;
    std::map<std::string, RunInfo> results;
};


using namespace std;

struct TestSettings
{
    TestSettings(Name name, TestContext* suite): m_name(name), m_context(suite) {}
    
    TestSettings& operator<<(TestFunction test) {
        m_test = test;
        return *this;
    }

    Name            m_name;
    TestContext*    m_context;
    TestFunction    m_test;
};


struct Registrator
{
    Registrator(const TestSettings& w) {
        w.m_context->add(w.m_name, w.m_test);
    }
};




#define LTEST(test_name) \
    ltest::Registrator ltest_ ## test_name = \
        ltest::TestSettings(#test_name,  &ltest_context__) << \
        [&](ltest::TestContext& ltest_context__, ltest::RunInfo& info__)


#define LBEFORE ltest_context__.m_before = [&]()
#define LAFTER  ltest_context__.m_after  = [&]()


// Unary
#define EXPECT_TRUE(expr)       info__.expect_true(__FILE__, __LINE__, #expr, expr)
#define EXPECT_FALSE(expr)      EXPECT_TRUE(!(expr))

// Binary
#define EXPECT_EQ(expr1, expr2) EXPECT_TRUE((expr1) == (expr2))
#define EXPECT_NE(expr1, expr2) EXPECT_TRUE((expr1) != (expr2))
#define EXPECT_LT(expr1, expr2) EXPECT_TRUE((expr1) < (expr2))
#define EXPECT_LE(expr1, expr2) EXPECT_TRUE((expr1) <= (expr2))
#define EXPECT_GT(expr1, expr2) EXPECT_TRUE((expr1) > (expr2))
#define EXPECT_GE(expr1, expr2) EXPECT_TRUE((expr1) >= (expr2))

// Complex
template <class T> std::set<T> set(const std::initializer_list<T>& list) {
    return std::set<T>(list);
}
template <class T1, class T2>
bool in(const std::set<T1>& s, const T2& x) {
    return s.find(x) != s.end();
}
#define EXPECT_IN(set, expr)    EXPECT_TRUE(ltest::in(set, expr))

////////////////////////////////////////////////////////////////////////////////////////

} // namespace ltest

////////////////////////////////////////////////////////////////////////////////////////

ltest::TestContext ltest_context__("root", true);

////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    ltest_context__.run();
    return 0;
}