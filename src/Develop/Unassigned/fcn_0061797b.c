#pragma optimize("s", on)

#include <string.h>

typedef struct Obj61797b {
	char pad0[0xb4];
	int f0b4;
	char pad0b8[4];
	char* f0bc;
	char* f0c0;
	char* f0c4;
	char f0c8[0x108];
	int f1d0;
	char f1d4[0x204];
	int f3d8;
} Obj61797b;

int __cdecl fcn_006511ab(int c);
int __cdecl fcn_006510d8(int c);
int __cdecl fcn_00651156(int c);
int __cdecl fcn_006511fb(int c);
void __cdecl fcn_0061694d(Obj61797b* self, char* msg);
int __cdecl fcn_00616a83(Obj61797b* self);

extern char data_66742c[];
extern char data_667428[];
extern char data_667158[];

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x0061797b */
int __fastcall fcn_0061797b(Obj61797b* self)
{
	char* s;
	char* q;
	char* e;
	char c;
	char* dst;
	int n;
	int i;
	int r;
	int flag;

	self->f3d8 = 0;
	for (;;) {
		s = self->f0c0;
		if ((unsigned int) self->f0c4 <= (unsigned int) s) {
			if (s == self->f0c4) {
				self->f0c0 = s + 1;
				self->f3d8 = 1;
				return 0x10c;
			}
			return -1;
		}
		c = *s;
		if (c == '\n') {
			self->f0c0 = s + 1;
			self->f1d0 += 1;
			self->f0bc = s + 1;
			continue;
		}
		if (fcn_006511ab(c) != 0) {
			self->f0c0 = s + 1;
			continue;
		}
		if (c == '#') {
			q = s + 1;
			self->f0c0 = q;
			while (q < self->f0c4 && *q != '\n') {
				q++;
				self->f0c0 = q;
			}
			if (q - s > 5 && strncmp(s, "#line", 5) == 0) {
				s = self->f0c0;
				q = s;
				if (q < self->f0c4) {
					while (q < self->f0c4 && *q != '"') {
						q++;
					}
				}
				n = (int) (q - s);
				if (n > 0xff) {
					n = 0xff;
				}
				e = q;
				if (e < self->f0c4) {
					e++;
					while (e < self->f0c4 && *e != '"') {
						e++;
					}
				}
				flag = (int) (e - q);
				if (flag > 1) {
					dst = self->f1d4;
					for (q = s + 1; q < e; q++) {
						c = *q;
						q++;
						*dst = c;
						if (c == '\\' && q < e && *q == '\\') {
							q++;
						}
						dst++;
					}
					*dst = 0;
				}
				i = (int) (e - s);
				if (i > 0xff) {
					i = 0xff;
				}
				if (i != 0) {
					memcpy(self->f1d4, s, i);
					self->f1d4[i] = 0;
					self->f1d0 = fcn_00651156((int) self->f1d4) - 1;
				}
				self->f0c0 = e;
				continue;
			}
			fcn_0061694d(self, "preprocessor directives are not supported");
			continue;
		}
		if (c == ';') {
			self->f0c0 = s + 1;
			q = self->f0c0;
			while (q < self->f0c4) {
				if (*q == '\n') {
					break;
				}
				q++;
				self->f0c0 = q;
			}
			continue;
		}
		if (c == '/') {
			q = self->f0c4;
			q = self->f0c0 + 1;
			if (q < self->f0c4 && *q == '/') {
				self->f0c0 = q;
				while (q < self->f0c4) {
					if (*q == '\n') {
						break;
					}
					q++;
					self->f0c0 = q;
				}
				continue;
			}
			if (q < self->f0c4 && *q == '*') {
				q = self->f0c0 + 2;
				self->f0c0 = q;
				while (q < self->f0c4) {
					q = self->f0c0;
					if (*q == '*' && q + 1 < self->f0c4 && q[1] == '/') {
						self->f0c0 = q + 2;
						break;
					}
					if (*q == '\n') {
						self->f1d0 += 1;
						self->f0bc = q + 1;
					}
					self->f0c0 = q + 1;
					q = self->f0c0;
					if (q >= self->f0c4) {
						break;
					}
				}
				continue;
			}
		}
		r = fcn_006510d8(c);
		if (r != 0) {
			s = self->f0c0;
			q = s + 1;
			self->f0c0 = q;
			while (q < self->f0c4) {
				if (fcn_006511fb(*q) == 0 && *q != '_') {
					break;
				}
				q++;
				self->f0c0 = q;
			}
			n = (int) (self->f0c0 - s);
			if (n > 0xff) {
				n = 0xff;
			}
			memcpy(self->f0c8, s, n);
			self->f0c8[n] = 0;
			self->f3d8 = 1;
			if (strcmp(self->f0c8, data_66742c) == 0) {
				return 0x101;
			}
			if (strcmp(self->f0c8, data_667428) == 0) {
				return 0x102;
			}
			if (strcmp(self->f0c8, data_667158) == 0) {
				return 0x103;
			}
			r = fcn_00616a83(self);
			if (r == 0x109) {
				self->f3d8 = 0;
			}
			return r;
		}
		r = fcn_00651156(c);
		if (r == 0) {
			if (*self->f0c0 == '+') {
				self->f3d8 = 1;
			}
			self->f0c0 = self->f0c0 + 1;
			return (int) c;
		}
		s = self->f0c0;
		self->f0c0 = s + 1;
		q = self->f0c0;
		while (q < self->f0c4) {
			r = fcn_00651156(*q);
			if (r == 0) {
				if (self->f0b4 == 0 || (*q != '.' && *q != 'e')) {
					c = *q;
					if ((c != '+' && c != '-') || q[-1] != 'e') {
						break;
					}
				}
			}
			q++;
			self->f0c0 = q;
		}
		n = (int) (self->f0c0 - s);
		if (n > 0xff) {
			n = 0xff;
		}
		memcpy(self->f0c8, s, n);
		self->f0c8[n] = 0;
		if (self->f0b4 != 0 && self->f0c0 < self->f0c4 && *self->f0c0 == 'f') {
			self->f0c0 = self->f0c0 + 1;
		}
		return (int) self->f0c8;
	}
}
