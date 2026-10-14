

// SIZE 0x70
typedef struct Item {
	char pad[0x54];
	unsigned char flags;
	char pad2[0x1b];
} Item;

extern char* g_104049c;
extern unsigned int g_10404a0;
extern int g_67a370;

void __cdecl fcn_00437ac0(int, int, int, void*);
void __cdecl fcn_00443270(void);

void __cdecl fcn_00443230(void)
{
	unsigned int i;

	for (i = 0; i < g_10404a0; i++) {
		((Item*)g_104049c)[i].flags &= 0xbf;
	}
	fcn_00437ac0(g_67a370, 0, 0x40, fcn_00443270);
}
