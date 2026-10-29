extern int g_10405c4;

// SIZE 0x70
typedef struct {
	char name[0x40];
	int x40;
	int x44;
	int x48;
	int x4c;
	int x50;
	unsigned char flags;
	char p55[3];
	int x58;
	unsigned char x5c;
	char p5d[3];
	int x60;
	int x64;
	int x68;
	int x6c;
} Tex;

extern char* g_104049c;
extern unsigned int g_10404a0;
extern int g_10405c0;

Tex* __cdecl fcn_0045c290(int, int);


/* ADDRESS: GOLDTL 0x0045d1e0 */
Tex* __cdecl fcn_0045d1e0(Tex* src, int color, char recurse)
{
	Tex* p;
	volatile int n;
	int c;
	unsigned int i;

	if (src == 0) {
		return 0;
	}
	p = fcn_0045c290(color, 0);
	if (p != 0) {
		n = 0x70;
		/*
		 * TODO: replace this inline-asm copy with proper C once a spelling is
		 * found; no msvc6 C memcpy form emits the prelude
		 * (docs/codegen-walls.md section 6b).
		 */
		__asm {
			mov edi, p
			mov esi, src
			mov ebx, n
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L1
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
		L1:
			add ecx, ebx
			rep movsb
		}
		p->x58 = color;
		c = ((unsigned char*) &color)[1];
		p->x40 = 1;
		p->x4c = (int) src;
		p->x6c = (((c << 8) | c) << 8) | c;
		p->flags |= 2;
		if (src->flags & 2) {
			p->x44 = src->x44;
		} else {
			p->x44 = src - ((Tex*)g_104049c);
		}
		g_10405c4++;
		if (p->x48 != -1 && p->x5c > 0 && recurse) {
			p->x48 = g_10405c0;
			for (i = 0; i < g_10404a0; i++) {
				if (((Tex*)g_104049c)[i].x40 > 0 && ((Tex*)g_104049c)[i].x48 == src->x48) {
					fcn_0045d1e0(&((Tex*)g_104049c)[i], color, 0);
				}
			}
			g_10405c0++;
		}
	}
	return p;
}
