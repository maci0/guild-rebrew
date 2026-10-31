#include <stdarg.h>
#include <string.h>

void __cdecl ReportClientMessage(char*);
int __cdecl fcn_0042b2f0(char*, int, int);
int __cdecl gm_RandomMod(int);
void __cdecl fcn_0046ac30(void);
void __cdecl fcn_0046dff0(int, int);
void __cdecl fcn_0046f2c0(int, int);
void __cdecl fcn_00471490(int);
void __cdecl d2_SetForm(char*, int, int);
int __cdecl fcn_00500d60(int, char*);
int __cdecl fcn_004fe330(char*, int);
int __cdecl fcn_0050bc10(int, int, char*);
int __cdecl fcn_00517c00(int, char*, int, char*);
int __cdecl fcn_0051e070(void);
char* __cdecl fcn_0064d41a(char*, char*, ...);
char* __cdecl fcn_0064d530(char*, char*, unsigned);
void* __cdecl fcn_0064d740(void*, const void*, unsigned);
int __cdecl toupper(int);
char* __cdecl fcn_00657a73(int, char*, int);
long __cdecl fcn_0064eeec(char*);

/*
 * io_Text family markup expander.
 * Native extent 0x519190-0x51af00 (0x1d70 bytes: 0x1cac code, 0x68-entry
 * jump table at 0x51ae3c, 0x53-byte index table at 0x51aea4, 8 NOPs).
 * Native locals, measured from the post-push esp: rbuf 0x80, abuf[7][0x40]
 * 0xa0, text 0x260, work 0x1a30, i.e. 0x3200 bytes of stack. MSVC 6 /O2 only
 * puts text above abuf when the two 0x17d0 buffers are members of one
 * aggregate, so they share a struct here. This build's locals total 0x31ec;
 * the native 0x31f4 immediate adds the 4 bytes that its `and esp,-8` prologue
 * reserves. That prologue is not reachable from C at /O2 (see group-323).
 */
