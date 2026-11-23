#include "Develop/DieGildeAddOn/game/event_deal.h"
unsigned int __cdecl vfs_fwrite(void* data, int size, int count, void* stream);

#pragma pack(1)
#include "Develop/DieGildeAddOn/game/he_action.h"
























#include "Develop/DieGildeAddOn/game/he_ap_event.h"
#pragma pack()


extern HE_AP_EVENT g_7dcae0[256];

/* ADDRESS: GOLDTL 0x00520d90 */
int __cdecl he_SaveEvents(void* stream)
{
	int count;
	int i;
	int k;

	count = 0;
	for (i = 0; i < 1024; i++) {
		if (g_77e980[i].kind != 0)
			count++;
	}
	if (vfs_fwrite(&count, 4, 1, stream) <= 0)
		return 0;
	i = 0xa0;
	if (vfs_fwrite(&i, 4, 1, stream) <= 0)
		return 0;
	for (i = 0; i < 1024; i++) {
		if (g_77e980[i].kind != 0) {
			HE_ACTION* u = &g_77e980[i];
			if (vfs_fwrite(&u->kind, 1, 1, stream) <= 0)
				return 0;
			if (vfs_fwrite(&u->serial, 4, 1, stream) <= 0)
				return 0;
			if (vfs_fwrite(&u->house, 2, 1, stream) <= 0)
				return 0;
			if (vfs_fwrite(&u->owner, 4, 1, stream) <= 0)
				return 0;
			if (vfs_fwrite(&u->unk_10, 4, 1, stream) <= 0)
				return 0;
			if (vfs_fwrite(u->unk_14, 0x30, 1, stream) <= 0)
				return 0;
			if (vfs_fwrite(u->position, 0xe, 1, stream) <= 0)
				return 0;
			if (vfs_fwrite(u->unk_52, 0xe, 1, stream) <= 0)
				return 0;
			if (vfs_fwrite(u->unk_60, 0xe, 1, stream) <= 0)
				return 0;
			if (vfs_fwrite(&u->unk_70, 4, 1, stream) <= 0)
				return 0;
			if (vfs_fwrite(&u->flags, 1, 1, stream) <= 0)
				return 0;
			for (k = 0; k < 8; k++) {
				if (vfs_fwrite(&u->unk_8c[k], 4, 1, stream) <= 0)
					return 0;
			}
			if (u->data != 0 && u->data_size != 0) {
				if (vfs_fwrite(&u->data_size, 4, 1, stream) <= 0)
					return 0;
				if (vfs_fwrite(u->data, u->data_size, 1, stream) <= 0)
					return 0;
			}
			else {
				int zero = 0;
				if (vfs_fwrite(&zero, 4, 1, stream) <= 0)
					return 0;
			}
			if (vfs_fwrite(u->unk_ac, 0xa0, 1, stream) <= 0)
				return 0;
		}
	}
	count = 0;
	for (i = 0; i < 256; i++) {
		if (g_7d2020[i].id != 0)
			count++;
	}
	if (vfs_fwrite(&count, 4, 1, stream) <= 0)
		return 0;
	for (i = 0; i < 256; i++) {
		if (g_7d2020[i].id == 0)
			continue;
		if (vfs_fwrite((void*) (g_7d2020[i].id + 4), 4, 1, stream) <= 0)
			return 0;
		if (vfs_fwrite(&g_7d2020[i].state, 1, 1, stream) <= 0)
			return 0;
		if (vfs_fwrite(&g_7d2020[i].has_amount, 4, 1, stream) <= 0)
			return 0;
		if (vfs_fwrite(&g_7d2020[i].owner, 4, 1, stream) <= 0)
			return 0;
		if (vfs_fwrite(&g_7d2020[i].amount, 4, 1, stream) <= 0)
			return 0;
		if (vfs_fwrite(&g_7d2020[i].pos, 0xe, 1, stream) <= 0)
			return 0;
		if (vfs_fwrite(g_7d2020[i].name, 0x80, 1, stream) <= 0)
			return 0;
	}
	count = 0;
	for (i = 0; i < 256; i++) {
		if (g_7dcae0[i].value_08 != 0 || g_7dcae0[i].value_0c != 0 || g_7dcae0[i].name[0] != 0)
			count++;
	}
	if (vfs_fwrite(&count, 4, 1, stream) <= 0)
		return 0;
	for (i = 0; i < 256; i++) {
		if (g_7dcae0[i].value_08 == 0 && g_7dcae0[i].value_0c == 0 && g_7dcae0[i].name[0] == 0)
			continue;
		if (vfs_fwrite(&g_7dcae0[i].lifetime, 1, 1, stream) <= 0)
			return 0;
		if (vfs_fwrite(&g_7dcae0[i].subject_id, 4, 1, stream) <= 0)
			return 0;
		if (vfs_fwrite(&g_7dcae0[i].value_08, 4, 1, stream) <= 0)
			return 0;
		if (vfs_fwrite(&g_7dcae0[i].value_0c, 4, 1, stream) <= 0)
			return 0;
		if (vfs_fwrite(g_7dcae0[i].name, 0x40, 1, stream) <= 0)
			return 0;
	}
	return 1;
}
unsigned char _dpad_7d1d80[672];
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_7d2020[41984];
unsigned char _dpad_7dc440[1696];
unsigned char _dpad_7dcae0[21648];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_7d2420[7536];
unsigned char _dpad_7d4194[33420];
unsigned char _dpad_7dc444[668];
unsigned char _dpad_7dc7e0[768];
unsigned char _dpad_7dcee0[19456];
unsigned char _dpad_7e1ae1[255];
unsigned char _dpad_7e1be1[287];
unsigned char _dpad_7e1d02[62];
unsigned char _dpad_7e1d44[28];
unsigned char _dpad_7e1f64[12];
#endif
