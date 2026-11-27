

void __cdecl d2_UpdateRoutePointImage(void*);

void __cdecl fcn_004bfc10(void)
{
	int a;

	for (a = 0x10058a0; a < 0x10058e0; a += 8) {
		if (*(int*) a != -1) {
			d2_UpdateRoutePointImage((void*) a);
		}
	}
}
