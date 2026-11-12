/* Run the credit window state machine: validate the open request, refresh the
 * slot message and record the activity time stamp. */

int __cdecl fcn_004c4450(int);
int __cdecl gm_StartFilteredEntitySearch(int, int, int);
int __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_AccumulateTyped2(int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);
int __cdecl fcn_004c5620(int, int);
int __cdecl fcn_005c4ec0(int, int, int, char*);
extern double g_6640e8;
void __cdecl fcn_64d41a(char*, char*, int);
void __cdecl fcn_00546190(int);
void __cdecl fcn_004c51a0(int, int, int, int);

/* ADDRESS: GOLDTL 0x00564b90 */
void __cdecl he_RunKredit(int a0)
{
	char buf[0x400];
	char msg[0x400];
	char info[0x3f0];
	char* slot;
	float f;
	int obj;
	int n;
	int time;

	if (*(int*) (a0 + 0x84) != -1 && !fcn_004c4450(*(int*) (a0 + 0x84))) {
		return;
	}
	n = *(int*) (a0 + 0x70);
	*(int*) (a0 + 0x84) = -1;
	if (n < -2) {
		return;
	}
	if (n >= 0) {
		if (n != 0) {
			return;
		}
		if (*(unsigned char*) (a0 + 0x78) & 2) {
			obj = gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0xac));
			if (!obj) {
				fcn_64d41a(buf, (char*) 0x6a6620, *(int*) (a0 + 0xac));
				fcn_00546190(a0);
				return;
			}
			n = gm_LookupEntityRecordById(*(int*) (a0 + 0xb0));
			slot = (char*) 0x7f4ca0 +
			       (unsigned short) *(unsigned short*) (obj + 0x27) * 0x21c;
			if (!n) {
				io_FormatTextBuffer(buf, 0x18e7, *(int*) (a0 + 0xb4));
				fcn_00545d40(*(int*) (slot + 4), -1, buf, 0, 0x5ff, 0);
				*(int*) (a0 + 0x84) = fcn_004c5620(-1, a0);
				return;
			}
			f = (float) (*(int*) (a0 + 0xc0) * g_6640e8 *
			             *(int*) (a0 + 0xb4));
			time = gm_AccumulateTyped2(n);
			if ((float) time < f) {
				time = (int) f;
				io_FormatTextBuffer(msg, 0x18e8, time);
				n = fcn_005c4ec0(*(int*) ((char*) obj + 1), n, time, msg);
				*(int*) ((char*) obj + 0x55) += n;
				if (*(unsigned char*) (slot + 2) == 6 ||
				    *(unsigned char*) (slot + 2) == 7) {
					fcn_00545d40(*(int*) (a0 + 0xb0), -1, msg, 0, 0x5ff, 0);
				}
			} else {
				fcn_004c51a0(*(int*) ((char*) obj + 1), *(int*) (a0 + 0xb0),
				           *(unsigned char*) 0x773d75, (int) f);
				*(int*) ((char*) obj + 0x55) = (int) f;
			}
		}
		n = *(int*) (a0 + 0xbc) - 1;
		*(int*) (a0 + 0xbc) = n;
		if (n >= 0) {
			return;
		}
		obj = gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0xac));
		if (obj) {
			slot = (char*) 0x7f4ca0 +
			       (unsigned short) *(unsigned short*) (obj + 0x27) * 0x21c;
			n = gm_LookupEntityRecordById(*(int*) (a0 + 0xb0));
			if (*(unsigned char*) (a0 + 0x78) & 2) {
				time = gm_AccumulateTyped2(n);
				io_FormatTextBuffer(buf, *(int*) (a0 + 0xb4) <= time ? 0x18e9 : 0x18ea,
				           *(int*) (a0 + 0xb4));
				fcn_005c4ec0(*(int*) ((char*) obj + 1), n,
				           *(int*) (a0 + 0xb4), buf);
				fcn_00545d40(*(int*) (a0 + 0xb0), -1, buf, 0, 0x5ff,
				           *(int*) (a0 + 0xb4) <= time ? (char*) 0x6b5c60 : (char*) 0x699a88);
				if (*(unsigned char*) (slot + 2) == 6 ||
				    *(unsigned char*) (slot + 2) == 7) {
					io_FormatTextBuffer(msg, 0x18d8, *(unsigned short*) n, obj,
					           *(int*) (a0 + 0xb4));
					fcn_00545d40(*(int*) (slot + 4), -1, msg, 0, 0x5ff, 0);
					fcn_00546190(a0);
					return;
				}
			}
		}
	} else {
		obj = gm_StartFilteredEntitySearch(1, 1, *(int*) (a0 + 0xac));
		if (obj) {
			n = gm_LookupEntityRecordById(*(int*) (a0 + 0xb0));
			slot = (char*) 0x7f4ca0 +
			       (unsigned short) *(unsigned short*) (obj + 0x27) * 0x21c;
			if (!n) {
				io_FormatTextBuffer(msg, 0x18e7, *(int*) (a0 + 0xb4));
				fcn_00545d40(*(int*) (slot + 4), -1, msg, 0, 0x5ff, 0);
			}
		}
	}
	fcn_00546190(a0);
}
