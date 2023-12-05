#include "PointerRequestReceiver.h"
#include "RequestRoutines.h"

PointerRequestReceiver::PointerRequestReceiver()
{
    Request_Pointers.Basic_Request_Pointer_A = new std::function<void()>(std::bind(&RequestRoutines::Routine_A));
    Request_Pointers.Basic_Request_Pointer_B = new std::function<void()>(std::bind(&RequestRoutines::Routine_B));
    Request_Pointers.Basic_Request_Pointer_C = new std::function<void()>(std::bind(&RequestRoutines::Routine_C));
    Request_Pointers.Basic_Request_Pointer_D = new std::function<void()>(std::bind(&RequestRoutines::Routine_D));
    Request_Pointers.Basic_Request_Pointer_E = new std::function<void()>(std::bind(&RequestRoutines::Routine_E));
    Request_Pointers.Basic_Request_Pointer_F = new std::function<void()>(std::bind(&RequestRoutines::Routine_F));
    Request_Pointers.Basic_Request_Pointer_G = new std::function<void()>(std::bind(&RequestRoutines::Routine_G));
    Request_Pointers.Basic_Request_Pointer_H = new std::function<void()>(std::bind(&RequestRoutines::Routine_H));
    Request_Pointers.Basic_Request_Pointer_I = new std::function<void()>(std::bind(&RequestRoutines::Routine_I));
    Request_Pointers.Basic_Request_Pointer_J = new std::function<void()>(std::bind(&RequestRoutines::Routine_J));
    Request_Pointers.Basic_Request_Pointer_K = new std::function<void()>(std::bind(&RequestRoutines::Routine_K));
    Request_Pointers.Basic_Request_Pointer_L = new std::function<void()>(std::bind(&RequestRoutines::Routine_L));
    Request_Pointers.Basic_Request_Pointer_M = new std::function<void()>(std::bind(&RequestRoutines::Routine_M));
    Request_Pointers.Basic_Request_Pointer_N = new std::function<void()>(std::bind(&RequestRoutines::Routine_N));
    Request_Pointers.Basic_Request_Pointer_O = new std::function<void()>(std::bind(&RequestRoutines::Routine_O));
    Request_Pointers.Basic_Request_Pointer_P = new std::function<void()>(std::bind(&RequestRoutines::Routine_P));
    Request_Pointers.Basic_Request_Pointer_Q = new std::function<void()>(std::bind(&RequestRoutines::Routine_Q));
    Request_Pointers.Basic_Request_Pointer_R = new std::function<void()>(std::bind(&RequestRoutines::Routine_R));
    Request_Pointers.Basic_Request_Pointer_S = new std::function<void()>(std::bind(&RequestRoutines::Routine_S));
    Request_Pointers.Basic_Request_Pointer_T = new std::function<void()>(std::bind(&RequestRoutines::Routine_T));
    Request_Pointers.Basic_Request_Pointer_U = new std::function<void()>(std::bind(&RequestRoutines::Routine_U));
    Request_Pointers.Basic_Request_Pointer_V = new std::function<void()>(std::bind(&RequestRoutines::Routine_V));
    Request_Pointers.Basic_Request_Pointer_W = new std::function<void()>(std::bind(&RequestRoutines::Routine_W));
    Request_Pointers.Basic_Request_Pointer_X = new std::function<void()>(std::bind(&RequestRoutines::Routine_X));
    Request_Pointers.Basic_Request_Pointer_Y = new std::function<void()>(std::bind(&RequestRoutines::Routine_Y));
    Request_Pointers.Basic_Request_Pointer_Z = new std::function<void()>(std::bind(&RequestRoutines::Routine_Z));
}

