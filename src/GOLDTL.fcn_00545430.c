extern char g_7d2020[0xa400];
extern char g_7dcae0[0x5000];
extern char g_7dc6e0[0x400];

// FUNCTION: GOLDTL 0x545430
// SIZE: 221
// FUNCTION: GOLD 0x0053d710
// SIZE: 224

#include <string.h>

int __cdecl fcn_00545580(int, void*, void*);
void __cdecl fcn_00545390(void);
void __cdecl fcn_005453d0(void);
void __cdecl fcn_00545410(void);
void __cdecl fcn_00545420(void);
int __cdecl fcn_0055b3e0(void);
int __cdecl fcn_00570960(void);
int __cdecl fcn_00575710(void);
int __cdecl fcn_005780b0(void);
int __cdecl fcn_00575900(void);
int __cdecl fcn_00576ae0(void);
int __cdecl fcn_0057bbc0(void);
int __cdecl fcn_0057ba30(void);

int __cdecl fcn_00545430(void)
{
	if (fcn_00545580(0, (void*) fcn_00545390, (void*) fcn_005453d0) != 0) {
		return 1;
	}
	if (fcn_00545580(1, (void*) fcn_00545410, (void*) fcn_00545420) != 0) {
		return 1;
	}
	if (fcn_0055b3e0() != 0) {
		return 1;
	}
	if (fcn_00570960() != 0) {
		return 1;
	}
	if (fcn_00575710() != 0) {
		return 1;
	}
	if (fcn_005780b0() != 0) {
		return 1;
	}
	if (fcn_00575900() != 0) {
		return 1;
	}
	if (fcn_00576ae0() != 0) {
		return 1;
	}
	if (fcn_0057bbc0() != 0) {
		return 1;
	}
	if (fcn_0057ba30() != 0) {
		return 1;
	}
	memset(g_7d2020, 0, sizeof(g_7d2020));
	memset(g_7dcae0, 0, sizeof(g_7dcae0));
	memset(g_7dc6e0, 0, sizeof(g_7dc6e0));
	return 0;
}
