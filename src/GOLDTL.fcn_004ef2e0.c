unsigned int __cdecl ls_ReadVfsDataChecked(void* outBuffer, int elementSize, int elementCount, void* streamCtx);

/* ADDRESS: GOLDTL 0x004ef2e0 */
int __cdecl fcn_004ef2e0(void* stream)
{
	int p;

	if (ls_ReadVfsDataChecked((void*) 0x772fe8, 4, 1, stream) <= 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked((void*) 0x772fec, 2, 1, stream) <= 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked((void*) 0x772fee, 4, 1, stream) <= 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked((void*) 0x772ff2, 4, 1, stream) <= 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked((void*) 0x9a9200, 4, 1, stream) <= 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked((void*) 0x9a9204, 4, 1, stream) <= 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked((void*) 0x9a9208, 0xc, 1, stream) <= 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked((void*) 0x9a9214, 4, 1, stream) <= 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked((void*) 0x9a9218, 4, 1, stream) <= 0) {
		return 0;
	}
	if (ls_ReadVfsDataChecked((void*) 0x9a921c, 4, 1, stream) <= 0) {
		return 0;
	}
	p = 0x7731f0;
	do {
		if (ls_ReadVfsDataChecked((void*) (p - 0x38), 4, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p - 0x30), 4, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p - 0x2c), 4, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p - 0x28), 4, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p - 0x24), 4, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p - 0x20), 0x10, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p - 0x10), 0x10, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) p, 0x10, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0x20), 0x10, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0x30), 4, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0x34), 4, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0x38), 4, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0x3c), 4, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0x44), 4, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0x48), 0x10, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0x58), 0x10, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0x68), 0x10, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0x88), 0x10, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0x98), 4, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0x9c), 4, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0xa0), 4, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0xa4), 4, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0xac), 4, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0xb0), 0x10, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0xc0), 0x10, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0xd0), 0x10, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0xf0), 0x10, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0x100), 4, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0x104), 4, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0x108), 4, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0x10c), 4, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0x114), 4, 1, stream) <= 0) {
			return 0;
		}
		if (ls_ReadVfsDataChecked((void*) (p + 0x118), 0xc, 1, stream) <= 0) {
			return 0;
		}
		p += 0x170;
	} while (p < 0x773d70);
	return 1;
}
