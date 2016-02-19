#include "Manager/Manager.hpp"
#include "Encoder/x265Encoder.hpp"

int main(int argc, char**argv)
{
	Manager manager = Manager(argc, argv);

	manager.startRTSP();
	manager.startInterpretor();

	return (0);
}
