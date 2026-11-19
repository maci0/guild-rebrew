#ifndef DOWNLOAD_STATE_H
#define DOWNLOAD_STATE_H

/* Bulk-transfer counters and eight per-player progress slots form one block. */
struct DownloadState {
    unsigned int total_size;
    unsigned int received;
    unsigned int slots[8];
    unsigned int buffer;
};
extern struct DownloadState srv_DownloadState;
#define g_download_total_size srv_DownloadState.total_size
#define srv_DownloadReceivedBytes srv_DownloadState.received
#define g_download_slots srv_DownloadState.slots
#define g_download_buffer srv_DownloadState.buffer

#endif
