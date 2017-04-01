#include <csvxx/record.hpp>

#include <gtest/gtest.h>


using namespace csvxx;


//simple tests
TEST(SimpleRecordTest, defaultCtorAndDtor)
{
    record r;
    ASSERT_TRUE(r.empty());
    ASSERT_EQ(r.size(), 0);
}


//operator tests
template<typename T>
class AppendOperatorRecordTest : public ::testing::Test
{
protected:
    static const T TestValue;
};

template<> const std::string AppendOperatorRecordTest<std::string>::TestValue = "test";
template<> const int64_t AppendOperatorRecordTest<int64_t>::TestValue         = -1;
template<> const uint64_t AppendOperatorRecordTest<uint64_t>::TestValue       = 1;
template<> const double AppendOperatorRecordTest<double>::TestValue           = 2.0;
template<> const bool AppendOperatorRecordTest<bool>::TestValue               = true;

using AppendOperatorRecordTestTypes = ::testing::Types<std::string, int64_t, uint64_t, double, bool>;
TYPED_TEST_CASE(AppendOperatorRecordTest, AppendOperatorRecordTestTypes);

TYPED_TEST(AppendOperatorRecordTest, appendOp)
{
    record r;
    ASSERT_TRUE(r.empty());

    r << TestFixture::TestValue;
    ASSERT_EQ(r.size(), 1);
    auto& f = r.front();
    ASSERT_EQ(static_cast<TypeParam>(f), TestFixture::TestValue);
}

TEST(OperatorRecordTest, indexOp)
{
    //TODO rewrite without using index operator
    record r1;
    r1 << "test" << 1 << 2.0;
    ASSERT_EQ(r1[1].as_signed(), 1);

    r1[1] = 3;
    ASSERT_EQ(r1[1].as_signed(), 3);

    r1[3] = 10u;
    ASSERT_EQ(r1[3].as_unsigned(), 10);

    const record& r2 = r1;
    ASSERT_THROW(r2[10].as_string(), std::out_of_range);
}

TEST(OperatorRecordTest, mergeOp)
{
    record r1;
    r1 << "test";
    record r2;
    r1 << 1 << 2.0;
    r1 += r2;
    ASSERT_EQ(r1.size(), 3);
    ASSERT_EQ(r1[1].as_signed(), 1);
    ASSERT_DOUBLE_EQ(r1[2].as_double(), 2.0);
}

TEST(OperatorRecordTest, concatOp)
{
    record r1, r2;
    r1 << 5;
    r2 << -3;

    auto r3 = r1 + r2;
    ASSERT_EQ(r3.size(), r1.size() + r2.size());
    ASSERT_EQ(r3[0].as_signed(), r1[0].as_signed());
    ASSERT_EQ(r3[1].as_signed(), r2[0].as_signed());
}

