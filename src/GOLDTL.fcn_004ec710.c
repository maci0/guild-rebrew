// FUNCTION: GOLD 0x004ea990
// FUNCTION: GOLDTL 0x004ec710

typedef struct
{
	int id;
	unsigned char kind;
	char pad[0x13];
} Rec18;
// SIZE 0x18

typedef struct
{
	char pad[8];
	int x8;
	char pad2[0xc];
} Tab18;
// SIZE 0x18

extern Rec18 g_9a9224[42];
extern Tab18 g_68da6c[];
extern float g_665264[];

void __cdecl fcn_004f4830(int kind, int* out);

int __cdecl fcn_004ec710(void)
{
	int buf[9];
	int mult;
	int total;
	int i;

	fcn_004f4830(0xf, buf);
	mult = (int) g_665264[buf[6]];
	total = 0;
	for (i = 0; i < 42; i++) {
		if (g_9a9224[i].id != -1) {
			total += (int) ((float) (g_68da6c[g_9a9224[i].kind].x8 << 5) * mult);
		}
	}
	return total;
}
