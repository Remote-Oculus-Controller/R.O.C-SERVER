#include "Manager/Manager.hpp"

int main(int argc, char**argv)
{
	Manager manager = Manager(argc, argv);

	if (manager.startVideoManager() == false)
		return 1;
	if (manager.startRTSP() == false)
		return 2;
	if (manager.startInterpretor() == false)
		return 3;

	return 0;
}
