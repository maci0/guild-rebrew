typedef struct Device Device;
typedef struct Snd Snd;

typedef struct {
	char p0[0x14];
	int (__stdcall* Draw)(Snd*, int, void*);
	int (__stdcall* Release)(Snd*);
} SndVtbl;

typedef struct {
	char p0[0x2c];
	int (__stdcall* Lock)(Device*, int, int, void*, int);
	int (__stdcall* Unlock)(Device*);
	char p34[0x88 - 0x34];
	int (__stdcall* Begin)(Device*);
	int (__stdcall* End)(Device*);
	char p90[0x38];
	int (__stdcall* SetRenderState)(Device*, int, int);
	char pcc[0x28];
	int (__stdcall* SelectBank)(Device*, int, int);
	char pf8[0x20];
	int (__stdcall* SelectSample)(Device*, int, int, int);
} DevVtbl;

struct Device {
	DevVtbl* vtbl;
};

struct Snd {
	SndVtbl* vtbl;
};







/* the 0xa8 byte prefix copied per entry */
typedef struct {
	char p0[0xa8];
} BankData;

/* sample descriptor filled for one draw call */
typedef struct {
	int f0;
	int f4;
	int f8;
	int fc;
	int f10;
	int f14;
} Sample;

#include "Develop/DieGildeAddOn/game/game_data.h"
extern Device* g_772614;
extern Device* g_6b5de0;
#include "Develop/Unassigned/render_quad.h"

void __cdecl d2_BindQuadVertexBuffer(void);
void __cdecl d2_ResetQuadDeviceState(void);
void __cdecl d3_SetRenderMaterialState(int, int, int, int, int);

/* ADDRESS: GOLDTL 0x0047c560 */
int __cdecl d2_FlushQueuedQuads(int idx, Snd* snd, char* src)
{
	int start;
	int count;
	int i;
	int j;
	int id;
	RENDER_QUAD* first;
	RENDER_QUAD* rec;
	BankData *data;
	RENDER_QUAD* p;
	Sample s;

	start = idx;
	if (((Device*) g_772614)->vtbl->Lock((Device*) g_772614, 0, d2_QueuedQuadCount * 0x18 - idx * 0x18, &idx, 0x2000) < 0) {
		return 0;
	}
	data = (BankData*) idx;
	first = &g_1552020[start];
	rec = first;
	for (i = start; i < d2_QueuedQuadCount; i++) {
		*data = *(BankData*) rec;
		rec++;
		data++;
	}
	((Device*) g_772614)->vtbl->Unlock((Device*) g_772614);
	d2_BindQuadVertexBuffer();
	g_6b5de0->vtbl->SetRenderState(g_6b5de0, 7, 0);
	g_6b5de0->vtbl->SetRenderState(g_6b5de0, 0x88, 0);
	d3_SetRenderMaterialState(0xff, 0, 0, 1, 1);
	if (d2_QueuedQuadCount != 0) {
		if (snd != 0) {
			s.f0 = 0;
			s.f4 = 0;
			s.f14 = 0x3f800000;
			s.f8 = *(int*) (src + 0x54);
			s.fc = *(int*) (src + 0x58);
			s.f10 = 0;
			if (snd->vtbl->Draw(snd, *(int*) (src + 0x24), &s) < 0) {
				goto done;
			}
			g_6b5de0->vtbl->SetRenderState(g_6b5de0, 7, 0);
		} else {
			if (g_6b5de0->vtbl->Begin(g_6b5de0) < 0) {
				goto done;
			}
		}
		rec = first;
		for (i = start; i < d2_QueuedQuadCount; i += count, rec += count) {
			id = rec->tex;
			p = rec;
			count = 0;
			j = i;
			do {
				if (j >= d2_QueuedQuadCount) {
					break;
				}
				p++;
				count++;
				j++;
			} while (id == p->tex);
			g_6b5de0->vtbl->SelectBank(g_6b5de0, 0, id);
			g_6b5de0->vtbl->SelectSample(g_6b5de0, 4, i * 6, count * 2);
		}
		if (snd != 0) {
			snd->vtbl->Release(snd);
			g_6b5de0->vtbl->SetRenderState(g_6b5de0, 7, 1);
		} else {
			g_6b5de0->vtbl->End(g_6b5de0);
		}
	}
done:
	d2_QueuedQuadCount = start;
	g_6b5de0->vtbl->SetRenderState(g_6b5de0, 7, 1);
	g_6b5de0->vtbl->SetRenderState(g_6b5de0, 0x88, 1);
	d2_ResetQuadDeviceState();
	return 1;
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_1552020[181252];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_1553020[177156];
#endif
