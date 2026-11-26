#include <string.h>
extern __int64 g_666018;

unsigned short* __cdecl fcn_005cd440(unsigned int*, char*, int, int);
int __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_HasActiveSpecialObject(int, int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, int);

/* ADDRESS: GOLDTL 0x005dd2f0 */
unsigned int __cdecl fcn_005dd2f0(int actorRec, int eventArgs)
{
	unsigned int q[20];
	char buf[0x100];
	char name[0x400];
	unsigned short* firstTarget;
	unsigned short* secondTarget;
	int effectDelta;


	if (*(char*) (actorRec + 2) == 6) {
		memset(q, 0, 0x50);
		memset(q + 7, 0xff, 0x20);
		io_FormatTextBuffer(buf, 0x9c);
		q[0] = 0;
		q[1] = 0x400;
		q[4] = 6;
		*(__int64*) (q + 2) = g_666018;
		firstTarget = fcn_005cd440(q, buf, 0, 0);
		if (firstTarget != 0) {
			q[5] = 3;
			*(unsigned short*) &q[7] = *firstTarget;
			io_FormatTextBuffer(buf, 0x9e);
			secondTarget = fcn_005cd440(q, buf, 0, 0);
			if (secondTarget != 0) {
				goto do_apply;
			}
		}
		return 0;
	} else {
		firstTarget = (unsigned short*) gm_LookupEntityRecordById(*(int*) (eventArgs + 4));
		secondTarget = (unsigned short*) gm_LookupEntityRecordById(*(int*) (eventArgs + 8));
		if (firstTarget == 0 || secondTarget == 0) {
			return 0;
		}
	}
do_apply:
	effectDelta = ((gm_HasActiveSpecialObject(actorRec, 0x2c5) != 0) + 1) * -0x28;
	cm_RequestCopyEntityData(*(unsigned int*) ((char*) firstTarget + 4), *(unsigned int*) ((char*) secondTarget + 4), effectDelta, 1);
	cm_RequestCopyEntityData(*(unsigned int*) ((char*) secondTarget + 4), *(unsigned int*) ((char*) firstTarget + 4), effectDelta, 1);
	if (*(char*) ((char*) firstTarget + 2) == 6 || *(char*) ((char*) firstTarget + 2) == 7) {
		io_FormatTextBuffer(name, 0xfea, *secondTarget);
		fcn_00545d40(*(unsigned int*) ((char*) firstTarget + 4), -1, name, 1, 0x5fb, 0);
	}
	if (*(char*) ((char*) secondTarget + 2) == 6 || *(char*) ((char*) secondTarget + 2) == 7) {
		io_FormatTextBuffer(name, 0xfeb, *firstTarget, *firstTarget);
		fcn_00545d40(*(unsigned int*) ((char*) secondTarget + 4), -1, name, 1, 0x5fb, 0);
	}
	return 1;
}
