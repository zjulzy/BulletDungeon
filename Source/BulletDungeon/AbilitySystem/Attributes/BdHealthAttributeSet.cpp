// Fill out your copyright notice in the Description page of Project Settings.


#include "BdHealthAttributeSet.h"

UBdHealthAttributeSet::UBdHealthAttributeSet()
{
}

void UBdHealthAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if(Attribute==GetHealthAttribute())
	{
		if(NewValue<0)
		{
			NewValue = 0;
		}
	}
}
