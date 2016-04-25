#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "Video/Camera.hpp"

using namespace std;
using namespace cv;

namespace {

	class CameraTest : public ::testing::Test {
	protected:
		Camera *camera;

		CameraTest() {
    // You can do set-up work for each test here.
		}

		virtual ~CameraTest() {
    // You can do clean-up work that doesn't throw exceptions here.
		}

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods

		virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
			this->camera = new Camera(0);
		}

		virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
		}

		bool OpenCamera(int id) {
			return (new Camera(id))->initCamera();
		}

  // Objects declared here can be used by all tests in the test case for Foo.
	};

	TEST_F(CameraTest, CameraOpeningOk) {
		ASSERT_TRUE(this->camera->initCamera());
	}

	TEST_F(CameraTest, CameraOpeningFailed) {
		ASSERT_FALSE(this->OpenCamera(0));
	}

	// TEST_F(CameraTest, ParserPamaters)
	// {
	// 	// int width  	= this->parser->getValueOf("width");
	// 	// int height 	= this->parser->getValueOf("height");
	// 	// int fps 	= this->parser->getValueOf("fps");

	// 	// ASSERT_EQ(width,1280);
	// 	// ASSERT_EQ(height,720);
	// 	// ASSERT_EQ(fps,30);

	// }
}  // namespace
