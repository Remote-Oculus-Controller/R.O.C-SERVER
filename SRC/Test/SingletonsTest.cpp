#include <iostream>
#include <string>

#include "gtest/gtest.h"
#include "Video/Camera.hpp"
#include "Singletons/VideoManagerSingleton.hpp"

using namespace std;
using namespace cv;

namespace {

	class SingletonTest : public ::testing::Test {
	protected:
		

		SingletonTest() {
		}

		virtual ~SingletonTest() {
		}

		virtual void SetUp() {

		}

		virtual void TearDown() {

		}

	};

	TEST_F(SingletonTest, VideoManagerSingletonGetInstance) {
		ASSERT_TRUE(VideoManagerSingleton::getInstance() != NULL);
	}

}  // namespace
