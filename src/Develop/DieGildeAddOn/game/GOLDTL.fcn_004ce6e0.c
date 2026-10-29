


extern unsigned char g_773d75;

unsigned short* __cdecl fcn_00502cd0(int, int, int);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_004ce590(int);
int __cdecl fcn_004c51f0(int, int, int, int, char, int);

void __cdecl fcn_004ce6e0(char* a1)
{
	unsigned short* p;
	int id;

	for (p = fcn_00502cd0(*(int*) (a1 + 0x178), 1, 5); p != 0; p = gm_NextEntityQueryMatch()) {
		id = *p;
		if (fcn_004ce590(id) != 0) {
			fcn_004c51f0(-1, *(int*) (a1 + 4), id, *(int*) ((char*) p + 0xe), (*(char*)&g_773d75), 0);
		}
	}
}
