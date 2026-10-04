#include <gtest/gtest.h>

namespace {
int GetMeaningOfLife() { return 42; }
} // namespace

TEST(pointless_ass_test, test_equality) { EXPECT_EQ(GetMeaningOfLife(), 40) << "ERROR OH NO!"; }
