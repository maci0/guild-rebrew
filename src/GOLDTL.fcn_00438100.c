// FUNCTION: GOLDTL 0x00438100
// SIZE: 364

void __cdecl fcn_004557c0(char* obj, int a, int b, char* m);
float* __stdcall fcn_005eb970(float* out, const float* a, const float* b);

void __cdecl fcn_00438100(char* obj, char* cam, char force)
{
	float m[16];
	int n;
	char* s;
	float* d;
	int n2;
	char* s2;
	char* d2;

	if (!(obj[0x216] & 0x20) || force) {
		fcn_004557c0(obj, 0, 0, *(char**) (obj + 0x1ec) + 8);
		obj[0x216] |= 0x20;
	}
	if ((obj[0x216] & 0x40) && !force && *(char**) (*(char**) (obj + 0x1ec) + 4) == cam) {
		return;
	}
	if (cam != 0 && !(obj[0x214] & 0x20)) {
		n = 0x40;
		s = *(char**) (obj + 0x1ec) + 8;
		d = m;
		__asm {
			mov edi, d
			mov esi, s
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
		m[12] -= *(float*) (cam + 0x4c);
		m[13] -= *(float*) (cam + 0x50);
		m[14] -= *(float*) (cam + 0x54);
		m[12] -= *(float*) (cam + 0x78);
		m[13] -= *(float*) (cam + 0x7c);
		m[14] -= *(float*) (cam + 0x80);
		fcn_005eb970((float*) (*(char**) (obj + 0x1ec) + 0x48), m, (float*) (cam + 0x18c));
	} else {
		n2 = 0x40;
		s2 = *(char**) (obj + 0x1ec) + 8;
		d2 = *(char**) (obj + 0x1ec) + 0x48;
		__asm {
			mov edi, d2
			mov esi, s2
			mov ebx, n2
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short L2
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
		L2:
			add ecx, ebx
			rep movsb
		}
	}
	*(char**) (*(char**) (obj + 0x1ec) + 4) = cam;
	obj[0x216] |= 0x40;
}
