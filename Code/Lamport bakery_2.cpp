// bakery_sync.c — Đồng bộ Lamport Bakery cho T1, T2, T3 (Windows + CreateThread)
#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>

#define NTHREAD 3  // T1, T2, T3

// ====== Biến dùng chung ======
static volatile LONG x = 0, y = 1;

// ====== Trạng thái Lamport Bakery ======
static volatile LONG choosing[NTHREAD];  // choosing[i] = 1 khi i đang chọn vé
static volatile LONG number  [NTHREAD];  // number[i]   = vé (0 = không muốn vào)

// Đọc/ghi nguyên tử + barrier
static __forceinline LONG atomic_load_long(volatile LONG* p) {
    return InterlockedExchangeAdd(p, 0);
}
static __forceinline void atomic_store_long(volatile LONG* p, LONG v) {
    InterlockedExchange(p, v);
    MemoryBarrier();
}
static int max_ticket(void){
    int m = 0;
    for (int i = 0; i < NTHREAD; ++i) {
        int v = (int)atomic_load_long(&number[i]);
        if (v > m) m = v;
    }
    return m;
}
static __forceinline int pair_less(int a,int b,int c,int d){
    return (a < c) || (a == c && b < d);
}

static void bakery_lock(int i){
    atomic_store_long(&choosing[i], 1);
    int my = 1 + max_ticket();
    atomic_store_long(&number[i], my);
    atomic_store_long(&choosing[i], 0);

    for (int j = 0; j < NTHREAD; ++j) {
        if (j == i) continue;
        while (atomic_load_long(&choosing[j]) != 0) { SwitchToThread(); }
        for (;;) {
            int nj = (int)atomic_load_long(&number[j]);
            if (nj == 0) break; // j không muốn vào CS
            int ni = (int)atomic_load_long(&number[i]);
            if (pair_less(nj, j, ni, i)) { SwitchToThread(); }
            else break;
        }
    }
}
static void bakery_unlock(int i){
    atomic_store_long(&number[i], 0);
}

// ====== 3 thread proc ======
// T1: x = y + 1; in x (chỉ in số như code gốc)
static DWORD WINAPI T1_proc(LPVOID param){
    int id = *(int*)param; // 0
    for(;;){
        bakery_lock(id);
        LONG y_now = atomic_load_long(&y);
        LONG x_new = y_now + 1;
        x = x_new;
        printf("%4ld", x_new); fflush(stdout);
        bakery_unlock(id);
        // tùy chọn: Sleep(0) hoặc SwitchToThread();
    }
    return 0;
}

// T2: y = 2; y = y * 2;
static DWORD WINAPI T2_proc(LPVOID param){
    int id = *(int*)param; // 1
    for(;;){
        bakery_lock(id);
        y = 2;
        y = y * 2;  // hai bước này giờ là nguyên tử theo nghĩa quan sát
        bakery_unlock(id);
    }
    return 0;
}

// T3: y = 5; y = y + 10;
static DWORD WINAPI T3_proc(LPVOID param){
    int id = *(int*)param; // 2
    for(;;){
        bakery_lock(id);
        y = 5;
        y = y + 10;
        bakery_unlock(id);
    }
    return 0;
}

int main(void){
    HANDLE h[NTHREAD];
    DWORD tid;
    int ids[NTHREAD] = {0,1,2};

    // khởi tạo bakery
    for (int i = 0; i < NTHREAD; ++i) {
        atomic_store_long(&choosing[i], 0);
        atomic_store_long(&number[i],   0);
    }

    // tạo 3 luồng
    h[0] = CreateThread(NULL, 0, T1_proc, &ids[0], 0, &tid);
    h[1] = CreateThread(NULL, 0, T2_proc, &ids[1], 0, &tid);
    h[2] = CreateThread(NULL, 0, T3_proc, &ids[2], 0, &tid);

    WaitForMultipleObjects(NTHREAD, h, TRUE, INFINITE);
    for (int i = 0; i < NTHREAD; ++i) CloseHandle(h[i]);
    return 0;
}
