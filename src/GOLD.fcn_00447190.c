
// fcn_00447190 — if(a){ fcn_0043d0e0(a); fcn_0043c7a0(a); return 1; } return 0.

int __cdecl fcn_0043d0e0(int);
int __cdecl fcn_0043c7a0(int);

int __cdecl fcn_00447190(int a)
{
	if (a != 0) {
		fcn_0043d0e0(a);
		fcn_0043c7a0(a);
		return 1;
	}
	return 0;
}
