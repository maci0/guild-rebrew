#include <string.h>
#include <stdio.h>

void* __cdecl gm_LookupEntityRecordById(int);
int __cdecl fcn_004fe2e0(char*, int, int*, int*, int, int*);
void __cdecl fcn_004ce9e0(char*);
char* __cdecl fcn_004ce610(char*);
char* __cdecl fcn_004ce680(char*);

/* ADDRESS: GOLDTL 0x004d1970 */
void* __cdecl fcn_004d1970(int a1, int a2)
{
	char* src;
	char* rec;
	char* obj;
	char* e;
	int i;
	int f;

	src = (char*) gm_LookupEntityRecordById(a1);
	i = 0;
	for (;;) {
		if (*(unsigned short*) (0x9b4a40 + i * 0x21c) == 0xffff)
			break;
		i++;
		if (0x9b4a40 + i * 0x21c >= 0x9b8dc0)
			return 0;
	}
	rec = (char*) (0x9b4a40 + i * 0x21c);
	memcpy(rec, src, 0x21c);
	*(int*) (rec + 0x1ac) = 0;
	*(int*) (rec + 0x184) = 0;
	fcn_004fe2e0(rec, *(int*) 0x6b8010, 0, 0, 0, (int*) a2);
	obj = *(char**) (rec + 0x184);
	*(unsigned char*) (obj + 0x240) = 4;
	*(unsigned char*) (obj + 0x8d) |= 0x80;
	fcn_004ce9e0(rec);
	e = (char*) fcn_004ce610((char*) a1);
	obj = *(char**) (rec + 0x184);
	*(float*) (obj + 0x1a0) = (float) ((double) *(unsigned char*) (e + 9) * *(double*) 0x662ae8);
	f = *(int*) (obj + 0x34);
	sprintf((char*) f, (char*) 0x68b85c, rec + 4);
	e = (char*) fcn_004ce680((char*) a1);
	if (e != 0) {
		if (*(int*) (e + 0x58) == 2) {
			*(int*) (e + 0x20) = 6;
		} else {
			*(int*) (e + 0x20) = 0x0f;
		}
	}
	return rec;
}
