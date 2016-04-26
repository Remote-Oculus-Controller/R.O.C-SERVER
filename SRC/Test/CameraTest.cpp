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
        delete this->camera;
		}

		bool OpenCamera(int id) {
			return (new Camera(id))->initCamera();
		}

  // Objects declared here can be used by all tests in the test case for Foo.
	};

	TEST_F(CameraTest, CameraOpening) {
		ASSERT_TRUE(this->camera->initCamera());
	}

	TEST_F(CameraTest, CameraParameters)
	{
		int width  	= this->camera->getWidth();
		int height 	= this->camera->getHeight();
		int fps 	= this->camera->getFps();

		ASSERT_EQ(width,1280);
		ASSERT_EQ(height,720);
		ASSERT_EQ(fps,30);

	}
}  // namespace
