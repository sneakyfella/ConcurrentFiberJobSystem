#pragma once
#include "ForwardDeclarations.h"

inline bool CheckPowerOfTwo(Uint32 x)
{
	// Keep shifting
	while (((x & 1) == 0) && x > 1)
		x >>= 1;

	return x == 1;
}

inline void* AlignForward(void* address, Uint8 alignment)
{
#if ALLOCATOR_DEBUG
	assert(CheckPowerOfTwo(alignment));
#endif
	return (void*)((reinterpret_cast<uintptr_t>(address) + static_cast<uintptr_t>(alignment - 1)) & static_cast<uintptr_t>(~(alignment - 1)));
}

inline const void* AlignForward(const void* address, Uint8 alignment)
{
	return (void*)((reinterpret_cast<uintptr_t>(address) + static_cast<uintptr_t>(alignment - 1)) & static_cast<uintptr_t>(~(alignment - 1)));
}
inline void* AlignBackward(void* address, Uint8 alignment)
{
	return (void*)(reinterpret_cast<uintptr_t>(address) & static_cast<uintptr_t>(~(alignment - 1)));
}

inline const void* AlignBackward(const void* address, Uint8 alignment)
{
	return (void*)(reinterpret_cast<uintptr_t>(address) & static_cast<uintptr_t>(~(alignment - 1)));
}

inline Uint8 AlignForwardAdjustment(const void* address, Uint8 alignment)
{
	Uint8 adjustment = alignment - (reinterpret_cast<uintptr_t>(address) & static_cast<uintptr_t>(alignment - 1));

	adjustment = (adjustment == alignment) ? 0 : adjustment;

	return adjustment;
}
inline Uint8 AlignForwardWithHeader(const void* address, Uint8 alignment, Uint8 headerSize)
{
	Uint8 adjustment = AlignForwardAdjustment(address, alignment);

	Uint8 neededSpace = headerSize;

	if (adjustment < neededSpace)
	{
		neededSpace -= adjustment;

		//Increase adjustment to fit header
		adjustment += alignment * (neededSpace / alignment);

		if (neededSpace % alignment > 0)
			adjustment += alignment;
	}

	return adjustment;
}
inline void* AddOffset(void* p, size_t x)
{
	return (void*)(reinterpret_cast<uintptr_t>(p) + x);
}

inline const void* AddOffset(const void* p, size_t x)
{
	return (const void*)(reinterpret_cast<uintptr_t>(p) + x);
}

inline void* SubtractOffset(void* p, size_t x)
{
	return (void*)(reinterpret_cast<uintptr_t>(p) - x);
}

inline const void* SubtractOffset(const void* p, size_t x)
{
	return (const void*)(reinterpret_cast<uintptr_t>(p) - x);
}