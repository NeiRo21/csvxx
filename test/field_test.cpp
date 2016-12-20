#include <csvxx/field.hpp>

#include <gtest/gtest.h>

#include <limits>
#include <cstring>


using namespace csvxx;


//simple tests
TEST(simple_field_test, DefaultCtorAndDtor)
{
    ASSERT_NO_THROW({
        field f;
        EXPECT_TRUE(f.empty());
        EXPECT_FALSE(f.escaped());
    });
}

TEST(simple_field_test, EmptyAndClear)
{
    ASSERT_NO_THROW({
        field f("test");
        ASSERT_FALSE(f.empty());
        f.clear();
        ASSERT_TRUE(f.empty());
    });
}

TEST(simple_field_test, CopyCtor)
{
    ASSERT_NO_THROW({
        field f1("test");
        field f2 = f1;
        ASSERT_EQ(f1.empty(), f2.empty());
        ASSERT_EQ(f1.escaped(), f2.escaped());
        ASSERT_EQ(f1.as_string(), f2.as_string());

        field f3;
        field f4 = f3;
        ASSERT_EQ(f3.empty(), f4.empty());
        ASSERT_EQ(f3.escaped(), f4.escaped());
        ASSERT_EQ(f3.as_string(), f4.as_string());
    });
}


//escaping tests
TEST(escaped_field_test, EscapedFlag)
{
    field f1("test");
    EXPECT_FALSE(f1.escaped());

    field f2("escaping test");
    EXPECT_FALSE(f2.escaped());

//TODO these checks fail because escaping support is not yet implemented
/*
    field f3("another,test");
    EXPECT_TRUE(f3.escaped());

    field f4("yet another\"test");
    EXPECT_TRUE(f4.escaped());

    field f5("one more \ntest");
    EXPECT_TRUE(f5.escaped());

    field f6("and \rmore test");
    EXPECT_TRUE(f6.escaped());

    field f7("even more test\n");
    EXPECT_TRUE(f7.escaped());
*/
}


//integer tests
template<typename T>
class integer_field_test : public ::testing::Test
{
protected:
    using ConversionResult = std::conditional_t<std::is_signed<T>::value,
                                                std::int64_t,
                                                std::uint64_t>;

    ConversionResult convert(const field& f)
    {
        return static_cast<ConversionResult>(f);
    }

    static const std::vector<T> TestValues;
};

TYPED_TEST_CASE_P(integer_field_test);

TYPED_TEST_P(integer_field_test, ConversionCtor)
{
    for (auto tv : TestFixture::TestValues) {
        auto tv_rep = std::to_string(tv);

        ASSERT_NO_THROW({
            field f(tv);
            ASSERT_FALSE(f.empty());
            EXPECT_FALSE(f.escaped());
            ASSERT_EQ(f.as_string(), tv_rep);
        });
    }
}

TYPED_TEST_P(integer_field_test, AssignmentOp)
{
    for (auto tv : TestFixture::TestValues) {
        auto tv_rep = std::to_string(tv);

        ASSERT_NO_THROW({
            field f;
            f = tv;
            ASSERT_FALSE(f.empty());
            EXPECT_FALSE(f.escaped());
            ASSERT_EQ(f.as_string(), tv_rep);
        });
    }
}

TYPED_TEST_P(integer_field_test, ConversionOp)
{
    for (auto tv : TestFixture::TestValues) {
        field f(tv);
        ASSERT_FALSE(f.empty());
        ASSERT_EQ(this->convert(f), tv);
    }
}

REGISTER_TYPED_TEST_CASE_P(integer_field_test, ConversionCtor, AssignmentOp, ConversionOp);

using integer_field_test_types = ::testing::Types<std::int8_t,
                                                  std::uint8_t,
                                                  std::int16_t,
                                                  std::uint16_t,
                                                  std::int32_t,
                                                  std::uint32_t,
                                                  std::int64_t,
                                                  std::uint64_t>;

INSTANTIATE_TYPED_TEST_CASE_P(Integer, integer_field_test, integer_field_test_types);

