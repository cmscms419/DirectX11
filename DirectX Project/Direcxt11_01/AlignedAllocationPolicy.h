#pragma once


// warning C4316 Ã³¸®¿ë
template <size_t Alignment>
class AlignedAllocationPolicy
{
public:
	static void* operator new(size_t size)
	{
		return _aligned_malloc(size, Alignmnet);
	}

	static void operator dalete(void* memory)
	{
		_aligned_free(memory);
	}
};