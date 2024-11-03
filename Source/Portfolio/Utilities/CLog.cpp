#include "CLog.h"

DEFINE_LOG_CATEGORY_STATIC(GameProject,Log,All)

void CLog::Print(int32 Value, int32 Key, float Duration, FColor Color)
{
	GEngine->AddOnScreenDebugMessage(Key, Duration, Color, FString::FromInt(Value));
}

void CLog::Print(float Value, int32 Key, float Duration, FColor Color)
{
	GEngine->AddOnScreenDebugMessage(Key, Duration, Color, FString::SanitizeFloat(Value));
}

void CLog::Print(const FString& Value, int32 Key, float Duration, FColor Color)
{
	GEngine->AddOnScreenDebugMessage(Key, Duration, Color, Value);
}

void CLog::Print(const FVector& Value, int32 Key, float Duration, FColor Color)
{
	GEngine->AddOnScreenDebugMessage(Key, Duration, Color, Value.ToString());
}

void CLog::Print(const FRotator& Value, int32 Key, float Duration, FColor Color)
{
	GEngine->AddOnScreenDebugMessage(Key, Duration, Color, Value.ToString());
}

void CLog::Log(int32 Value)
{
	UE_LOG(GameProject, Log, TEXT("%d"), Value);
}

void CLog::Log(float Value)
{
	UE_LOG(GameProject, Log, TEXT("%f"), Value);
}

void CLog::Log(const FString& Value)
{
	UE_LOG(GameProject, Log, TEXT("%s"), *Value);
}

void CLog::Log(const FVector& Value)
{
	UE_LOG(GameProject, Log, TEXT("%s"), *Value.ToString());
}

void CLog::Log(const FRotator& Value)
{
	UE_LOG(GameProject, Log, TEXT("%s"), *Value.ToString());
}

void CLog::Log(const UObject* Object)
{
	FString Str;
	if (Object)
	{
		Str.Append(Object->GetName());
	}

	Str.Append(Object ? " is not null" : "null");

	UE_LOG(GameProject, Log, TEXT("%s"), *Str);
}

void CLog::Log(const FString& FuncName, int32 LineNumber)
{
	FString Str;
	Str.Append(FuncName);
	Str.Append(", ");
	Str.Append(FString::FromInt(LineNumber));

	UE_LOG(GameProject, Log, TEXT("%s"), *Str);
}