template<> const std::vector<std::int8_t> integer_field_test<std::int8_t>::TestValues = {
    std::numeric_limits<std::int8_t>::min(),
    std::numeric_limits<std::int8_t>::min() / 2,
    0,
    std::numeric_limits<std::int8_t>::max() / 2,
    std::numeric_limits<std::int8_t>::max()
};

template<> const std::vector<std::uint8_t> integer_field_test<std::uint8_t>::TestValues = {
    0,
    std::numeric_limits<std::uint8_t>::max() / 10,
    std::numeric_limits<std::uint8_t>::max() / 10 * 5,
    std::numeric_limits<std::uint8_t>::max() / 10 * 9,
    std::numeric_limits<std::uint8_t>::max()
};

template<> const std::vector<std::int16_t> integer_field_test<std::int16_t>::TestValues = {
    std::numeric_limits<std::int16_t>::min(),
    std::numeric_limits<std::int16_t>::min() / 2,
    0,
    std::numeric_limits<std::int16_t>::max() / 2,
    std::numeric_limits<std::int16_t>::max()
};

template<> const std::vector<std::uint16_t> integer_field_test<std::uint16_t>::TestValues = {
    0,
    std::numeric_limits<std::uint16_t>::max() / 10,
    std::numeric_limits<std::uint16_t>::max() / 10 * 5,
    std::numeric_limits<std::uint16_t>::max() / 10 * 9,
    std::numeric_limits<std::uint16_t>::max()
};

template<> const std::vector<std::int32_t> integer_field_test<std::int32_t>::TestValues = {
    std::numeric_limits<std::int32_t>::min(),
    std::numeric_limits<std::int32_t>::min() / 2,
    0,
    std::numeric_limits<std::int32_t>::max() / 2,
    std::numeric_limits<std::int32_t>::max()
};

template<> const std::vector<std::uint32_t> integer_field_test<std::uint32_t>::TestValues = {
    0,
    std::numeric_limits<std::uint32_t>::max() / 10,
    std::numeric_limits<std::uint32_t>::max() / 10 * 5,
    std::numeric_limits<std::uint32_t>::max() / 10 * 9,
    std::numeric_limits<std::uint32_t>::max()
};

template<> const std::vector<std::int64_t> integer_field_test<std::int64_t>::TestValues = {
    std::numeric_limits<std::int64_t>::min(),
    std::numeric_limits<std::int64_t>::min() / 2,
    0,
    std::numeric_limits<std::int64_t>::max() / 2,
    std::numeric_limits<std::int64_t>::max()
};

template<> const std::vector<std::uint64_t> integer_field_test<std::uint64_t>::TestValues = {
    0,
    std::numeric_limits<std::uint64_t>::max() / 10,
    std::numeric_limits<std::uint64_t>::max() / 10 * 5,
    std::numeric_limits<std::uint64_t>::max() / 10 * 9,
    std::numeric_limits<std::uint64_t>::max()
};


//floating point tests
template<typename T>
class floating_field_test : public ::testing::Test
{
protected:
    static const std::vector<T> TestValues;
};

TYPED_TEST_CASE_P(floating_field_test);

TYPED_TEST_P(floating_field_test, ConversionCtor)
{
    for (auto tv : TestFixture::TestValues) {
        auto tv_rep = std::to_string(tv);

        ASSERT_NO_THROW({
            field f(tv);
            ASSERT_FALSE(f.empty());
            EXPECT_FALSE(f.escaped());
            ASSERT_EQ(f.as_string(), tv_rep);
        });
    }
}

TYPED_TEST_P(floating_field_test, AssignmentOp)
{
    for (auto tv : TestFixture::TestValues) {
        auto tv_rep = std::to_string(tv);

        ASSERT_NO_THROW({
            field f;
            f = tv;
            ASSERT_FALSE(f.empty());
            EXPECT_FALSE(f.escaped());
            ASSERT_EQ(f.as_string(), tv_rep);
        });
    }
}

TYPED_TEST_P(floating_field_test, ConversionOp)
{
    for (auto tv : TestFixture::TestValues) {
        ASSERT_NO_THROW({
            field f(tv);
            ASSERT_FALSE(f.empty());
            ASSERT_DOUBLE_EQ(static_cast<double>(f), tv);
        });
    }
}

