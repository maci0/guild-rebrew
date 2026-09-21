// FUNCTION: GOLD 0x00501000
// SIZE: 41
// fcn_00501000 — e=fcn_00501190(1,0,0x47); while(e && [e+0x65]!=a) e=fcn_00501030(); return e.

int __cdecl fcn_00501190(int, int, int);
int __cdecl fcn_00501030(void);

int __cdecl fcn_00501000(int a)
{
	char* e;
	e = (char*) fcn_00501190(1, 0, 0x47);
	while (e != 0 && *(int*) (e + 0x65) != a) {
		e = (char*) fcn_00501030();
	}
	return (int) e;
}
