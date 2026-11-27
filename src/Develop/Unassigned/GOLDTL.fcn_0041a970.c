/* The reference frame keeps EBP; /O2 /Gd omits the frame pointer, so restore
 * it here instead of overriding the locked CFLAGS. */
#pragma optimize("y", off)
#include <stdlib.h>
#include <string.h>
extern char g_14ce820[]; extern void * g_6b5de0;
typedef int (__cdecl *INDEXFN)(int count, int ptr);
typedef int (__stdcall *VTBLFN)(void *self, int a, int b, int c, int d,
	void *rec, int *out);

extern char __cdecl d3_LoadSavedDisplayConfig(unsigned int *adapter, int *mode);
extern char __cdecl d3_ShowDisplaySetupDialog(int a, int b);
extern int __cdecl d3_RestoreDeviceResources(void);

/* ADDRESS: GOLDTL 0x0041a970 */
char __cdecl d3_CreateGraphicsDevice(int hwnd, INDEXFN indexCallback, unsigned char windowed, unsigned char triple_buffer)
{
	int ready;
	int slot;
	int best;
	int index;
	int pos[4];
	unsigned int i;
	int dist;
	signed char found;
	char ok;
	unsigned char *rec;
	int *entry;
	char *csrc;
	int ccnt;

	ready = *(int *) 0x6b5ddc;
	*(int *) 0x14ce730 = hwnd;
	if (ready == 0 || *(unsigned int *) 0x6b5de8 <= 0)
		goto done;
	slot = -1;
	*(unsigned char *) 0x6b5dec = (indexCallback != 0);
	found = d3_LoadSavedDisplayConfig((unsigned int *) &slot, pos);
	while (!found) {
		if (!d3_ShowDisplaySetupDialog(0, hwnd))
			break;
		found = d3_LoadSavedDisplayConfig((unsigned int *) &slot, pos);
	}
	if (slot < 0) {
		slot = 0;
		entry = *(int **) (*(int *) 0x6b5dd0 + 0x504);
		pos[0] = entry[0];
		pos[1] = entry[1];
		pos[2] = entry[2];
		pos[3] = entry[3];
	}
	if (indexCallback) {
		index = indexCallback(*(int *) (*(int *) 0x6b5dd0 + slot * 0x508 + 0x500),
			*(int *) (*(int *) 0x6b5dd0 + slot * 0x508 + 0x504));
		if (index < 0 || (rec = (unsigned char *) (*(int *) 0x6b5dd0 + slot * 0x508),
			index >= *(int *) (rec + 0x500)))
			return 0;
	} else {
		rec = (unsigned char *) (*(int *) 0x6b5dd0 + slot * 0x508);
		best = 0x40000000;
		entry = *(int **) (rec + 0x504);
		for (i = 0; i < *(unsigned int *) (rec + 0x500); i++, entry += 4) {
			dist = abs(pos[3] - entry[3])
				+ 4 * (abs(pos[1] - entry[1]) + abs(pos[0] - entry[0]));
			if (dist < best) {
				best = dist;
				index = i;
				if (dist == 0)
					break;
			}
		}
	}
	entry = (int *) (*(int *) (rec + 0x504) + index * 0x10);
	pos[0] = entry[0];
	pos[1] = entry[1];
	pos[2] = entry[2];
	pos[3] = entry[3];
	*(int *) 0x14ce828 = pos[3];
	*(int *) &g_14ce820 = pos[0];
	*(int *) 0x14ce824 = pos[1];
	*(int *) 0x14ce844 = pos[2];
	*(int *) 0x14ce840 = pos[2] != 0;
	*(int *) 0x14ce82c = triple_buffer + 1;
	*(int *) 0x14ce83c = windowed;
	*(int *) 0x14ce848 = 0;
	*(int *) 0x14ce850 = 0;
	*(int *) 0x14ce84c = 0;
	*(int *) 0x14ce838 = hwnd;
	*(int *) 0x14ce830 = 0;
	*(int *) 0x14ce834 = 1;
	ok = *(unsigned int *) (rec + 0x4cc) >= 8
		&& (*(unsigned int *) (rec + 0x4c8) & 8)
		&& (*(unsigned int *) (rec + 0x4c8) & 0x10);
	*(int *) &g_6b5de0 = 0;
	if (ok) {
		(*(VTBLFN *) (*(int *) (*(int *) 0x6b5ddc) + 0x3c))(
			(void *) *(int *) 0x6b5ddc, slot, 1, hwnd, 0x50,
			(void *) &g_14ce820, (int *) &g_6b5de0);
		if (*(int *) &g_6b5de0)
			goto success;
		if (triple_buffer) {
			(*(VTBLFN *) (*(int *) (*(int *) 0x6b5ddc) + 0x3c))(
				(void *) *(int *) 0x6b5ddc, slot, 1, hwnd, 0x50,
				(void *) &g_14ce820, (int *) &g_6b5de0);
			if (*(int *) &g_6b5de0)
				goto success;
		}
		*(int *) 0x14ce82c = triple_buffer + 1;
		(*(VTBLFN *) (*(int *) (*(int *) 0x6b5ddc) + 0x3c))(
			(void *) *(int *) 0x6b5ddc, slot, 1, hwnd, 0x40,
			(void *) &g_14ce820, (int *) &g_6b5de0);
		if (*(int *) &g_6b5de0)
			goto success;
		if (triple_buffer) {
			(*(VTBLFN *) (*(int *) (*(int *) 0x6b5ddc) + 0x3c))(
				(void *) *(int *) 0x6b5ddc, slot, 1, hwnd, 0x40,
				(void *) &g_14ce820, (int *) &g_6b5de0);
			if (*(int *) &g_6b5de0)
				goto success;
		}
	}
	*(int *) 0x14ce82c = triple_buffer + 1;
	(*(VTBLFN *) (*(int *) (*(int *) 0x6b5ddc) + 0x3c))(
		(void *) *(int *) 0x6b5ddc, slot, 1, hwnd, 0x20,
		(void *) &g_14ce820, (int *) &g_6b5de0);
	if (*(int *) &g_6b5de0)
		goto success;
	if (!triple_buffer)
		goto done;
	(*(VTBLFN *) (*(int *) (*(int *) 0x6b5ddc) + 0x3c))(
		(void *) *(int *) 0x6b5ddc, slot, 1, hwnd, 0x20,
		(void *) &g_14ce820, (int *) &g_6b5de0);
	if (!*(int *) &g_6b5de0)
		goto done;
success:
	ccnt = 0xd4;
	csrc = (char *) (*(int *) 0x6b5dd0 + slot * 0x508 + 0x42c);
	/* Reviewed original operand-homed copy (inline fill/copy block). */
	__asm {
		mov edi, 0x14ce740
		mov esi, csrc
		mov ebx, ccnt
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L1
		rep movsb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep movsd
	L1:
		add ecx, ebx
		rep movsb
	}
	if (*(unsigned int *) 0x14ce7e0 < 8)
		*(int *) 0x14ce7e0 = 8;
	ccnt = 0x10;
	csrc = (char *) pos;
	/* Reviewed original operand-homed copy (inline fill/copy block). */
	__asm {
		mov edi, 0x14ce860
		mov esi, csrc
		mov ebx, ccnt
		lea ecx, [edi+edi*2]
		and ecx, 3
		sub ebx, ecx
		jle short L2
		rep movsb
		mov ecx, ebx
		and ebx, 3
		shr ecx, 2
		rep movsd
	L2:
		add ecx, ebx
		rep movsb
	}
	*(int *) 0x14ce72c = 1;
	d3_RestoreDeviceResources();
done:
	return *(int *) &g_6b5de0 != 0;
}
