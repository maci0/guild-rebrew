


extern char g_7f4ca0[];
void* __cdecl gm_LookupEntityRecordById(int);
int  __cdecl fcn_004a55c0(void*, int, int*, float, float, unsigned short*);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl io_FormatTextBuffer(void*, int, int, int);
void __cdecl he_PostEntityMessage(int, int, void*, int, int, int);

int __cdecl gm_HandleMsg16BoostFavor(void* request)
{
	char buf[0x400];
	int d2;
	unsigned short w1;
	void* p;
	void* e;
	int n;

	p = gm_LookupEntityRecordById(*(int*) request);
	if (p == 0) {
		return 1;
	}
	d2 = 0x600c00;
	if (fcn_004a55c0(p, 1, &d2, 33.0f, 100.0f, &w1) == 0) {
		return 0x400;
	}
	e = (void*) ((int) g_7f4ca0 + 540 * w1);
	n = 2 * gm_RandomMod(5) + 6;
	cm_RequestCopyEntityData(*(int*) ((char*) p + 4), *(int*) ((char*) e + 4), n, 1);
	io_FormatTextBuffer(buf, *(unsigned short*) ((char*) request + 4) + 0x12e7,
	    *(unsigned short*) e, *(unsigned short*) e);
	he_PostEntityMessage(*(int*) ((char*) p + 4), *(int*) ((char*) p + 4), buf,
	    (unsigned) strlen(buf) > 0x100, 0x603, 0);
	return 0;
}
