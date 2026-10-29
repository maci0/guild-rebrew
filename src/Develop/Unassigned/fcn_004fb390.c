void __cdecl fcn_004faed0(void*);
void __cdecl fcn_004c62c0(void*);
void* __cdecl memcpy(void* dst, const void* src, unsigned int n);

/* ADDRESS: GOLDTL 0x004fb390 */
void __cdecl fcn_004fb390(void)
{
	int buf[0x19];

	fcn_004faed0(buf);
	if (*(float*) 0x773d4c < *(float*) 0x6628a8) {
		*(float*) 0x773d50 = (float) buf[5];
		*(float*) 0x773d4c = (float) buf[5]
		    * (float) *(double*) 0x6640f0;
		*(float*) 0x99f5f4 = (float) buf[5];
	} else {
		*(float*) 0x773d50 = *(float*) 0x773d50
		    + ((float) buf[5] - *(float*) 0x773d50)
		    * *(float*) 0x6628cc;
		*(float*) 0x99f5f4 = *(float*) 0x773d50;
	}
	memcpy((void*) 0x99f5e0, buf, 0x28);
	*(int*) 0x99f5f8 = *(int*) 0x773d4c;
	*(float*) 0x99ec14 = (*(float*) 0x99f5f4
	    - *(float*) 0x773d4c) * (float) *(double*) 0x6653d0;
	*(int*) 0x99f590 = *(int*) 0x7f4c00;
	*(int*) 0x99f594 = *(int*) 0x7f4c04;
	*(int*) 0x99f598 = *(int*) 0x7f4c08;
	*(short*) 0x99f59c = *(short*) 0x7f4c0c;
	*(int*) ((char*) buf + 0x28) = *(int*) 0x99f5e0;
	*(int*) ((char*) buf + 0x2c) = *(int*) 0x99f5e4;
	*(int*) ((char*) buf + 0x30) = *(int*) 0x99f5e8;
	*(int*) ((char*) buf + 0x34) = *(int*) 0x99f5ec;
	*(int*) ((char*) buf + 0x38) = *(int*) 0x99f5f0;
	*(float*) ((char*) buf + 0x3c) = (*(float*) 0x99f5f4
	    - *(float*) 0x773d4c) * (float) *(double*) 0x6653d0;
	*(int*) ((char*) buf + 0x40) = *(int*) 0x773d4c;
	*(int*) ((char*) buf + 0x44) = *(int*) 0x99f5fc;
	*(int*) ((char*) buf + 0x48) = *(int*) 0x99f600;
	*(int*) ((char*) buf + 0x4c) = *(int*) 0x99f604;
	*(float*) ((char*) buf + 0x50) = (*(float*) 0x99f5f4
	    - *(float*) 0x773d4c) * (float) *(double*) 0x6653d0;
	*(int*) ((char*) buf + 0x54) = *(int*) 0x7f4c00;
	*(int*) ((char*) buf + 0x58) = *(int*) 0x7f4c04;
	*(int*) ((char*) buf + 0x5c) = *(int*) 0x7f4c08;
	*(short*) ((char*) buf + 0x60) = *(short*) 0x7f4c0c;
	fcn_004c62c0((char*) buf + 0x28);
}