PointerRequestReceiver::~PointerRequestReceiver()
{
    delete Request_Pointers.Basic_Request_Pointer_A;
    delete Request_Pointers.Basic_Request_Pointer_B;
    delete Request_Pointers.Basic_Request_Pointer_C;
    delete Request_Pointers.Basic_Request_Pointer_D;
    delete Request_Pointers.Basic_Request_Pointer_E;
    delete Request_Pointers.Basic_Request_Pointer_F;
    delete Request_Pointers.Basic_Request_Pointer_G;
    delete Request_Pointers.Basic_Request_Pointer_H;
    delete Request_Pointers.Basic_Request_Pointer_I;
    delete Request_Pointers.Basic_Request_Pointer_J;
    delete Request_Pointers.Basic_Request_Pointer_K;
    delete Request_Pointers.Basic_Request_Pointer_L;
    delete Request_Pointers.Basic_Request_Pointer_M;
    delete Request_Pointers.Basic_Request_Pointer_N;
    delete Request_Pointers.Basic_Request_Pointer_O;
    delete Request_Pointers.Basic_Request_Pointer_P;
    delete Request_Pointers.Basic_Request_Pointer_Q;
    delete Request_Pointers.Basic_Request_Pointer_R;
    delete Request_Pointers.Basic_Request_Pointer_S;
    delete Request_Pointers.Basic_Request_Pointer_T;
    delete Request_Pointers.Basic_Request_Pointer_U;
    delete Request_Pointers.Basic_Request_Pointer_V;
    delete Request_Pointers.Basic_Request_Pointer_W;
    delete Request_Pointers.Basic_Request_Pointer_X;
    delete Request_Pointers.Basic_Request_Pointer_Y;
    delete Request_Pointers.Basic_Request_Pointer_Z;
}

void PointerRequestReceiver::BasicRequestA()
{
    RequestRoutines::Routine_A();
}

void PointerRequestReceiver::BasicRequestB()
{
    RequestRoutines::Routine_B();
}

void PointerRequestReceiver::BasicRequestC()
{
    RequestRoutines::Routine_C();
}

void PointerRequestReceiver::BasicRequestD()
{
    RequestRoutines::Routine_D();
}

void PointerRequestReceiver::BasicRequestE()
{
    RequestRoutines::Routine_E();
}

void PointerRequestReceiver::BasicRequestF()
{
    RequestRoutines::Routine_F();
}

void PointerRequestReceiver::BasicRequestG()
{
    RequestRoutines::Routine_G();
}

void PointerRequestReceiver::BasicRequestH()
{
    RequestRoutines::Routine_H();
}

void PointerRequestReceiver::BasicRequestI()
{
    RequestRoutines::Routine_I();
}

void PointerRequestReceiver::BasicRequestJ()
{
    RequestRoutines::Routine_J();
}

void PointerRequestReceiver::BasicRequestK()
{
    RequestRoutines::Routine_K();
}

void PointerRequestReceiver::BasicRequestL()
{
    RequestRoutines::Routine_L();
}

void PointerRequestReceiver::BasicRequestM()
{
    RequestRoutines::Routine_M();
}

void PointerRequestReceiver::BasicRequestN()
{
    RequestRoutines::Routine_N();
}

void PointerRequestReceiver::BasicRequestO()
{
    RequestRoutines::Routine_O();
}

void PointerRequestReceiver::BasicRequestP()
{
    RequestRoutines::Routine_P();
}

void PointerRequestReceiver::BasicRequestQ()
{
    RequestRoutines::Routine_Q();
}

void PointerRequestReceiver::BasicRequestR()
{
    RequestRoutines::Routine_R();
}

void PointerRequestReceiver::BasicRequestS()
{
    RequestRoutines::Routine_S();
}

void PointerRequestReceiver::BasicRequestT()
{
    RequestRoutines::Routine_T();
}

void PointerRequestReceiver::BasicRequestU()
{
    RequestRoutines::Routine_U();
}

void PointerRequestReceiver::BasicRequestV()
{
    RequestRoutines::Routine_V();
}

void PointerRequestReceiver::BasicRequestW()
{
    RequestRoutines::Routine_W();
}

void PointerRequestReceiver::BasicRequestX()
{
    RequestRoutines::Routine_X();
}

void PointerRequestReceiver::BasicRequestY()
{
    RequestRoutines::Routine_Y();
}

void PointerRequestReceiver::BasicRequestZ()
{
    RequestRoutines::Routine_Z();
}