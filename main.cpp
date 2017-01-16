#include "bistro.hpp"

int main(int argc, char **argv)
{
	if (argc == 2){
		Bistro calcul(argv[1]);
		calcul.stacking();
	}
	return 0;
}