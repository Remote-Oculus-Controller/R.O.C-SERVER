#include "Logger/Logger.hpp"
#include "Manager/Manager.hpp"
#include "Parser/ConfigParser.hpp"

int main(int argc, char**argv)
{
	logger::log(START_SERVER 	, logger::logType::INFO);

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

	if (manager->startTcpServer() == false) {
		logger::log(ERROR_TCP , logger::logType::FAILURE);
		logger::waitSync();
		return 4;
	}

	if (manager->startInterpretor() == false) {
		logger::log(ERROR_INTERPRETOR , logger::logType::FAILURE);
		logger::waitSync();
		return 5;
	}

	delete manager;

	logger::log(STOP_SERVER , logger::logType::INFO);
	logger::waitSync();

	return 0;
}
