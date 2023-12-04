#include "PointerRequestReceiver.h"
#include "RequestRoutines.h"

PointerRequestReceiver::PointerRequestReceiver()
{
}

void PointerRequestReceiver::BasicRequestA()
{
    // Timer stop
    RequestRoutines::Routine_A();
}

void PointerRequestReceiver::BasicRequestB()
{
    // Timer stop
    RequestRoutines::Routine_B();
}

void PointerRequestReceiver::BasicRequestC()
{
    // Timer stop
    RequestRoutines::Routine_C();
}
