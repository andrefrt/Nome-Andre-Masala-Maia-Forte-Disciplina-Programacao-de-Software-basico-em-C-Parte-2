#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <windows.h>

int main(void) {
    HANDLE hSerial;
    DCB dcbSerialParams = {0};
    COMMTIMEOUTS timeouts = {0};

    hSerial = CreateFile("COM1", GENERIC_READ | GENERIC_WRITE, 0, NULL, OPEN_EXISTING, 0, NULL);
    if (hSerial == INVALID_HANDLE_VALUE) {
        printf("Erro.\n");
        return 1;
    }

    dcbSerialParams.DCBlength = sizeof(dcbSerialParams);
    if (!GetCommState(hSerial, &dcbSerialParams)) {
        printf("Erro.\n");
        CloseHandle(hSerial);
        return 1;
    }

    dcbSerialParams.BaudRate = CBR_9600;
    dcbSerialParams.ByteSize = 8;
    dcbSerialParams.StopBits = ONESTOPBIT;
    dcbSerialParams.Parity = NOPARITY;
    if (!SetCommState(hSerial, &dcbSerialParams)) {
        printf("Erro.\n");
        CloseHandle(hSerial);
        return 1;
    }

    if (!GetCommState(hSerial, &dcbSerialParams)) {
        printf("Erro.\n");
        CloseHandle(hSerial);
        return 1;
    }
    printf("Porta serial:\n");
    printf("Baud Rate: %d\n", dcbSerialParams.BaudRate);
    printf("Byte Size: %d\n", dcbSerialParams.ByteSize);
    printf("Stop Bits: %d\n", dcbSerialParams.StopBits);
    printf("Parity: %d\n", dcbSerialParams.Parity);

    CloseHandle(hSerial);

    return 0;
}
