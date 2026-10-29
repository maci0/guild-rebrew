/*
 * Task progression pass.
 *
 * Walks the 0x2c-byte task records of the current round, resolves the target
 * object of each live task and hands it to the per-type progress handler. The
 * native body is one loop with an eight-way dispatch on the task type.
 *
 * Reconstructed range 0x4d8d00..0x4d8db4: the pre-loop setup, the loop head,
 * the record fetch and the target resolution for the first task. The eight-way
 * dispatch table at 0x4d9ef8, the per-type bodies and the loop tail through
 * 0x4d9f18 are not reconstructed here.
 */

extern int g_772ea4;		/* 0x00772ea4 */

int __cdecl fcn_00508e40(unsigned int);
int __cdecl gm_LookupEntityRecordById(unsigned int);
int __cdecl fcn_004ce610(int);

typedef struct TaskRec {
	int f[11];
} TaskRec;

/* ADDRESS: GOLDTL 0x004d8d00 */
void __cdecl fcn_004d8d00(char* a0)
{
	TaskRec rec;
	TaskRec* p;
	char* obj;
	int h;
	int n;

	n = *(int*) (*(int*) 0x67a370 + 0xb0);
	if (g_772ea4) {
		return;
	}
	p = (TaskRec*) (a0 + 0x94);
	if (p) {
		rec = *p;
	}
	if (!rec.f[1] || rec.f[0] == -1) {
		return;
	}
	obj = (char*) (rec.f[1] == 5 ? fcn_00508e40((unsigned int) rec.f[0]) : gm_LookupEntityRecordById((unsigned int) rec.f[0]));
	h = fcn_004ce610((int) obj);
	if ((!obj || !*(char*) (obj + 8)) && h) {
		return;
	}
}
