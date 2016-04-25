#include <iostream>
#include <string>
#include "gtest/gtest.h"

#include "opencv2/core/core.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/imgcodecs.hpp"

#include "Parser/YAMLParser.hpp"

using namespace std;
using namespace cv;

namespace {

	class YamlTest : public ::testing::Test {
	protected:
		YAMLParser *parser;

		YamlTest() {
    // You can do set-up work for each test here.
		}

		virtual ~YamlTest() {
    // You can do clean-up work that doesn't throw exceptions here.
		}

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods

		virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
			this->parser= new YAMLParser("config/resolutions.yml" , FileStorage::READ);
		}

		virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
		}

  // Objects declared here can be used by all tests in the test case for Foo.
	};

	TEST_F(YamlTest, ParserOpening) {
		ASSERT_TRUE(this->parser->isOpened());
	}

	TEST_F(YamlTest, ParserPamaters)
	{
		int width  	= this->parser->getValueOf("width");
		int height 	= this->parser->getValueOf("height");
		int fps 	= this->parser->getValueOf("fps");

		ASSERT_EQ(width,1280);
		ASSERT_EQ(height,720);
		ASSERT_EQ(fps,30);

	}
}  // namespace
