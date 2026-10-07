// FUNCTION: GOLD 0x004bd610
// FUNCTION: GOLDTL 0x4bdeb0

#include <string.h>

int __cdecl fcn_0065f2f0(char*, char*, int);
void __cdecl fcn_00455350(char*, char*, float*);
int __cdecl fcn_00451840(char*, float*, float);

char __cdecl fcn_004bdeb0(char* e, char* obj)
{
	float v[4];

	if (fcn_0065f2f0(e, obj, strlen(obj)) == 0 || fcn_0065f2f0(e + 1, obj, strlen(obj)) == 0) {
		fcn_00455350(e, e + 0x4c, v);
		if (fcn_00451840(obj + 0x40, v, 100.0f) != 0) {
			*(char**) (obj + 0x50) = e;
			return 0;
		}
	}
	return 1;
}
