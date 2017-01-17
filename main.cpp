#include "bistro.hpp"

int main(int argc, char **argv)
{
	if (argc == 2){
		Bistro bistro(argv[1]);
		bistro.stacking();
		bistro.calcul();
	}
	return 0;
}