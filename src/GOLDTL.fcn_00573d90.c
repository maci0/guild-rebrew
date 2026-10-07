// FUNCTION: GOLD 0x0056b9a0
// FUNCTION: GOLDTL 0x00573d90

extern double g_665e30;

typedef struct {
	float x;
	int y;
	int z;
} Vec573d90;
// SIZE 0xc

void __cdecl fcn_00412cf0(char*, char*, Vec573d90*, int, int);

void __cdecl fcn_00573d90(char* e, char* b)
{
	Vec573d90 v;

	v.x = *(float*) (e + 0x84) + g_665e30;
	v.y = *(int*) (e + 0x88);
	v.z = *(int*) (e + 0x8c);
	fcn_00412cf0(e, e + 0x4c, &v, 0x46, 0x20);
	b[0xd0]--;
}
