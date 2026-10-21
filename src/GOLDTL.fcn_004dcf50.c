extern int g_772f3c;
extern int g_68bfc0;
extern int g_6b8010;
extern unsigned short g_774970;
extern float g_662b28;
extern unsigned char g_9a3800[];

int __cdecl fcn_004f4830(int idx, void* dst);
void __cdecl fcn_004e4450(int k, int flag);
void __cdecl fcn_004e4730(char* scene);
int __cdecl fcn_004f5740(int key, int* out);
char* __cdecl fcn_00508e40(int id);
int __cdecl fcn_004e44b0(int a1, int a2);
void __cdecl fcn_004e44f0(int a1);
int __cdecl fcn_004e4ae0(char* name, int a2);
int __cdecl fcn_004e4b20(int a1, int a2, char* name, int mode);
int __cdecl fcn_00420780(char* snd, int flag);
int __cdecl fcn_004e6cb0(int n);
void __cdecl fcn_004e4e90(char* snd);
int __cdecl fcn_00423460(int* a1);
void __cdecl fcn_004e4c90(int dur);
void __cdecl fcn_004727a0(int k, int i);
int __cdecl fcn_00493dc0(unsigned short* a, unsigned short* b);
unsigned int* __cdecl fcn_004fda30(unsigned int a0);
int __cdecl fcn_00519190(int fmt, ...);
int __cdecl sprintf(char*, const char*, ...);
unsigned int __cdecl strlen(const char*);
int __cdecl fcn_0050f980(int a, int b, int c);
int __cdecl fcn_004e4b40(int a1, int a2, char* s, int a4, int a5);

int __cdecl fcn_00493e50(int a, int b);
int __cdecl fcn_004938c0(void* m);
void __cdecl fcn_00493920(void* m);
void __cdecl fcn_004c51a0(int a, int b, int c, int d);
void __cdecl fcn_004c54c0(int a, int b, int c, int d);
float __cdecl fcn_004ff210(int a, int b);
int __cdecl fcn_005c6270(int a, int b);
void __cdecl fcn_004f6810(int a, int b);
void __cdecl fcn_004f6ce0(int a, int b, char* s);
void __cdecl fcn_004f6850(int a, int b, int c, int d, int e);
int* __cdecl fcn_00509570(int a);
void __cdecl fcn_004b4650(int a, int b);
void __cdecl fcn_004e48b0(void);
void __cdecl fcn_004e4eb0(void);
void __cdecl fcn_004c09b0(void);
void __cdecl fcn_00420840(int a);
void __cdecl fcn_004432d0(int a, int b);
void __cdecl fcn_004e4b00(int a);

typedef struct S2d {
	char b[0x2d];
} S2d;

int __cdecl fcn_004f56b0(int a, S2d s, int c);
int __cdecl fcn_004f5f30(int a, int b, int* c);
void __cdecl fcn_004e51d0(unsigned int* a0, int a1);
void* __cdecl memcpy(void*, const void*, unsigned int);

typedef struct CMsg {
	int state;      /* +0x00 */
	float f04;      /* +0x04 */
	int i08;        /* +0x08 */
	float f0c;      /* +0x0c */
	char text[4];   /* +0x10 */
	int id[6];      /* +0x14 */
	int pad[9];     /* +0x2c */
} CMsg;

