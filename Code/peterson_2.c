// peterson_two_threads.c
#include <windows.h>
#include <stdio.h>

volatile LONG x = 0, y = 1;

/* Peterson state */
volatile LONG want[2] = {0, 0};
volatile LONG turn = 0;

void peterson_enter(int i) {
    int j = 1 - i;
    want[i] = 1;
    turn = j;
    // chờ đến lượt
    while (want[j] && turn == j) {
        SwitchToThread(); // nhường CPU cho đỡ quay
    }
}
void peterson_leave(int i) {
    want[i] = 0;
}

/* Thread functions: CHÚ Ý có tên tham số (LPVOID arg) */
DWORD WINAPI T1(LPVOID arg) { // id = 0
    (void)arg;
    for (;;) {
        peterson_enter(0);
        x = y + 1;
        printf("%4ld", x);
        peterson_leave(0);
    }
    return 0;
}
DWORD WINAPI T2(LPVOID arg) { // id = 1
    (void)arg;
    for (;;) {
        peterson_enter(1);
        y = 2;
        y = y * 2;  // hai bước này là "nguyên tử" theo nghĩa quan sát
        peterson_leave(1);
    }
    return 0;
}

int main(void) {
    HANDLE h1, h2; DWORD tid1, tid2;

    h1 = CreateThread(NULL, 0, T1, NULL, 0, &tid1);
    h2 = CreateThread(NULL, 0, T2, NULL, 0, &tid2);

    WaitForSingleObject(h1, INFINITE);
    WaitForSingleObject(h2, INFINITE);

    CloseHandle(h1);
    CloseHandle(h2);
    return 0;
}
