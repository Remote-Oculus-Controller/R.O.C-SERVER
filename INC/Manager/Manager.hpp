#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "RTSPFactory/RTSPFactory.hpp"
#include "Interpretor/Reader.hpp"
#include "Parser/YAMLParser.hpp"
#include "Singletons/VideoManagerSingleton.hpp"

#define VIDEO_MANAGER_CONFIG_FILE "config/resolutions.yml"

class Manager
{
	public:

	Manager(int argc, char **argv);
	~Manager();

	bool startRTSP();
	bool stopRTSP();

	bool startVideoManager();
	bool stopVideoManager();

	bool startInterpretor();
	bool stopInterpretor();

	private:

	RTSPFactory _RTSPFactory;
	Reader 		_reader;
	VideoManager * _videoHandler;

	// TCP Server 	(get and send commands)
	// Interpretor
	// Controls

	int 		_argc;
	char **		_argv;

};

#endif // MANAGER_HPP
