#include <string.h>

int __cdecl fcn_00507ab0(int);
int __cdecl fcn_0050d170(int);
void __cdecl fcn_004c4eb0(void*);
void __cdecl fcn_004c4ef0(void*);
void __cdecl fcn_004c5150(int, int, int, int);
void __cdecl fcn_004c5530(void*);

/* Client dialog record setup: allocates the dialog object (fcn_00507ab0(1)),
 * accepts only type 0xf records on channel 4, clears a 0x3e-dword stack record,
 * fills it with the entity position block (g_7f4c00..g_7f4c0c), the object id
 * and the open flag, then runs the fcn_004c4eb0/fcn_004c5150/fcn_004c5530 chain
 * and returns 0x31. */
/* ADDRESS: GOLDTL 0x0049dc70 */
int __cdecl fcn_0049dc70(unsigned char* rec, unsigned char* obj, unsigned char* out)
{
	int dialog;
	int v;

	dialog = fcn_00507ab0(1);
	if (dialog == 0) {
		return 0;
	}
	if (rec[0x166] != 0xf) {
		return 0;
	}
	if (out[0] != 4 && *(int*) (obj + 0x10) == 0) {
		v = 0;
	}
	return 0x31;
}
