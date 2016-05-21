#include "Logger/Logger.hpp"
#include "Manager/Manager.hpp"
#include "Parser/ConfigParser.hpp"

int main(int argc, char**argv)
{
	logger::log(START_SERVER 	, logger::logType::INFO);

	if (configuration::loadConfig() == false) {
		return 1;
	}

	Manager manager = Manager();

	if (manager.startVideoManager() == false) {
		logger::log(ERROR_VIDEOMANAGER , logger::logType::FAILURE);
		return 2;
	}

	if (manager.startRTSP() == false) {
		logger::log(ERROR_RTSP , logger::logType::FAILURE);
		return 3;
	}

	if (manager.startInterpretor() == false) {
		logger::log(ERROR_INTERPRETOR , logger::logType::FAILURE);
		return 4;
	}

	return 0;
}
