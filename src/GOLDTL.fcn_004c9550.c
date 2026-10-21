#include <stdio.h>
#include <string.h>

/* 14-byte packed time stamp used by the set-time message. */
#pragma pack(2)
typedef struct {
	int day;
	int minute;
	int second;
	unsigned short hour;
} Stamp;
#pragma pack()

void __cdecl fcn_00538060(void);
int __cdecl srv_SeedRandom(int seed);
int __cdecl fcn_0042df70(void* fn);
int __cdecl fcn_0042df30(void* fn, int flag);
void __cdecl fcn_004432d0(int a, int b);
void __cdecl fcn_0045b290(int a, int b);
void __cdecl fcn_004ad2d0(int v);
void __cdecl fcn_004b3d40(int a, int b);
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
unsigned short* __cdecl fcn_00502cd0(int, int, int, int);
int __cdecl fcn_00508e40(int id);
void __cdecl fcn_005167c0(void* ent, int v);
void __cdecl fcn_0052a3a0(void* t, int flag);
void __cdecl fcn_0052da70(int idx);
void __cdecl fcn_00533a40(void* p);
void __cdecl fcn_005e2510(void);

/* ADDRESS: GOLDTL 0x004c9550 */
int __cdecl fcn_004c9550(char* pkt, char* out)
{
	int status;
	char buf[0x99];
	unsigned int cmd;
	int v;
	int i;
	int saved;
	unsigned short* r;
	unsigned char* e;

	memcpy(buf, pkt, sizeof buf);
	cmd = *(unsigned int*) (buf + 0x10);
	status = 1;
	switch (cmd & 0xff) {
	case 0:
	{
		Stamp t;

		t.day = 0;
		t.minute = 0;
		t.second = 0;
		t.hour = 0;
		t.day = *(int*) (buf + 0x11);
		srv_SeedRandom(*(int*) (buf + 0x15));
		fcn_0052a3a0(&t, 1);
		break;
	}
	case 2:
		*(int*) 0xfb5744 = 1;
		if (*(int*) (buf + 0x11) != 0)
			*(int*) 0x77494c = (*(int*) 0x77494c & 0xffffffef) | 8;
		else
			*(int*) 0x77494c = (*(int*) 0x77494c & 0xfffffff7) | 0x10;
		break;
	case 3:
		v = fcn_0042df70((void*) fcn_00538060);
		if (v == 0)
			fcn_0042df30((void*) fcn_00538060, 1);
		*(int*) 0x7f4c00 = *(int*) (buf + 0x11);
		*(unsigned short*) 0x7f4c04 = *(unsigned short*) (buf + 0x15);
		*(int*) 0x7f4c06 = *(int*) (buf + 0x17);
		*(int*) 0x7f4c0a = *(int*) (buf + 0x1b);
		*(Stamp*) 0x7e1f70 = *(Stamp*) 0x7f4c00;
		if (v == 0)
			fcn_0042df30((void*) fcn_00538060, 0);
		break;
	case 4:
		e = gm_StartFilteredEntitySearch(1, 1, *(int*) (buf + 0x11));
		if (e != 0) {
			r = fcn_00502cd0(*(int*) ((char*) e + 0x5d), 1, 1,
			                 *(int*) (buf + 0x15));
			if (r != 0)
				fcn_005167c0(e, *r);
			else
				fcn_005167c0(e, 0xfd);
		}
		break;
	case 5:
		srv_SeedRandom(*(int*) (buf + 0x11));
		*(int*) 0x1007cd0 = 0;
		break;
	case 7:
		*(int*) 0x14cbcb4 = *(int*) (buf + 0x11);
		break;
	case 6:
		*(char*) 0x6a375c = (char) (cmd >> 8);
		break;
	case 8:
		if (*(int*) 0x6a3760 != -1)
			goto bad;
		v = *(int*) (buf + 0x11);
		if (fcn_00508e40(v) == 0)
			goto bad;
		*(int*) 0x6a3760 = v;
		break;
	case 9:
		*(char*) 0x6a3440 = (char) (cmd >> 8);
		*(unsigned int*) 0x7e1f60 = *(unsigned int*) (buf + 0x15);
		break;
	case 10:
		if (*(int*) 0x6a3760 != *(int*) (buf + 0x11))
			goto bad;
		v = *(int*) (buf + 0x21);
		*(int*) 0x6a3760 = -1;
		if (v == 1)
			*(int*) 0x774954 = 1;
		if (*(char*) 0x6a3440 == 5)
			fcn_004b3d40(
			    *(int*) (0x7f4ca4 + (unsigned int) *(unsigned short*) 0x774970 * 0x21c),
			    *(int*) (buf + 0x31));
		break;
	case 12:
		saved = *(int*) 0x6b8010;
		fcn_004432d0(0, 1);
		fcn_0045b290(*(int*) (*(int*) 0x67a370 + 0xb0), *(int*) 0x6b8300);
		fcn_004432d0(saved, 1);
		*(char**) 0x6b5c54 = 0;
		break;
	case 13:
		fcn_0052da70(*(int*) (buf + 0x11));
		break;
	case 15:
		*(int*) 0x774980 = *(int*) (buf + 0x11);
		{
			char* d;
			char* s;

			d = (char*) 0x774988;
			s = buf + 0x15;
			while ((*d++ = *s++) != 0)
				;
		}
		break;
	case 16:
		for (i = 0; i < 8; i++) {
			if (*(int*) (0x7f3ac0 + i * 8) == -1) {
				*(int*) (0x7f3ac0 + i * 8) = *(int*) (buf + 0x11);
				*(int*) (0x7f3ac0 + i * 8 + 4) = *(int*) (buf + 0x15);
				break;
			}
		}
		break;
	case 17:
		if (*(unsigned short*) 0x774970 != 0xffff &&
		    (*(int*) (0x7f4eac +
		              (unsigned int) *(unsigned short*) 0x774970 * 0x21c) !=
		         *(int*) (buf + 0x11) ||
		     *(int*) (buf + 0x11) == -1))
			*(int*) 0x772e84 = *(int*) 0x772e84 + 1;
		break;
	case 18:
		v = *(int*) (pkt + 0x11);
		if (v >= 4)
			v = 4;
		*(int*) 0x68a9cc = v;
		*(int*) 0x68a9c8 = *(int*) (0x664ea8 + v * 4);
		fcn_00533a40(*(void**) (0x14ac528 + v * 4));
		fcn_005e2510();
		break;
	case 19:
		*(int*) 0x68a9dc = *(int*) (buf + 0x11);
		break;
	case 20:
		fcn_004ad2d0(*(int*) (buf + 0x11));
		break;
	}
	goto done;
bad:
	status = 2;
done:
	sprintf(buf, "cm_ExSysMessage() type: %i", cmd & 0xff);
	if (out != 0) {
		out[1] = 0;
		out[0] = (char) status;
		*(int*) (out + 6) = 0;
	}
	return 0;
}
