#include <windows.h>
#include <stdlib.h>
#include <string.h>

typedef struct rec6 {
	short w[3];
} Rec6;

typedef struct str9 {
	char b[9];
} Str9;

typedef struct str8 {
	char b[8];
} Str8;

typedef struct str7 {
	char b[7];
} Str7;

extern char* __cdecl fcn_0064d1a0(char* s, int c);
extern char* __cdecl fcn_0064d470(char* s, char* sub);
extern char* __cdecl fcn_0064e790(char* s, int c);
extern int __cdecl fcn_0064eeec(char* s);
extern int __cdecl fcn_0065f220(char* a, char* b);
extern char* __cdecl fcn_0066080a(char* s);
extern int __cdecl gm_RandomMod(int n);
extern int __cdecl fcn_004fdec0(char* name);
extern void __cdecl fcn_004b20d0(unsigned char v);
extern void __cdecl fcn_0057ddc0(char* ini);
extern int __cdecl fcn_00538680(void** handle);
extern int __cdecl fcn_00539090(HINSTANCE inst, int unused, int windowed);
extern int __cdecl fcn_00538710(void);
extern void __cdecl fcn_00544750(void);
extern int __cdecl fcn_00538850(int topmost);
extern int __cdecl fcn_00538d00(void);
extern void __cdecl fcn_00538220(void);
extern void __cdecl fcn_00538160(void);
extern int __cdecl fcn_005356e0(void);
extern void __cdecl fcn_0053a400(void);
extern void __cdecl fcn_0051dfe0(char* language);
extern Rec6* __cdecl fcn_00506d50(Rec6* dst, int idx);
extern void __cdecl fcn_005438c0(int v);
extern void __cdecl fcn_005386c0(void* p);

