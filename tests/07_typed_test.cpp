#include <gtest/gtest.h>

#include <cstdint>
#include <type_traits>

template <typename T>
class GenericAccumulator {
public:
    void add(T value) {
        total_ += value;
    }

    T total() const {
        return total_;
    }

private:
    T total_{};
};

template <typename T>
class AccumulatorTypedTest : public ::testing::Test {
protected:
    GenericAccumulator<T> accumulator;
};

using NumericTypes = ::testing::Types<int, long long, double>;
TYPED_TEST_SUITE(AccumulatorTypedTest, NumericTypes);

TYPED_TEST(AccumulatorTypedTest, StartsAtZero) {
    EXPECT_EQ(this->accumulator.total(), static_cast<TypeParam>(0));
}

TYPED_TEST(AccumulatorTypedTest, AddsTwoValues) {
    this->accumulator.add(static_cast<TypeParam>(10));
    this->accumulator.add(static_cast<TypeParam>(5));
    EXPECT_EQ(this->accumulator.total(), static_cast<TypeParam>(15));
}
