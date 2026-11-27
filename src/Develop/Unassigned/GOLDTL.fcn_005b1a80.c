#include "g_774a78.h"

extern Node* g_774a78;


/* ADDRESS: GOLDTL 0x005b1a80 */
char* __cdecl hp_FindProdSettingNode(int key)
{
	char* p;

	p = (char*) g_774a78;
	while (p != 0) {
		if (*(int*) p == key) {
			return p;
		}
		p = *(char**) (p + 0x48);
	}
	return 0;
}

void __cdecl hp_UpdateProdSetting(int a, char* o);


/* ADDRESS: GOLDTL 0x005b1e20 */
void __cdecl hp_SyncProdSetting(char* p)
{
	char* o;

	o = hp_FindProdSettingNode(*(int*) (p + 1));
	if (o != 0) {
		hp_UpdateProdSetting((int) p, o);
	}
}

float __cdecl gm_NextLCGFloat(char* o);
extern float g_662cf8;


/* ADDRESS: GOLDTL 0x005b1e40 */
int __cdecl hp_PickWeightedProdItem(char* p)
{
	char* o;
	int thr;
	int k;
	int res;
	int sum;
	int* e;

	o = hp_FindProdSettingNode(*(int*) (p + 1));
	if (o == 0) {
		return 0;
	}
	thr = (int) (gm_NextLCGFloat(o) * g_662cf8);
	k = 0;
	res = 0;
	sum = 0;
	e = (int*) (o + 0xc);
	for (; k < 7; k++, e += 2) {
		if (res != 0) {
			break;
		}
		if (e[0] != 0) {
			sum += *(unsigned char*) (e + 1);
			if (*(unsigned char*) (e + 1) != 0 && thr < sum) {
				res = e[0];
			}
		}
	}
	return res;
}
