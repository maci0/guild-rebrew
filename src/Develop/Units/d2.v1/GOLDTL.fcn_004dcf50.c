extern int g_772f3c;
extern int g_68bfc0;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
extern float g_662b28;
#include "client_straftat.h"
extern char g_9b0eb4[];
extern char g_9b1210[];
extern char g_9b156c[];

int __cdecl gm_GetLawEntry(int idx, void* dst);
void __cdecl d2_SetFormVisibilityIfAllowed(int k, int flag);
void __cdecl cut_StartSceneCutscene(char* scene);
int __cdecl gs_CollectStraftatenByState(int key, int* out);
char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl evt_StartGfxScript(int a1, int a2);
void __cdecl cut_WaitForScript(int a1);
int __cdecl sb_LoadLocalizedSampleBankIfAllowed(char* name, int a2);
int __cdecl d3snd_PlaySoundEffectIfAllowed(int a1, int a2, char* name, int mode);
int __cdecl msx_StartAmbientTrack(char* snd, int flag);
int __cdecl cut_RandMod(int n);
void __cdecl msx_StartMusicIfAllowed(char* snd);
int __cdecl sb_CheckVoicePlaying(int a1);
void __cdecl cut_WaitTicks(int dur);
void __cdecl d2_SetForm(int k, int i);
int __cdecl gm_CalcTrialCourtFee(unsigned short* a, unsigned short* b);
unsigned int* __cdecl gm_SelectEntityHeadSet(unsigned int a0);
int __cdecl io_AppendText(int fmt, ...);
int __cdecl sprintf(char*, const char*, ...);
unsigned int __cdecl strlen(const char*);
float __cdecl gm_CalcEntityFavor(unsigned int a, unsigned int b, unsigned int c);
int __cdecl d3snd_QueueSoundIfAllowed(int a1, int a2, char* s, int a4, int a5);

int __cdecl gm_CalcTrialTortureFee(int a, int b);
int __cdecl gm_CalcTrialTortureRounds(void* m);
void __cdecl cut_EvaluateTortureStep(void* m);
int __cdecl cm_RequestTransferCurrencyNoKill(int a, int b, unsigned char c, int d);
void __cdecl cm_RequestCopyEntityData(int a, int b, int c, int d);
float __cdecl gm_ApplyEntityHealthDelta(int a, int b);
int __cdecl gm_HasActiveSpecialObject(int a, int b);
void __cdecl gm_ValidateProzessCharge(int a, int b);
void __cdecl cut_FormatProzessPunishment(int a, int b, char* s);
void __cdecl cut_ExecuteProzessPunishment(int a, int b, int c, int d, int e);
int* __cdecl gm_GetEntityTableEntry(int a);
void __cdecl gm_IncrementMissionActionCount(int a, int b);
void __cdecl cut_FadeToBlack(void);
void __cdecl msx_RestoreMusicIfAllowed(void);
void __cdecl d3snd_StopTrackedVoices(void);
void __cdecl msx_StopAmbientTrack(int a);
void __cdecl d3_SelectSceneContext(int a, int b);
void __cdecl cut_UnloadSampleBank(int a);

typedef struct S2d {
	char b[0x2d];
} S2d;

int __cdecl gs_FormatStraftatText(int a, S2d s, int c);
int __cdecl gs_ClearStraftatenByIds(int a, int b, int* c);
void __cdecl cut_RunTurnRound(unsigned int* a0, int a1);
void* __cdecl memcpy(void*, const void*, unsigned int);

typedef struct CMsg {
	int state;      /* +0x00 */
	float f04;      /* +0x04 */
	int i08;        /* +0x08 */
	float f0c;      /* +0x0c */
	unsigned char text[4];   /* +0x10 */
	int id[6];      /* +0x14 */
	int pad[9];     /* +0x2c */
	int hnd[8];
} CMsg;

