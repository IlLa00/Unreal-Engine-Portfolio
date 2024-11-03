#pragma once

#include "CoreMinimal.h"

#define PrintLine() {CLog::Log(__FUNCTION__, __LINE__);}

class PORTFOLIO_API CLog
{
public:
	static void Print(int32 Value, int32 Key = -1, float Duration = 2.f, FColor Color = FColor::White);
	static void Print(float Value, int32 Key = -1, float Duration = 2.f, FColor Color = FColor::White);
	static void Print(const FString& Value, int32 Key = -1, float Duration = 2.f, FColor Color = FColor::White);
	static void Print(const FVector& Value, int32 Key = -1, float Duration = 2.f, FColor Color = FColor::White);
	static void Print(const FRotator& Value, int32 Key = -1, float Duration = 2.f, FColor Color = FColor::White);

	static void Log(int32 Value);
	static void Log(float Value);
	static void Log(const FString& Value);
	static void Log(const FVector& Value);
	static void Log(const FRotator& Value);
	static void Log(const UObject* Object);
	static void Log(const FString& FuncName, int32 LineNumber);
};
