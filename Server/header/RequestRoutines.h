#pragma once
class RequestRoutines
{
public:
	static void Routine_A();
	static void Routine_B();
	static void Routine_C();

private:
	static int Number_A_Requested;
	static int Number_B_Requested;
	static int Number_C_Requested;
};