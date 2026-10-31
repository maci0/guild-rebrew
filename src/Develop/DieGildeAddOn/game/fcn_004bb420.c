#include <string.h>

unsigned short __cdecl fcn_0042e410(int n);
char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl fcn_005c6270(char* rec, int mode);
void __cdecl fcn_004c6ba0(int a, int id, int off);
void __cdecl io_FormatTextBuffer(char* buf, int msg, int arg);
void __cdecl fcn_00545d40(int a, int b, char* buf, int overflow, int msg, int zero);

/* ADDRESS: GOLDTL 0x004bb420 */
int __cdecl fcn_004bb420(unsigned short* param)
{
	char buf[0x100];
	int id;
	char* rec;
	int v;
	int n;

	id = fcn_0042e410(5) & 0xffff;
	rec = gm_LookupEntityRecordById(*(int*) param);
	if (rec == 0) {
		return 1;
	}
	v = *(unsigned char*) (rec + id + 0x80);
	if (fcn_005c6270(rec, 0x290) != 0) {
		return 0x400;
	}
	if (v <= 0) {
		return 0x400;
	}
	if (v < (fcn_0042e410(0xc) & 0xffff) + 6) {
		n = v;
	} else {
		n = (fcn_0042e410(0xc) & 0xffff) + 6;
	}
	fcn_004c6ba0(*(int*) (rec + 4), id, -((char) n));
	io_FormatTextBuffer(buf, param[2] + 0x12e7, id + 0x16b7);
	fcn_00545d40(*(int*) (rec + 4), *(int*) (rec + 4), buf,
		(int) (strlen(buf) > 0x100), 0x603, 0);
	return 0;
}
