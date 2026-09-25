// FUNCTION: GOLD 0x004ced80
// SIZE: 53
// FUNCTION: GOLDTL 0x4cfc00
// SIZE: 53

typedef struct
{
	char pad[0x188];
	char active;
	char tail[0x93];
} Ent21c;
// SIZE 0x21c

extern Ent21c g_9b4a40[32];

void __cdecl fcn_004cfa80(void);
void __cdecl fcn_004cfab0(int, Ent21c*);

void __cdecl fcn_004cfc00(int a1)
{
	Ent21c* e;

	fcn_004cfa80();
	for (e = g_9b4a40; (int) e < (int) (g_9b4a40 + 32); e++) {
		if (e->active != 0) {
			fcn_004cfab0(a1, e);
		}
	}
}
