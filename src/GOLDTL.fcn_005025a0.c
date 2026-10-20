#include "client_types.h"

extern char g_85ab90[];
extern char* g_item_def_table;
extern unsigned char g_773d75;
extern float flt_1;
extern float g_6628a8;
extern double g_664e78;
extern double dbl_1_0;

char* __cdecl fcn_00503d10(int id);
char* __cdecl fcn_00503e50(int owner);
char* __cdecl fcn_00502cd0(int a, int b, ...);
float __cdecl fcn_0050b980(int id, int arg);

/* Slot price of one season slot: stock against the slot's base rate, clamped
 * to 0.25..5 and moved 0.4 of the way from the slot's last price. */
/* ADDRESS: GOLDTL 0x005025a0 */
float __cdecl fcn_005025a0(int season, int slot)
{
	char* def;
	char* store;
	char* e;
	int id;
	float stock;
	float last;
	float ratio;
	float scale;
	int off;

	off = season * 0x2a90 + slot * 0x80;
	id = *(unsigned short*) (g_85ab90 + off);
	def = g_item_def_table + id * 0x41;
	store = fcn_00503d10(id);
	if (store == 0 && season != g_773d75) {
		e = fcn_00503e50(season);
		if (e != 0) {
			store = fcn_00502cd0(*(int*) (e + 0x5d), 2, 0, 0x1db, 6);
		}
	}
	stock = 0.0f;
	if (store == 0) {
		return fcn_0050b980(id, 100);
	}
	e = fcn_00502cd0(*(int*) (store + 0x14), 1, 0, id);
	if (e != 0) {
		stock = (float) *(int*) (e + 0xe);
	}
	ratio = *(float*) (g_85ab90 + off + 0x24) / *(float*) (g_85ab90 + off + 0x20);
	last = *(float*) (g_85ab90 + off + 0x38);
	if (stock > *(float*) (g_85ab90 + off + 0x20) && *def != 0x17) {
		if (stock < 1.0) {
			ratio *= *(float*) (g_85ab90 + off + 0x20) / 1.0;
		} else {
			ratio *= *(float*) (g_85ab90 + off + 0x20) / stock;
		}
	} else {
		ratio *= flt_1;
	}
	if (ratio > 0.25) {
		scale = ratio;
	} else {
		scale = 0.25;
	}
	if (scale >= 5.0) {
		scale = 5.0;
	}
	stock = scale;
	if (last <= g_6628a8) {
		stock = fcn_0050b980(id, 100);
		if (stock < 512.0f) {
			return 512.0f;
		}
		return stock;
	}
	return (float) (((double) fcn_0050b980(id, 100) * (double) stock - (double) last) * 0.4f + (double) last);
}
