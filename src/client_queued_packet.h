#ifndef CLIENT_QUEUED_PACKET_H
#define CLIENT_QUEUED_PACKET_H

#pragma pack(push, 1)
/* SIZE 0x99 */
typedef struct pkt99 {
    unsigned char type;
    unsigned short crc;
    unsigned char flag;
    int seq;
    int cur;
    int nextseq;
    unsigned char data[0x80];
    char unk_90;
    struct pkt99* prev;
    struct pkt99* next;
} CLIENT_QUEUED_PACKET;
#pragma pack(pop)

extern CLIENT_QUEUED_PACKET g_aed740[0x8000];

#endif
