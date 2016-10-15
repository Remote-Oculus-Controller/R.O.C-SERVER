#include <stdlib.h>

#include "Logger/Logger.hpp"
#include "Manager/Manager.hpp"
#include "Manager/Cleanup.hpp"
#include "Parser/ConfigParser.hpp"
#include "Encoder/x265Encoder.hpp"

int main(int argc, char**argv)
{
	logger::log(START_SERVER 	, logger::logType::INFO);

	ROC_DEFER_CLEANUP;

  x265Encoder * test = new x265Encoder(640 , 480 , 30);
  test->initialize();

	Manager * manager = new Manager();

	if (configuration::loadConfig() == false) {
		logger::log(ERROR_CONFIG , logger::logType::FAILURE);
		logger::waitSync();
		return 1;
	}

	if (manager->startVideoManager() == false) {
		logger::log(ERROR_VIDEOMANAGER , logger::logType::FAILURE);
		logger::waitSync();
		return 2;
	}

	if (manager->startRTSP() == false) {
		logger::log(ERROR_RTSP , logger::logType::FAILURE);
		logger::waitSync();
		return 3;
	}

	if(manager->startNetworkManager() == false) {
		logger::log(ERROR_NETWORKMANAGER , logger::logType::FAILURE);
		logger::waitSync();
		return 4;
	}

	if (manager->startNetworkInterpretor() == false) {
		logger::log(ERROR_NETWORKINTEPRETOR , logger::logType::FAILURE);
		logger::waitSync();
		return 5;
	}
	manager->waitFlag();

	logger::log(STOP_SERVER , logger::logType::INFO);
	logger::waitSync();

	delete manager;

	return 0;
}
