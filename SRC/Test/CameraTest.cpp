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
		}

		virtual ~CameraTest() {
		}

		virtual void SetUp() {

			this->camera = new Camera(0);
			this->camera->initCamera();		}

			virtual void TearDown() {

				delete this->camera;
			}

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

		TEST_F(CameraTest, RetrieveFrame) {
			ASSERT_TRUE(this->camera->retrieveFrame());
		}

		TEST_F(CameraTest, GrabFrame) {
			ASSERT_TRUE(this->camera->grabFrame());
		}

		TEST_F(CameraTest, ReOpenCamera) {
			ASSERT_TRUE(this->camera->reOpenCamera());
		}

}  // namespace
