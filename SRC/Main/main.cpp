#include "Manager/Manager.hpp"

int main(int argc, char**argv)
{
	Manager manager = Manager(argc, argv);

	if (manager.startRTSP() == false)
		return 1;
	manager.startInterpretor();

	return 0;
}
