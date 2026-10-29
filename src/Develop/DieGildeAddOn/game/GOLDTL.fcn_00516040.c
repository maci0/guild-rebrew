extern char* g_6b8300;
extern char g_7f4c00[];

int __cdecl fcn_00500e20(char*);
char* __cdecl strstr(char*, char*);
int __cdecl sprintf(char*, char*, ...);
int __cdecl fcn_0045be40(char*);
void __cdecl fcn_0043f990(char*, char*, int);

/* ADDRESS: GOLDTL 0x00516040 */
void __cdecl fcn_00516040(void)
{
	char buf[0x80];
	char name[0x80];
	int mode;
	int found;
	int off;
	int i;
	char* p;
	char* q;
	char* s;
	char* d;

	mode = fcn_00500e20(g_7f4c00);
	if (g_6b8300 == 0) {
		return;
	}
	if (mode == 3) {
		found = 0;
		for (off = 0; off < 0x200; off += 0x40) {
			if (g_6b8300[off + 0x7e24] != 0 &&
			    strstr(&g_6b8300[off + 0x7e24], "_SNOW") != 0) {
				found = 1;
				break;
			}
		}
		if (found) {
			return;
		}
		for (off = 0, i = 0; off < 0x200; off += 0x40, i++) {
			p = &g_6b8300[off + 0x7e24];
			if (*p == 0) {
				continue;
			}
			s = p;
			d = buf;
			while ((*d = *s) != 0) {
				s++;
				d++;
			}
			q = strstr(buf, "_FRUEHLING");
			if (q == 0) {
				q = strstr(buf, "_HERBST");
				if (q == 0) {
					q = strstr(buf, "_SNOW");
				}
			}
			if (q != 0) {
				*q = 0;
			}
			sprintf(name, "%s_SNOW", buf);
			if (fcn_0045be40(name) != 0) {
				fcn_0043f990(g_6b8300, name, i);
			} else {
				fcn_0043f990(g_6b8300, buf, i);
			}
		}
		return;
	}
	if (mode == 2) {
		found = 0;
		for (off = 0; off < 0x200; off += 0x40) {
			if (g_6b8300[off + 0x7e24] != 0 &&
			    strstr(&g_6b8300[off + 0x7e24], "_HERBST") != 0) {
				found = 1;
				break;
			}
		}
		if (found) {
			return;
		}
		for (off = 0, i = 0; off < 0x200; off += 0x40, i++) {
			p = &g_6b8300[off + 0x7e24];
			if (*p == 0) {
				continue;
			}
			s = p;
			d = buf;
			while ((*d = *s) != 0) {
				s++;
				d++;
			}
			q = strstr(buf, "_FRUEHLING");
			if (q == 0) {
				q = strstr(buf, "_HERBST");
				if (q == 0) {
					q = strstr(buf, "_SNOW");
				}
			}
			if (q != 0) {
				*q = 0;
			}
			sprintf(name, "%s_HERBST", buf);
			if (fcn_0045be40(name) != 0) {
				fcn_0043f990(g_6b8300, name, i);
			} else {
				fcn_0043f990(g_6b8300, buf, i);
			}
		}
		return;
	}
	if (mode == 0) {
		found = 0;
		for (off = 0; off < 0x200; off += 0x40) {
			if (g_6b8300[off + 0x7e24] != 0 &&
			    strstr(&g_6b8300[off + 0x7e24], "_FRUEHLING") != 0) {
				found = 1;
				break;
			}
		}
		if (found) {
			return;
		}
		for (off = 0, i = 0; off < 0x200; off += 0x40, i++) {
			p = &g_6b8300[off + 0x7e24];
			if (*p == 0) {
				continue;
			}
			s = p;
			d = buf;
			while ((*d = *s) != 0) {
				s++;
				d++;
			}
			q = strstr(buf, "_FRUEHLING");
			if (q == 0) {
				q = strstr(buf, "_HERBST");
				if (q == 0) {
					q = strstr(buf, "_SNOW");
				}
			}
			if (q != 0) {
				*q = 0;
			}
			sprintf(name, "%s_FRUEHLING", buf);
			if (fcn_0045be40(name) != 0) {
				fcn_0043f990(g_6b8300, name, i);
			} else {
				fcn_0043f990(g_6b8300, buf, i);
			}
		}
		return;
	}
	if (mode == 1) {
		found = 0;
		for (off = 0; off < 0x200; off += 0x40) {
			p = &g_6b8300[off + 0x7e24];
			if (*p != 0 &&
			    (strstr(p, "_FRUEHLING") != 0 ||
			     strstr(p, "_HERBST") != 0 ||
			     strstr(p, "_SNOW") != 0)) {
				found = 1;
				break;
			}
		}
		if (found == 0) {
			return;
		}
		for (off = 0, i = 0; off < 0x200; off += 0x40, i++) {
			p = &g_6b8300[off + 0x7e24];
			if (*p == 0) {
				continue;
			}
			s = p;
			d = buf;
			while ((*d = *s) != 0) {
				s++;
				d++;
			}
			q = strstr(buf, "_FRUEHLING");
			if (q == 0) {
				q = strstr(buf, "_HERBST");
				if (q == 0) {
					q = strstr(buf, "_SNOW");
				}
			}
			if (q != 0) {
				*q = 0;
				if (fcn_0045be40(buf) != 0) {
					fcn_0043f990(g_6b8300, buf, i);
				}
			}
		}
	}
}
unsigned char _dpad_6b8300[376];