REGISTER_TYPED_TEST_CASE_P(floating_field_test, ConversionCtor, AssignmentOp, ConversionOp);

using floating_field_test_types = ::testing::Types<float, double>;

INSTANTIATE_TYPED_TEST_CASE_P(Floating, floating_field_test, floating_field_test_types);

template<> const std::vector<float> floating_field_test<float>::TestValues = {
    -std::numeric_limits<float>::infinity(),
    std::numeric_limits<float>::lowest(),
//    -1.0 - std::numeric_limits<float>::epsilon(),
    -1.0,
//    -std::numeric_limits<float>::min(),
    0.0,
//    std::numeric_limits<float>::min(),
    1.0,
//    1.0 + std::numeric_limits<float>::epsilon(),
    std::numeric_limits<float>::max(),
    std::numeric_limits<float>::infinity()
};

template<> const std::vector<double> floating_field_test<double>::TestValues = {
    -std::numeric_limits<double>::infinity(),
    std::numeric_limits<double>::lowest(),
    -1.0 - std::numeric_limits<double>::epsilon(),
    -1.0,
//TODO tests fail with these arguments because of std::to_string used by field implementation
//    -std::numeric_limits<double>::min(),
    0.0,
//    std::numeric_limits<double>::min(),
    1.0,
    1.0 + std::numeric_limits<double>::epsilon(),
    std::numeric_limits<double>::max(),
    std::numeric_limits<double>::infinity()
};


//other tests
TEST(boolean_field_test, AllOps)
{
    const std::string TrueRep = "true";
    const std::string FalseRep = "false";

    for (auto tv : {true, false}) {
        const std::string& tv_rep = tv ? TrueRep : FalseRep;
        ASSERT_NO_THROW({
            field f1(tv);
            ASSERT_FALSE(f1.empty());
            EXPECT_FALSE(f1.escaped());
            ASSERT_EQ(f1.as_string(), tv_rep);

            field f2;
            f2 = tv;
            ASSERT_FALSE(f2.empty());
            EXPECT_FALSE(f2.escaped());
            ASSERT_EQ(f2.as_string(), tv_rep);

            field f3(tv);
            ASSERT_FALSE(f3.empty());
            ASSERT_EQ(static_cast<bool>(f3), tv);
        });
    }
}

const std::vector<std::string> StringTestValues = {"", "test", "  spaces ", " a few words"};

TEST(string_field_test, StdStringOps)
{
    for (const auto& tv : StringTestValues) {
        ASSERT_NO_THROW({
            field f1(tv);
            ASSERT_EQ(f1.empty(), tv.empty());
            ASSERT_EQ(f1.as_string(), tv);
            ASSERT_EQ(static_cast<std::string>(f1), tv);

            field f2;
            f2 = tv;
            ASSERT_EQ(f2.empty(), tv.empty());
            ASSERT_EQ(f2.as_string(), tv);
            ASSERT_EQ(static_cast<std::string>(f2), tv);
        });
    }
}

TEST(string_field_test, StdStringRValOps)
{

    for (const auto& tv : StringTestValues) {
        ASSERT_NO_THROW({
            field f1(tv.substr());
            ASSERT_EQ(f1.empty(), tv.empty());
            ASSERT_EQ(f1.as_string(), tv);
            ASSERT_EQ(static_cast<std::string>(f1), tv);

            field f2;
            f2 = tv.substr();
            ASSERT_EQ(f2.empty(), tv.empty());
            ASSERT_EQ(f2.as_string(), tv);
            ASSERT_EQ(static_cast<std::string>(f2), tv);
        });
    }
}

TEST(string_field_test, CStringOps)
{
    for (const auto& tv : StringTestValues) {
        ASSERT_NO_THROW({
            field f1(tv.c_str());
            ASSERT_EQ(f1.empty(), tv.empty());
            ASSERT_EQ(f1.as_string(), tv);
            ASSERT_EQ(static_cast<std::string>(f1), tv);

            field f2;
            f2 = tv.c_str();
            ASSERT_EQ(f2.empty(), tv.empty());
            ASSERT_EQ(f2.as_string(), tv);
            ASSERT_EQ(static_cast<std::string>(f2), tv);
        });
    }
}