/* ADDRESS: GOLDTL 0x004dcf50 */
int __cdecl fcn_004dcf50(int a0)
{
	int rec[9];
	int list[0x20];
	int sel[0x20];
	int flags[0x20];
	float ratio[5];
	union {
		float f[9];
		int i[9];
	} tmp;
	CMsg msg;
	char str[0x100];
	char path[0x100];
	char line[0x100];
	char work[0x100];
	char buf[0x100];
	float f;
	float fsum;
	int n;
	int i;
	int j;
	int cnt;
	unsigned char cbe;
	char recbuf[0x2d];
	char tmprec[0x2d];
	int h;
	int h2;
	int hWait;
	int h88;
	int h94;
	int h80;
	int h84;
	int h8c;
	int h90;
	int h9c;
	int h0;
	int hStrafe;
	int h14;
	int x60;
	int x6c;
	int x68;
	int x74;
	int x98;
	int inst;
	int st;
	int rnd;
	int votes;
	int eIdx;
	int didFolter;
	int div3;
	int hAnk;
	int acc;
	char* p34;
	char* p38;
	char* p3c;
	char* p40;
	char* p44;
	char* p48;
	char* end;
	char* pend;
	char* nam;
	char* pent;

	h88 = 0;
	h94 = 0;
	h80 = 0;
	h84 = 0;
	h8c = 0;
	h90 = 0;
	h9c = 0;
	h0 = 0;
	h14 = 0;
	hStrafe = 0;
	hAnk = 0;
	x98 = -1;
	didFolter = 0;
	fcn_004f4830(0, rec);
	ratio[0] = 1.4f;
	ratio[1] = 1.2f;
	ratio[2] = 1.0f;
	ratio[3] = 0.8f;
	ratio[4] = 0.6f;
	i = rec[6];
	if (i >= 4) {
		i = 4;
	} else if (i <= 0) {
		i = 0;
	}
	f = ratio[i];
	fcn_004e4450(g_68bfc0, 0);
	fcn_004e4730("Gericht.ed3");
	msg.state = 0;
	msg.f04 = 0.0f;
	msg.i08 = 0;
	msg.f0c = 1000.0f;
	msg.text[0] = 10;
	msg.text[1] = 0;
	msg.id[0] = *(int*) (a0 + 0x34);
	msg.id[1] = *(int*) (a0 + 0x38);
	msg.id[2] = *(int*) (a0 + 0x3c);
	msg.id[3] = *(int*) (a0 + 0x40);
	msg.id[4] = *(int*) (a0 + 0x44);
	msg.id[5] = *(int*) (a0 + 0x48);
	for (i = 0; i < 9; i++) {
		msg.pad[i] = 0;
	}
	n = fcn_004f5740(*(int*) (a0 + 0x7c), list);
	p34 = fcn_00508e40(*(int*) (a0 + 0x34));
	if (p34 == 0) {
		return;
	}
	msg.text[1] = (char) n;
	p38 = fcn_00508e40(*(int*) (a0 + 0x38));
	if (p38 == 0) {
		return;
	}
	p3c = fcn_00508e40(*(int*) (a0 + 0x3c));
	if (p3c == 0) {
		return;
	}
	p40 = fcn_00508e40(*(int*) (a0 + 0x40));
	if (p40 == 0) {
		return;
	}
	p44 = fcn_00508e40(*(int*) (a0 + 0x44));
	if (p44 == 0) {
		return;
	}
	p48 = fcn_00508e40(*(int*) (a0 + 0x48));
	if (p48 == 0) {
		if (msg.text[1] > 2 && *(int*) (a0 + 0x48) != -1) {
			return;
		}
	}
	if (g_772f3c == 0) {
		h9c = fcn_00420780("Athmos\\Athmo_sitzung.mp3", 0x40);
	}
	if (fcn_004e6cb0(2) != 0) {
		fcn_004e4e90("cd2\\ArmerDelinquent.mp3");
	} else {
		fcn_004e4e90("cd2\\ImKerker.mp3");
	}
	h2 = fcn_004e4ae0("ADDON\\PROZESS_NEU.sbf", 0);
	msg.pad[0] = fcn_00493dc0((unsigned short*) p34, (unsigned short*) p38);
	sprintf(str, "%s ", fcn_004fda30(*(unsigned short*) p3c));
	end = str + strlen(str);
	sprintf(end, "%s ", fcn_004fda30(*(unsigned short*) p34));
	end = str + strlen(str);
	sprintf(end, "%s ", fcn_004fda30(*(unsigned short*) p38));
	end = str + strlen(str);
	sprintf(end, "%s ", fcn_004fda30(*(unsigned short*) p40));
	end = str + strlen(str);
	sprintf(end, "%s", fcn_004fda30(*(unsigned short*) p44));
	fcn_004e44b0((int) "cutscenes\\prozess\\prozess-create2.esc", (int) str);
	fcn_004e44b0((int) "cutscenes\\prozess\\prozess-richter.esc", (int) "2");
	fcn_004e44b0((int) "cutscenes\\prozess\\prozess-beisitzer1.esc", (int) "2");
	fcn_004e44b0((int) "cutscenes\\prozess\\prozess-beisitzer2.esc", (int) "2");
	fcn_004e44f0(fcn_004e44b0((int) "cutscenes\\prozess\\prozess-intro.esc", (int) ""));
	fcn_004e44b0((int) "cutscenes\\prozess\\prozess-richter-reden.esc", (int) "");
	fcn_004e4450(g_68bfc0, 1);
	fcn_004727a0(g_68bfc0, 0);
	fcn_00519190(0x1491);
	hWait = fcn_004e4b20(*(unsigned short*) p3c, h2, "_PROZESS_NEU", 5);
	while (hWait != 0 && fcn_00423460(&hWait) != 0) {
		fcn_004e4c90(1);
	}
	fcn_004e4c90(1);
	fcn_004727a0(g_68bfc0, 0);
	fcn_00519190(0x6811b0);
	fcn_00519190(0x1492, *(unsigned short*) p34, *(unsigned short*) p38,
		*(unsigned short*) p34);
	fcn_004e4c90(4);
	h = fcn_004e44b0((int) "cutscenes\\prozess\\prozess-klaeger.esc", (int) "1");
	fcn_004727a0(g_68bfc0, 0);
	fcn_00519190(0x6811b0);
	fcn_00519190(0x1499, *(unsigned short*) p38);
	hWait = fcn_004e4b20(*(unsigned short*) p34, h2, "_PROZESS_NEU",
		*(char*) (p38 + 9) == 1);
	while (hWait != 0 && fcn_00423460(&hWait) != 0) {
		fcn_004e4c90(1);
	}
	fcn_004e4c90(1);
	fcn_004e44f0(h);
	for (i = 0; i < 0x20; i++) {
		flags[i] = 0;
	}
	cnt = 0;
	for (i = 0; i < n; i++) {
		sel[i] = *(int*) (g_9a3800 + list[i] * 45);
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
			memcpy(recbuf, g_9a3800 + list[i] * 45, 45);
			flags[i] = 1;
			for (j = i + 1; j < n; j++) {
				if (flags[j] == -1) {
					continue;
				}
				memcpy(tmprec, g_9a3800 + list[j] * 45, 45);
				if (recbuf[0x1c] == tmprec[0x1c]) {
					flags[j] = -1;
					flags[i] += 1;
				}
			}
		}
	}
	fsum = 0.0f;
	for (j = 0; j < n; j++) {
		memcpy(recbuf, g_9a3800 + list[j] * 45, 45);
		fcn_004f4830(recbuf[0x1c] & 0xff, tmp.i);
		if (flags[j] != -1) {
			fsum += (float) tmp.i[3] * f;
			h = fcn_004e44b0((int) "cutscenes\\prozess\\prozess-klaeger.esc", (int) "1");
			fcn_004f56b0((int) work, *(S2d*) recbuf, flags[j]);
			fcn_004727a0(g_68bfc0, 0);
			fcn_00519190(0x68c998);
			fcn_00519190((int) work);
			hWait = fcn_004e4b20(*(unsigned short*) p34, h2, "_PROZESS_GESETZ", cbe & 0xff);
			while (hWait != 0 && fcn_00423460(&hWait) != 0) {
				fcn_004e4c90(1);
			}
			fcn_004e4c90(1);
			fcn_004e6cb0(0x1e);
			fcn_00519190(0x6811b0);
			fcn_004e44f0(h);
		}
	}
	msg.f04 = fsum;
	fcn_004e44b0((int) "cutscenes\\prozess\\prozess-richter-reden.esc", (int) "");
	fcn_00519190(0x14ba, *(unsigned short*) p38, n);
	{
		char ch;

		ch = *(char*) (p38 + 9);
		hWait = fcn_004e4b20(*(unsigned short*) p34, h2, "_PROZESS_NEU", (ch != 0) + 2);
	}
	while (hWait != 0 && fcn_00423460(&hWait) != 0) {
		fcn_004e4c90(1);
	}
	fcn_004e4c90(1);
	fcn_004727a0(g_68bfc0, 0);
	fcn_00519190(0x6811b0);
	fcn_004e44b0((int) "cutscenes\\prozess\\prozess-angeklagter.esc", (int) "0");
	fcn_004e4450(g_68bfc0, 0);
	{
		int id;
		int idx;

		fcn_004e51d0((unsigned int*) a0, (int) &msg);
		id = *(int*) (a0 + 0xc);
		idx = g_774970;
		if (id == *(int*) (0x7f4ca4 + idx * 540)) {
			fcn_004f5f30(*(int*) (p38 + 4), cnt, sel);
		}
	}
	fcn_004e44b0((int) "cutscenes\\prozess\\prozess-angeklagter.esc", (int) "1");
	{
		int cnt2;
		int idx;
		int v1;
		int v2;

		cnt2 = *(unsigned char*) (a0 + 0x30);
		idx = 0;
		if (cnt2 > 0) {
			while (*(int*) (0x9b0e30 + idx * 0x35c) != *(int*) (a0 + 0x34)) {
				idx++;
				if (idx >= cnt2) {
					break;
				}
			}
		}
		v1 = *(int*) (0x9b0eb4 + idx * 0x35c);
		v2 = *(int*) (0x9b0eb8 + idx * 0x35c);
		msg.f0c = *(float*) &v2;
		fcn_004e4450(g_68bfc0, 1);
		fcn_004727a0(g_68bfc0, 0);
		fcn_00519190(0x6811b0);
		msg.state = 4;
		if (v1 == 1) {
			float fm;

			fm = (float) fcn_0050f980(*(unsigned short*) p38, *(unsigned short*) p34, 1);
			msg.i08 = v1;
			fm *= fsum;
			fm *= g_662b28;
			msg.f04 = fsum - fm;
			h = fcn_004e4ae0("PROZESS_3_SCHULDIG.sbf", 0);
			fcn_004e4b40(*(unsigned short*) p38, h, "_PROZESS_3_SCHULDIG", 0, 0);
			fcn_00519190(0x14bd, *(unsigned short*) p38, 0x14be);
		} else {
			h = fcn_004e4ae0("PROZESS_3_NICHT_SCHULDIG.sbf", 0);
			msg.i08 = 0;
			fcn_004e4b40(*(unsigned short*) p38, h, "_PROZESS_3_NICHT_SCHULDIG", 0, 0);
			fcn_00519190(0x14bd, *(unsigned short*) p38, 0x14c4);
			if (p48 != 0 && n > 2) {
				msg.state = 1;
			}
		}
	}
	fcn_004e4c90(2);
	fcn_004e44b0((int) "cutscenes\\prozess\\prozess-beisitzer1.esc", (int) "1");
	fcn_004e44b0((int) "cutscenes\\prozess\\prozess-beisitzer2.esc", (int) "1");
	fcn_004e44b0((int) "cutscenes\\prozess\\prozess-richter-reden.esc", (int) "1");
	fcn_004e44b0((int) "cutscenes\\prozess\\prozess-richter.esc", (int) "");

	/* ---- 0x4dd976: msg.state == 1 follow-up ---- */
	if (msg.state == 1) {
		x60 = fcn_00493e50((int) p34, (int) p38);
		fcn_004727a0(g_68bfc0, 0);
		fcn_00519190(0x6811b0);
		fcn_00519190(0x14ca, *(unsigned short*) p34, *(unsigned short*) p38, x60);
		fcn_004e4c90(4);
		h = fcn_004e44b0((int) "cutscenes\\prozess\\prozess-folter-1.esc", (int) "");
		fcn_004727a0(g_68bfc0, 0);
		fcn_00519190(0x6811b0);
		fcn_004e4450(g_68bfc0, 0);
		fcn_004e51d0((unsigned int*) a0, (int) &msg);
		fcn_004e44f0(h);
		st = 0;
		if (*(unsigned char*) (a0 + 0x30) > 0) {
			for (i = 0; i < *(unsigned char*) (a0 + 0x30); i++) {
				if (*(int*) (0x9b0e30 + i * 0x35c) == *(int*) (a0 + 0x34)) {
					break;
				}
			}
		}
		st = *(int*) (0x9b0eb4 + i * 0x35c);
		fcn_004e4450(g_68bfc0, 1);
		fcn_004727a0(g_68bfc0, 0);
		fcn_00519190(0x6811b0);
		if (st == 1) {
			rnd = fcn_004e6cb0(6);
			votes = fcn_004e6cb0(6);
			h88 = fcn_004e4ae0("PROZESS_4_FOLTER_1.sbf", 0);
			h94 = fcn_004e4ae0("PROZESS_4_FOLTER_2.sbf", 0);
			fcn_004e4b40(*(unsigned short*) p34, h88, "_PROZESS_4_FOLTER_1", rnd, 0x32);
			fcn_004e4b40(*(unsigned short*) p34, h94, "_PROZESS_4_FOLTER_2", votes, 0x12c);
			fcn_00519190(0x14d9);
			fcn_004e4c90(1);
			fcn_00519190(0x6811b0);
			h = fcn_004e44b0((int) "cutscenes\\prozess\\prozess-folter-3.esc", (int) "1");
			msg.pad[6] = 1;
		} else {
			h = fcn_004e44b0((int) "cutscenes\\prozess\\prozess-folter-2.esc", (int) "");
			fcn_00519190(0x14d8);
			msg.pad[6] = 0;
		}
		fcn_004e4c90(4);
		fcn_004e44f0(h);
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
			int msgIds[7] = {
				0x14ed, 0x14f2, 0x14f7, 0x14fc, 0x1501, 0x1506, 0x150b
			};

			eIdx = g_774970;
			if (*(int*) (a0 + 0xc) == *(int*) (0x7f4ca4 + eIdx * 540)) {
				div3 = x60 / 3;
				fcn_004c51a0(*(int*) (p3c + 4), *(int*) (p34 + 4),
					*(unsigned char*) 0x773d75, div3);
				fcn_004c51a0(*(int*) (p40 + 4), *(int*) (p34 + 4),
					*(unsigned char*) 0x773d75, div3);
				fcn_004c51a0(*(int*) (p44 + 4), *(int*) (p34 + 4),
					*(unsigned char*) 0x773d75, div3);
			}

			/* 0x4de05c */
			i = 0;
			do {
				work[i] = "cutscenes\\prozess\\folter\\"[i];
			} while ("cutscenes\\prozess\\folter\\"[i++] != 0);
			pend = work + strlen(work);
			pent = fcn_00508e40(*(int*) (a0 + 0x48));
			fcn_004727a0(g_68bfc0, 0);
			fcn_00519190(0x6811b0);
			h = fcn_004e44b0((int) "cutscenes\\prozess\\prozess-klaeger.esc", (int) "0");
			msg.state = 2;
			fcn_004e4450(g_68bfc0, 0);
			fcn_004e51d0((unsigned int*) a0, (int) &msg);
			st = 0;
			if (*(unsigned char*) (a0 + 0x30) > 0) {
				for (i = 0; i < *(unsigned char*) (a0 + 0x30); i++) {
					if (*(int*) (0x9b0e30 + i * 0x35c) == *(int*) (a0 + 0x34)) {
						break;
					}
				}
			}
			fcn_004e44f0(h);
			h = fcn_004e44b0((int) "cutscenes\\prozess\\prozess-klaeger.esc", (int) "1");
			st = *(int*) (0x9b0eb4 + i * 0x35c);
			inst = st & 0xf;
			if (inst >= 6) {
				inst = 6;
			} else if (inst <= 0) {
				inst = 0;
			}
			x6c = fcn_004938c0(&msg);
			sprintf(buf, "PROZESS_5_FOLTER2_%s.sbf", folterName[inst]);
			h90 = fcn_004e4ae0("PROZESS_5_FOLTER2_GESTEHEN.sbf", 0);
			h8c = fcn_004e4ae0(buf, 0);
			h84 = fcn_004e4ae0("PROZESS_5_FOLTER2_WEITER.sbf", 0);
			h80 = fcn_004e4ae0("PROZESS_5_FOLTER2_UNSCHULDSBETEUERUNG.sbf", 0);
			sprintf(buf, "_PROZESS_5_FOLTER2_%s", folterName[inst]);
			fcn_004e4450(g_68bfc0, 1);
			fcn_004727a0(g_68bfc0, 0);
			fcn_00519190(0x6811b0);
			fcn_00519190(0x14dd, *(unsigned short*) p34, inst * 2 + 0xb20);
			fcn_004e4c90(4);
			fcn_004727a0(g_68bfc0, 0);
			fcn_00519190(0x6811b0);
			fcn_004e4450(g_68bfc0, 0);
			fcn_004e4c90(2);
			fcn_004e44f0(h);
			msg.state = 3;
			fcn_004e4450(g_68bfc0, 0);
			fcn_004e51d0((unsigned int*) a0, (int) &msg);
			st = 0;
			if (*(unsigned char*) (a0 + 0x30) > 0) {
				for (i = 0; i < *(unsigned char*) (a0 + 0x30); i++) {
					if (*(int*) (0x9b0e30 + i * 0x35c) == *(int*) (a0 + 0x3c)) {
						break;
					}
				}
			}
			x74 = *(int*) (0x9b0eb4 + i * 0x35c);
			end = str + strlen(str);
			nam = (char*) fcn_004fda30(*(unsigned short*) pent);
			if (nam != 0) {
				sprintf(end, " %s", nam + 4);
			} else {
				sprintf(end, " handwerker_MANN");
			}
			x98 = g_6b8010;
			fcn_004e4730("ob_GEFAENGNIS_FOLTERKAMMER.ed3");
			fcn_004e44b0((int) "cutscenes\\prozess\\folter-create.esc", (int) str);
			fcn_004e4450(g_68bfc0, 1);
			fcn_004727a0(g_68bfc0, 0);
			fcn_00519190(0x6811b0);
			fcn_00519190(0x14e4);
			hWait = fcn_004e4b20(*(unsigned short*) p3c, h2, "_PROZESS_NEU", 4);
			while (hWait != 0 && fcn_00423460(&hWait) != 0) {
				fcn_004e4c90(1);
			}
			fcn_004e4c90(1);
			i = 0;
			do {
				pend[i] = folterFile[inst][i];
			} while (folterFile[inst][i++] != 0);
			fcn_004e4450(g_68bfc0, 0);
			fcn_004727a0(g_68bfc0, 0);
			fcn_00519190(0x6811b0);
			h = fcn_004e44b0((int) work, (int) "");
			fcn_004e4c90(5);
			fcn_004e4450(g_68bfc0, 1);
			fcn_004727a0(g_68bfc0, 0);
			rnd = fcn_004e6cb0(5);
			fcn_004e4b40(*(unsigned short*) p34, h8c, buf, rnd, 0x320);
			fcn_00519190(0x6811b0);
			fcn_00519190(0x14ec, msgIds[inst] + rnd);
			fcn_004e4c90(5);
			fcn_004e4450(g_68bfc0, 0);
			fcn_00493920(&msg);
			fcn_004e44f0(h);
			fcn_004e4450(g_68bfc0, 1);
			fcn_004727a0(g_68bfc0, 0);
			if (msg.pad[7] != 0) {
				rnd = fcn_004e6cb0(0xa);
				fcn_004e4b40(*(unsigned short*) p38, h90, "_PROZESS_5_FOLTER2_GESTEHEN", rnd, 0);
				fcn_004e4b40(*(unsigned short*) p38, h84, "_PROZESS_5_FOLTER2_WEITER", 0, 0x1f4);
				fcn_004e4450(g_68bfc0, 1);
				fcn_004727a0(g_68bfc0, 0);
				fcn_00519190(0x6811b0);
				fcn_00519190(rnd + 0x1514);
				fcn_00519190(0x68112c);
				fcn_00519190(0x1510);
				fcn_004e4c90(4);
				didFolter = 1;
			} else {
				didFolter = 0;
				rnd = fcn_004e6cb0(6);
				fcn_004e4450(g_68bfc0, 1);
				fcn_004727a0(g_68bfc0, 0);
				fcn_00519190(0x6811b0);
				fcn_00519190(rnd + 0x14e6);
				fcn_004e4b40(*(unsigned short*) p38, h80, "_PROZESS_5_FOLTER2_UNSCHULDSBETEUERUNG", rnd, 0x1f4);
				fcn_004e4c90(5);
			}
		}
		/* 0x4de5fc */
		msg.state = 4;
	}

	/* ---- 0x4de60f ---- */
	if (msg.pad[6] != 0) {
		fcn_004e4450(g_68bfc0, 1);
		fcn_004727a0(g_68bfc0, 0);
		fcn_00519190(0x6811b0);
		if (msg.pad[7] != 0) {
			fcn_00519190(0x151e, *(unsigned short*) p38, *(unsigned short*) p34);
			msg.f04 = msg.f04 * 1.1f;
		} else {
			fcn_00519190(0x151f, *(unsigned short*) p38, *(unsigned short*) p34);
			msg.f04 = msg.f04 * 0.8f;
		}
		fcn_004e4c90(4);
		h = fcn_004e44b0((int) "cutscenes\\prozess\\folterexit.esc", (int) "");
		if (h != 0) {
			fcn_004e44f0(h);
		}
		if (g_772f3c == 0 && x98 != -1) {
			fcn_004432d0(x98, 0);
		}
	}
	/* 0x4de6e0 */
	fcn_004e44b0((int) "cutscenes\\prozess\\prozess-richter.esc", (int) "1");
	fcn_004e44b0((int) "cutscenes\\prozess\\prozess-beisitzer1.esc", (int) "1");
	fcn_004e44b0((int) "cutscenes\\prozess\\prozess-beisitzer2.esc", (int) "1");
	fcn_004e4450(g_68bfc0, 1);
	fcn_004727a0(g_68bfc0, 0);
	fcn_00519190(0x6811b0);
	if (msg.pad[6] != 0) {
		h0 = fcn_004e4ae0("PROZESS_6_FOLTERERGEBNIS.sbf", 0);
		fcn_004e44b0((int) "cutscenes\\prozess\\prozess-richter-reden.esc", (int) "");
		if (didFolter != 0) {
			fcn_004e4b40(*(unsigned short*) p34, h0, "_PROZESS_6_FOLTERERGEBNIS", 0, 0x64);
			fcn_00519190(0x1520, *(unsigned short*) p38, 0x1521);
		} else {
			fcn_004e4b40(*(unsigned short*) p34, h0, "_PROZESS_6_FOLTERERGEBNIS", 1, 0x64);
			fcn_00519190(0x1520, *(unsigned short*) p38, 0x1522);
		}
		fcn_004e4c90(4);
	}
	/* 0x4de7c9 */
	hAnk = fcn_004e4ae0("PROZESS_6_ANKUENDIGUNG.sbf", 0);
	fcn_004e4b40(*(unsigned short*) p34, hAnk, "_PROZESS_6_ANKUENDIGUNG", 0, 0);
	fcn_004e44b0((int) "cutscenes\\prozess\\prozess-richter-reden.esc", (int) "");
	fcn_004e4450(g_68bfc0, 0);
	fcn_004727a0(g_68bfc0, 0);
	fcn_00519190(0x6811b0);
	fcn_00519190(0x1523);
	fcn_004e4c90(4);
	fcn_004e44b0((int) "cutscenes\\prozess\\prozess-richter.esc", (int) "1");
	fcn_004e44b0((int) "cutscenes\\prozess\\prozess-beisitzer1.esc", (int) "1");
	fcn_004e44b0((int) "cutscenes\\prozess\\prozess-beisitzer2.esc", (int) "1");
	fcn_004e4450(g_68bfc0, 0);
	fcn_004e51d0((unsigned int*) a0, (int) &msg);
	fcn_004e4b00(hAnk);
	st = 0;
	if (*(unsigned char*) (a0 + 0x30) > 0) {
		for (i = 0; i < *(unsigned char*) (a0 + 0x30); i++) {
			if (*(int*) (0x9b0e30 + i * 0x35c) == *(int*) (a0 + 0x3c)) {
				break;
			}
		}
	}
	hStrafe = fcn_004e4ae0("PROZESS_6_ABSTIMMUNG_ERGEBNISSE.sbf", 0);
	fcn_004e44b0((int) "cutscenes\\prozess\\prozess-abstimmen-3.esc", (int) "");
	fcn_004e4450(g_68bfc0, 1);
	fcn_004727a0(g_68bfc0, 0);
	fcn_00519190(0x6811b0);
	fcn_00519190(0x1528, *(unsigned short*) p3c);
	fcn_004e4c90(2);
	acc = *(int*) (0x9b0eb4 + i * 0x35c);
	votes = fcn_004e6cb0(3) + acc * 3;
	fcn_004e4b40(*(unsigned short*) p3c, hStrafe, "_PROZESS_6_ABSTIMMUNG_ERGEBNISSE", votes, 0x64);
	fcn_00519190(*(int*) (0x9b0eb4 + i * 0x35c) + 0x152c);
	fcn_004e4c90(2);
	fcn_004e44b0((int) "cutscenes\\prozess\\prozess-richter.esc", (int) "1");
	fcn_004e44b0((int) "cutscenes\\prozess\\prozess-beisitzer1.esc", (int) "1");
	fcn_004e44b0((int) "cutscenes\\prozess\\prozess-beisitzer2.esc", (int) "1");
	if (msg.id[3] != -1) {
		x74 = *(int*) (0x9b1210 + i * 0x35c);
		fcn_004e44b0((int) "cutscenes\\prozess\\prozess-abstimmen-1.esc", (int) "");
		fcn_004727a0(g_68bfc0, 0);
		nam = fcn_00508e40(msg.id[3]);
		fcn_00519190(0x68112c);
		fcn_00519190(0x1528, *(unsigned short*) nam);
		fcn_004e4c90(2);
		fcn_00519190(x74 + 0x152c);
		votes = fcn_004e6cb0(3) + x74 * 3;
		fcn_004e4b40(*(unsigned short*) p3c, hStrafe, "_PROZESS_6_ABSTIMMUNG_ERGEBNISSE", votes, 0x64);
		fcn_004e4c90(2);
		fcn_004e44b0((int) "cutscenes\\prozess\\prozess-beisitzer1.esc", (int) "2");
		acc += *(int*) (0x9b1210 + i * 0x35c);
	}
	if (msg.id[4] != -1) {
		x74 = *(int*) (0x9b156c + i * 0x35c);
		fcn_004e44b0((int) "cutscenes\\prozess\\prozess-abstimmen-2.esc", (int) "");
		fcn_004727a0(g_68bfc0, 0);
		nam = fcn_00508e40(msg.id[4]);
		fcn_00519190(0x68112c);
		fcn_00519190(0x1528, *(unsigned short*) nam);
		fcn_004e4c90(2);
		fcn_00519190(x74 + 0x152c);
		votes = fcn_004e6cb0(3) + x74 * 3;
		fcn_004e4b40(*(unsigned short*) p3c, hStrafe, "_PROZESS_6_ABSTIMMUNG_ERGEBNISSE", votes, 0x64);
		fcn_004e4c90(2);
		fcn_004e44b0((int) "cutscenes\\prozess\\prozess-beisitzer2.esc", (int) "2");
		acc += *(int*) (0x9b156c + i * 0x35c);
	}
	/* 0x4deb1c */
	fcn_004e4b00(hStrafe);
	fcn_004e4b00(h0);
	h14 = fcn_004e4ae0("PROZESS_8.sbf", 0);
	if (acc >= 2) {
		/* 0x4dee4f: not guilty verdict */
		hStrafe = fcn_004e4ae0("PROZESS_7_NICHT_SCHULDIG.sbf", 0);
		fcn_004e4b40(*(unsigned short*) p3c, hStrafe, "_PROZESS_7_NICHT_SCHULDIG",
			(*(char*) (p38 + 9) == 1), 0x64);
		fcn_004e4b40(*(unsigned short*) p3c, h14, "_PROZESS_8",
			2 + (*(char*) (p34 + 9) == 1), 0xc8);
		fcn_004e44b0((int) "cutscenes\\prozess\\prozess-abstimmen-3.esc", (int) "");
		fcn_004e4450(g_68bfc0, 1);
		fcn_004727a0(g_68bfc0, 0);
		fcn_00519190(0x6811b0);
		fcn_00519190(0x152e, *(unsigned short*) p38);
		fcn_004e4c90(4);
		fcn_00519190(0x6811b0);
		fcn_00519190(0x1557, msg.pad[0], *(unsigned short*) p34);
		fcn_004e4c90(4);
		eIdx = g_774970;
		if (*(int*) (a0 + 0xc) == *(int*) (0x7f4ca4 + eIdx * 540)) {
			div3 = msg.pad[0] / 3;
			fcn_004c51a0(*(int*) (p3c + 4), *(int*) (p34 + 4),
				*(unsigned char*) 0x773d75, div3);
			fcn_004c51a0(*(int*) (p40 + 4), *(int*) (p34 + 4),
				*(unsigned char*) 0x773d75, div3);
			fcn_004c51a0(*(int*) (p44 + 4), *(int*) (p34 + 4),
				*(unsigned char*) 0x773d75, div3);
		}
	} else {
		/* 0x4deb4a: guilty verdict */
		msg.state = 5;
		fcn_004e44b0((int) "cutscenes\\prozess\\prozess-abstimmen-3.esc", (int) "");
		fcn_004e44b0((int) "cutscenes\\prozess\\prozess-richter-reden.esc", (int) "");
		fcn_004e4450(g_68bfc0, 0);
		fcn_004727a0(g_68bfc0, 0);
		fcn_004e51d0((unsigned int*) a0, (int) &msg);
		st = 0;
		if (*(unsigned char*) (a0 + 0x30) > 0) {
			for (i = 0; i < *(unsigned char*) (a0 + 0x30); i++) {
				if (*(int*) (0x9b0e30 + i * 0x35c) == *(int*) (a0 + 0x3c)) {
					break;
				}
			}
		}
		hStrafe = fcn_004e4ae0("PROZESS_7_STRAFEN.sbf", 0);
		h0 = fcn_004e4ae0("PROZESS_7_SCHULDIG.sbf", 0);
		st = *(int*) (0x9b0eb4 + i * 0x35c);
		if (st >= 4 && *(char*) (p34 + 2) == 6 && *(char*) (p38 + 0x166) != 0) {
			fcn_004b4650((int) p34, 0x13);
		}
		fcn_004e4450(g_68bfc0, 1);
		fcn_004727a0(g_68bfc0, 0);
		fcn_00519190(0x6811b0);
		fcn_00519190(0x152f, *(unsigned short*) p38);
		fcn_00519190(0x1530);
		fcn_004e4b40(*(unsigned short*) p3c, hStrafe, "_PROZESS_7_SCHULDIG",
			(*(char*) (p38 + 9) == 1), 0x64);
		fcn_004e4b40(*(unsigned short*) p3c, hStrafe, "_PROZESS_7_SCHULDIG", 2, 0xfa);
		fcn_004e4c90(3);
		fcn_004f6810((int) p38, st);
		fcn_004e4450(g_68bfc0, 1);
		fcn_004727a0(g_68bfc0, 0);
		fcn_004f6ce0((int) p38, st, buf);
		fcn_00519190((int) buf);
		if (*(char*) (p38 + 0x166) != 0) {
			if (st == 4 || st == 6 || st == 8) {
				int* p;

				p = fcn_00509570((int) p34);
				if (p != 0) {
					p[0x6c / 4] += 1;
				}
			}
		}
		fcn_004e4b40(*(unsigned short*) p3c, h0, "_PROZESS_7_STRAFEN", st, 0x64);
		fcn_004e4b40(*(unsigned short*) p3c, h14, "_PROZESS_8",
			(*(char*) (p38 + 9) == 1), 0xc8);
		eIdx = g_774970;
		if (*(int*) (a0 + 0xc) == *(int*) (0x7f4ca4 + eIdx * 540)) {
			fcn_004f6850((int) p38, st, (int) p3c, (int) p40, (int) p44);
		}
		fcn_00519190(0x1531);
		eIdx = g_774970;
		if (*(int*) (a0 + 0xc) == *(int*) (0x7f4ca4 + eIdx * 540)) {
			div3 = msg.pad[0] / 3;
			fcn_004c51a0(*(int*) (p3c + 4), *(int*) (p38 + 4),
				*(unsigned char*) 0x773d75, div3);
			fcn_004c51a0(*(int*) (p40 + 4), *(int*) (p38 + 4),
				*(unsigned char*) 0x773d75, div3);
			fcn_004c51a0(*(int*) (p44 + 4), *(int*) (p38 + 4),
				*(unsigned char*) 0x773d75, div3);
		}
		fcn_004e4c90(6);
		fcn_00519190(0x6811b0);
		fcn_00519190(0x1557, msg.pad[0], *(unsigned short*) p38);
		fcn_004e4c90(4);
	}
	/* 0x4defad */
	eIdx = g_774970;
	if (*(int*) (a0 + 0xc) == *(int*) (0x7f4ca4 + eIdx * 540)) {
		if (msg.pad[6] != 0 && *(float*) &msg.pad[8] != 0.0f) {
			fcn_004ff210(*(unsigned short*) p38, (int) *(float*) &msg.pad[8]);
		}
		if (fcn_005c6270((int) p38, 0x22e) != 0) {
			fcn_004c54c0(*(int*) (p38 + 4), *(int*) (p3c + 4), -0x1a, 1);
			fcn_004c54c0(*(int*) (p34 + 4), *(int*) (p3c + 4), 0x1a, 1);
			fcn_004c54c0(*(int*) (p38 + 4), *(int*) (p40 + 4), -0x1a, 1);
			fcn_004c54c0(*(int*) (p34 + 4), *(int*) (p40 + 4), 0x1a, 1);
			fcn_004c54c0(*(int*) (p38 + 4), *(int*) (p44 + 4), -0x1a, 1);
			fcn_004c54c0(*(int*) (p34 + 4), *(int*) (p44 + 4), 0x1a, 1);
		}
	}
	/* 0x4df09b cleanup ladder */
	fcn_004e48b0();
	h = fcn_004e44b0((int) "cutscenes\\prozess\\prozess-ende.esc", (int) "");
	fcn_004e44f0(h);
	h = fcn_004e44b0((int) "cutscenes\\prozess\\prozess-exit.esc", (int) "");
	fcn_004e44f0(h);
	if (h9c != 0) {
		fcn_00420840(h9c);
	}
	fcn_004e4eb0();
	fcn_004c09b0();
	if (h2 != 0) {
		fcn_004e4b00(h2);
	}
	if (h0 != 0) {
		fcn_004e4b00(h0);
	}
	if (hStrafe != 0) {
		fcn_004e4b00(hStrafe);
	}
	if (h14 != 0) {
		fcn_004e4b00(h14);
	}
	if (h90 != 0) {
		fcn_004e4b00(h90);
	}
	if (h8c != 0) {
		fcn_004e4b00(h8c);
	}
	if (h84 != 0) {
		fcn_004e4b00(h84);
	}
	if (h88 != 0) {
		fcn_004e4b00(h88);
	}
	if (h94 != 0) {
		fcn_004e4b00(h94);
	}
	if (h80 != 0) {
		fcn_004e4b00(h80);
	}

	return;
}
