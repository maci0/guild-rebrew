#ifndef DOWNLOAD_STATE_H
#define DOWNLOAD_STATE_H

/* Bulk-transfer counters and eight per-player progress slots form one block. */
struct DownloadState {
    unsigned int total_size;
    unsigned int received;
    unsigned int slots[8];
    unsigned int buffer;
};
extern struct DownloadState g_download_state;
#define g_download_total_size g_download_state.total_size
#define g_download_received g_download_state.received
#define g_download_slots g_download_state.slots
#define g_download_buffer g_download_state.buffer

#endif
