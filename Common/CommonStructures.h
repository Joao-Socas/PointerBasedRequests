#pragma once
#include <string>
#include <functional>

enum class IPVersion
{
    IPV4
//    IPV6,
//    AUTO
};

struct BroadcastData
{
    char Host_Name[64];
    IPVersion IP_Version;
    unsigned int Server_Port;
    char Server_IP_Adress[32];

    friend bool operator==(const BroadcastData& l, const BroadcastData& r)
    {
        return std::strcmp(l.Server_IP_Adress, r.Server_IP_Adress) == 0;
    }
};

struct ClientConnectionParams
{
    char Friendly_Name[64];
};

enum class REQUEST_CODES
{
    BASIC_A,
    BASIC_B,
    BASIC_C,
    BASIC_D,
    BASIC_E,
    BASIC_F,
    BASIC_G,
    BASIC_H,
    BASIC_I,
    BASIC_J,
    BASIC_K,
    BASIC_L,
    BASIC_M,
    BASIC_N,
    BASIC_O,
    BASIC_P,
    BASIC_Q,
    BASIC_R,
    BASIC_S,
    BASIC_T,
    BASIC_U,
    BASIC_V,
    BASIC_W,
    BASIC_X,
    BASIC_Y,
    BASIC_Z
    //DATA_RECEIVE,
    //DATA_TRANSMIT,
    //DATA_TRANSCEIVE
};

//struct DataExample
//{
//    char Data_Content[64];
//};

struct RequestPointers
{
    std::function<void()>* Basic_Request_Pointer_A;
    std::function<void()>* Basic_Request_Pointer_B;
    std::function<void()>* Basic_Request_Pointer_C;
    std::function<void()>* Basic_Request_Pointer_D;
    std::function<void()>* Basic_Request_Pointer_E;
    std::function<void()>* Basic_Request_Pointer_F;
    std::function<void()>* Basic_Request_Pointer_G;
    std::function<void()>* Basic_Request_Pointer_H;
    std::function<void()>* Basic_Request_Pointer_I;
    std::function<void()>* Basic_Request_Pointer_J;
    std::function<void()>* Basic_Request_Pointer_K;
    std::function<void()>* Basic_Request_Pointer_L;
    std::function<void()>* Basic_Request_Pointer_M;
    std::function<void()>* Basic_Request_Pointer_N;
    std::function<void()>* Basic_Request_Pointer_O;
    std::function<void()>* Basic_Request_Pointer_P;
    std::function<void()>* Basic_Request_Pointer_Q;
    std::function<void()>* Basic_Request_Pointer_R;
    std::function<void()>* Basic_Request_Pointer_S;
    std::function<void()>* Basic_Request_Pointer_T;
    std::function<void()>* Basic_Request_Pointer_U;
    std::function<void()>* Basic_Request_Pointer_V;
    std::function<void()>* Basic_Request_Pointer_W;
    std::function<void()>* Basic_Request_Pointer_X;
    std::function<void()>* Basic_Request_Pointer_Y;
    std::function<void()>* Basic_Request_Pointer_Z;
};

//struct SwitchRequest
//{
//    REQUEST_CODES Request_Code;
//    DataExample Data_Example;
//};
//
//struct PointerRequest
//{
//    std::function<void(PointerRequest&)>* Request_Pointer;
//    DataExample Data_Example;
//};

struct MultipleSwitchRequestsTest
{
    REQUEST_CODES Request_Codes[100000];
};

struct MultiplePointerRequestsTest
{
    std::function<void()>* Request_Pointers[100000];
};