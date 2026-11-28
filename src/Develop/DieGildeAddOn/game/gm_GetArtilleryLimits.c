


int __cdecl gm_QueryEntities(int a, int b, int c, int d, int e);

void __cdecl gm_GetArtilleryLimits(char* p, int* a, int* b)
{
	*b = 0;
	*a = 0;
	if (gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x265)) {
		*a = 2;
	} else {
		*a = gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x263) != 0;
	}
	if (gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x264)) {
		*b = 4;
	} else if (gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x262)) {
		*b = 3;
	} else if (gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x25e)) {
		*b = 2;
	} else {
		*b = gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x25a) != 0;
	}
}
