
#pragma once

#include "Net/Socket.h"
#include <windows.h>

class WinSocket : public Socket
{
public:
    WinSocket();
    WinSocket(SOCKET handle);
    ~WinSocket();

    bool SetBlockingMode(bool value) override;
    void Listen(int port) override;
    Socket* Accept() override;
    bool Connect(std::string host, int port) override;
    int Send(const char* buffer, int length) override;
    int Receive(char* buffer, int max) override;

private:
    void SetLastError();

    SOCKET handle;
    static int count;
};
