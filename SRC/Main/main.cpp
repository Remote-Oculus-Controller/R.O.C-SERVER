#include "Manager/Manager.hpp"

int main(int argc, char**argv)
{
	Manager manager = Manager(argc, argv);

	manager.startRTSP();
	manager.startInterpretor();

	return (0);
}
