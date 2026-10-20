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
	char p34[0x94];
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

/* table entry, stride 0xac */
typedef struct {
	char p0[0xa8];
	int key;
} BankRec;

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

extern int g_772604;
extern Device* g_772614;
extern Device* g_6b5de0;
extern BankRec g_1552020[];

void __cdecl fcn_0047c4e0(void);
void __cdecl fcn_0047c520(void);
void __cdecl fcn_004372d0(int, int, int, int, int);

/* ADDRESS: GOLDTL 0x0047c560 */
int __cdecl fcn_0047c560(int idx, Snd* snd, char* src)
{
	int start;
	int count;
	int i;
	int j;
	int id;
	BankRec* rec;
	char* data;
	char* p;
	Sample s;

	start = idx;
	if (((Device*) g_772614)->vtbl->Lock((Device*) g_772614, 0, (g_772604 - idx) * 0x18, &idx, 0x2000) < 0) {
		return 0;
	}
	data = (char*) idx;
	rec = g_1552020 + start;
	if (start < g_772604) {
		p = data;
		do {
			*(BankData*) p = *(BankData*) rec;
			p += 0xa8;
			rec++;
			start++;
		} while (start < g_772604);
	}
	((Device*) g_772614)->vtbl->Unlock((Device*) g_772614);
	fcn_0047c4e0();
	s.f0 = 0;
	s.f4 = 0;
	s.f8 = *(int*) (src + 0x54);
	s.fc = *(int*) (src + 0x58);
	s.f10 = 0;
	s.f14 = 0x3f800000;
	g_6b5de0->vtbl->SetRenderState(g_6b5de0, 7, 0);
	g_6b5de0->vtbl->SetRenderState(g_6b5de0, 0x88, 0);
	fcn_004372d0(0xff, 0, 0, 1, 1);
	if (g_772604 != 0) {
		if (snd != 0) {
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
		rec = g_1552020 + start;
		i = start;
		while (i < g_772604) {
			id = *(int*) ((char*) rec + 0xa8);
			p = (char*) rec + 0xa8;
			count = 0;
			j = i;
			while (j < g_772604) {
				if (id != *(int*) p) {
					break;
				}
				p += 0xac;
				count++;
				j++;
			}
			g_6b5de0->vtbl->SelectBank(g_6b5de0, 0, id);
			g_6b5de0->vtbl->SelectSample(g_6b5de0, 4, i * 6, count * 2);
			i += count;
			rec += count;
		}
	}
	if (snd != 0) {
		snd->vtbl->Release(snd);
		g_6b5de0->vtbl->SetRenderState(g_6b5de0, 7, 1);
	} else {
		g_6b5de0->vtbl->End(g_6b5de0);
	}
done:
	g_772604 = start;
	g_6b5de0->vtbl->SetRenderState(g_6b5de0, 7, 1);
	g_6b5de0->vtbl->SetRenderState(g_6b5de0, 0x88, 1);
	fcn_0047c520();
	return 1;
}
