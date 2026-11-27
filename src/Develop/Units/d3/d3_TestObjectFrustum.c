

// SIZE 0x1
typedef struct Res {
	unsigned char lo : 6;
	unsigned char b6 : 1;
	unsigned char b7 : 1;
} Res;

typedef int (__cdecl* D3_BBOX_QUERY_FN)(char*, char*, int);

Res __cdecl d3_TestBoxAgainstFrustum(int, char*, char*);

Res __cdecl d3_TestObjectFrustum(char* a, char* b, int c)
{
	Res r;
	char* t;
	int v;

	if ((a[0x215] & 0x10) != 0) {
		r.lo = 0x3f;
		r.b6 = 0;
		return r;
	}
	v = 0;
	if (b != 0 && (t = *(char**) (b + 0x318)) != 0) {
		v = (*(D3_BBOX_QUERY_FN*) (t + 0x1f0))(a, b, c);
	}
	if (v == 0) {
		r.b6 = 1;
		return r;
	}
	return d3_TestBoxAgainstFrustum(v, *(char**) (a + 0x1ec) + 0x88, *(char**) (a + 0x1ec) + 0x8c);
}
