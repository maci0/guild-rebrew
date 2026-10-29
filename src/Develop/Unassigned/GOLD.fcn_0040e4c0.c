
// fcn_0040e4c0 — fcn_005de800(a, arg2); if(r) fcn_00411b70(a); return 1.

int __cdecl fcn_005de800(void*, void*);
int __cdecl fcn_00411b70(void*);

char __cdecl fcn_0040e4c0(void* a, void* b)
{
	if (fcn_005de800(a, b) != 0) {
		fcn_00411b70(a);
	}
	return 1;
}
