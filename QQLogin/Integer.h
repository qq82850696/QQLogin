#pragma once
#include "INumeric.h"

class Integer :
	public INumber
{
public:
	static int MIN_VALUE;
	static int MAX_VALUE;
	static char digits[];

public:
	static String toString(int i);
	static String toString(int i, int radix);
public:
	//构造函数
	Integer();
	//析构函数
	~Integer();


};

