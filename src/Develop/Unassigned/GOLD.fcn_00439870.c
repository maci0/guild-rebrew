void __cdecl fcn_00458d90(char* object, int a, int b, float* output);
void __cdecl fcn_00453ed0(float* a, float* b, float* output);

/* ADDRESS: GOLD 0x00439870 */
void __cdecl fcn_00439870(char* object, char* parent, int force)
{
	float matrix[16];
	char* source;
	char* destination;
	double x;
	double y;
	if ((signed char) object[0x212] >= 0 || (char) force != 0) {
		fcn_00458d90(object, 0, 0, (float*) (*(char**) (object + 0x1ec) + 8));
		object[0x212] |= 0x80;
	}
	if ((object[0x213] & 1) && (char) force == 0
		&& *(char**) (*(char**) (object + 0x1ec) + 4) == parent) {
		return;
	}
	if (parent != 0 && (signed char) object[0x210] >= 0) {
		source = *(char**) (object + 0x1ec) + 8;
		destination = (char*) matrix;
		force = 0x40;
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
		x = (double) matrix[12] - *(float*) (parent + 0x4c);
		y = (double) matrix[13] - *(float*) (parent + 0x50);
		matrix[14] = matrix[14] - *(float*) (parent + 0x54);
		matrix[12] = x - *(float*) (parent + 0x78);
		matrix[13] = y - *(float*) (parent + 0x7c);
		matrix[14] = matrix[14] - *(float*) (parent + 0x80);
		fcn_00453ed0(matrix, (float*) (parent + 0x18c),
			(float*) (*(char**) (object + 0x1ec) + 0x48));
	} else {
		source = *(char**) (object + 0x1ec) + 8;
		destination = *(char**) (object + 0x1ec) + 0x48;
		force = 0x40;
		__asm {
			mov edi, destination
			mov esi, source
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
