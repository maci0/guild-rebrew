void __cdecl fcn_00458d90(char* object, int a, int b, float* output);
void __cdecl d3_MultiplyAffineMatrices(float* a, float* b, float* output);

/* ADDRESS: GOLD 0x00439870 */
void __cdecl fcn_00439870(char* object, char* parent, int force)
{
	float matrix[16];
	char* source;
	char* destination;
	if (!(object[0x212] & 0x80) || (char) force != 0) {
		fcn_00458d90(object, 0, 0, (float*) (*(char**) (object + 0x1ec) + 8));
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
		source = *(char**) (object + 0x1ec) + 8;
		destination = *(char**) (object + 0x1ec) + 0x48;
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