/* ADDRESS: GOLDTL 0x00519190 */
int __cdecl io_AppendText(char* format_selector, ...)
{
	struct { char text[0x17d0]; char work[0x17d0]; } S;
	char abuf[7][0x40];
	char rbuf[0x20];
	char dbuf[0xc];
	char nbuf[0x14];
	char sbuf[0x20];
	int v30;
	int v2c;
	int v28;
	char directive;
	int v24;
	int v20;
	int v1c;
	int v18;
	int v14;
	int v10;
	int v0c;
	int v08;
	int ap;
	int digit;
	int text_index;

	text_index = 0;
	v30 = 0;
	v2c = 0;
	v10 = 0;
	v1c = 0;
	v28 = 0;

	if (*(void**)0x1052de0 == 0) {
		return -1;
	}
	v14 = *(int*)0x772514;
	v14 = v14 * 3;
	v14 = v14 * 9;
	v14 = v14 * 9;
	v14 = v14 << 2;
	if (*(int*)(v14 + 0x10161d0) == 0) {
		return -1;
	}
	ap = (int)&format_selector + 4;
	memset(S.text, 0, 0x17d0);
	if ((unsigned)format_selector < 0x4800) {
		v18 = *(int*)((unsigned)format_selector * 4 + 0x14a5320);
		if (v18 == 0) {
			return -1;
		}
		if ((int)strlen((char*)v18) > 0x17c0) {
			return -1;
		}
		fcn_0064d530(S.text, (char*)v18, 0x17c0);
	} else {
		fcn_0064d740(S.text, format_selector, (unsigned)strlen(format_selector) + 1);
	}
	if ((int)strlen(S.text) == 0) {
		goto carry;
	}
loop:
	if (text_index > 0x17d0) {
		goto carry;
	}
	v08 = (unsigned char)S.text[text_index];
	if (v08 != 0x25 && v08 != 0x24 && v08 != 0x7b) {
		goto plain;
	}
	digit = (signed char)S.text[text_index + 1];
	text_index++;
	digit -= 0x30;
	if (digit < 0 || digit > 9) {
		digit = -1;
	} else {
		text_index++;
	}
	directive = S.text[text_index];
	v20 = (int)(S.text + text_index);
	if ((unsigned char)(directive - 0x25) > 0x52) {
		goto loop;
	}
	switch (directive) {
	case 'C':
		memset(*(void**)(v14 + 0x1015f7c), 0, 0x80);
		*(int*)(v14 + 0x10162d4) = 0;
		memset((void*)(v14 + 0x10161d4), 0, 0x100);
		fcn_0046f2c0(*(int*)(v14 + 0x1015f40), 0);
		text_index++;
		goto loop;
	case 'S':
	case 's':
		v0c = (int)(S.text - 1);
		v20 = v0c + text_index;
		if (*(char*)v20 == '$') {
			memcpy(S.text + text_index + 9, S.text + text_index + 1, strlen(S.text) - text_index);
			*(int*)v20 = 0x20202020;
			*(int*)(v20 + 4) = 0x20202020;
			*(short*)(v20 + 8) = 0x2020;
			goto loop;
		}
		v1c = 0xff;
		if (*(char*)v20 == '{') {
			text_index++;
			goto loop;
		}
		goto fmt;
	case 'F':
		text_index++;
		goto loop;
	case 'l':
	case 't':
		v28 = *(int*)ap;
		ap += 4;
		v2c = 1;
		v08 = *(int*)(v14 + 0x10162d4);
		*(int*)(v14 + v08 * 4 + 0x10161d4) = v28;
		*(int*)(v14 + 0x10162d4) = v08 + 1;
		text_index++;
		goto loop;
	case 'T':
		if (S.text[text_index - 1] != 0x25) {
			goto skipt;
		}
		v28 = *(int*)ap;
		ap += 4;
		*(short*)sbuf = *(short*)0x6a238c;
		sbuf[2] = *(char*)0x6a238e;
		fcn_00657a73(v28, nbuf, 10);
		strcat(sbuf, nbuf);
		*(short*)(sbuf + strlen(sbuf)) = *(short*)0x6a2388;
		if (v28 > 1 || v28 == 0) {
			v24 = 2;
		}
		v18 = (int)sbuf;
		fcn_0050bc10(v28, v28, sbuf);
		v08 = (int)strlen(S.text) - text_index + 2;
		memcpy(S.text + text_index + 4, S.text + text_index + 1, v08);
		v0c = (int)(S.text + text_index + 4);
		v24 = (int)strlen(sbuf);
		for (v08 = v24 - 1; v08 >= 0; v08--) {
			*(char*)(v0c + v08) = sbuf[v08];
		}
		*(short*)(S.text + text_index + 2 + v24) = *(short*)0x6a2388;
		memcpy(S.text + text_index + 2, sbuf, v24);
		text_index += v24;
		goto loop;
	skipt:
		v28 = *(int*)ap;
		ap += 4;
		fcn_0050bc10(v28, v28, sbuf);
		v24 = (int)strlen(sbuf);
		v08 = (int)strlen(S.text) - text_index + 2;
		memcpy(S.text + text_index + 2, S.text + text_index + 1, v08);
		*(short*)(S.text + text_index + v08 + 1) = *(short*)0x6a2388;
		memcpy(S.text + text_index, sbuf, v24);
		text_index += v24;
		goto loop;
	case 'w':
		v28 = *(int*)ap;
		ap += 4;
		v28 = *(short*)(v28 * 63 * 4 + 0x8680b4);
		v18 = *(int*)(v28 * 8 + 0x14a79c0);
		strcpy(S.work, (char*)v18);
		v08 = (int)strlen(S.text) - text_index;
		memcpy(S.text + text_index + 1, S.text + text_index + 2, v08);
		v24 = (int)strlen(S.work);
		memcpy(S.text + text_index, S.work, v24 + 1);
		text_index += v24;
		goto loop;
	case 'i':
		v08 = (unsigned char)S.text[text_index + 1];
		if (v08 == 'i' || v08 == 'c' || v08 == 'b' || v08 == 'a'
		    || v08 == 'n' || v08 == 't') {
			goto icon;
		}
		if (digit != -1) {
			v28 = *(int*)ap;
			ap += 4;
			v24 = digit;
			*(short*)sbuf = *(short*)0x6a238c;
			sbuf[2] = *(char*)0x6a238e;
			fcn_00657a73(v24, nbuf, 10);
			strcat(sbuf, nbuf);
			*(short*)(sbuf + strlen(sbuf)) = *(short*)0x6790c4;
			if (v28 > 1 || v28 == 0) {
				v30 = 2;
			}
			fcn_0064d41a(S.work, sbuf, v28);
			v24 = (int)strlen(S.work);
			v08 = (int)strlen(S.text) - text_index;
			memcpy(S.text + text_index + 1, S.text + text_index + 2, v08);
			memcpy(S.text + text_index, S.work, v24 + 1);
			text_index += v24 - 2;
			goto loop;
		}
		v28 = *(int*)ap;
		ap += 4;
		*(short*)sbuf = *(short*)0x6a238c;
		sbuf[2] = *(char*)0x6a238e;
		fcn_00657a73(v28, nbuf, 10);
		strcat(sbuf, nbuf);
		*(short*)(sbuf + strlen(sbuf)) = *(short*)0x6790c4;
		if (v28 > 1 || v28 == 0) {
			v30 = 2;
		}
		fcn_0064d41a(S.work, sbuf, v28);
		v24 = (int)strlen(S.work);
		v08 = (int)strlen(S.text) - text_index;
		memcpy(S.text + text_index + 1, S.text + text_index + 2, v08);
		memcpy(S.text + text_index, S.work, v24 + 1);
		text_index += v24;
		goto loop;
	icon:
		v08 = *(int*)(v14 + 0x10162d4);
		if (v08 > 0x40) {
			ReportClientMessage((char*)0x6a235c);
			text_index += 2;
			goto loop;
		}
		*(int*)(v14 + v08 * 4 + 0x10161d4) = -1;
		v18 = (unsigned char)S.text[text_index + 1];
		if (v18 == 'a' || v18 == 'n') {
			v24 = *(int*)(v14 + 0x10161cc);
			if (v24 != 0x53 && v24 != 0x55) {
				*(int*)(v14 + v08 * 4 + 0x10161d4) = -1;
			}
		} else if (v18 == 't') {
			v24 = *(int*)(v14 + 0x10161cc);
			if (v24 == 0x53 || v24 == 0x55) {
				*(int*)(v14 + v08 * 4 + 0x10161d4) = 2;
			} else {
				*(int*)(v14 + v08 * 4 + 0x10161d4) = 5;
			}
		} else {
			*(int*)(v14 + v08 * 4 + 0x10161d4) = *(int*)ap;
			ap += 4;
		}
		v2c = 1;
		*(int*)(v14 + 0x10162d4) = v08 + 1;
		text_index += 2;
		goto loop;
	case 'I':
		v28 = 1;
		ap += 8;
		v24 = (int)*(double*)(ap - 8);
		if (digit == -1) {
			fcn_0064d41a(S.work, (char*)0x67d444, v24);
			goto join;
		}
		*(short*)sbuf = *(short*)0x6a238c;
		sbuf[2] = *(char*)0x6a238e;
		fcn_00657a73(digit, nbuf, 10);
		strcat(sbuf, nbuf);
		*(short*)(sbuf + strlen(sbuf)) = *(short*)0x6790c4;
		fcn_0064d41a(sbuf, sbuf, v24);
		*(short*)(sbuf + strlen(sbuf)) = *(short*)0x6a2350;
		fcn_0064d41a(S.work + 4, sbuf, *(double*)(ap - 8));
	join:
		v08 = (int)strlen(S.work);
		v18 = (int)strlen(S.text) - text_index;
		memcpy(S.text + text_index + 1, S.text + text_index + 2, v18);
		memcpy(S.text + text_index, S.work, v08 + 1);
		text_index += v08;
		goto loop;
	case 'f':
		v08 = (signed char)S.text[text_index + 1] - 0x30;
		if (v08 > 0 && v08 < 9) {
			text_index++;
			v14 = v08;
		} else {
			v14 = 2;
		}
		ap += 8;
		v24 = (int)*(double*)(ap - 8);
		fcn_00657a73(v14, nbuf, 10);
		*(short*)sbuf = *(short*)0x6a234c;
		sbuf[2] = *(char*)0x6a234e;
		strcat(sbuf, nbuf);
		*(short*)(sbuf + strlen(sbuf)) = *(short*)0x6a2350;
		fcn_00657a73(digit, sbuf, 10);
		fcn_0064d41a(S.work + 4, sbuf, *(double*)(ap - 8));
		v28 = 1;
		v08 = (int)strlen(S.work + 4);
		v18 = (int)strlen(S.text) - text_index;
		memcpy(S.text + text_index + 1, S.text + text_index + 2, v18);
		memcpy(S.text + text_index, S.work + 4, v08 + 1);
		text_index += v08;
		goto loop;
	case 'v':
		v08 = (unsigned char)S.text[text_index];
		text_index++;
		if ((char)v08 == 'v') {
			ap += 4;
		}
		goto loop;
	case 'm':
		v08 = (unsigned char)S.text[text_index];
		text_index++;
		v2c = 1;
		v18 = *(int*)(v14 + 0x10162d4);
		if ((char)v08 == 't') {
			*(int*)(v14 + v18 * 4 + 0x10161d4) = *(int*)ap;
			ap += 4;
			*(int*)(v14 + v18 * 4 + 0x10161d8) = *(int*)ap;
			ap += 4;
			*(int*)(v14 + 0x10162d4) = v18 + 2;
			text_index++;
		} else if ((char)v08 == 'b') {
			*(int*)(v14 + v18 * 4 + 0x10161d4) = -1;
			*(int*)(v14 + 0x10162d4) = v18 + 1;
			text_index++;
		} else {
			*(int*)(v14 + v18 * 4 + 0x10161d4) = -1;
			*(int*)(v14 + 0x10162d4) = v18 + 1;
		}
		goto loop;
	case 'X':
		S.text[text_index - 1] = 0x20;
		v30 = 1;
		*(char*)v20 = 0x20;
		text_index++;
		goto loop;
	case 'W':
		if (digit == -1) {
			digit = 0;
		}
		v08 = (signed char)S.text[text_index + 1] - 0x30;
		if (v08 > 0 && v08 < 9) {
			v10 = v08;
		} else {
			v10 = -1;
		}
		v18 = (int)(S.text + text_index + 1);
		v24 = (int)(strlen((char*)*(int*)(v14 + 0x1015f7c))
			    + strlen(S.text));
		if (v24 < 0x17cf) {
			strncat((char*)*(int*)(v14 + 0x1015f7c), S.text, text_index);
			*(short*)(*(int*)(v14 + 0x1015f7c)
				  + strlen((char*)*(int*)(v14 + 0x1015f7c)))
				= *(short*)0x677c94;
			*(int*)(v14 + 0x10161b8) = 2;
		}
		v24 = (int)strlen(S.text) - text_index;
		memcpy(S.text + text_index + 2, S.text + text_index + 1, v24);
		*(char*)(S.text + text_index + v24 + 2) = 0;
		d2_SetForm((char*)*(int*)(v14 + 0x1015f7c), v10, v18);
		if (digit != -1) {
			text_index += 2;
		} else {
			text_index++;
		}
		goto loop;
	case 'u':
		v10 = 1;
		goto shift1;
	case 'U':
		v10 = 2;
	shift1:
		v0c = text_index - (digit != -1 ? 2 : 1);
		v24 = (int)strlen(S.text) - text_index;
		memcpy(S.text + v0c + 2, S.text + text_index + 1, v24);
		text_index = v0c;
		goto loop;
	case 'b':
		v0c = text_index - (digit != -1 ? 2 : 1);
		if (S.text[v0c] != 0x25) {
			goto fmt;
		}
		v10 = 3;
		v24 = (int)strlen(S.text) - text_index;
		memcpy(S.text + v0c + 2, S.text + text_index + 1, v24);
		text_index = v0c;
		goto loop;
	case 'B':
		v0c = text_index - (digit != -1 ? 2 : 1);
		if (S.text[v0c] != 0x25) {
			goto fmt;
		}
		v10 = 4;
		v24 = (int)strlen(S.text) - text_index;
		memcpy(S.text + v0c + 2, S.text + text_index + 1, v24);
		text_index = v0c;
		goto loop;
	case 'e':
		v10 = 5;
		goto shift2;
	case 'E':
		v10 = 6;
	shift2:
		v08 = (unsigned char)S.text[text_index + 1];
		v24 = (int)strlen(S.text) - text_index;
		v18 = (digit != -1 ? 2 : 1);
		if ((char)v08 == 0x20) {
			memcpy(S.text + text_index + 2, S.text + text_index + 1, v24);
			v0c = text_index - v18;
			memcpy(S.text + v0c + 2, S.text + text_index + 2, v24);
		} else {
			memcpy(S.text + text_index + 2, S.text + text_index + 1, v24);
			v0c = text_index - v18;
			memcpy(S.text + v0c + 3, S.text + text_index + 1, v24);
		}
		text_index = v0c;
		goto loop;
	case 'N':
		text_index++;
		if (digit == -1) {
			goto loop;
		}
		if (S.text[text_index - 2] != 0x25 || S.text[text_index - 1] == 0x24) {
			goto loop;
		}
		v08 = S.text[text_index] - 0x30;
		v18 = *(int*)(v14 + 0x10161bc);
		fcn_00517c00(v18, (char*)0x6a2354, v08, S.work);
		v24 = (int)strlen(S.work) - 2;
		fcn_0064d740(S.text + text_index + 2, S.work, v24);
		text_index += v24;
		goto loop;
	case 'a':
		v28 = 0x14;
		if (S.text[text_index - 1] != 0x25) {
			v24 = *(int*)ap;
			ap += 4;
			fcn_0064d41a(S.work, (char*)0x67d444, v24);
			v08 = (int)strlen(S.work) - 2;
			v18 = (int)strlen(S.text) - text_index;
			memcpy(S.text + text_index + 1, S.text + text_index + 1, v18);
			memcpy(S.text + text_index, S.work, v08);
			text_index += v08;
			goto loop;
		}
		v24 = *(int*)ap;
		ap += 4;
		fcn_0064d41a(S.work, (char*)0x699a68, v24);
		v08 = (int)strlen(S.work) - 2;
		v18 = (int)strlen(S.text) - text_index;
		memcpy(S.text + text_index + 2, S.text + text_index + 1, v18);
		memcpy(S.text + text_index, S.work, v08);
		text_index += v08;
		goto loop;
	case 'r':
		if (directive != 'r') {
			goto loop;
		}
		memset(rbuf, 0, 0x20);
		v0c = 0;
		v08 = (signed char)S.text[text_index + 1] - 0x31;
		if (v08 >= 0 && v08 <= 9) {
			v0c = v08 + 9;
		}
		v18 = text_index + 3;
		for (v08 = v18; ; v08++) {
			if ((unsigned char)S.text[v08] < 0x30
			    || (unsigned char)S.text[v08] > 0x39) {
				break;
			}
		}
		v14 = v08 - v18;
		fcn_0064d530(rbuf, S.text + text_index + 3, v14);
		v14 = fcn_0064eeec(rbuf);
		v24 = *(int*)&format_selector;
		v28 = *(int*)0x6b7f98;
		for (v08 = v24; v08 < v28; v08++) {
			if (*(int*)(v08 * 4 + 0x11bb000) == v0c) {
				break;
			}
		}
		if (v08 >= v28) {
			ReportClientMessage((char*)0x6a2318);
			goto loop;
		}
		v24 = (gm_RandomMod(v14) & 0xffff) + v08;
		v18 = *(int*)(v24 * 4 + 0x14a5320);
		if (v18 == 0) {
			goto loop;
		}
		v24 = (int)strlen(S.text) - text_index;
		memcpy(S.text + text_index + 5, S.text + text_index + 1, v24);
		v28 = (int)strlen((char*)v18);
		memcpy(S.text + text_index + 3, (char*)v18, v28);
		*(char*)(S.text + text_index + 3 + v28) = 0;
		text_index += v28;
		goto loop;
	case 'D':
		v24 = *(int*)ap;
		ap += 4;
		fcn_00500d60(v24, dbuf);
		v08 = fcn_004fe330(dbuf, *(short*)(dbuf + 2));
		v18 = *(int*)(v08 * 4 + 0x14a5450);
		fcn_0064d41a(S.work, (char*)0x6a2310, (char*)v18);
		v08 = (int)strlen(S.work) - 2;
		v24 = (int)strlen(S.text) - text_index;
		memcpy(S.text + text_index + 2, S.text + text_index + 1, v24);
		memcpy(S.text + text_index, S.work, v08);
		text_index += v08;
		goto loop;
	case 'G':
		text_index++;
		v18 = *(int*)ap;
		ap += 4;
		v08 = (unsigned char)*(char*)v18;
		v08 = v08 * 7 + 0x48e;
		if (v08 > 0x4800) {
			v24 = v08;
		} else {
			v28 = *(int*)(v08 * 4 + 0x11bb000);
			v24 = *(int*)(v08 * 4 + 0x14a5320);
		}
		if (digit != -1) {
			v24 = fcn_0042b2f0((char*)v24, digit, 4);
		}
		if (v24 == 0) {
			v24 = *(int*)(v08 * 4 + 0x14a5320);
		}
		v0c = v18 + 5;
		if (*(char*)v0c != 0) {
			fcn_0064d41a(abuf[0], (char*)0x6a2308, (char*)v24,
				     (char*)v0c);
		} else {
			fcn_0064d740(abuf[0], (char*)v24,
				     (unsigned)strlen((char*)v24) + 1);
		}
		if (v10 != 0) {
			if (v10 == 1 || v10 == 2) {
				fcn_0064d41a(abuf[0], (char*)0x68b3f8,
					     (char*)v24,
					     *(char**)(v28 * 4 + 0x14a540c));
				if (fcn_0051e070() == 0 && v10 == 2) {
					*(char*)v0c = (char)toupper(
						*(char*)v0c);
				}
			} else if (v10 == 3 || v10 == 4) {
				fcn_0064d41a(abuf[1], (char*)0x68b3f8,
					     (char*)v24,
					     *(char**)(v28 * 4 + 0x14a5400));
				if (fcn_0051e070() == 0 && v10 == 4) {
					*(char*)v0c = (char)toupper(
						*(char*)v0c);
				}
			} else if (v10 == 5 || v10 == 6) {
				fcn_0064d41a(abuf[6], (char*)0x68b3f8,
					     (char*)v24,
					     *(char**)(v28 * 4 + 0x14a5418));
				if (fcn_0051e070() == 0 && v10 == 6) {
					*(char*)v0c = (char)toupper(
						*(char*)v0c);
				}
			}
		}
		v24 = (int)strlen(S.text) - text_index;
		memcpy(S.text + text_index + 2, S.text + text_index + 1, v24);
		memcpy(S.text + text_index, abuf[0], strlen(abuf[0]));
		text_index += (int)strlen(abuf[0]) - 2;
		goto loop;
	case '%':
		v24 = (int)strlen(S.text) - text_index;
		S.text[text_index - 1] = 0x16;
		memcpy(S.text + text_index + 4, S.text + text_index + 1, v24);
		text_index += 0;
		goto loop;
	default:
		goto loop;
	}

	/* shared va_arg formatter (native 0x5193a3), reached by S/s, b, B */
fmt:
	v24 = *(int*)ap;
	ap += 4;
	text_index++;
	if (v24 > 0x4800) {
		v18 = v24;
	} else {
		v18 = *(int*)(v24 * 4 + 0x14a5320);
		v1c = *(int*)(v24 * 4 + 0x11bb000);
	}
	v08 = (digit != -1) + 2;
	if (v1c != 0xff) {
		if (digit == -1) {
			digit = 1;
		}
		if (S.text[text_index - 1] == 's' && v2c == 0) {
			fcn_0042b2f0((char*)v18, digit, 4);
		} else {
			fcn_0042b2f0((char*)v18, digit, 8);
		}
	} else {
		if (v18 == 0) {
			v18 = *(int*)(v24 * 4 + 0x14a5320);
		}
	}
	if (v10 == 0) {
		if ((int)strlen((char*)v18) + text_index > 0x17cb) {
			goto fail;
		}
		v14 = text_index - v08;
		v24 = (int)strlen(S.text) - text_index;
		memmove(S.text + text_index + 4, S.text + text_index + 1, v24);
		v28 = (int)strlen((char*)v18);
		fcn_0064d740(S.text + v14 + 2, (char*)v18, v28);
		*(char*)(S.text + v14 + 2 + v28) = 0;
		text_index = v14 + v28;
		goto loop;
	}
	if (v10 == 1 || v10 == 2) {
		if (S.text[text_index] == 's' && v2c == 0) {
			v08 = 4;
		} else {
			v08 = 8;
		}
		v18 = fcn_0042b2f0((char*)v18, digit, v08);
		v08 = (int)strlen((char*)v18);
		if (v10 == 2) {
			fcn_0064d41a(S.work, (char*)0x68b3f8, (char*)v18,
				     *(char**)(v10 * 4 + 0x14a540c));
		}
		v24 = (int)strlen(S.text) - text_index;
		memcpy(S.text + text_index + 2, S.text + text_index + 1, v24);
		memcpy(S.text + text_index, S.work, v08 + 1);
		text_index += v08;
		goto loop;
	}
	if (v10 == 3 || v10 == 4) {
		if (S.text[text_index] == 's' && v2c == 0) {
			v08 = 4;
		} else {
			v08 = 8;
		}
		v18 = fcn_0042b2f0((char*)v18, digit, v08);
		v08 = (int)strlen((char*)v18);
		if (v10 == 4) {
			fcn_0064d41a(S.work + 0x18, (char*)0x68b3f8,
				     (char*)v18,
				     *(char**)(v10 * 4 + 0x14a5400));
		}
		v24 = (int)strlen(S.text) - text_index;
		memcpy(S.text + text_index + 2, S.text + text_index + 1, v24);
		memcpy(S.text + text_index, S.work + 0x18, v08 + 1);
		text_index += v08;
		goto loop;
	}
	if (v10 == 5 || v10 == 6) {
		if (S.text[text_index] == 's' && v2c == 0) {
			v08 = 4;
		} else {
			v08 = 8;
		}
		v18 = fcn_0042b2f0((char*)v18, digit, v08);
		v08 = (int)strlen((char*)v18);
		fcn_0064d41a(S.work + 0x1c, (char*)0x68b3f8, (char*)v18,
			     *(char**)(v10 * 4 + 0x14a5418));
		v24 = (int)strlen(S.text) - text_index;
		memcpy(S.text + text_index + 2, S.text + text_index + 1, v24);
		memcpy(S.text + text_index, S.work + 0x1c, v08 + 1);
		text_index += v08;
		goto loop;
	}
	goto loop;

plain:
	text_index++;
	if (text_index < (int)strlen(S.text)) {
		goto loop;
	}
carry:
	v24 = (int)(strlen((char*)*(int*)(v14 + 0x1015f7c))
		    + strlen(S.text));
	if (v24 > 0x17cf) {
		goto fail;
	}
	strcat((char*)*(int*)(v14 + 0x1015f7c), S.text);
	*(int*)(v14 + 0x10161b8) = 2;
	v24 = *(int*)(v14 + 0x1015f6c);
	if (v2c == 0) {
		if (v30 != 0) {
			fcn_0046ac30();
		}
		return v24;
	}
	if (v30 != 0) {
		fcn_0046ac30();
		return v24;
	}
	v08 = *(int*)0x772554;
	*(int*)0x772554 = 1;
	v28 = *(int*)(v14 + 0x10161bc);
	v28 = ((v28 << 6) - v28) * 3;
	v20 = *(int*)0x1015ea0 + v28 * 4 + 0x50;
	if (v20 == 0) {
		fcn_0046dff0(*(int*)0x772514, *(int*)0x77250c);
		*(int*)0x772554 = v08;
		return v24;
	}
	if (*(int*)(v20 + 0x198) == 0) {
		fcn_0046dff0(*(int*)0x772514, *(int*)0x77250c);
		*(int*)0x772554 = v08;
		return v24;
	}
	fcn_00471490(*(int*)v20);
	*(int*)0x772554 = v08;
	return v24;
fail:
	return -1;
}
