#include "stdafx.h"
#include "Integer.h"


#ifdef _DEBUG
#define new DEBUG_NEW
#endif


static bool COMPACT_STRINGS = true;

int Integer::MIN_VALUE = 0x80000000;

int Integer::MAX_VALUE = 0x7fffffff;

char Integer::digits[] = {
		'0' , '1' , '2' , '3' , '4' , '5' ,
		'6' , '7' , '8' , '9' , 'a' , 'b' ,
		'c' , 'd' , 'e' , 'f' , 'g' , 'h' ,
		'i' , 'j' , 'k' , 'l' , 'm' , 'n' ,
		'o' , 'p' , 'q' , 'r' , 's' , 't' ,
		'u' , 'v' , 'w' , 'x' , 'y' , 'z'
};

typedef byte BYTE;

String Integer::toString(int i, int radix)
{
	if (radix < Character::MIN_RADIX || radix > Character::MAX_RADIX)
		radix = 10;

	/* Use the faster version */
	if (radix == 10) {
		return toString(i);
	}

	if (COMPACT_STRINGS) {
		byte *buf = new byte[33];
		boolean negative = (i < 0);
		int charPos = 32;

		if (!negative) {
			i = -i;
		}

		while (i <= -radix) {
			buf[charPos--] = (byte)digits[-(i % radix)];
			i = i / radix;
		}
		buf[charPos] = (byte)digits[-i];

		if (negative) {
			buf[--charPos] = '-';
		}
		SafeDeleteArray(buf);
		//return StringLatin1.newString(buf, charPos, (33 - charPos));
	}
	//return toStringUTF16(i, radix);
	return String();
}

String Integer::toString(int /*i*/)
{
	/*int size = stringSize(i);
	if (COMPACT_STRINGS) {
		byte* buf = new byte[size];
		getChars(i, size, buf);
		return new String(buf, LATIN1);
	}
	else {
		byte[] buf = new byte[size * 2];
		StringUTF16.getChars(i, size, buf);
		return new String(buf, UTF16);
	}*/
	return String();
}

Integer::Integer()
{
}


Integer::~Integer()
{
}
