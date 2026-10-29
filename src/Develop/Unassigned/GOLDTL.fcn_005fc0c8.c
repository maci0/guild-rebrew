/* The stored 68-byte extent runs 24 bytes past this constructor into the
 * sibling body at 0x005fc0f4; this definition is the 44-byte constructor. */
/* ADDRESS: GOLDTL 0x005fc0c8 */
void *__fastcall fcn_005fc0c8(void *self)
{
	char *obj;

	obj = (char *)self;
	*(int *)obj = 0x6665e0;
	*(int *)(obj + 0x4) = 0;
	*(int *)(obj + 0x1c) = 0;
	*(int *)(obj + 0x40) = 0;
	*(int *)(obj + 0x10) = 0;
	*(int *)(obj + 0x14) = 0;
	*(int *)(obj + 0x18) = 0;
	*(int *)(obj + 0x2c) = 0;
	*(int *)(obj + 0x48) = 0;
	*(int *)(obj + 0x4c) = 0;
	*(int *)(obj + 0x44) = 0;
	*(int *)(obj + 0x50) = 0;
	return self;
}
