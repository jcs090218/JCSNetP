#ifndef __BYTESWAP_H__
/**
 * $File: ByteSwap.h $
 * $Date: 2017-04-09 22:39:07 $
 * $Revision: $
 * $Creator: Jen-Chieh Shen $
 * $Notice: See LICENSE.txt for modification and distribution information
 *                   Copyright (c) 2017 by Shen, Jen-Chieh $
 */
#define __BYTESWAP_H__


NS_JCS_BEGIN

/**
 * @func ByteSwap2
 * @brief Handle endianness
 * @param inData : input data.
 * return uint16 : endianness result.
 */
PUBLIC inline uint16 ByteSwap2(uint16 inData)
{
	return (inData >> 8) | (inData << 8);
}

/**
 * @func ByteSwap4
 * @brief Handle endianness
 * @param inData : input data.
 * return uint16 : endianness result.
 */
PUBLIC inline uint32 ByteSwap4(uint32 inData)
{
	return  ((inData >> 24) & 0x000000ff) |
		((inData >> 8) & 0x0000ff00) |
		((inData << 8) & 0x00ff0000) |
		((inData << 24) & 0xff000000);
}

/**
 * @func ByteSwap8
 * @brief Handle endianness
 * @param inData : input data.
 * return uint16 : endianness result.
 */
PUBLIC inline uint64 ByteSwap8(uint64 inData)
{
	return ((inData >> 56) & 0x00000000000000ff) |
		((inData >> 40) & 0x000000000000ff00) |
		((inData >> 24) & 0x0000000000ff0000) |
		((inData >> 8) & 0x00000000ff000000) |
		((inData << 8) & 0x000000ff00000000) |
		((inData << 24) & 0x0000ff0000000000) |
		((inData << 40) & 0x00ff000000000000) |
		((inData << 56) & 0xff00000000000000);
}

/**
 * @class TypeAliaser<tFrom, tTo>
 * @breif N/A
 */
template <typename tFrom, typename tTo>
class TypeAliaser
{
public:
	union
	{
		tFrom mAsFromType;
		tTo   mAsToType;
	};

public:
	TypeAliaser(tFrom inFromValue) 
		: mAsFromType(inFromValue) 
	{ }

	/* getter */
	tTo& Get() { return mAsToType; }
};


template <typename T, size_t tSize > class ByteSwapper;

/**
 * @class ByteSwapper<T, 1>
 * @brief specialize for 1...
 * @param T : general data type.
 */
template <typename T>
class ByteSwapper<T, 1>
{
public:
	T Swap(T inData) const
	{
		return inData;
	}
};

/**
 * @class ByteSwapper<T, 2>
 * @brief specialize for 2...
 * @param T : general data type.
 */
template <typename T>
class ByteSwapper<T, 2>
{
public:
	T Swap(T inData) const
	{
		uint16 result = ByteSwap2(TypeAliaser<T, uint16>(inData).Get());
		return TypeAliaser<uint16, T>(result).Get();
	}
};

/**
 * @class ByteSwapper<T, 4>
 * @brief specialize for 4...
 * @param T : general data type.
 */
template <typename T>
class ByteSwapper<T, 4>
{
public:
	T Swap(T inData) const
	{
		uint32 result = ByteSwap4(TypeAliaser<T, uint32>(inData).Get());
		return TypeAliaser<uint32, T>(result).Get();
	}
};

/**
 * @class BytSwap<T, 8>
 * @brief specialize for 8...
 * @param T : general data type.
 */
template <typename T>
class ByteSwapper<T, 8>
{
public:
	T Swap(T inData) const
	{
		uint64 result = ByteSwap8(TypeAliaser< T, uint64>(inData).Get());
		return TypeAliaser<uint64, T>(result).Get();
	}
};


/**
 * @func BytSwap<T>
 * @brief
 * @param T : general data type.
 */
template <typename T>
T ByteSwap(T inData)
{
	return ByteSwapper< T, sizeof(T) >().Swap(inData);
}

NS_JCS_END

#endif /* __BYTESWAP_H__ */
