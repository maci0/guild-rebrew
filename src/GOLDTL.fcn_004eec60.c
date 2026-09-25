// FUNCTION: GOLD 0x004ece60
// SIZE: 176
// FUNCTION: GOLDTL 0x004eec60
// SIZE: 176

#include <string.h>

unsigned short* __cdecl fcn_00508e40(int id);
char* __cdecl fcn_00502cd0(int a, int b, int c, int d, int e);
void __cdecl fcn_00502e30(void* list, unsigned int id);
void __cdecl fcn_00506ab0(unsigned int idx, int param);

int __cdecl fcn_004eec60(int cmd, int* ids, char* parent)
{
	unsigned short* entity;
	char* query;
	unsigned int* slot;
	int count;

	entity = fcn_00508e40(*ids);
	if (entity != 0) {
		query = fcn_00502cd0(*(int*) (parent + 0x5d), 2, 6, 0, 0xff);
		*(int*) (entity + 0xb8) = 0;
		*(int*) (entity + 0xb6) = 0;
		slot = (unsigned int*) (ids + 3);
		count = 6;
		do {
			if (*slot != 0) {
				if (query != 0) {
					fcn_00502e30(query + 0x14, *slot);
				}
				slot[0] = 0;
				slot[1] = 0;
			}
			slot += 2;
			count--;
		} while (count != 0);
		memset(ids, 0, 0xf * 4);
		fcn_00506ab0(*entity, 1);
		return 1;
	}
	return 0;
}
