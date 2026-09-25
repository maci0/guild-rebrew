extern int g_7749d4;
extern char g_7f4c00[];
extern void (__cdecl* g_7dc440[])(unsigned char*);

// SIZE 0x14c
struct s_77e980 {
	unsigned char b0;
	char pad[0x51];
	char f52[0x26];
	unsigned char b78;
	char pad2[0xd3];
};

extern struct s_77e980 g_77e980[1024];

// FUNCTION: GOLDTL 0x546d10
// SIZE: 117

void __cdecl fcn_00546b40(void);
void __cdecl fcn_00546850(struct s_77e980*);
int __cdecl fcn_00500cb0(char*, char*);
void __cdecl fcn_00546be0(struct s_77e980*);

void __cdecl fcn_00546d10(void)
{
	int i;

	fcn_00546b40();
	for (i = 0; i <= g_7749d4 && i < 1024; i++) {
		if (g_77e980[i].b0 != 0 && (g_77e980[i].b78 & 0x18) == 0) {
			fcn_00546850(&g_77e980[i]);
			if (fcn_00500cb0(g_7f4c00, g_77e980[i].f52) > 0 && g_77e980[i].b0 < 0xa7) {
				fcn_00546be0(&g_77e980[i]);
				g_7dc440[g_77e980[i].b0](&g_77e980[i].b0);
			}
		}
	}
}
