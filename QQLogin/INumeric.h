#pragma once
#include "stdafx.h"


class Character
{
public:
	/**
	* The minimum radix available for conversion to and from strings.
	* The constant value of this field is the smallest value permitted
	* for the radix argument in radix-conversion methods such as the
	* {@code digit} method, the {@code forDigit} method, and the
	* {@code toString} method of class {@code Integer}.
	*
	* @see     Character#digit(char, int)
	* @see     Character#forDigit(int, int)
	* @see     Integer#toString(int, int)
	* @see     Integer#valueOf(String)
	*/
	static int MIN_RADIX;
	/**
	* The maximum radix available for conversion to and from strings.
	* The constant value of this field is the largest value permitted
	* for the radix argument in radix-conversion methods such as the
	* {@code digit} method, the {@code forDigit} method, and the
	* {@code toString} method of class {@code Integer}.
	*
	* @see     Character#digit(char, int)
	* @see     Character#forDigit(int, int)
	* @see     Integer#toString(int, int)
	* @see     Integer#valueOf(String)
	*/
	static int MAX_RADIX;
private:

};

__declspec(selectany) int Character::MIN_RADIX = 2;

__declspec(selectany) int Character::MAX_RADIX = 36;

class INumber
{
public:
	/**
	 * Returns the value of the specified number as an {@code int}.
	 *
	 * @return  the numeric value represented by this object after conversion
	 *          to type {@code int}.
	 */
	virtual int intValue() = 0;

	/**
	 * Returns the value of the specified number as a {@code long}.
	 *
	 * @return  the numeric value represented by this object after conversion
	 *          to type {@code long}.
	 */
	virtual long longValue() = 0;

	/**
	 * Returns the value of the specified number as a {@code float}.
	 *
	 * @return  the numeric value represented by this object after conversion
	 *          to type {@code float}.
	 */
	virtual float floatValue() = 0;

	/**
	 * Returns the value of the specified number as a {@code double}.
	 *
	 * @return  the numeric value represented by this object after conversion
	 *          to type {@code double}.
	 */
	virtual double doubleValue() = 0;

	/**
	 * Returns the value of the specified number as a {@code byte}.
	 *
	 * <p>This implementation returns the result of {@link #intValue} cast
	 * to a {@code byte}.
	 *
	 * @return  the numeric value represented by this object after conversion
	 *          to type {@code byte}.
	 * @since   1.1
	 */
	BYTE byteValue() {
		return (BYTE)intValue();
	}

	/**
	 * Returns the value of the specified number as a {@code short}.
	 *
	 * <p>This implementation returns the result of {@link #intValue} cast
	 * to a {@code short}.
	 *
	 * @return  the numeric value represented by this object after conversion
	 *          to type {@code short}.
	 * @since   1.1
	 */
	short shortValue() {
		return (short)intValue();
	}

	/** use serialVersionUID from JDK 1.0.2 for interoperability */
private:
	static  LONGLONG serialVersionUID;
};

__declspec(selectany) LONGLONG INumber::serialVersionUID = -8742448824652078965L;
