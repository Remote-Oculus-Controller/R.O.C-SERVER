#ifndef MANAGER_HPP
#define MANAGER_HPP

#include "RTSPFactory/RTSPFactory.hpp"
#include "Interpretor/Reader.hpp"

class Manager
{
	public:
	
	Manager(int argc, char **argv);
	~Manager();

	bool startRTSP();
	bool stopRTSP();

	bool startInterpretor();
	bool stopInterpretor();

	private:

	RTSPFactory _RTSPFactory;
	Reader 		_reader;

	// TCP Server 	(get and send commands)
	// Interpretor
	// Controls

	int 		_argc;
	char **		_argv;

};

#endif // MANAGER_HPP
