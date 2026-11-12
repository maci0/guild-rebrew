#include <stdio.h>
#include <string.h>

/* entry of the 0x21c-stride table at 0x7f4ca0 */
typedef struct {
	int unused0;
	unsigned int value;
	char unused8;
	char type;
	char pad[0x21c - 10];
} Rec_7f4ca0;

extern Rec_7f4ca0 g_7f4ca0[];
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

int __cdecl fcn_004234a0(int a0, char* text);
int __cdecl fcn_00422600(int a0, char* text, int n);
int __cdecl fcn_00422460(int a0, char* text);

/* ADDRESS: GOLDTL 0x004c2de0 */
int __cdecl fcn_004c2de0(int code, int a1, char* a2, int a3)
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
		sprintf(buf, g_67728c, a2, num);
		res = fcn_004234a0(a1, buf);
		if (a3 >= 0 && res == 0) {
			sprintf(tmp, g_68a4c4, a3);
			strcat(num, tmp);
		}
		sprintf(buf, g_67728c, a2, num);
		if (res != 0 && a3 >= 0) {
			res = fcn_00422600(a1, buf, a3);
			if (res == 0) {
				sprintf(buf, g_68a498, a2, a3);
			}
			return res;
		}
	} else {
		sprintf(buf, a2);
	}
	res = fcn_00422460(a1, buf);
	if (res == 0) {
		sprintf(buf, g_68a47c, a2);
	}
	return res;
}
