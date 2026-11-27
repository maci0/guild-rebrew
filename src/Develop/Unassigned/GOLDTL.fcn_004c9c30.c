


int __cdecl fcn_004f5940(int, int);

int __cdecl cm_ExRemoveStraftat(char* request, char* output)
{
	switch (fcn_004f5940(*(int*) (request + 0x10), *(int*) (request + 0x14))) {
	case 1:
		return 1;
	case 2:
		return 2;
	case 3:
		return 3;
	}
	if (output != 0) {
		*output = 1;
	}
	return 0;
}
