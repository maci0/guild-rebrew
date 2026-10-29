extern int g_772ea4;
extern int g_774654;

int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_0052ae80(void);
char* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_004cf180(void);
int __cdecl fcn_004cf6b0(void);
void __cdecl fcn_004d0070(void);

struct slot_4d4640 {
	int id;
	int active;
	char pad8[0x24];
};
// SIZE 0x2c


/* ADDRESS: GOLDTL 0x004d4640 */
void __cdecl fcn_004d4640(char* a1)
{
	struct slot_4d4640* s;
	char* r;
	int busy;
	int i;

	while (g_772ea4 == 0 && fcn_005373e0(fcn_004d4640, 0x7d6c6) != 0) {
		fcn_0052ae80();
		busy = 0;
		for (i = 0; i < 16; i++) {
			s = (struct slot_4d4640*) (a1 + 0x94) + i;
			if (s->active != 0 && s->id != -1) {
				r = gm_LookupEntityRecordById(s->id);
				if (r != 0 && *(char**) (r + 0x184) != 0
				    && *(int*) (*(char**) (r + 0x184) + 0x128) != 0) {
					busy = 1;
					break;
				}
			}
		}
		if (fcn_004cf180() != 0)
			busy = 1;
		if (fcn_004cf6b0() != 0)
			busy = 1;
		fcn_004d0070();
		if (busy == 0)
			g_774654 = 1;
	}
}
