void __cdecl fcn_00418e90(char*, int, char*);

typedef struct Vec4Words {
	int a;
	int b;
	int c;
	int d;
} Vec4Words;

typedef int (__stdcall* ObjFn)(void*, int, Vec4Words*, int, int, float, int);

/* ADDRESS: GOLD 0x00435fb0 */
void __cdecl fcn_00435fb0(void)
{
	Vec4Words v;
	void* obj;
	unsigned char first;
	unsigned char second;
	int mask;
	int r;

	first = *(unsigned char*) 0x631223;
	second = *(unsigned char*) 0x631222;
	if (first != 0 && second != 0) {
		return;
	}
	mask = 0;
	if (*(int*) 0x633420 != 0 && first == 0) {
		mask = 2;
	}
	if (*(int*) 0x631208 != 0 && second == 0) {
		mask |= 1;
	}
	if (mask != 0) {
		v.a = *(int*) 0xfc2930;
		v.b = *(int*) 0xfc2934;
		v.c = *(int*) 0xfc2938;
		v.d = *(int*) 0xfc293c;
		obj = *(void**) 0x63341c;
		r = ((ObjFn) *(void**) (*(int*) obj + 0x50))(obj, 1, &v, mask, *(int*) 0x6334a0, 1.0f, 0);
		*(int*) 0x14661a4 = r;
		if (r != 0) {
			fcn_00418e90((char*) 0x5f944c, 0x145, (char*) 0x5f9570);
		}
	}
	*(unsigned char*) 0x631222 = 1;
	*(unsigned char*) 0x631223 = 1;
}
