#include "serial.hpp"
#include <windows.h>  // Añade este include para las funciones de Windows
#include <string>     // Añade este include para std::string

Serial::Serial() : com_port(INVALID_HANDLE_VALUE)
{}

Serial::~Serial()
{
    close();
}

bool Serial::is_valid() const
{
    return com_port != INVALID_HANDLE_VALUE;
}

bool Serial::open(const std::string& name, std::string& errmsg)
{
    bool retval = false;
    DCB config;
    COMMTIMEOUTS timeouts = { 0 };  // Declaración TEMPRANA

    errmsg.clear();

    if (com_port != INVALID_HANDLE_VALUE)
    {
        errmsg = "COM port already open";
        goto exit;
    }

    // Abrir puerto COM (modo compartido)
    com_port = CreateFileA(  // Usamos CreateFileA en lugar de CreateFile
        name.c_str(),
        GENERIC_READ | GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,  // Permite compartir el puerto
        NULL,
        OPEN_EXISTING,
        0,
        NULL
    );

    if (com_port == INVALID_HANDLE_VALUE)
    {
        errmsg = "Can not open COM port";
        goto exit;
    }

    config.DCBlength = sizeof(config);
    if (!GetCommState(com_port, &config))
    {
        errmsg = "Can not get COM port config";
        goto exit;
    }

    config.BaudRate = CBR_115200;
    config.StopBits = ONESTOPBIT;
    config.Parity = NOPARITY;
    config.ByteSize = 8;

    if (!SetCommState(com_port, &config))
    {
        errmsg = "Can not set COM port config";
        goto exit;
    }

    // Configurar timeouts (parte nueva)
    timeouts.ReadIntervalTimeout = 50;
    timeouts.ReadTotalTimeoutConstant = 50;
    timeouts.ReadTotalTimeoutMultiplier = 10;
    timeouts.WriteTotalTimeoutConstant = 50;
    timeouts.WriteTotalTimeoutMultiplier = 10;

    if (!SetCommTimeouts(com_port, &timeouts))
    {
        errmsg = "Can not set COM timeouts";
        goto exit;
    }

    retval = true;

exit:
    if (retval == false)
    {
        close();
    }
    return retval;
}

void Serial::close()
{
    if (com_port != INVALID_HANDLE_VALUE)
    {
        CloseHandle(com_port);
        com_port = INVALID_HANDLE_VALUE;
    }
}

void Serial::write(const unsigned char* data, unsigned length)
{
    if (data == 0 || length == 0)
        return;

    if (com_port != INVALID_HANDLE_VALUE)
    {
        unsigned long wrote;
        WriteFile(com_port, data, length, &wrote, NULL);
        FlushFileBuffers(com_port);
    }
}