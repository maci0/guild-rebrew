extern char g_7f4c00[];

char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_00500bb0(char*, int, int, int);
int __cdecl fcn_004c5620(int, char*);
void __cdecl fcn_004c4eb0(char*);
void __cdecl fcn_004c4ef0(char*);
int __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_004c54c0(int, int, int, int);

/* ADDRESS: GOLDTL 0x00556a20 */
void __cdecl fcn_00556a20(char* p)
{
	char* a;
	char* b;
	int* q;

	a = gm_LookupEntityRecordById(*(int*) (p + 0xb0));
	b = gm_LookupEntityRecordById(*(int*) (p + 0xac));
	if (*(unsigned char*) (p + 0x78) & 4) {
		return;
	}
	q = (int*) (p + 0x52);
	q[0] = *(int*) ((char*) g_7f4c00);
	q[1] = *(int*) ((char*) g_7f4c00 + 4);
	q[2] = *(int*) ((char*) g_7f4c00 + 8);
	*(short*) (q + 3) = *(short*) ((char*) g_7f4c00 + 0xc);
	fcn_00500bb0((char*) q, 0, 1, 0);
	if (a == 0) {
		*(int*) (p + 0x84) = fcn_004c5620(-1, p);
		return;
	}
	if (*(int*) (a + 0x1c8) & 0x800000) {
		*(int*) (p + 0x84) = fcn_004c5620(-1, p);
		return;
	}
	fcn_004c4eb0("Alloc_Geliebte");
	fcn_004c5420(*(int*) (a + 4), 0x1c8, 4, 0x800000, 0);
	fcn_004c54c0(*(int*) (b + 4), *(int*) (a + 4), 0x32, 1);
	fcn_004c4ef0("Alloc_Geliebte AI");
	*(int*) (p + 0xb4) = 0;
	*(int*) (p + 0xb8) = 2;
	*(int*) (p + 0xbc) = -1;
	*(int*) (p + 0x84) = fcn_004c5620(2, p);
}
