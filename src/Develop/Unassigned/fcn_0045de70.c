struct deflate_state_45de70 {
	char pad0[8];
	unsigned char* pending_buf;
	char pad[8];
	unsigned int pending;
};

/* ADDRESS: GOLDTL 0x0045de70 */
void __cdecl fcn_0045de70(struct deflate_state_45de70* s, unsigned int b)
{
	s->pending_buf[s->pending++] = (unsigned char) (b >> 8);
	s->pending_buf[s->pending++] = (unsigned char) b;
}
