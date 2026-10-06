#include <string.h>

#pragma pack(1)
typedef struct pkt99 {
	unsigned char type;
	unsigned short crc;
	unsigned char flag;
	int seq;
	int cur;
	int nextseq;
	int who;
	int key;
	int target;
	unsigned char mode;
	char name[0x20];
	char text[0x20];
	char rest[0x3c];
} pkt99;
// SIZE 0x99
#pragma pack()

char* __cdecl fcn_00508e40(int);
char* __cdecl gm_SearchTable67(int);
int __cdecl gm_CheckEntityType(char*);
char* __cdecl fcn_00502cd0(int, int, int, int);
char* __cdecl gm_SetupEntityQuery(char*);
int __cdecl fcn_004c4330(pkt99*);

// FUNCTION: GOLD 0x004c52e0
// FUNCTION: GOLDTL 0x4c5da0

int __cdecl fcn_004c5da0(int who, int key, int target, char* name, int mode, char* text)
{
	pkt99 pkt;
	char* e;
	char* s;
	char* q;
	char c;

	pkt.type = 0x35;
	pkt.who = who;
	pkt.key = key;
	pkt.target = target;
	pkt.mode = mode;
	if (text != 0)
		strncpy(pkt.text, text, 0x1f);
	else
		pkt.text[0] = 0;
	if (name != 0) {
		s = name;
		do {
			c = *s;
			pkt.name[s - name] = c;
			s++;
		} while (c != 0);
	} else {
		pkt.name[0] = 0;
	}
	e = fcn_00508e40(who);
	if (e != 0 && e[8] == 0)
		return -1;
	if (mode == 0 && target == -1) {
		s = gm_SearchTable67(key);
		if (s != 0) {
			if (gm_CheckEntityType(s) != 0) {
				q = fcn_00502cd0(*(int*) (s + 0x5d), 1, 0, 0xfd);
				if (q != 0) {
					pkt.target = *(int*) (q + 2);
					goto send;
				}
			} else {
				q = gm_SetupEntityQuery(s);
				if (q != 0) {
					pkt.target = *(int*) (q + 2);
					goto send;
				}
			}
		}
		pkt.mode = 1;
		pkt.target = -1;
	}
send:
	return fcn_004c4330(&pkt);
}
