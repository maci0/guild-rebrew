#include <string.h>
#include <stdlib.h>

/* SIZE 0x80 */
typedef struct {
	unsigned short id;
	char pad2[2];
	int active;
	char pad8[0x20 - 8];
	float base;
	float price;
	char pad28[0x38 - 0x28];
	float value;
	char pad3c[0x80 - 0x3c];
} Ent80;

extern char g_85ab90[];
extern char* lpObjektePROT;
extern unsigned char g_773d75;

int __cdecl fcn_0064eeec(char*);
char* __cdecl fcn_004ce590(int);
float __cdecl eval_ObjektPreis2Credits(int, int);
void __cdecl fcn_004c6190(char*, char);

/* ADDRESS: GOLDTL 0x004b1320 */
int __cdecl fcn_004b1320(int a1, int a2, char* a3)
{
	float f;
	float factor;

	if (*a3 != '-')
		return 0;
	{
		int sign[2] = { -1, 1 };
		char names[2][6] = { "MINUS", "PLUS" };
		char cats[3][12] = { "WAFFEN", "BUECHER", "ENDPRODUKTE" };
		Ent80 copy;
		int amount;
		int i;
		int j;
		char* row;
		char* p;

		a3++;
		for (i = 0; i < 2; i++) {
			if (memcmp(a3, names[i], strlen(names[i])) == 0)
				break;
		}
		if (i >= 2)
			return 0;
		sign[0] = sign[i];
		a3 += strlen(names[i]);
		if (*a3 != '_')
			return 0;
		a3++;
		for (j = 0; j < 3; j++) {
			if (memcmp(a3, cats[j], strlen(cats[j])) == 0)
				break;
		}
		if (j >= 3)
			return 0;
		a3 += strlen(cats[j]);
		if (*a3 != '_')
			return 0;
		a3++;
		amount = atoi(a3) * sign[1];
		{
			factor = sign[0] * 0.01;
			if (j == 0) {
				f = factor + 1.0f;
				for (i = 0; i < 0x2a80; i += 0x80) {
					row = g_85ab90 + g_773d75 * 0x681c0 + i;
					if (*(unsigned short*) row == 0)
						continue;
					if (*(int*) (row + 4) == 0)
						continue;
					p = fcn_004ce590(*(unsigned short*) row);
					if (p == 0 || *(int*) p == 0)
						continue;
					copy = *(Ent80*) row;
					copy.price = copy.base * f;
					copy.value = eval_ObjektPreis2Credits(*(unsigned short*) row, 0x64) * f;
					fcn_004c6190((char*) &copy, g_773d75);
				}
				return 1;
			}
			if (j == 1) {
				f = factor + 1.0f;
				for (i = 0; i < 0x2a80; i += 0x80) {
					row = g_85ab90 + g_773d75 * 0x681c0 + i;
					if (*(unsigned short*) row == 0)
						continue;
					if (*(int*) (row + 4) == 0)
						continue;
					if (*(char*) (lpObjektePROT + *(unsigned short*) row * 0x40) != 8)
						continue;
					copy = *(Ent80*) row;
					copy.price = copy.base * f;
					copy.value = eval_ObjektPreis2Credits(*(unsigned short*) row, 0x64) * f;
					fcn_004c6190((char*) &copy, g_773d75);
				}
				return 1;
			}
			if (j == 2) {
				f = factor + 1.0f;
				for (i = 0; i < 0x2a80; i += 0x80) {
					row = g_85ab90 + g_773d75 * 0x681c0 + i;
					if (*(unsigned short*) row == 0)
						continue;
					if (*(int*) (row + 4) == 0)
						continue;
					if (*(char*) (lpObjektePROT + *(unsigned short*) row * 0x40) != 0x20)
						continue;
					copy = *(Ent80*) row;
					copy.price = copy.base * f;
					copy.value = eval_ObjektPreis2Credits(*(unsigned short*) row, 0x64) * f;
					fcn_004c6190((char*) &copy, g_773d75);
				}
			}
		}
	}
	return 1;
}
