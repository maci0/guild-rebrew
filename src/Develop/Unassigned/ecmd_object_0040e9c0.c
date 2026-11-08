extern char* g_6b7e98;
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);
int __cdecl fcn_00412b10(char* e, float x, float y, float z, float rx, float ry, float rz, int w, int f);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);
int __cdecl fcn_00412b10(char* e, float x, float y, float z, float rx, float ry, float rz, int w, int f);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);
int __cdecl fcn_00412b10(char* e, float x, float y, float z, float rx, float ry, float rz, int w, int f);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);
int __cdecl fcn_00412b10(char* e, float x, float y, float z, float rx, float ry, float rz, int w, int f);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);
void __cdecl fcn_00442d90(char* e, int v);
void __cdecl fcn_00425bf0(char* g, int h, const char* msg);

/* ADDRESS: GOLDTL 0x0040e9c0 */
int __cdecl ecmd_SetAngle(char** a, float* x, float* y, float* z)
{
	if (*a != 0) {
		*(float*) (*a + 0x84) = *x * 0.017453292f;
		*(float*) (*a + 0x88) = *y * 0.017453292f;
		*(float*) (*a + 0x8c) = *z * 0.017453292f;
		*(unsigned char*) (*a + 0x214) |= 4;
		return 0;
	}
	fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
	return 0;
}

/* ADDRESS: GOLD 0x0040db30 */
/* ADDRESS: GOLDTL 0x0040ea40 */
int __cdecl ecmd_MoveObject(char** a, int* x, int* y, int* z, int* w)
{
	if (*a != 0) {
		fcn_00412b10(*a, (float) *x, (float) *y, (float) *z, *(float*) (*a + 0x84),
			     *(float*) (*a + 0x88), *(float*) (*a + 0x8c), *w, 0);
		return 0;
	}
	fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
	return 0;
}

/* ADDRESS: GOLD 0x0040dbb0 */
/* ADDRESS: GOLDTL 0x0040eac0 */
char** __cdecl ecmd_RotateObject(char** a, int* x, int* y, int* z, int* w)
{
	if (*a != 0) {
		fcn_00412b10(*a, *(float*) (*a + 0x4c), *(float*) (*a + 0x50), *(float*) (*a + 0x54),
			     *x * 0.017453292f, *y * 0.017453292f, *z * 0.017453292f, *w, 0);
		return a;
	}
	fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
	return a;
}

/* ADDRESS: GOLD 0x0040dc30 */
/* ADDRESS: GOLDTL 0x0040eb40 */
int __cdecl ecmd_MoveObjectRelative(char** a, int* x, int* y, int* z, int* w)
{
	if (*a != 0) {
		fcn_00412b10(*a, *x + *(float*) (*a + 0x4c), *y + *(float*) (*a + 0x50),
			     *z + *(float*) (*a + 0x54), *(float*) (*a + 0x84), *(float*) (*a + 0x88),
			     *(float*) (*a + 0x8c), *w, 0);
		return 0;
	}
	fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
	return 0;
}

/* ADDRESS: GOLD 0x0040dcb0 */
/* ADDRESS: GOLDTL 0x0040ebc0 */
int __cdecl ecmd_RotateObjectRelative(char** a, int* x, int* y, int* z, int* w)
{
	if (*a != 0) {
		fcn_00412b10(*a, *(float*) (*a + 0x4c), *(float*) (*a + 0x50), *(float*) (*a + 0x54),
			     *x * 0.017453292f + *(float*) (*a + 0x84),
			     *y * 0.017453292f + *(float*) (*a + 0x88),
			     *z * 0.017453292f + *(float*) (*a + 0x8c), *w, 0);
		return 1;
	}
	fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
	return 1;
}

/* ADDRESS: GOLD 0x0040ddb0 */
/* ADDRESS: GOLDTL 0x0040ecc0 */
int __cdecl ecmd_ReplaceObject(char** a, int* v)
{
	if (*a != 0) {
		fcn_00442d90(*a, *v);
		return 1;
	}
	fcn_00425bf0(g_6b7e98, *(int*) (g_6b7e98 + 0x118), "invalid object");
	return 1;
}
