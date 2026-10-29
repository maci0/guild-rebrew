extern int g_7e46ac;



char* __cdecl fcn_00426cc0(int);
void __cdecl fcn_005373e0(int, unsigned int);

void __cdecl fcn_005312d0(int a)
{
	unsigned int fl;
	char* r;

	fl = ((*(unsigned int*)&g_7e46ac) & 0xffffff3f) | 0x100200;
	for (r = fcn_00426cc0(a); r != 0 && (r[0x124] & 1) != 0; r = fcn_00426cc0(a)) {
		fcn_005373e0(0, fl);
	}
}
