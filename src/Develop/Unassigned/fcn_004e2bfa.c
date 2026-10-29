/* Fragment evidence: this is not a function start, it is an interior split of
   fcn_004e2b70.

   The owning function starts at 0x4e2b70 with `mov eax,0x23EC; call 0x64D710`
   (__chkstk), then push ebx/ebp/esi/edi and the 0x23EC-byte local frame; it
   returns through two epilogues at `add esp,0x22D0; ret` 0x4e32A2 and
   0x4e32BE. So the function spans 0x4e2b70..0x4e32BE, 1871 bytes, which is
   exactly the two adjacent inventory rows 0x4e2b70 (138) and 0x4e2bfa
   (1733). The split sits on an interior branch target, not a boundary.

   Entry 0x4e2bfa is the jl target of 0x4e2bf0 (`jl 0x4e2bfa`); the fallthrough
   path 0x4e2bf2..0x4e2bf8 jumps to 0x4e2bfc, and both paths continue the
   enclosing loop body. The first instruction 0x4e2bfa `mov ebp,eax` consumes
   the loop index left in eax; ebx/esi/edi and the 0x23EC frame are live on
   entry. Whole-.text scan finds no call, jump-table or data reference to
   0x4e2bfa; the seven `ret` bytes inside this extent (0x4e2c61, 0x4e2d43,
   0x4e2e33, 0x4e2f67, 0x4e301e, 0x4e32A2, 0x4e32BE) are the owning function's
   own exits.

   Consequence: a standalone C89 function cannot reproduce these bytes. The
   compiler always emits its own prologue/epilogue, and the body's locals live
   in the caller's 0x23EC frame at [esp + ...], so the extent has no callable
   ABI of its own. The honest repair is the extent merge below, then one body
   for the whole 1871-byte function in src/fcn_004e2b70.c:

     rebrew binary repair-extents --merge 0x4e2b70=0x4e2bfa --reason \
       "interior jl target 0x4e2bfa is split off fcn_004e2b70; the function
        runs 0x4e2b70..0x4e32be (1871 bytes) through the ret at 0x4e32be"

   That repair is a metadata write and is out of scope for this slice, so this
   row stays a documented empty stub (STUB, object 1 byte, 0/1733 matched).
*/
/* ADDRESS: GOLDTL 0x004e2bfa */
void __cdecl fcn_004e2bfa(void)
{
}
