#include <gtest/gtest.h>
#include <grayt/utils/Color.h>
using namespace grayt::utils;
namespace {
  class ColorTest : public ::testing::Test {
  protected:
    ColorTest() : color_default(), color_args(1.0,2.0,3.0,1.0) {
      // You can do set-up work for each test here.
    }

    virtual ~ColorTest() {
      // You can do clean-up work that doesn't throw exceptions here
    }

    // If the constructor and destructor are not enough for setting up
    // and cleaning up each test, you can define the following methods:

    virtual void SetUp() {
      // code here will be called immediately after the constructor
      // (right before each test).
    }

    virtual void TearDown() {
      // Code here will be called immediately after each test
      // (right before the destructor).
    }


    // Objects declared here can be  used by all tests in the test
    // case for ColorTest
    Color color_args;
    Color color_default;

  };


  TEST_F(ColorTest, TrivialCases) {
    EXPECT_TRUE(color_default.red == color_default.red);
    EXPECT_TRUE(color_default.green == color_default.green);
    EXPECT_TRUE(color_default.blue == color_default.blue);
    EXPECT_TRUE(color_default.alpha == color_default.alpha);

    EXPECT_TRUE(color_args.red == color_args.red);
    EXPECT_TRUE(color_args.green == color_args.green);
    EXPECT_TRUE(color_args.blue == color_args.blue);
    EXPECT_TRUE(color_args.alpha == color_args.alpha);


  }

  TEST_F(ColorTest, ValuesCorrect) {
    EXPECT_EQ(0.0, color_default.red);
    EXPECT_EQ(0.0, color_default.green);
    EXPECT_EQ(0.0, color_default.blue);
    EXPECT_EQ(0.0, color_default.alpha);

    EXPECT_EQ(1.0, color_args.red);
    EXPECT_EQ(2.0, color_args.green);
    EXPECT_EQ(3.0, color_args.blue);
    EXPECT_EQ(1.0, color_args.alpha);

  }

}
