#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "Video/Camera.hpp"
#include "Network/LiveSourceWithx264.hpp"
using namespace std;
using namespace cv;

namespace {

	class EncoderTest : public ::testing::Test {
	protected:
		Camera *camera;
		x264Encoder *encoder;

		EncoderTest() {
		}

		virtual ~EncoderTest() {
		}

		virtual void SetUp() {

			this->camera = new Camera(0);
			this->camera->initCamera();
		}

			virtual void TearDown() {

				delete this->camera;
			}

		};

		TEST_F(EncoderTest, Initilize) {
			this->encoder = new x264Encoder(this->camera->getWidth(),
				this->camera->getHeight(),
				this->camera->getFps());
			ASSERT_TRUE(this->encoder->initilize());
		}

		TEST_F(EncoderTest, Encoder) {
			this->encoder = new x264Encoder(this->camera->getWidth(),
				this->camera->getHeight(),
				this->camera->getFps());
			this->encoder->initilize();

			this->camera->grabFrame();
			this->camera->retrieveFrame();

			this->encoder->encodeFrame(this->camera->getFrame());
			ASSERT_TRUE(encoder->isNalsAvailableInOutputQueue());

		}
}  // namespace
