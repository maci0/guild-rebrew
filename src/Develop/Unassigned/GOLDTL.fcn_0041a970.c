/* The reference frame keeps EBP; /O2 /Gd omits the frame pointer, so restore
 * it here instead of overriding the locked CFLAGS. */
#pragma optimize("y", off)
#include <stdlib.h>
#include <string.h>

typedef int (__cdecl *INDEXFN)(int count, int ptr);
typedef int (__stdcall *VTBLFN)(void *self, int a, int b, int c, int d,
	void *rec, int *out);

extern char __cdecl fcn_0041b290(unsigned int *adapter, int *mode);
extern char __cdecl fcn_0041ad80(int a, int b);
extern int __cdecl fcn_0041ba40(void);

/* ADDRESS: GOLDTL 0x0041a970 */
char __cdecl fcn_0041a970(int a0, INDEXFN a1, int a2, int a3)
{
	int slot;
	int best;
	int index;
	int pos[4];
	unsigned int i;
	int dist;
	signed char found;
	char ok;
	unsigned char *rec;
	unsigned char *dst;
	int *entry;

	*(int *) 0x14ce730 = a0;
	if (*(int *) 0x6b5ddc == 0 || *(unsigned int *) 0x6b5de8 <= 0)
		return *(int *) 0x6b5de0 != 0;
	slot = -1;
	*(unsigned char *) 0x6b5dec = (a1 != 0);
	found = fcn_0041b290((unsigned int *) &slot, pos);
	while (!found) {
		if (!fcn_0041ad80(0, a0))
			break;
		found = fcn_0041b290((unsigned int *) &slot, pos);
	}
	if (slot < 0) {
		slot = 0;
		entry = *(int **) (*(int *) 0x6b5dd0 + 0x504);
		pos[0] = entry[0];
		pos[1] = entry[1];
		pos[2] = entry[2];
		pos[3] = entry[3];
	}
	rec = (unsigned char *) (*(int *) 0x6b5dd0 + slot * 0x508);
	if (a1) {
		index = a1(*(int *) (rec + 0x500), *(int *) (rec + 0x504));
		if (index < 0 || index >= *(int *) (rec + 0x500))
			return 0;
	} else {
		best = 0x40000000;
		entry = *(int **) (rec + 0x504);
		for (i = 0; i < *(unsigned int *) (rec + 0x500); i++) {
			dist = abs(pos[3] - entry[3])
				+ 4 * (abs(pos[1] - entry[1]) + abs(pos[0] - entry[0]));
			if (dist < best) {
				best = dist;
				index = i;
				if (dist == 0)
					break;
			}
			entry += 4;
		}
	}
	entry = (int *) (*(int *) (rec + 0x504) + index * 0x10);
	pos[0] = entry[0];
	pos[1] = entry[1];
	pos[2] = entry[2];
	pos[3] = entry[3];
	*(int *) 0x14ce828 = pos[3];
	*(int *) 0x14ce820 = pos[0];
	*(int *) 0x14ce824 = pos[1];
	*(int *) 0x14ce844 = pos[2];
	*(int *) 0x14ce840 = pos[2] != 0;
	*(int *) 0x14ce82c = (a3 & 0xff) + 1;
	*(int *) 0x14ce83c = a2 & 0xff;
	*(int *) 0x14ce848 = 0;
	*(int *) 0x14ce850 = 0;
	*(int *) 0x14ce84c = 0;
	*(int *) 0x14ce838 = a0;
	*(int *) 0x14ce830 = 0;
	*(int *) 0x14ce834 = 1;
	ok = *(unsigned int *) (rec + 0x4cc) >= 8
		&& (*(unsigned int *) (rec + 0x4c8) & 8)
		&& (*(unsigned int *) (rec + 0x4c8) & 0x10);
	*(int *) 0x6b5de0 = 0;
	if (ok) {
		(*(VTBLFN *) (*(int *) (*(int *) 0x6b5ddc) + 0x3c))(
			(void *) *(int *) 0x6b5ddc, slot, 1, a0, 0x50,
			(void *) 0x14ce820, (int *) 0x6b5de0);
		if (*(int *) 0x6b5de0)
			goto success;
		if ((char) a3) {
			(*(VTBLFN *) (*(int *) (*(int *) 0x6b5ddc) + 0x3c))(
				(void *) *(int *) 0x6b5ddc, slot, 1, a0, 0x50,
				(void *) 0x14ce820, (int *) 0x6b5de0);
			if (*(int *) 0x6b5de0)
				goto success;
		}
		*(int *) 0x14ce82c = (a3 & 0xff) + 1;
		(*(VTBLFN *) (*(int *) (*(int *) 0x6b5ddc) + 0x3c))(
			(void *) *(int *) 0x6b5ddc, slot, 1, a0, 0x40,
			(void *) 0x14ce820, (int *) 0x6b5de0);
		if (*(int *) 0x6b5de0)
			goto success;
		if ((char) a3) {
			(*(VTBLFN *) (*(int *) (*(int *) 0x6b5ddc) + 0x3c))(
				(void *) *(int *) 0x6b5ddc, slot, 1, a0, 0x40,
				(void *) 0x14ce820, (int *) 0x6b5de0);
			if (*(int *) 0x6b5de0)
				goto success;
		}
	}
	*(int *) 0x14ce82c = (a3 & 0xff) + 1;
	(*(VTBLFN *) (*(int *) (*(int *) 0x6b5ddc) + 0x3c))(
		(void *) *(int *) 0x6b5ddc, slot, 1, a0, 0x20,
		(void *) 0x14ce820, (int *) 0x6b5de0);
	if (*(int *) 0x6b5de0)
		goto success;
	if ((char) a3) {
		(*(VTBLFN *) (*(int *) (*(int *) 0x6b5ddc) + 0x3c))(
			(void *) *(int *) 0x6b5ddc, slot, 1, a0, 0x20,
			(void *) 0x14ce820, (int *) 0x6b5de0);
		if (*(int *) 0x6b5de0)
			goto success;
	}
	return *(int *) 0x6b5de0 != 0;
success:
	dst = (unsigned char *) 0x14ce740;
	memcpy(dst, (void *) (*(int *) 0x6b5dd0 + slot * 0x508 + 0x42c), 0xd4);
	if (*(unsigned int *) 0x14ce7e0 < 8)
		*(int *) 0x14ce7e0 = 8;
	dst = (unsigned char *) 0x14ce860;
	memcpy(dst, pos, 0x10);
	*(int *) 0x14ce72c = 1;
	fcn_0041ba40();
	return *(int *) 0x6b5de0 != 0;
}
