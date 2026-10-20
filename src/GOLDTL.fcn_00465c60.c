#include <stdio.h>

typedef struct VfsEntry {
	char name[0x30];
	int offset;
	void* data;
	int size;
	int kind;
	int refs;
	int flags;
	int stamp;
	char pad[8];
} VfsEntry;
// SIZE 0x54

extern char* g_772500;
extern int g_772508;
extern int g_77250c;
extern int g_772524;
extern int g_77253c;
extern int g_772540;
extern FILE* g_772564;
extern int g_77256c;
extern int g_77257c;
extern int g_772580;
extern int g_772584;
extern int g_772588;
extern int g_7725ac;
extern int g_1015ea0;
extern int g_14ce728;

void __cdecl fcn_004732f0(void);
void __cdecl fcn_0046f280(int a1);
void __cdecl fcn_0046b2b0(int id);
void __cdecl fcn_0047b5d0(void* p);
void __cdecl fcn_0041ddd0(void* p);
void __cdecl fcn_00475f80(void* o);
void __cdecl fcn_00477550(void);
void __cdecl fcn_0047ce50(int a1);
void __cdecl fcn_0047c4b0(void);
void __cdecl fcn_00477480(void);

/* Shuts the resource system down: drops the animation tracks, every entry of
 * the file table, the open archive handles and the tracked allocations. */
/* ADDRESS: GOLDTL 0x00465c60 */
void __cdecl fcn_00465c60(void)
{
	int* track;

	int i;
	int off;
	int table;
	VfsEntry* entry;
	void* object;

	fcn_004732f0();
	i = 0;
	track = (int*) 0x10161d0;
	do {
		if (*track == 1) {
			fcn_0046f280(i);
		}
		track = (int*) ((char*) track + 0x3cc);
		i++;
	} while ((int) track < 0x102ce50);
	i = 0;
	do {
		fcn_0046b2b0(i);
		i++;
	} while (i < 0x3ff);
	off = 0;
	table = (int) g_772500;
	do {
		entry = (VfsEntry*) (table + off);
		if (entry->data != 0 && entry->size != 0) {
			if (entry->kind < 0x10) {
				fcn_0047b5d0(entry->data);
			} else {
				fcn_0041ddd0(entry->data);
				entry->data = 0;
			}
			g_772508 -= entry->size;
			entry->data = 0;
			table = (int) g_772500;
		}
		off += 0x54;
	} while (off < 0x2a000);
	if (g_77250c != 0) {
		object = *(void**) (g_77250c + 0x24);
		g_14ce728 = (*(int (__stdcall**) (void*)) (*(int*) object + 8))(object);
		*(int*) (g_77250c + 0x24) = 0;
		fcn_00475f80((void*) g_77250c);
		g_77250c = 0;
	}
	if (g_77256c != 0) {
		fcn_00475f80((void*) g_77256c);
		g_77256c = 0;
	}
	fcn_00477550();
	if (g_77253c != 0) {
		fcn_0047ce50(g_77253c);
		g_77253c = 0;
	}
	if (g_772564 != 0) {
		fclose(g_772564);
	}
	g_772524 = 0;
	g_772564 = 0;
	if (g_772540 != 0) {
		fcn_0041ddd0((void*) g_772540);
		g_772540 = 0;
	}
	if (g_1015ea0 != 0) {
		fcn_0041ddd0((void*) g_1015ea0);
		g_1015ea0 = 0;
	}
	if (g_772500 != 0) {
		fcn_0041ddd0(g_772500);
		g_772500 = 0;
	}
	if (g_77257c != 0) {
		fcn_0041ddd0((void*) g_77257c);
		g_77257c = 0;
	}
	if (g_772580 != 0) {
		fcn_0041ddd0((void*) g_772580);
		g_772580 = 0;
	}
	if (g_772584 != 0) {
		fcn_0041ddd0((void*) g_772584);
		g_772584 = 0;
	}
	if (g_772588 != 0) {
		fcn_0041ddd0((void*) g_772588);
		g_772588 = 0;
	}
	if (g_7725ac != 0) {
		fcn_0041ddd0((void*) g_7725ac);
		g_7725ac = 0;
	}
	fcn_0047c4b0();
	fcn_00477480();
}
