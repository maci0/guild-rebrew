#include <string.h>

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;
extern unsigned short g_7f4c04;
extern int g_7f4c08;
extern short g_7f4c0c;
extern unsigned char g_773d75;
extern float g_66414c;

char* __cdecl fcn_00507ab0(int k);
void __cdecl fcn_004c4eb0(char* s);
void __cdecl fcn_004c4ef0(char* s);
int __cdecl fcn_0050d170(int k);
void __cdecl fcn_004c5150(int a, int b, char c, int n);
void __cdecl fcn_004c5530(char* msg);

/* Client dialog record setup: allocates the dialog object (fcn_00507ab0(1)),
 * accepts only type 0xf records on channel 4, clears a 0x3e-dword stack record,
 * fills it with the entity position block (g_7f4c00..g_7f4c0c), the object id
 * and the open flag, then runs the fcn_004c4eb0/fcn_004c5150/fcn_004c5530 chain
 * and returns 0x31. */
/* ADDRESS: GOLDTL 0x0049dc70 */
int __cdecl ai_RunBuergermeisterRathaus(unsigned char* rec, unsigned char* obj, unsigned char* out)
{
	char msg[0xf8];
	char* dialog;

	dialog = fcn_00507ab0(1);
	if (dialog == 0) {
		return 0;
	}
	if (rec[0x166] != 0xf) {
		return 0;
	}
	if (out[0] != 4 && *(int*) (obj + 0x10) != 0) {
		return 0;
	}
	memset(msg, 0, sizeof(msg));
	*(int*) (msg + 8) = *(int*) (rec + 4);
	msg[4] = 0x1e;
	*(int*) (msg + 0xc) = *(int*) (out + 4);
	msg[0x36] = 1;
	*(int*) (msg + 0x28) = (*(int*)&g_7f4c00);
	*(int*) (msg + 0x2c) = (*(int*)&g_7f4c04);
	*(int*) (msg + 0x30) = g_7f4c08;
	*(short*) (msg + 0x34) = g_7f4c0c;
	*(int*) (msg + 0x58) = *(int*) (out + 4);
	fcn_004c4eb0((char*) 0x67eb10);
	fcn_004c5150(-1, *(int*) (dialog + 2), (*(char*)&g_773d75), (int) (fcn_0050d170(*(int*) (obj + 4)) * g_66414c));
	fcn_004c5530(msg);
	fcn_004c4ef0((char*) 0x67eb10);
	return 0x31;
}
