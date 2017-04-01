#include <csvxx/file.hpp>

#include <gtest/gtest.h>


using namespace csvxx;


//simple tests
TEST(SimpleFileTest, defaultCtorAndDtor)
{
    file f;
    ASSERT_TRUE(f.empty());
    ASSERT_EQ(f.size(), 0);
}

TEST(SimpleFileTest, width)
{
    file f;
    ASSERT_EQ(f.getWidth(), 0);

    record r;
    r << 1 << "10" << 100.0;
    f << r;
    ASSERT_EQ(f.getWidth(), 3);
}

TEST(SimpleFileTest, clear)
{
    file f;
    record r;
    r << 1 << "10" << 100.0;
    f << r;
    ASSERT_FALSE(f.empty());

    f.clear();
    ASSERT_TRUE(f.empty());
    ASSERT_EQ(f.size(), 0);
    ASSERT_EQ(f.getWidth(), 0);
}


//initializer_list method tests
TEST(ILFileTest, ctor)
{
    record r1;
    r1 << "test" << 1 << 2.0;

    record r2;
    r2 << "test 2" << 5 << -1.75;

    file f{r1, r2};
    ASSERT_DOUBLE_EQ(f.front()[2].as_double(), 2.0);
    ASSERT_EQ(f.back()[1].as_unsigned(), 5);
}

TEST(ILFileTest, assignmentOp)
{
    record r;
    r << 12345;
    file f;
    f << r;

    record r1;
    r1 << "test" << 1 << 2.0;

    record r2;
    r2 << "test 2" << 5 << -1.75;

    f = {r1, r2};
    ASSERT_EQ(f.front()[0].as_string(), "test");
    ASSERT_DOUBLE_EQ(f.back()[2].as_double(), -1.75);
}


//operator tests
TEST(OperatorFileTest, appendOp)
{
    const std::string TestString = "test";

    file f;
    ASSERT_TRUE(f.empty());

    record r;
    r << TestString;

    f << r;
    ASSERT_EQ(f.size(), 1);
    ASSERT_EQ(f.front().front().as_string(), TestString);
}

TEST(OperatorFileTest, indexOp)
{
    record r1;
    r1 << "test" << 1 << 2.0;

    record r2;
    r2 << "test 2" << 5 << -1.75;

    file f{r1, r2};
    ASSERT_DOUBLE_EQ(f[0][2].as_double(), 2.0);
    ASSERT_DOUBLE_EQ(f[1][2].as_double(), -1.75);

    record r3;
    r3 << 42;

    ASSERT_NO_THROW({
        f[3] = r3;
        ASSERT_EQ(f[3].front().as_unsigned(), 42);
    });

    const file& cf = f;
    ASSERT_THROW(cf[10].front().as_string(), std::out_of_range);
}

