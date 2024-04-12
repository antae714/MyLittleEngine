#pragma once

#include "Containers/DynamicArray.h"
#include "Containers/String.h"




#define GENERATED_BODY(CLASS, BASECLASS)	\
public:										\
	virtual ~CLASS() {}						\
private:									\
	using Base = BASECLASS;					\
//	MACRO_COMBINE(HEADER,_,__LINE__)


//generated


//#define MACRO_COMBINE_INNER(a, b, c) a##b##c
//#define MACRO_COMBINE(a, b, c) MACRO_COMBINE_INNER(a,b,c)
//#define HEADER ConsoleGamePlayerCharacter_h
//
//#define ConsoleGamePlayerCharacter_h_10_CLASS 
//#define ConsoleGamePlayerCharacter_h_10 