/* ADDRESS: GOLDTL 0x004dcf50 */
int __cdecl cut_RunProzess(int a0)
{
	CMsg msg;
	int i;
	int j;
	int n;
	int cnt;
	float f;
	float fsum;
	char* p34;
	char* p38;
	char* p3c;
	char* p40;
	char* p44;
	char* p48;
	int h;
	int h2;
	int hWait;
	int h0;
	int h14;
	int hStrafe;
	int hAnk;
	int x68;
	int x74;
	int st;
	int rnd;
	int votes;
	int eIdx;
	int didFolter;
	int div3;
	int acc;
	char* end;
	char* pend;
	char* nam;
	char* pent;
	union {
		float f[5];
		int i[9];
		char c[0x2d];
	} tbl;
	union {
		int i[9];
		char c[0x2d];
	} rec;
	char str[0x100];
	int list[0x20];
	int sel[0x20];
	char work[0x100];
	char buf[0x200];


	msg.hnd[2] = 0;
	msg.hnd[5] = 0;
	msg.hnd[0] = 0;
	msg.hnd[1] = 0;
	msg.hnd[3] = 0;
	msg.hnd[4] = 0;
	msg.hnd[7] = 0;
	msg.hnd[6] = -1;
	tbl.f[0] = 1.4f;
	tbl.f[1] = 1.2f;
	tbl.f[2] = 1.0f;
	tbl.f[3] = 0.8f;
	tbl.f[4] = 0.6f;
	gm_GetLawEntry(0, rec.i);
	i = rec.i[6];
	if (i < 4) {
		if (i <= 0) {
			i = 0;
		}
	} else {
		i = 4;
	}
	f = tbl.f[i];
	d2_SetFormVisibilityIfAllowed(g_68bfc0, 0);
	cut_StartSceneCutscene("Gericht.ed3");
	msg.state = 0;
	msg.f04 = 0.0f;
	msg.i08 = 0;
	msg.f0c = 1000.0f;
	msg.text[0] = 10;
	msg.text[1] = 0;
	msg.pad[0] = 0;
	msg.pad[1] = 0;
	msg.pad[2] = 0;
	msg.pad[3] = 0;
	msg.pad[4] = 0;
	msg.pad[5] = 0;
	msg.pad[6] = 0;
	msg.pad[7] = 0;
	msg.pad[8] = 0;
	msg.id[0] = *(int*) (a0 + 0x34);
	msg.id[1] = *(int*) (a0 + 0x38);
	msg.id[2] = *(int*) (a0 + 0x3c);
	msg.id[3] = *(int*) (a0 + 0x40);
	msg.id[4] = *(int*) (a0 + 0x44);
	msg.id[5] = *(int*) (a0 + 0x48);
	n = gs_CollectStraftatenByState(*(int*) (a0 + 0x7c), list);
	msg.text[1] = (char) n;
	p34 = gm_LookupEntityRecordById(*(int*) (a0 + 0x34));
	if (p34 == 0) {
		return;
	}
	p38 = gm_LookupEntityRecordById(*(int*) (a0 + 0x38));
	if (p38 == 0) {
		return;
	}
	p3c = gm_LookupEntityRecordById(*(int*) (a0 + 0x3c));
	if (p3c == 0) {
		return;
	}
	p40 = gm_LookupEntityRecordById(*(int*) (a0 + 0x40));
	if (p40 == 0) {
		return;
	}
	p44 = gm_LookupEntityRecordById(*(int*) (a0 + 0x44));
	if (p44 == 0) {
		return;
	}
	p48 = gm_LookupEntityRecordById(*(int*) (a0 + 0x48));
	if (p48 == 0) {
		if (msg.text[1] > 2 && *(int*) (a0 + 0x48) != -1) {
			return;
		}
	}
	if (g_772f3c == 0) {
		msg.hnd[7] = msx_StartAmbientTrack("Athmos\\Athmo_sitzung.mp3", 0x40);
	}
	if (cut_RandMod(2) != 0) {
		msx_StartMusicIfAllowed("cd2\\ArmerDelinquent.mp3");
	} else {
		msx_StartMusicIfAllowed("cd2\\ImKerker.mp3");
	}
	h2 = sb_LoadLocalizedSampleBankIfAllowed("ADDON\\PROZESS_NEU.sbf", 0);
	msg.pad[0] = gm_CalcTrialCourtFee((unsigned short*) p34, (unsigned short*) p38);
	sprintf(str, "%s ", (char*) gm_SelectEntityHeadSet(*(unsigned short*) p3c) + 4);
	end = str + strlen(str);
	sprintf(end, "%s ", (char*) gm_SelectEntityHeadSet(*(unsigned short*) p34) + 4);
	end = str + strlen(str);
	sprintf(end, "%s ", (char*) gm_SelectEntityHeadSet(*(unsigned short*) p38) + 4);
	end = str + strlen(str);
	sprintf(end, "%s ", (char*) gm_SelectEntityHeadSet(*(unsigned short*) p40) + 4);
	end = str + strlen(str);
	sprintf(end, "%s", (char*) gm_SelectEntityHeadSet(*(unsigned short*) p44) + 4);
	evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-create2.esc", (int) str);
	evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-richter.esc", (int) "2");
	evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-beisitzer1.esc", (int) "2");
	evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-beisitzer2.esc", (int) "2");
	cut_WaitForScript(evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-intro.esc", (int) ""));
	evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-richter-reden.esc", (int) "");
	d2_SetFormVisibilityIfAllowed(g_68bfc0, 1);
	d2_SetForm(g_68bfc0, 0);
	io_AppendText(0x1491);
	hWait = d3snd_PlaySoundEffectIfAllowed(*(unsigned short*) p3c, h2, "_PROZESS_NEU", 5);
	while (hWait != 0 && sb_CheckVoicePlaying(hWait) != 0) {
		cut_WaitTicks(1);
	}
	cut_WaitTicks(1);
	d2_SetForm(g_68bfc0, 0);
	io_AppendText(0x6811b0);
	io_AppendText(0x1492, *(unsigned short*) p34, *(unsigned short*) p38,
		*(unsigned short*) p34);
	cut_WaitTicks(4);
	h = evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-klaeger.esc", (int) "1");
	d2_SetForm(g_68bfc0, 0);
	io_AppendText(0x6811b0);
	io_AppendText(0x1499, *(unsigned short*) p38);
	hWait = d3snd_PlaySoundEffectIfAllowed(*(unsigned short*) p34, h2, "_PROZESS_NEU",
		*(char*) (p38 + 9) == 1);
	while (hWait != 0 && sb_CheckVoicePlaying(hWait) != 0) {
		cut_WaitTicks(1);
	}
	cut_WaitTicks(1);
	cut_WaitForScript(h);
	{
		int flags[0x20];

		for (i = 0; i < 0x20; i++) {
			flags[i] = 0;
		}
		cnt = 0;
		for (i = 0; i < n; i++) {
			sel[i] = g_9a3800[list[i]].id;
			cnt++;
		}
		for (; cnt < 0x20; cnt++) {
			sel[cnt] = -1;
		}
		if (n > 0) {
			for (i = 0; i < n; i++) {
				if (flags[i] == -1) {
					continue;
				}
				memcpy(rec.c, &g_9a3800[list[i]], 45);
				flags[i] = 1;
				for (j = i + 1; j < n; j++) {
					if (flags[j] == -1) {
						continue;
					}
					memcpy(tbl.c, &g_9a3800[list[j]], 45);
					if (rec.c[0x1c] == tbl.c[0x1c]) {
						flags[j] = -1;
						flags[i] += 1;
					}
				}
			}
		}
		fsum = 0.0f;
		for (j = 0; j < n; j++) {
			memcpy(rec.c, &g_9a3800[list[j]], 45);
			gm_GetLawEntry(rec.c[0x1c] & 0xff, tbl.i);
			if (flags[j] != -1) {
				fsum += (float) tbl.i[3] * f;
				h = evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-klaeger.esc", (int) "1");
				gs_FormatStraftatText((int) work, *(S2d*) rec.c, flags[j]);
				d2_SetForm(g_68bfc0, 0);
				io_AppendText(0x68c998);
				io_AppendText((int) work);
				hWait = d3snd_PlaySoundEffectIfAllowed(*(unsigned short*) p34, h2, "_PROZESS_GESETZ",
					tbl.c[0x1e] & 0xff);
				while (hWait != 0 && sb_CheckVoicePlaying(hWait) != 0) {
					cut_WaitTicks(1);
				}
				cut_WaitTicks(1);
				cut_RandMod(0x1e);
				io_AppendText(0x6811b0);
				cut_WaitForScript(h);
			}
		}
	}
	msg.f04 = fsum;
	evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-richter-reden.esc", (int) "");
	io_AppendText(0x14ba, *(unsigned short*) p38, n);
	{
		char ch;

		ch = *(char*) (p38 + 9);
		hWait = d3snd_PlaySoundEffectIfAllowed(*(unsigned short*) p34, h2, "_PROZESS_NEU", (ch != 0) + 2);
	}
	while (hWait != 0 && sb_CheckVoicePlaying(hWait) != 0) {
		cut_WaitTicks(1);
	}
	cut_WaitTicks(1);
	d2_SetForm(g_68bfc0, 0);
	io_AppendText(0x6811b0);
	evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-angeklagter.esc", (int) "0");
	d2_SetFormVisibilityIfAllowed(g_68bfc0, 0);
	{
		int id;
		int idx;

		cut_RunTurnRound((unsigned int*) a0, (int) &msg);
		id = *(int*) (a0 + 0xc);
		idx = g_774970;
		if (id == *(int*) (0x7f4ca4 + idx * 540)) {
			gs_ClearStraftatenByIds(*(int*) (p38 + 4), cnt, sel);
		}
	}
	evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-angeklagter.esc", (int) "1");
	{
		int cnt2;
		int idx;
		int v1;
		int v2;

		cnt2 = *(unsigned char*) (a0 + 0x30);
		idx = 0;
		if (cnt2 > 0) {
			do {
				if (*(int*) (0x9b0e30 + idx * 0x35c) == msg.id[0]) {
					break;
				}
				idx++;
			} while (idx < cnt2);
		}
		v1 = *(int*) (g_9b0eb4 + idx * 0x35c);
		v2 = *(int*) (0x9b0eb8 + idx * 0x35c);
		msg.f0c = *(float*) &v2;
		d2_SetFormVisibilityIfAllowed(g_68bfc0, 1);
		d2_SetForm(g_68bfc0, 0);
		io_AppendText(0x6811b0);
		msg.state = 4;
		if (v1 == 1) {
			float fm;

			fm = (float) gm_CalcEntityFavor(*(unsigned short*) p38, *(unsigned short*) p34, 1);
			msg.i08 = v1;
			fm *= fsum;
			fm *= g_662b28;
			msg.f04 = fsum - fm;
			h = sb_LoadLocalizedSampleBankIfAllowed("PROZESS_3_SCHULDIG.sbf", 0);
			d3snd_QueueSoundIfAllowed(*(unsigned short*) p38, h, "_PROZESS_3_SCHULDIG", 0, 0);
			io_AppendText(0x14bd, *(unsigned short*) p38, 0x14be);
		} else {
			h = sb_LoadLocalizedSampleBankIfAllowed("PROZESS_3_NICHT_SCHULDIG.sbf", 0);
			msg.i08 = 0;
			d3snd_QueueSoundIfAllowed(*(unsigned short*) p38, h, "_PROZESS_3_NICHT_SCHULDIG", 0, 0);
			io_AppendText(0x14bd, *(unsigned short*) p38, 0x14c4);
			if (p48 != 0 && n > 2) {
				msg.state = 1;
			}
		}
	}
	cut_WaitTicks(2);
	evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-beisitzer1.esc", (int) "1");
	evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-beisitzer2.esc", (int) "1");
	evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-richter-reden.esc", (int) "1");
	evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-richter.esc", (int) "");

	/* ---- 0x4dd976: msg.state == 1 follow-up ---- */
	if (msg.state == 1) {
		msg.pad[1] = gm_CalcTrialTortureFee((int) p34, (int) p38);
		d2_SetForm(g_68bfc0, 0);
		io_AppendText(0x6811b0);
		io_AppendText(0x14ca, *(unsigned short*) p34, *(unsigned short*) p38, msg.pad[1]);
		cut_WaitTicks(4);
		h = evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-folter-1.esc", (int) "");
		d2_SetForm(g_68bfc0, 0);
		io_AppendText(0x6811b0);
		d2_SetFormVisibilityIfAllowed(g_68bfc0, 0);
		cut_RunTurnRound((unsigned int*) a0, (int) &msg);
		cut_WaitForScript(h);
		{
			int cnt2;
			cnt2 = *(unsigned char*) (a0 + 0x30);
			st = 0;
			if (cnt2 > 0) {
				for (i = 0; i < cnt2; i++) {
					if (*(int*) (0x9b0e30 + i * 0x35c) == msg.id[0]) {
						break;
					}
				}
			}
		}
		st = *(int*) (g_9b0eb4 + i * 0x35c);
		d2_SetFormVisibilityIfAllowed(g_68bfc0, 1);
		d2_SetForm(g_68bfc0, 0);
		io_AppendText(0x6811b0);
		if (st == 1) {
			rnd = cut_RandMod(6);
			votes = cut_RandMod(6);
			msg.hnd[2] = sb_LoadLocalizedSampleBankIfAllowed("PROZESS_4_FOLTER_1.sbf", 0);
			msg.hnd[5] = sb_LoadLocalizedSampleBankIfAllowed("PROZESS_4_FOLTER_2.sbf", 0);
			d3snd_QueueSoundIfAllowed(*(unsigned short*) p34, msg.hnd[2], "_PROZESS_4_FOLTER_1", rnd, 0x32);
			d3snd_QueueSoundIfAllowed(*(unsigned short*) p34, msg.hnd[5], "_PROZESS_4_FOLTER_2", votes, 0x12c);
			io_AppendText(0x14d9);
			cut_WaitTicks(1);
			io_AppendText(0x6811b0);
			h = evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-folter-3.esc", (int) "1");
			msg.pad[6] = 1;
		} else {
			h = evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-folter-2.esc", (int) "");
			io_AppendText(0x14d8);
			msg.pad[6] = 0;
		}
		cut_WaitTicks(4);
		cut_WaitForScript(h);
		if (msg.pad[6] != 0) {
			char folterFile[7][0x10] = {
				"dschraube.esc", "stiefel.esc", "peitsche.esc",
				"brandeisen.esc", "eistropfer.esc", "kaefig.esc",
				"streckbank.esc"
			};
			char folterName[7][0x20] = {
				"DAUMENSCHRAUBEN", "SPANISCHE_STIEFEL",
				"NEUNSCHWAENZIGE_PEITSCHE", "ESSE_UND_BRANDEISEN",
				"EISWASSERTROPFER", "HAENGENDER_KAEFIG", "STRECKBANK"
			};
			msg.pad[7] = 0;
			tbl.i[0] = 0x14ed;
			tbl.i[1] = 0x14f2;
			tbl.i[2] = 0x14f7;
			tbl.i[3] = 0x14fc;
			tbl.i[4] = 0x1501;
			tbl.i[5] = 0x1506;
			tbl.i[6] = 0x150b;

			eIdx = g_774970;
			if (*(int*) (a0 + 0xc) == *(int*) (0x7f4ca4 + eIdx * 540)) {
				div3 = msg.pad[1] / 3;
				cm_RequestTransferCurrencyNoKill(*(int*) (p3c + 4), *(int*) (p34 + 4),
					*(signed char*) 0x773d75, div3);
				cm_RequestTransferCurrencyNoKill(*(int*) (p40 + 4), *(int*) (p34 + 4),
					*(signed char*) 0x773d75, div3);
				cm_RequestTransferCurrencyNoKill(*(int*) (p44 + 4), *(int*) (p34 + 4),
					*(signed char*) 0x773d75, div3);
			}

			/* 0x4de05c */
			memcpy(work, "cutscenes\\prozess\\folter\\", 26);
			pend = work + strlen(work);
			pent = gm_LookupEntityRecordById(*(int*) (a0 + 0x48));
			d2_SetForm(g_68bfc0, 0);
			io_AppendText(0x6811b0);
			h = evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-klaeger.esc", (int) "0");
			msg.state = 2;
			d2_SetFormVisibilityIfAllowed(g_68bfc0, 0);
			cut_RunTurnRound((unsigned int*) a0, (int) &msg);
			st = 0;
			{
				int cnt2;
				cnt2 = *(unsigned char*) (a0 + 0x30);
				if (cnt2 > 0) {
					for (i = 0; i < cnt2; i++) {
						if (*(int*) (0x9b0e30 + i * 0x35c) == msg.id[0]) {
							break;
						}
					}
				}
			}
			cut_WaitForScript(h);
			h = evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-klaeger.esc", (int) "1");
			st = *(int*) (g_9b0eb4 + i * 0x35c) & 0xf;
			if (st < 6) {
				if (st > 0) {
					msg.pad[3] = st;
				} else {
					msg.pad[3] = 0;
				}
			} else {
				msg.pad[3] = 6;
			}
			msg.pad[4] = gm_CalcTrialTortureRounds(&msg);
			msg.pad[5] = 0;
			sprintf(buf, "PROZESS_5_FOLTER2_%s.sbf", folterName[msg.pad[3]]);
			msg.hnd[4] = sb_LoadLocalizedSampleBankIfAllowed("PROZESS_5_FOLTER2_GESTEHEN.sbf", 0);
			msg.hnd[3] = sb_LoadLocalizedSampleBankIfAllowed(buf, 0);
			msg.hnd[1] = sb_LoadLocalizedSampleBankIfAllowed("PROZESS_5_FOLTER2_WEITER.sbf", 0);
			msg.hnd[0] = sb_LoadLocalizedSampleBankIfAllowed("PROZESS_5_FOLTER2_UNSCHULDSBETEUERUNG.sbf", 0);
			sprintf(buf, "_PROZESS_5_FOLTER2_%s", folterName[msg.pad[3]]);
			d2_SetFormVisibilityIfAllowed(g_68bfc0, 1);
			d2_SetForm(g_68bfc0, 0);
			io_AppendText(0x6811b0);
			io_AppendText(0x14dd, *(unsigned short*) p34, msg.pad[3] * 2 + 0xb20);
			cut_WaitTicks(4);
			d2_SetForm(g_68bfc0, 0);
			io_AppendText(0x6811b0);
			d2_SetFormVisibilityIfAllowed(g_68bfc0, 0);
			cut_WaitTicks(2);
			cut_WaitForScript(h);
			msg.state = 3;
			d2_SetFormVisibilityIfAllowed(g_68bfc0, 0);
			cut_RunTurnRound((unsigned int*) a0, (int) &msg);
			st = 0;
			{
				int cnt2;
				cnt2 = *(unsigned char*) (a0 + 0x30);
				if (cnt2 > 0) {
					for (i = 0; i < cnt2; i++) {
						if (*(int*) (0x9b0e30 + i * 0x35c) == msg.id[2]) {
							break;
						}
					}
				}
			}
			msg.pad[5] = *(int*) (g_9b0eb4 + i * 0x35c);
			end = str + strlen(str);
			nam = (char*) gm_SelectEntityHeadSet(*(unsigned short*) pent);
			if (nam != 0) {
				sprintf(end, " %s", nam + 4);
			} else {
				sprintf(end, " handwerker_MANN");
			}
			msg.hnd[6] = d3_CurrentContextIndex;
			cut_StartSceneCutscene("ob_GEFAENGNIS_FOLTERKAMMER.ed3");
			evt_StartGfxScript((int) "cutscenes\\prozess\\folter-create.esc", (int) str);
			d2_SetFormVisibilityIfAllowed(g_68bfc0, 1);
			d2_SetForm(g_68bfc0, 0);
			io_AppendText(0x6811b0);
			io_AppendText(0x14e4);
			hWait = d3snd_PlaySoundEffectIfAllowed(*(unsigned short*) p3c, h2, "_PROZESS_NEU", 4);
			while (hWait != 0 && sb_CheckVoicePlaying(hWait) != 0) {
				cut_WaitTicks(1);
			}
			cut_WaitTicks(1);
			i = 0;
			do {
				pend[i] = folterFile[msg.pad[3]][i];
			} while (folterFile[msg.pad[3]][i++] != 0);
			d2_SetFormVisibilityIfAllowed(g_68bfc0, 0);
			d2_SetForm(g_68bfc0, 0);
			io_AppendText(0x6811b0);
			h = evt_StartGfxScript((int) work, (int) "");
			cut_WaitTicks(5);
			d2_SetFormVisibilityIfAllowed(g_68bfc0, 1);
			d2_SetForm(g_68bfc0, 0);
			rnd = cut_RandMod(5);
			d3snd_QueueSoundIfAllowed(*(unsigned short*) p34, msg.hnd[3], buf, rnd, 0x320);
			io_AppendText(0x6811b0);
			io_AppendText(0x14ec, tbl.i[msg.pad[3]] + rnd);
			cut_WaitTicks(5);
			d2_SetFormVisibilityIfAllowed(g_68bfc0, 0);
			cut_EvaluateTortureStep(&msg);
			cut_WaitForScript(h);
			d2_SetFormVisibilityIfAllowed(g_68bfc0, 1);
			d2_SetForm(g_68bfc0, 0);
			if (msg.pad[7] != 0) {
				rnd = cut_RandMod(0xa);
				d3snd_QueueSoundIfAllowed(*(unsigned short*) p38, msg.hnd[4], "_PROZESS_5_FOLTER2_GESTEHEN", rnd, 0);
				d3snd_QueueSoundIfAllowed(*(unsigned short*) p38, msg.hnd[1], "_PROZESS_5_FOLTER2_WEITER", 0, 0x1f4);
				d2_SetFormVisibilityIfAllowed(g_68bfc0, 1);
				d2_SetForm(g_68bfc0, 0);
				io_AppendText(0x6811b0);
				io_AppendText(rnd + 0x1514);
				io_AppendText(0x68112c);
				io_AppendText(0x1510);
				cut_WaitTicks(4);
				didFolter = 1;
			} else {
				didFolter = 0;
				rnd = cut_RandMod(6);
				d2_SetFormVisibilityIfAllowed(g_68bfc0, 1);
				d2_SetForm(g_68bfc0, 0);
				io_AppendText(0x6811b0);
				io_AppendText(rnd + 0x14e6);
				d3snd_QueueSoundIfAllowed(*(unsigned short*) p38, msg.hnd[0], "_PROZESS_5_FOLTER2_UNSCHULDSBETEUERUNG", rnd, 0x1f4);
				cut_WaitTicks(5);
			}
		}
		/* 0x4de5fc */
		msg.state = 4;
	}

	/* ---- 0x4de60f ---- */
	if (msg.pad[6] != 0) {
		d2_SetFormVisibilityIfAllowed(g_68bfc0, 1);
		d2_SetForm(g_68bfc0, 0);
		io_AppendText(0x6811b0);
		if (msg.pad[7] != 0) {
			io_AppendText(0x151e, *(unsigned short*) p38, *(unsigned short*) p34);
			msg.f04 = msg.f04 * 1.1f;
		} else {
			io_AppendText(0x151f, *(unsigned short*) p38, *(unsigned short*) p34);
			msg.f04 = msg.f04 * 0.8f;
		}
		cut_WaitTicks(4);
		h = evt_StartGfxScript((int) "cutscenes\\prozess\\folterexit.esc", (int) "");
		if (h != 0) {
			cut_WaitForScript(h);
		}
		if (g_772f3c == 0 && msg.hnd[6] != -1) {
			d3_SelectSceneContext(msg.hnd[6], 0);
		}
	}
	/* 0x4de6e0 */
	evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-richter.esc", (int) "1");
	evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-beisitzer1.esc", (int) "1");
	evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-beisitzer2.esc", (int) "1");
	d2_SetFormVisibilityIfAllowed(g_68bfc0, 1);
	d2_SetForm(g_68bfc0, 0);
	io_AppendText(0x6811b0);
	if (msg.pad[6] != 0) {
		h0 = sb_LoadLocalizedSampleBankIfAllowed("PROZESS_6_FOLTERERGEBNIS.sbf", 0);
		evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-richter-reden.esc", (int) "");
		if (didFolter != 0) {
			d3snd_QueueSoundIfAllowed(*(unsigned short*) p34, h0, "_PROZESS_6_FOLTERERGEBNIS", 0, 0x64);
			io_AppendText(0x1520, *(unsigned short*) p38, 0x1521);
		} else {
			d3snd_QueueSoundIfAllowed(*(unsigned short*) p34, h0, "_PROZESS_6_FOLTERERGEBNIS", 1, 0x64);
			io_AppendText(0x1520, *(unsigned short*) p38, 0x1522);
		}
		cut_WaitTicks(4);
	}
	/* 0x4de7c9 */
	hAnk = sb_LoadLocalizedSampleBankIfAllowed("PROZESS_6_ANKUENDIGUNG.sbf", 0);
	d3snd_QueueSoundIfAllowed(*(unsigned short*) p34, hAnk, "_PROZESS_6_ANKUENDIGUNG", 0, 0);
	evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-richter-reden.esc", (int) "");
	d2_SetForm(g_68bfc0, 0);
	io_AppendText(0x6811b0);
	io_AppendText(0x1523);
	cut_WaitTicks(4);
	evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-richter.esc", (int) "1");
	evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-beisitzer1.esc", (int) "1");
	evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-beisitzer2.esc", (int) "1");
	d2_SetFormVisibilityIfAllowed(g_68bfc0, 0);
	cut_RunTurnRound((unsigned int*) a0, (int) &msg);
	cut_UnloadSampleBank(hAnk);
	st = 0;
	{
		int cnt2;
		cnt2 = *(unsigned char*) (a0 + 0x30);
		if (cnt2 > 0) {
			for (i = 0; i < cnt2; i++) {
				if (*(int*) (0x9b0e30 + i * 0x35c) == msg.id[2]) {
					break;
				}
			}
		}
	}
	hStrafe = sb_LoadLocalizedSampleBankIfAllowed("PROZESS_6_ABSTIMMUNG_ERGEBNISSE.sbf", 0);
	evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-abstimmen-3.esc", (int) "");
	d2_SetFormVisibilityIfAllowed(g_68bfc0, 1);
	d2_SetForm(g_68bfc0, 0);
	io_AppendText(0x6811b0);
	io_AppendText(0x1528, *(unsigned short*) p3c);
	cut_WaitTicks(2);
	acc = *(int*) (g_9b0eb4 + i * 0x35c);
	votes = cut_RandMod(3) + *(int*) (g_9b0eb4 + i * 0x35c) * 3;
	d3snd_QueueSoundIfAllowed(*(unsigned short*) p3c, hStrafe, "_PROZESS_6_ABSTIMMUNG_ERGEBNISSE", votes, 0x64);
	io_AppendText(acc + 0x152c);
	cut_WaitTicks(2);
	evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-richter.esc", (int) "1");
	evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-beisitzer1.esc", (int) "1");
	evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-beisitzer2.esc", (int) "1");
	if (msg.id[3] >= 0) {
		x74 = *(int*) (g_9b1210 + i * 0x35c);
		evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-abstimmen-1.esc", (int) "");
		d2_SetForm(g_68bfc0, 0);
		nam = gm_LookupEntityRecordById(msg.id[3]);
		io_AppendText(0x68112c);
		io_AppendText(0x1528, *(unsigned short*) nam);
		cut_WaitTicks(2);
		io_AppendText(x74 + 0x152c);
		votes = cut_RandMod(3) + *(int*) (g_9b1210 + i * 0x35c) * 3;
		d3snd_QueueSoundIfAllowed(*(unsigned short*) p3c, hStrafe, "_PROZESS_6_ABSTIMMUNG_ERGEBNISSE", votes, 0x64);
		cut_WaitTicks(2);
		acc += *(int*) (g_9b1210 + i * 0x35c);
		evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-beisitzer1.esc", (int) "2");
	}
	if (msg.id[4] != -1) {
		x74 = *(int*) (g_9b156c + i * 0x35c);
		evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-abstimmen-2.esc", (int) "");
		d2_SetForm(g_68bfc0, 0);
		nam = gm_LookupEntityRecordById(msg.id[4]);
		io_AppendText(0x68112c);
		io_AppendText(0x1528, *(unsigned short*) nam);
		cut_WaitTicks(2);
		io_AppendText(x74 + 0x152c);
		votes = cut_RandMod(3) + *(int*) (g_9b156c + i * 0x35c) * 3;
		d3snd_QueueSoundIfAllowed(*(unsigned short*) p3c, hStrafe, "_PROZESS_6_ABSTIMMUNG_ERGEBNISSE", votes, 0x64);
		cut_WaitTicks(2);
		acc += *(int*) (g_9b156c + i * 0x35c);
		evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-beisitzer2.esc", (int) "2");
	}
	/* 0x4deb1c */
	cut_UnloadSampleBank(hStrafe);
	cut_UnloadSampleBank(h0);
	h14 = sb_LoadLocalizedSampleBankIfAllowed("PROZESS_8.sbf", 0);
	if ((unsigned int) acc < 2) {
		/* 0x4deb4a: guilty verdict */
		hStrafe = sb_LoadLocalizedSampleBankIfAllowed("PROZESS_7_SCHULDIG.sbf", 0);
		h0 = sb_LoadLocalizedSampleBankIfAllowed("PROZESS_7_STRAFEN.sbf", 0);
		msg.state = 5;
		evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-abstimmen-3.esc", (int) "");
		evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-richter-reden.esc", (int) "");
		d2_SetFormVisibilityIfAllowed(g_68bfc0, 0);
		cut_RunTurnRound((unsigned int*) a0, (int) &msg);
		st = 0;
		cnt = *(unsigned char*) (a0 + 0x30);
		if (cnt > 0) {
			i = 0;
			do {
				if (*(int*) (0x9b0e30 + i * 0x35c) == msg.id[2]) {
					break;
				}
				i++;
			} while (i < cnt);
		}
		st = *(int*) (g_9b0eb4 + i * 0x35c);
		if ((unsigned int) st >= 4 && *(char*) (p34 + 2) == 6 && *(char*) (p38 + 0x166) != 0) {
			gm_IncrementMissionActionCount((int) p34, 0x13);
		}
		d2_SetFormVisibilityIfAllowed(g_68bfc0, 1);
		d2_SetForm(g_68bfc0, 0);
		io_AppendText(0x6811b0);
		io_AppendText(0x152f, *(unsigned short*) p38);
		io_AppendText(0x1530);
		d3snd_QueueSoundIfAllowed(*(unsigned short*) p3c, hStrafe, "_PROZESS_7_SCHULDIG",
			((*(char*) (p38 + 9) == 1) & 1), 0x64);
		d3snd_QueueSoundIfAllowed(*(unsigned short*) p3c, hStrafe, "_PROZESS_7_SCHULDIG", 2, 0xfa);
		cut_WaitTicks(3);
		gm_ValidateProzessCharge((int) p38, st);
		d2_SetFormVisibilityIfAllowed(g_68bfc0, 1);
		d2_SetForm(g_68bfc0, 0);
		cut_FormatProzessPunishment((int) p38, st, buf);
		io_AppendText((int) buf);
		if (*(char*) (p38 + 0x166) != 0) {
			if (st == 4 || st == 6 || st == 8) {
				int* p;

				p = gm_GetEntityTableEntry((int) p34);
				if (p != 0) {
					p[0x6c / 4] += 1;
				}
			}
		}
		d3snd_QueueSoundIfAllowed(*(unsigned short*) p3c, h0, "_PROZESS_7_STRAFEN", st, 0x64);
		d3snd_QueueSoundIfAllowed(*(unsigned short*) p3c, h14, "_PROZESS_8",
			((*(char*) (p38 + 9) == 1) & 1), 0xc8);
		eIdx = g_774970;
		if (*(int*) (a0 + 0xc) == *(int*) (0x7f4ca4 + eIdx * 540)) {
			cut_ExecuteProzessPunishment((int) p38, st, (int) p3c, (int) p40, (int) p44);
		}
		io_AppendText(0x1531);
		eIdx = g_774970;
		if (*(int*) (a0 + 0xc) == *(int*) (0x7f4ca4 + eIdx * 540)) {
			div3 = msg.pad[0] / 3;
			cm_RequestTransferCurrencyNoKill(*(int*) (p3c + 4), *(int*) (p38 + 4),
				*(signed char*) 0x773d75, div3);
			cm_RequestTransferCurrencyNoKill(*(int*) (p40 + 4), *(int*) (p38 + 4),
				*(signed char*) 0x773d75, div3);
			cm_RequestTransferCurrencyNoKill(*(int*) (p44 + 4), *(int*) (p38 + 4),
				*(signed char*) 0x773d75, div3);
		}
		cut_WaitTicks(6);
		io_AppendText(0x6811b0);
		io_AppendText(0x1557, msg.pad[0], *(unsigned short*) p38);
		cut_WaitTicks(4);
	} else {
		/* 0x4dee4f: not guilty verdict */
		hStrafe = sb_LoadLocalizedSampleBankIfAllowed("PROZESS_7_NICHT_SCHULDIG.sbf", 0);
		d3snd_QueueSoundIfAllowed(*(unsigned short*) p3c, hStrafe, "_PROZESS_7_NICHT_SCHULDIG",
			((*(char*) (p38 + 9) == 1) & 1), 0x64);
		d3snd_QueueSoundIfAllowed(*(unsigned short*) p3c, h14, "_PROZESS_8",
			2 + ((*(char*) (p34 + 9) == 1) & 1), 0xc8);
		evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-abstimmen-3.esc", (int) "");
		d2_SetFormVisibilityIfAllowed(g_68bfc0, 1);
		d2_SetForm(g_68bfc0, 0);
		io_AppendText(0x6811b0);
		io_AppendText(0x152e, *(unsigned short*) p38);
		cut_WaitTicks(4);
		io_AppendText(0x6811b0);
		io_AppendText(0x1557, msg.pad[0], *(unsigned short*) p34);
		cut_WaitTicks(4);
		eIdx = g_774970;
		if (*(int*) (a0 + 0xc) == *(int*) (0x7f4ca4 + eIdx * 540)) {
			div3 = msg.pad[0] / 3;
			cm_RequestTransferCurrencyNoKill(*(int*) (p3c + 4), *(int*) (p34 + 4),
				*(signed char*) 0x773d75, div3);
			cm_RequestTransferCurrencyNoKill(*(int*) (p40 + 4), *(int*) (p34 + 4),
				*(signed char*) 0x773d75, div3);
			cm_RequestTransferCurrencyNoKill(*(int*) (p44 + 4), *(int*) (p34 + 4),
				*(signed char*) 0x773d75, div3);
		}
	}
	/* 0x4defad */
	eIdx = g_774970;
	if (*(int*) (a0 + 0xc) == *(int*) (0x7f4ca4 + eIdx * 540)) {
		if (msg.pad[6] != 0 && *(float*) &msg.pad[8] < 0.0f) {
			gm_ApplyEntityHealthDelta(*(unsigned short*) p38, (int) *(float*) &msg.pad[8]);
		}
		if (gm_HasActiveSpecialObject((int) p38, 0x22e) != 0) {
			cm_RequestCopyEntityData(*(int*) (p38 + 4), *(int*) (p3c + 4), -0x1a, 1);
			cm_RequestCopyEntityData(*(int*) (p34 + 4), *(int*) (p3c + 4), 0x1a, 1);
			cm_RequestCopyEntityData(*(int*) (p38 + 4), *(int*) (p40 + 4), -0x1a, 1);
			cm_RequestCopyEntityData(*(int*) (p34 + 4), *(int*) (p40 + 4), 0x1a, 1);
			cm_RequestCopyEntityData(*(int*) (p38 + 4), *(int*) (p44 + 4), -0x1a, 1);
			cm_RequestCopyEntityData(*(int*) (p34 + 4), *(int*) (p44 + 4), 0x1a, 1);
		}
	}
	/* 0x4df09b cleanup ladder */
	cut_FadeToBlack();
	h = evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-ende.esc", (int) "");
	cut_WaitForScript(h);
	h = evt_StartGfxScript((int) "cutscenes\\prozess\\prozess-exit.esc", (int) "");
	cut_WaitForScript(h);
	if (msg.hnd[7] != 0) {
		msx_StopAmbientTrack(msg.hnd[7]);
	}
	msx_RestoreMusicIfAllowed();
	d3snd_StopTrackedVoices();
	if (h2 != 0) {
		cut_UnloadSampleBank(h2);
	}
	if (h0 != 0) {
		cut_UnloadSampleBank(h0);
	}
	if (hStrafe != 0) {
		cut_UnloadSampleBank(hStrafe);
	}
	if (h14 != 0) {
		cut_UnloadSampleBank(h14);
	}
	if (msg.hnd[4] != 0) {
		cut_UnloadSampleBank(msg.hnd[4]);
	}
	if (msg.hnd[3] != 0) {
		cut_UnloadSampleBank(msg.hnd[3]);
	}
	if (msg.hnd[1] != 0) {
		cut_UnloadSampleBank(msg.hnd[1]);
	}
	if (msg.hnd[2] != 0) {
		cut_UnloadSampleBank(msg.hnd[2]);
	}
	if (msg.hnd[5] != 0) {
		cut_UnloadSampleBank(msg.hnd[5]);
	}
	if (msg.hnd[0] != 0) {
		cut_UnloadSampleBank(msg.hnd[5]); /* Native tests slot 0, then passes slot 5. */
	}

	return;
}
