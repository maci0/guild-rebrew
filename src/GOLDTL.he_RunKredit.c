/* Run the credit window state machine: validate the open request, refresh the
 * slot message and record the activity time stamp. */

int __cdecl fcn_004c4450(int);
int __cdecl fcn_503fe0(int, int, int);
int __cdecl fcn_508e40(int);
int __cdecl fcn_50d2a0(int);
void __cdecl fcn_51af00(char*, int, ...);
void __cdecl fcn_545d40(int, int, char*, int, int, char*);
int __cdecl fcn_4c5620(int, int);
int __cdecl fcn_5c4ec0(int, int, int, char*);
int __cdecl fcn_64d228(void);
void __cdecl fcn_64d41a(char*, char*, int);
void __cdecl fcn_546190(int);
void __cdecl fcn_4c51a0(int, int, int, int);

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
			obj = fcn_503fe0(1, 1, *(int*) (a0 + 0xac));
			if (!obj) {
				fcn_64d41a(buf, (char*) 0x6a6620, *(int*) (a0 + 0xac));
				fcn_546190(a0);
				return;
			}
			slot = (char*) 0x7f4ca0 +
			       (unsigned short) *(unsigned short*) (obj + 0x27) * 0x21c;
			n = fcn_508e40(*(int*) (a0 + 0xb0));
			if (!n) {
				fcn_51af00(buf, 0x18e7, *(int*) (a0 + 0xb4));
				fcn_545d40(*(int*) (slot + 4), -1, buf, 0, 0x5ff, 0);
				*(int*) (a0 + 0x84) = fcn_4c5620(-1, a0);
				return;
			}
			f = (float) (*(int*) (a0 + 0xc0) * 0.01 *
			             *(int*) (a0 + 0xb4));
			obj = fcn_50d2a0(n);
			if (f <= (float) obj) {
				fcn_4c51a0(*(int*) ((char*) n + 1), *(int*) (a0 + 0xb0),
				           *(unsigned char*) 0x773d75, fcn_64d228());
				time = fcn_64d228();
				*(int*) ((char*) n + 0x55) = time;
			} else {
				time = fcn_64d228();
				fcn_51af00(msg, 0x18e8, time);
				obj = fcn_5c4ec0(*(int*) ((char*) n + 1), n, time, msg);
				*(int*) ((char*) n + 0x55) += obj;
				if (*(unsigned char*) (slot + 2) == 6 ||
				    *(unsigned char*) (slot + 2) == 7) {
					fcn_545d40(*(int*) (a0 + 0xb0), -1, msg, 0, 0x5ff, 0);
				}
			}
		}
		n = *(int*) (a0 + 0xbc) - 1;
		*(int*) (a0 + 0xbc) = n;
		if (n >= 0) {
			return;
		}
		obj = fcn_503fe0(1, 1, *(int*) (a0 + 0xac));
		if (obj) {
			slot = (char*) 0x7f4ca0 +
			       (unsigned short) *(unsigned short*) (obj + 0x27) * 0x21c;
			n = fcn_508e40(*(int*) (a0 + 0xb0));
			if (*(unsigned char*) (a0 + 0x78) & 2) {
				time = fcn_50d2a0(n);
				if (*(int*) (a0 + 0xb4) <= time) {
					fcn_51af00(buf, 0x18e9, *(int*) (a0 + 0xb4));
				} else {
					fcn_51af00(buf, 0x18ea, *(int*) (a0 + 0xb4));
				}
				fcn_5c4ec0(*(int*) ((char*) obj + 1), n,
				           *(int*) (a0 + 0xb4), buf);
				if (*(int*) (a0 + 0xb4) <= time) {
					fcn_545d40(*(int*) (a0 + 0xb0), -1, buf, 0, 0x5ff,
					           (char*) 0x6b5c60);
				} else {
					fcn_545d40(*(int*) (a0 + 0xb0), -1, buf, 0, 0x5ff,
					           (char*) 0x699a88);
				}
				if (*(unsigned char*) (slot + 2) == 6 ||
				    *(unsigned char*) (slot + 2) == 7) {
					fcn_51af00(msg, 0x18d8, *(unsigned short*) n, obj,
					           *(int*) (a0 + 0xb4));
					fcn_545d40(*(int*) (slot + 4), -1, msg, 0, 0x5ff, 0);
					fcn_546190(a0);
					return;
				}
			}
		}
	} else {
		obj = fcn_503fe0(1, 1, *(int*) (a0 + 0xac));
		if (obj) {
			n = fcn_508e40(*(int*) (a0 + 0xb0));
			slot = (char*) 0x7f4ca0 +
			       (unsigned short) *(unsigned short*) (obj + 0x27) * 0x21c;
			if (!n) {
				fcn_51af00(msg, 0x18e7, *(int*) (a0 + 0xb4));
				fcn_545d40(*(int*) (slot + 4), -1, msg, 0, 0x5ff, 0);
			}
		}
	}
	fcn_546190(a0);
}