/* ADDRESS: GOLDTL 0x00544c50 */
int __stdcall WinMain(void *instance, void *previous, char *command, int show)
{
	char text[0x100];
	OSVERSIONINFOA os;
	char pbuf[0x8c];
	void *mutex;
	int server;
	int windowed;
	char *p;
	char *e;
	char *q;
	int i;
	int n;
	int mode;
	int val;

	server = 0;
	*(void**) 0x7e1f80 = instance;
	os.dwOSVersionInfoSize = sizeof(os);
	GetVersionExA(&os);
	*(int*) 0x7e246c = (os.dwPlatformId != 1);

	GetModuleFileNameA(*(HMODULE*) 0x7e1f80, (char*) 0x7e22c0, 0x104);
	strcpy((char*) 0x7e2080, (char*) 0x7e22c0);
	p = fcn_0064d1a0((char*) 0x7e2080, 0x5c);
	*p = 0;
	p = fcn_0064d1a0((char*) 0x7e22c0, 0x5c) + 1;
	*(Str9*) p = *(Str9*) 0x6a474c;

	fcn_0057ddc0((char*) 0x7e22c0);

	GetPrivateProfileStringA("Network", "Server", "Server\\Server.dll", (char*) 0x7e1be0, 0x104, (char*) 0x7e22c0);
	strcpy((char*) 0x7e25e0, (char*) 0x7e1be0);
	p = fcn_0064d1a0((char*) 0x7e25e0, 0x5c);
	*p = 0;
	fcn_0066080a(command);

	*(int*) 0x7747e4 = GetPrivateProfileIntA("Gfx", "TextureDivider", 0, (char*) 0x7e22c0);
	*(int*) 0x774930 = GetPrivateProfileIntA("Sound", "msx", 0, (char*) 0x7e22c0);
	*(int*) 0x6a3444 = GetPrivateProfileIntA("Sound", "ambient", 0, (char*) 0x7e22c0);
	*(int*) 0x774934 = GetPrivateProfileIntA("Sound", "sfx", 0, (char*) 0x7e22c0);
	*(int*) 0x774938 = GetPrivateProfileIntA("Sound", "weather", 1, (char*) 0x7e22c0);

	GetPrivateProfileStringA("General", "Bildmodus", "FULLSCREEN", text, 0x100, (char*) 0x7e22c0);
	fcn_0066080a(text);
	windowed = (memcmp(text, (void*) 0x6a46cc, 0xd) == 0);
	if (fcn_0064d470(command, (char*) 0x6a46cc) != 0)
		windowed = 1;
	if (fcn_0064d470(command, (char*) 0x6a46f0) != 0)
		windowed = 0;

	GetPrivateProfileStringA("General", "GfxPath", "\\project\\gfx\\", (char*) 0x6a3448, 0x104, (char*) 0x7e22c0);
	GetPrivateProfileStringA("General", "GamePath", "\\project\\game\\", (char*) 0x6a3550, 0x104, (char*) 0x7e22c0);
	GetPrivateProfileStringA("General", "MoviePath", "\\project\\movie\\", (char*) 0x6a3658, 0x104, (char*) 0x7e22c0);
	GetPrivateProfileStringA("General", "Language", "german", (char*) 0x679888, 0x40, (char*) 0x7e22c0);
	fcn_0051dfe0((char*) 0x679888);
	*(int*) 0x77492c = GetPrivateProfileIntA("General", "show_intro", 0, (char*) 0x7e22c0);
	*(unsigned char*) 0x77534c = (unsigned char) GetPrivateProfileIntA("Gfx", "cur_res", 0, (char*) 0x7e22c0);
	i = *(unsigned char*) 0x77534c;
	q = (char*) 0x6acf68 + i * 8;
	*(int*) 0x6acf80 = *(int*) q;
	*(int*) 0x6acf84 = *(int*) (q + 4);
	if (fcn_0064d470(command, (char*) 0x6a4648) != 0)
		*(int*) 0x7747fc = 1;

	GetPrivateProfileStringA("General", "Stadt", "Augsburg", (char*) 0x7e1d00, 0x40, (char*) 0x7e22c0);
	GetPrivateProfileStringA("Network", "Host", "128.0.0.1", (char*) 0x7e2000, 0x80, (char*) 0x7e22c0);
	*(int*) 0x7e2510 = GetPrivateProfileIntA("Network", "Port", 0x1d6b, (char*) 0x7e22c0);

	p = fcn_0064d470(command, (char*) 0x6a4618);
	if (p != 0) {
		p += 7;
		e = fcn_0064e790(p, 0x22);
		q = (char*) 0x7e1d00;
		if (e != 0) {
			while (p < e)
				*q++ = *p++;
		}
		*q = 0;
	}

	p = fcn_0064d470(command, (char*) 0x6a4610);
	if (p != 0) {
		p += 7;
		e = fcn_0064e790(p, 0x22);
		q = (char*) 0x774828;
		if (e != 0) {
			while (p < e)
				*q++ = *p++;
		}
		*q = 0;
	}

	p = fcn_0064d470(command, (char*) 0x6a4608);
	if (p != 0) {
		p += 4;
		e = fcn_0064e790(p, 0x22);
		q = (char*) 0x7e2000;
		if (e != 0) {
			while (p < e)
				*q++ = *p++;
		}
		*q = 0;
		server = 1;
	} else {
		n = server;
	}

	p = fcn_0064d470(command, (char*) 0x6a4600);
	if (p != 0) {
		p += 6;
		e = fcn_0064e790(p, 0x22);
		if (e != 0) {
			i = e - p;
			memcpy(pbuf, p, i);
			pbuf[i] = 0;
		}
		*(int*) 0x7e2510 = fcn_0064eeec(pbuf);
	}

	if (fcn_00538680(&mutex) != 0)
		exit(1);

	if (fcn_00539090((HINSTANCE) instance, (int) command, windowed) == 0) {
		fcn_00538220();
		return 0;
	}
	if (fcn_00538710() == 0) {
		fcn_00538220();
		return 0;
	}
	if (*(int*) 0x77492c != 0)
		fcn_00544750();
	if (fcn_00538850(windowed) == 0) {
		fcn_00538220();
		return 0;
	}
	if (fcn_00538d00() == 0) {
		fcn_00538220();
		return 0;
	}

	mode = 9;
	val = 0x59a;
	do {
		if (*(int*) 0x7747ec != 0) {
			n = 0x38;
			if (*(char*) 0x774828 != 0) {
				for (i = 0; i < 0x5f; i++) {
					if (fcn_0065f220((char*) 0x774828, *(char**) (0x14a57e0 + i * 4)) == 0) {
						n = i;
						break;
					}
				}
			}
			*(int*) 0x7747b0 = mode;
			*(char*) 0x7e23e0 = (char) (gm_RandomMod(0x5f) + 1);
			*(char*) 0x7e23e1 = (char) (gm_RandomMod(0x5f) + 1);
			*(char*) 0x7e23e3 = (char) n;
			*(char*) 0x7e23e2 = 0x12;
			*(int*) 0x7e23e4 = val;
			*(char*) 0x7e23e8 = 0;
			*(char*) 0x7e23e9 = 1;
			*(Str7*) 0x7e23ea = *(Str7*) 0x6a45f8;
			*(Str8*) 0x7e240a = *(Str8*) 0x6a45f0;
			*(int*) 0x7e2468 = fcn_004fdec0((char*) 0x6a3db4) + 0x639;
			p = (char*) fcn_00506d50((Rec6*) (pbuf + 4), (int) *(unsigned char*) 0x7e23e3);
			*(int*) 0x7e2430 = *(int*) p;
			*(short*) pbuf = *(short*) (p + 4);
			*(char*) 0x7e2434 = (char) *(short*) pbuf;
			*(char*) 0x7e2433 = 0xa8;
			*(char*) 0x7e2430 = 0;
			*(char*) 0x7e2431 = 0;
			fcn_004b20d0(1);
		} else if (server != 0) {
			*(int*) 0x7747b0 = 5;
		} else {
			fcn_0053a400();
			if (*(int*) 0x77495c != 0) {
				fcn_00538160();
				fcn_005356e0();
				if (fcn_00538850(windowed) == 0) {
					fcn_00538220();
					return 0;
				}
				*(int*) 0x77495c = server;
				fcn_005356e0();
			}
		}
		*(int*) 0x774958 = 1;
		if (*(int*) 0x7747b0 != 0 && *(int*) 0x77496c == 0) {
			do {
				fcn_005438c0(0);
			} while (*(int*) 0x774958 != 0);
		}
		if (*(int*) 0x7747ec != 0 || server != 0)
			*(int*) 0x77496c = 1;
		*(int*) 0x774654 = 0;
		*(int*) 0x774650 = 0;
	} while (*(int*) 0x77496c == 0);

	fcn_00538220();
	if (*(int*) 0x774974 != 0)
		fcn_005386c0((void*) 1);
	return 1;
}
