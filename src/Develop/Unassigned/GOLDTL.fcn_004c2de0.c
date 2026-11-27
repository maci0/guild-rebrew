#include <stdio.h>
#include <string.h>

/* entry of the 0x21c-stride table at 0x7f4ca0 */
typedef struct {
	int unused0;
	unsigned int value;
	char unused8;
	char type;
	char pad[0x21c - 10];
} VOICE_ENTITY_RECORD;

extern VOICE_ENTITY_RECORD g_7f4ca0[];
extern int g_774934;
extern char g_6b5c60;
extern char g_68a4cc[]; /* "_HS" */
extern char g_68a4d0[]; /* "_M3" */
extern char g_68a4d4[]; /* "_M2" */
extern char g_68a4d8[]; /* "_M1" */
extern char g_68a4dc[]; /* "_W2" */
extern char g_68a4e0[]; /* "_W1" */
extern char g_68a4e4[]; /* "_M%i" */
extern char g_68a4ec[]; /* "_W%i" */
extern char g_68a4c4[]; /* "%02i" */
extern char g_67728c[]; /* "%s%s" */
extern char g_68a47c[]; /* "Voicesample not found:\n%s" */
extern char g_68a498[]; /* "Voicesample not found in variation:\n%s %i" */

int __cdecl sb_IsSampleType2(int a0, char* text);
int __cdecl sb_PreparePrioritizedVoice(int a0, char* text, int n);
int __cdecl sb_PrepareVoice(int a0, char* text);

/* ADDRESS: GOLDTL 0x004c2de0 */
int __cdecl d3snd_PrepareVoiceSample(int code, int bank, char* text, int variation)
{
	char num[0x14];
	char tmp[0x10];
	char buf[0x104];
	int res;

	if (g_774934 == 0) {
		return 0;
	}
	if (code != -7) {
		if (code >= 0x300 || code < 0) {
			if (code == -2) {
				memcpy(num, g_68a4e0, 4);
			} else if (code == -1) {
				memcpy(num, g_68a4dc, 4);
			} else if (code == -5) {
				memcpy(num, g_68a4d8, 4);
			} else if (code == -4) {
				memcpy(num, g_68a4d4, 4);
			} else if (code == -3) {
				memcpy(num, g_68a4d0, 4);
			} else if (code == -6) {
				memcpy(num, g_68a4cc, 4);
			} else if (code == -8) {
				num[0] = g_6b5c60;
			}








		} else {
			if (g_7f4ca0[code].type == 1) {
				sprintf(num, g_68a4ec, (g_7f4ca0[code].value & 1) + 1);
			} else if (g_7f4ca0[code].type == 0) {
				sprintf(num, g_68a4e4, g_7f4ca0[code].value % 3 + 1);
			}



		}
		sprintf(buf, g_67728c, text, num);
		res = sb_IsSampleType2(bank, buf);
		if (variation >= 0 && res == 0) {
			sprintf(tmp, g_68a4c4, variation);
			strcat(num, tmp);
		}
		sprintf(buf, g_67728c, text, num);
		if (res != 0 && variation >= 0) {
			res = sb_PreparePrioritizedVoice(bank, buf, variation);
			if (res == 0) {
				sprintf(buf, g_68a498, text, variation);
			}
			return res;
		}
	} else {
		sprintf(buf, text);
	}
	res = sb_PrepareVoice(bank, buf);
	if (res == 0) {
		sprintf(buf, g_68a47c, text);
	}
	return res;
}
