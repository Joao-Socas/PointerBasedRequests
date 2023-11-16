#pragma once
#include <functional>

enum class REQUEST_CODES
{
    BASIC,
    DATA_RECEIVE,
    DATA_TRANSMIT,
    DATA_TRANSCEIVE
};

struct RequestPointers
{
    std::function<void()> Basic_Request_Pointer;
    std::function<void()> Data_Receive_Request_Pointer;
    std::function<void()> Data_Transmit_Request_Pointer;
    std::function<void()> Data_Transceive_Request_Pointer;
};

struct DataExample
{
    char Data_Content[64];
};

struct SwitchRequest
{
    REQUEST_CODES Request_Code;
    DataExample Data_Example;
};

struct PointerRequest
{
    std::function<void()> Request_Pointer;
    DataExample Data_Example;
};