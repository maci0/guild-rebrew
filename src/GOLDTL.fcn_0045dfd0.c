#include "deflate.h"

int __cdecl fcn_0045df20(z_streamp strm);

// FUNCTION: GOLDTL 0x45dfd0
int __cdecl fcn_0045dfd0(z_streamp dest, z_streamp source)
{
	deflate_state* ds;
	deflate_state* ss;
	ushf* overlay;

	if (source == Z_NULL || dest == Z_NULL || source->state == Z_NULL) {
		return Z_STREAM_ERROR;
	}

	ss = source->state;

	*dest = *source;

	ds = (deflate_state*) ZALLOC(dest, 1, sizeof(deflate_state));
	if (ds == Z_NULL) {
		return Z_MEM_ERROR;
	}
	dest->state = (struct internal_state FAR*) ds;
	*ds = *ss;
	ds->strm = dest;

	ds->window = (Bytef*) ZALLOC(dest, ds->w_size, 2 * sizeof(Byte));
	ds->prev = (Posf*) ZALLOC(dest, ds->w_size, sizeof(Pos));
	ds->head = (Posf*) ZALLOC(dest, ds->hash_size, sizeof(Pos));
	overlay = (ushf*) ZALLOC(dest, ds->lit_bufsize, sizeof(ush) + 2);
	ds->pending_buf = (uchf*) overlay;

	if (ds->window == Z_NULL || ds->prev == Z_NULL || ds->head == Z_NULL || ds->pending_buf == Z_NULL) {
		fcn_0045df20(dest);
		return Z_MEM_ERROR;
	}
	zmemcpy(ds->window, ss->window, ds->w_size * 2 * sizeof(Byte));
	zmemcpy(ds->prev, ss->prev, ds->w_size * sizeof(Pos));
	zmemcpy(ds->head, ss->head, ds->hash_size * sizeof(Pos));
	zmemcpy(ds->pending_buf, ss->pending_buf, (uInt) ds->pending_buf_size);

	ds->pending_out = ds->pending_buf + (ss->pending_out - ss->pending_buf);
	ds->d_buf = overlay + ds->lit_bufsize / sizeof(ush);
	ds->l_buf = ds->pending_buf + (1 + sizeof(ush)) * ds->lit_bufsize;

	ds->l_desc.dyn_tree = ds->dyn_ltree;
	ds->d_desc.dyn_tree = ds->dyn_dtree;
	ds->bl_desc.dyn_tree = ds->bl_tree;

	return Z_OK;
}
