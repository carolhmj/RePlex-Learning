#include <gtest/gtest.h>

TEST(SillyTest, IsFourPositive) {
	EXPECT_GT(4, 0);
};

TEST(SillyTest, IsFourTimesFourSixteen) {
	int x = 4;
	EXPECT_EQ(x * x, 16);
}

int main(int argc, char** argv) {
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}