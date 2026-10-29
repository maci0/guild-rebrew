struct inflate_blocks_state {
	int mode;
};

/* ADDRESS: GOLDTL 0x00460a40 */
int __cdecl fcn_00460a40(struct inflate_blocks_state* s)
{
	return s->mode == 1;
}
