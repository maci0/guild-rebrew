void __cdecl d3_BuildViewMatrix(char* object, int a, int b, float* output);
void __cdecl d3_MultiplyAffineMatrices(float* a, float* b, float* output);
void __cdecl d3_ComposeObserverMatrix(char* obj, char* a, int b, char* m);
float* __stdcall fcn_005eb970(float* out, const float* a, const float* b);

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x00439870 */
void __cdecl d3_UpdateObjectCameraTransform(char* object, char* parent, int force)
{
	float matrix[16];
	char* source;
	char* destination;
	char* source2;
	char* destination2;
	if (!(object[0x212] & 0x80) || (char) force != 0) {
		d3_BuildViewMatrix(object, 0, 0, (float*) (*(char**) (object + 0x1ec) + 8));
		object[0x212] |= 0x80;
	}
	if ((object[0x213] & 1) && (char) force == 0
		&& *(char**) (*(char**) (object + 0x1ec) + 4) == parent) {
		return;
	}
	if (parent != 0 && !(object[0x210] & 0x80)) {
		force = 0x40;
		source = *(char**) (object + 0x1ec) + 8;
		destination = (char*) matrix;
		__asm {
			mov edi, destination
			mov esi, source
			mov ebx, force
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short first_copy_end
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
		first_copy_end:
			add ecx, ebx
			rep movsb
		}
		matrix[12] = matrix[12] - *(float*) (parent + 0x4c);
		matrix[13] = matrix[13] - *(float*) (parent + 0x50);
		matrix[14] = matrix[14] - *(float*) (parent + 0x54);
		matrix[12] = matrix[12] - *(float*) (parent + 0x78);
		matrix[13] = matrix[13] - *(float*) (parent + 0x7c);
		matrix[14] = matrix[14] - *(float*) (parent + 0x80);
		d3_MultiplyAffineMatrices(matrix, (float*) (parent + 0x18c),
			(float*) (*(char**) (object + 0x1ec) + 0x48));
	} else {
		force = 0x40;
		source2 = *(char**) (object + 0x1ec) + 8;
		destination2 = *(char**) (object + 0x1ec) + 0x48;
		__asm {
			mov edi, destination2
			mov esi, source2
			mov ebx, force
			lea ecx, [edi+edi*2]
			and ecx, 3
			sub ebx, ecx
			jle short second_copy_end
			rep movsb
			mov ecx, ebx
			and ebx, 3
			shr ecx, 2
			rep movsd
		second_copy_end:
			add ecx, ebx
			rep movsb
		}
	}
	*(char**) (*(char**) (object + 0x1ec) + 4) = parent;
	object[0x213] |= 1;
}
#else
/* ADDRESS: GOLDTL 0x00438100 */
void __cdecl d3_UpdateObjectCameraTransform(char* obj, char* cam, char force)
{
	float m[16];
	int n;
	char* s;
	float* d;
	int n2;
	char* s2;
	char* d2;

	if (!(obj[0x216] & 0x20) || force) {
		d3_ComposeObserverMatrix(obj, 0, 0, *(char**) (obj + 0x1ec) + 8);
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
#endif
