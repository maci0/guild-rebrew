// FUNCTION: GOLD 0x00501400
// SIZE: 176
// FUNCTION: GOLDTL 0x00504250
// SIZE: 176

#pragma pack(push, 1)
typedef struct
{
	unsigned char k;
	unsigned short ids[10];
} Rec15;
// SIZE 0x15
#pragma pack(pop)

extern Rec15 g_699058[37];

char* __cdecl fcn_00502cd0(int list, int a, int b, int c, ...);
char* __cdecl fcn_00502fe0(int a, int b, int c);

void __cdecl fcn_00504250(unsigned char* e)
{
	char* o;
	int i;
	int j;

	for (i = 0; i < 37; i++) {
		if (e[0] == g_699058[i].k) {
			o = fcn_00502cd0(*(int*) (e + 0x5d), 2, 6, 0, 0xff);
			if (o == 0) {
				o = fcn_00502fe0(*(int*) (e + 1), 0xff, 1);
				if (o == 0) {
					continue;
				}
			}
			for (j = 0; j < 10; j++) {
				if (g_699058[i].ids[j] != 0 && !fcn_00502cd0(*(int*) (o + 0x14), 1, 0, g_699058[i].ids[j])) {
					fcn_00502fe0(*(int*) (o + 2), g_699058[i].ids[j], 2);
				}
			}
		}
	}
}
