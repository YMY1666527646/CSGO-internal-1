#ifndef __flow_H__
#define __flow_H__

#include <stdint.h>

#define flow_VERSION "1.2.6"

#define flow_INCLUDE_D3D9   1 // 1 if you need D3D9 hook
#define flow_INCLUDE_D3D10  0 // 1 if you need D3D10 hook
#define flow_INCLUDE_D3D11  0 // 1 if you need D3D11 hook
#define flow_INCLUDE_D3D12  0 // 1 if you need D3D12 hook
#define flow_INCLUDE_OPENGL 0 // 1 if you need OpenGL hook
#define flow_INCLUDE_VULKAN 0 // 1 if you need Vulkan hook
#define flow_USE_MINHOOK    1 // 1 if you will use flow::bind function

#define flow_ARCH_X64 0
#define flow_ARCH_X86 0

#if defined(_M_X64)	
# undef  flow_ARCH_X64
# define flow_ARCH_X64 1
#else
# undef  flow_ARCH_X86
# define flow_ARCH_X86 1
#endif

#if flow_ARCH_X64
typedef uint64_t uint150_t;
#else
typedef uint32_t uint150_t;
#endif

namespace flow
{
	struct Status
	{
		enum Enum
		{
			UnknownError = -1,
			NotSupportedError = -2,
			ModuleNotFoundError = -3,

			AlreadyInitializedError = -4,
			NotInitializedError = -5,

			Success = 0,
		};
	};

	struct RenderType
	{
		enum Enum
		{
			None,

			D3D9,
			D3D10,
			D3D11,
			D3D12,

			OpenGL,
			Vulkan,

			Auto
		};
	};

	Status::Enum init(RenderType::Enum renderType);
	void shutdown();

	Status::Enum bind(uint16_t index, void** original, void* function);
	void unbind(uint16_t index);

	RenderType::Enum getRenderType();
	uint150_t* getMethodsTable();
}

#endif // __flow_H__