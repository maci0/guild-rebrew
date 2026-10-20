/* Inventory extent defect, no function entry at 0x00654df1. The first 53
 * bytes (0x00654df1..0x00654e25) are the tail of a CRT x87 helper: entry
 * is mid-expression with st(0) already live, so nothing in this range is a
 * callable start. The following 34 bytes are a separate CRT math wrapper
 * (fnsave/frstor around 0x0065504c), and 0x00654e57..0x00654e5f is int3
 * padding. The extent must be repaired before a C body can be claimed. */
/* ADDRESS: GOLDTL 0x00654df1 */
int __cdecl fcn_00654df1(void)
{
    return 0;
}
