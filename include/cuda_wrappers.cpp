/**********************************************************************************************************************************************\
	Copyright© 2020-2021 Mason DeRoss

	Released under the MIT License.

	Copying and distribution of this file, with or without modification, are permitted in any medium without royalty,
	provided the copyright notice and this notice are preserved. This file is offered as-is, without any warranty.

	DESCRIPTION:

\**********************************************************************************************************************************************/

#include "stdafx.h"

#include <cuda_device_runtime_api.h>

//#include <driver_types.h>
//#include <crt/host_defines.h>

struct cudaFuncAttributes;

#if defined(_WIN32)
#define __NV_WEAK__ __declspec(nv_weak)
#else
#define __NV_WEAK__ __attribute__((nv_weak))
#endif
/*
__device__ __NV_WEAK__ ::std::pair<void*, cudaError_t> CUDARTAPI
//cudaMalloc(void** p, size_t s)
my::cudaMalloc(size_t s)
{
	void* p;
	cuddaError_t error = ::cudaMalloc(&p, s);
	return ::std::pair(p, error); // cudaErrorUnknown;
}

__device__ __NV_WEAK__ ::std::pair<cudaFuncAttributes, cudaError_t> CUDARTAPI
//cudaFuncGetAttributes(struct cudaFuncAttributes* p, const void* c)
my::cudaFuncGetAttributes(const void* c)
{
	cudaFuncAttributes p;
	cuddaError_t error = ::cudaFuncGetAttributes(&p, c); 
	return ::std::pair(p, error); // cudaErrorUnknown;
}

__device__ __NV_WEAK__ ::std::pair<int, cudaError_t> CUDARTAPI
//cudaDeviceGetAttribute(int* value, enum cudaDeviceAttr attr, int device)
my::cudaDeviceGetAttribute(cudaDeviceAttr attr, int device)
{
	int value;
	cuddaError_t error = ::cudaDeviceGetAttribute(&value, attr, device);
	return ::std::pair(value, error); // cudaErrorUnknown;
}

__device__ __NV_WEAK__ ::std::pair<int, cudaError_t> CUDARTAPI
//cudaGetDevice(int* device)
my::cudaGetDevice()
{
	int device;
	cuddaError_t error = ::cudaGetDevice(&device);
	return ::std::pair(device, error); // cudaErrorUnknown;
}

__device__ __NV_WEAK__ ::std::pair<int, cudaError_t> CUDARTAPI
//cudaOccupancyMaxActiveBlocksPerMultiprocessor(int* numBlocks, const void* func, int blockSize, size_t dynamicSmemSize)
my::cudaOccupancyMaxActiveBlocksPerMultiprocessor(const void* func, int blockSize, size_t dynamicSmemSize)
{
	int numBlocks;
	cuddaError_t error = ::cudaOccupancyMaxActiveBlocksPerMultiprocessor(numBlocks, func, blockSize, dynamicSmemSize);
	return ::std::pair(numBlocks, error); // cudaErrorUnknown;
}

__device__ __NV_WEAK__ ::std::pair<int, cudaError_t> CUDARTAPI
//cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(int* numBlocks, const void* func, int blockSize, size_t dynamicSmemSize, unsigned int flags)
my::cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(const void* func, int blockSize, size_t dynamicSmemSize, unsigned flags)
{
	int numBlocks;
	cuddaError_t error = ::cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(&numBlocks, func, blockSize, flags);
	return ::std::pair(numBlocks, error); // cudaErrorUnknown;
}

__device__ __cudart_builtin__ ::std::pair<int, cudaError_t> CUDARTAPI
//cudaDeviceGetAttribute(int* value, enum cudaDeviceAttr attr, int device);
my::cudaDeviceGetAttribute(cudaDeviceAttr attr, int device)
{
	int value;
	cuddaError_t error = ::cudaDeviceGetAttribute(&value, attr, device);
	return ::std::pair(value, error);
}

__device__ __cudart_builtin__ ::std::pair<size_t, cudaError_t> CUDARTAPI
//cudaDeviceGetLimit(size_t* pValue, enum cudaLimit limit);
my::cudaDeviceGetLimit(cudaLimit limit)
{
	size_t pValue;
	cuddaError_t error = ::cudaDeviceGetLimit(&pValue, limit);
	return ::std::pair(pValue, error);
}

__device__ __cudart_builtin__ ::std::pair<cudaFuncCache, cudaError_t> CUDARTAPI
//cudaDeviceGetCacheConfig(enum cudaFuncCache* pCacheConfig);
my::cudaDeviceGetCacheConfig()
{
	cudaFuncCache pCacheConfig;
	cuddaError_t error = ::cudaDeviceGetCacheConfig(&pCacheConfig);
	return ::std::pair(pCacheConfig, error);
}

__device__ __cudart_builtin__ ::std::pair<cudaSharedMemConfig, cudaError_t> CUDARTAPI
//cudaDeviceGetSharedMemConfig(enum cudaSharedMemConfig* pConfig);
my::cudaDeviceGetSharedMemConfig()
{
	cudaSharedMemConfig pConfig;
	cuddaError_t error = ::cudaDeviceGetSharedMemConfig(&pConfig);
	return ::std::pair(pConfig, error);
}

//__device__ __cudart_builtin__ cudaError_t CUDARTAPI
////cudaDeviceSynchronize(void);
//my::cudaDeviceSynchronize()
//{
//	::cudaDeviceSynchronize();
//}

//__device__ __cudart_builtin__ cudaError_t CUDARTAPI
////cudaGetLastError(void);
//my::cudaGetLastError()
//{
//	::cudaGetLastError();
//}

//__device__ __cudart_builtin__ cudaError_t CUDARTAPI
////cudaPeekAtLastError(void);
//my::cudaPeekAtLastError()
//{
//	::cudaPeekAtLastError();
//}

//__device__ __cudart_builtin__ const char* CUDARTAPI
////cudaGetErrorString(cudaError_t error);
//my::cudaGetErrorString()
//{
//	::cudaGetErrorString(cudaError_t error);
//}

//__device__ __cudart_builtin__ const char* CUDARTAPI
////cudaGetErrorName(cudaError_t error);
//my::cudaGetErrorName()
//{
//	::cudaGetErrorName(cudaError_t error);
//}

__device__ __cudart_builtin__ ::std::pair<int, cudaError_t> CUDARTAPI
//cudaGetDeviceCount(int* count);
my::cudaGetDeviceCount()
{
	int count;
	cuddaError_t error = ::cudaGetDeviceCount(&count);
	return ::std::pair(count, error);
}

__device__ __cudart_builtin__ ::std::pair<int, cudaError_t> CUDARTAPI
//cudaGetDevice(int* device);
my::cudaGetDevice()
{
	int device;
	cuddaError_t error = ::cudaGetDevice(&device);
	return ::std::pair(device, error);
}

__device__ __cudart_builtin__ ::std::pair<cudaStream_t, cudaError_t> CUDARTAPI
//cudaStreamCreateWithFlags(cudaStream_t* pStream, unsigned int flags);
my::cudaStreamCreateWithFlags(unsigned flags)
{
	cudaStream_t pStream;
	cuddaError_t error = ::cudaStreamCreateWithFlags(&pStream, flags);
	return ::std::pair(pStream, error);
}

//__device__ __cudart_builtin__ cudaError_t CUDARTAPI
////cudaStreamDestroy(cudaStream_t stream);
//my::cudaStreamDestroy()
//{
//	::cudaStreamDestroy(cudaStream_t stream);
//}

//__device__ __cudart_builtin__ cudaError_t CUDARTAPI
////cudaStreamWaitEvent(cudaStream_t stream, cudaEvent_t event, unsigned int flags);
//my::cudaStreamWaitEvent(cudaEvent_t event, unsigned int flags)
//{
//	::cudaStreamWaitEvent(cudaStream_t stream, cudaEvent_t event, unsigned int flags);
//}

//__device__ __cudart_builtin__ cudaError_t CUDARTAPI
////cudaStreamWaitEvent_ptsz(cudaStream_t stream, cudaEvent_t event, unsigned int flags);
//my::cudaStreamWaitEvent_ptsz(cudaEvent_t event, unsigned int flags)
//{
//	::cudaStreamWaitEvent_ptsz(cudaStream_t stream, cudaEvent_t event, unsigned int flags);
//}

__device__ __cudart_builtin__ ::std::pair<cudaEvent_t, cudaError_t> CUDARTAPI
//cudaEventCreateWithFlags(cudaEvent_t* event, unsigned int flags);
my::cudaEventCreateWithFlags(unsigned flags)
{
	cudaEvent_t event;
	cuddaError_t error = ::cudaEventCreateWithFlags(&event, flags);
	return ::std::pair(event, error);
}

//__device__ __cudart_builtin__ cudaError_t CUDARTAPI
////cudaEventRecord(cudaEvent_t event, cudaStream_t stream);
//my::cudaEventRecord(cudaStream_t stream)
//{
//	::cudaEventRecord(cudaEvent_t event, cudaStream_t stream);
//}

//__device__ __cudart_builtin__ cudaError_t CUDARTAPI
////cudaEventRecord_ptsz(cudaEvent_t event, cudaStream_t stream);
//my::cudaEventRecord_ptsz(cudaStream_t stream)
//{
//	::cudaEventRecord_ptsz(cudaEvent_t event, cudaStream_t stream);
//}

//__device__ __cudart_builtin__ cudaError_t CUDARTAPI
////cudaEventRecordWithFlags(cudaEvent_t event, cudaStream_t stream, unsigned int flags);
//my::cudaEventRecordWithFlags(cudaStream_t stream, unsigned int flags)
//{
//	::cudaEventRecordWithFlags(cudaEvent_t event, cudaStream_t stream, unsigned int flags);
//}

//__device__ __cudart_builtin__ cudaError_t CUDARTAPI
////cudaEventRecordWithFlags_ptsz(cudaEvent_t event, cudaStream_t stream, unsigned int flags);
//my::cudaEventRecordWithFlags_ptsz(cudaStream_t stream, unsigned int flags)
//{
//	::cudaEventRecordWithFlags_ptsz(cudaEvent_t event, cudaStream_t stream, unsigned int flags);
//}

//__device__ __cudart_builtin__ cudaError_t CUDARTAPI
////cudaEventDestroy(cudaEvent_t event);
//my::cudaEventDestroy()
//{
//	::cudaEventDestroy(cudaEvent_t event);
//}

__device__ __cudart_builtin__ ::std::pair<cudaFuncAttributes, cudaError_t> CUDARTAPI
//cudaFuncGetAttributes(struct cudaFuncAttributes* attr, const void* func);
my::cudaFuncGetAttributes(const void* func)
{
	cudaFuncAttributes attr;
	cuddaError_t error = ::cudaFuncGetAttributes(&attr, func);
	return ::std::pair(attr, error);
}

//__device__ __cudart_builtin__ cudaError_t CUDARTAPI
////cudaFree(void* devPtr);
//my::cudaFree()
//{
//	::cudaFree(void* devPtr);
//}

__device__ __cudart_builtin__ ::std::pair<void**, cudaError_t> CUDARTAPI
//cudaMalloc(void** devPtr, size_t size);
my::cudaMalloc(size_t size)
{
	void** devPtr;
	cuddaError_t error = ::cudaMalloc(devPtr, size);
	return ::std::pair(devPtr, error);
}

__device__ __cudart_builtin__ ::std::pair<void*, cudaError_t> CUDARTAPI
//cudaMemcpyAsync(void* dst, const void* src, size_t count, enum cudaMemcpyKind kind, cudaStream_t stream);
my::cudaMemcpyAsync(const void* src, size_t count, cudaMemcpyKind kind, cudaStream_t stream)
{
	void* dst;
	cuddaError_t error = ::cudaMemcpyAsync(dst, src, count, kind, stream);
	return ::std::pair(dst, error);
}

__device__ __cudart_builtin__ ::std::pair<void*, cudaError_t> CUDARTAPI
//cudaMemcpyAsync_ptsz(void* dst, const void* src, size_t count, enum cudaMemcpyKind kind, cudaStream_t stream);
my::cudaMemcpyAsync_ptsz(const void* src, size_t count, cudaMemcpyKind kind, cudaStream_t stream)
{
	void* dst;
	cuddaError_t error = ::cudaMemcpyAsync_ptsz(dst, src, count, kind, stream);
	return ::std::pair(dst, error);
}

__device__ __cudart_builtin__ ::std::pair<void*, cudaError_t> CUDARTAPI
//cudaMemcpy2DAsync(void* dst, size_t dpitch, const void* src, size_t spitch, size_t width, size_t height, enum cudaMemcpyKind kind, cudaStream_t stream);
my::cudaMemcpy2DAsync(size_t dpitch, const void* src, size_t spitch, size_t width, size_t height, cudaMemcpyKind kind, cudaStream_t stream)
{
	void* dst;
	cuddaError_t error = ::cudaMemcpy2DAsync(dst, dpitch, src, spitch, width, height, kind, stream);
	return ::std::pair(dst, error);
}

__device__ __cudart_builtin__ ::std::pair<void*, cudaError_t> CUDARTAPI
//cudaMemcpy2DAsync_ptsz(void* dst, size_t dpitch, const void* src, size_t spitch, size_t width, size_t height, enum cudaMemcpyKind kind, cudaStream_t stream);
my::cudaMemcpy2DAsync_ptsz(size_t dpitch, const void* src, size_t spitch, size_t width, size_t height, cudaMemcpyKind kind, cudaStream_t stream)
{
	void* dst;
	cuddaError_t error = ::cudaMemcpy2DAsync_ptsz(dst, dpitch, src, spitch, width, height, kind, stream);
	return ::std::pair(dst, error);
}

__device__ __cudart_builtin__ ::std::pair<const cudaMemcpy3DParms, cudaError_t> CUDARTAPI
//cudaMemcpy3DAsync(const struct cudaMemcpy3DParms* p, cudaStream_t stream);
my::cudaMemcpy3DAsync(cudaStream_t stream)
{
	cudaMemcpy3DParms p;
	cuddaError_t error = ::cudaMemcpy3DAsync(&p, stream);
	return ::std::pair(p, error);
}

__device__ __cudart_builtin__ ::std::pair<const cudaMemcpy3DParms, cudaError_t> CUDARTAPI
//cudaMemcpy3DAsync_ptsz(const struct cudaMemcpy3DParms* p, cudaStream_t stream);
my::cudaMemcpy3DAsync_ptsz(cudaStream_t stream)
{
	const cudaMemcpy3DParms p;
	cuddaError_t error = ::cudaMemcpy3DAsync_ptsz(&p, stream);
	return ::std::pair(p, error);
}

__device__ __cudart_builtin__ ::std::pair<void*, cudaError_t> CUDARTAPI
//cudaMemsetAsync(void* devPtr, int value, size_t count, cudaStream_t stream);
my::cudaMemsetAsync(int value, size_t count, cudaStream_t stream)
{
	void* devPtr;
	cuddaError_t error = ::cudaMemsetAsync(devPtr, value, count, stream);
	return ::std::pair(devPtr, error);
}

__device__ __cudart_builtin__ ::std::pair<void*, cudaError_t> CUDARTAPI
//cudaMemsetAsync_ptsz(void* devPtr, int value, size_t count, cudaStream_t stream);
my::cudaMemsetAsync_ptsz(int value, size_t count, cudaStream_t stream)
{
	void* devPtr;
	cuddaError_t error = ::cudaMemsetAsync_ptsz(devPtr, value, count, stream);
	return ::std::pair(devPtr, error);
}

__device__ __cudart_builtin__ ::std::pair<void*, cudaError_t> CUDARTAPI
//cudaMemset2DAsync(void* devPtr, size_t pitch, int value, size_t width, size_t height, cudaStream_t stream);
my::cudaMemset2DAsync(size_t pitch, int value, size_t width, size_t height, cudaStream_t stream)
{
	void* devPtr;
	cuddaError_t error = ::cudaMemset2DAsync(devPtr, pitch, value, width, height, stream);
	return ::std::pair(devPtr, error);
}

__device__ __cudart_builtin__ ::std::pair<void*, cudaError_t> CUDARTAPI
//cudaMemset2DAsync_ptsz(void* devPtr, size_t pitch, int value, size_t width, size_t height, cudaStream_t stream);
my::cudaMemset2DAsync_ptsz(size_t pitch, int value, size_t width, size_t height, cudaStream_t stream)
{
	void* devPtr;
	cuddaError_t error = ::cudaMemset2DAsync_ptsz(devPtr, pitch, value, width, height, stream);
	return ::std::pair(devPtr, error);
}

__device__ __cudart_builtin__ ::std::pair<cudaPitchedPtr, cudaError_t> CUDARTAPI
//cudaMemset3DAsync(struct cudaPitchedPtr pitchedDevPtr, int value, struct cudaExtent extent, cudaStream_t stream);
my::cudaMemset3DAsync(int value, struct cudaExtent extent, cudaStream_t stream)
{
	cudaPitchedPtr pitchedDevPtr;
	cuddaError_t error = ::cudaMemset3DAsync(pitchedDevPtr, value, extent, stream);
	return ::std::pair(pitchedDevPtr, error);
}

__device__ __cudart_builtin__ ::std::pair<cudaPitchedPtr, cudaError_t> CUDARTAPI
//cudaMemset3DAsync_ptsz(struct cudaPitchedPtr pitchedDevPtr, int value, struct cudaExtent extent, cudaStream_t stream);
my::cudaMemset3DAsync_ptsz(int value, struct cudaExtent extent, cudaStream_t stream)
{
	cudaPitchedPtr pitchedDevPtr;
	cuddaError_t error = ::cudaMemset3DAsync_ptsz(pitchedDevPtr, value, extent, stream);
	return ::std::pair(pitchedDevPtr, error);
}

__device__ __cudart_builtin__ ::std::pair<int, cudaError_t> CUDARTAPI
//cudaRuntimeGetVersion(int* runtimeVersion);
my::cudaRuntimeGetVersion()
{
	int runtimeVersion;
	cuddaError_t error = ::cudaRuntimeGetVersion(&runtimeVersion);
	return ::std::pair(runtimeVersion, error);
}
*/

/**
 * \ingroup CUDART_EXECUTION
 * \brief Obtains a parameter buffer
 *
 * Obtains a parameter buffer which can be filled with parameters for a kernel launch.
 * Parameters passed to ::cudaLaunchDevice must be allocated via this function.
 *
 * This is a low level API and can only be accessed from Parallel Thread Execution (PTX).
 * CUDA user code should use <<< >>> to launch kernels.
 *
 * \param alignment - Specifies alignment requirement of the parameter buffer
 * \param size      - Specifies size requirement in bytes
 *
 * \return
 * Returns pointer to the allocated parameterBuffer
 * \notefnerr
 *
 * \sa cudaLaunchDevice
*/
//extern __device__ __cudart_builtin__ void* CUDARTAPI
//cudaGetParameterBuffer(size_t alignment, size_t size);
//my::cudaGetParameterBuffer(size_t alignment, size_t size)
//{
//	::cudaGetParameterBuffer(size_t alignment, size_t size)
//}

/**
 * \ingroup CUDART_EXECUTION
 * \brief Launches a specified kernel
 *
 * Launches a specified kernel with the specified parameter buffer. A parameter buffer can be obtained
 * by calling ::cudaGetParameterBuffer().
 *
 * This is a low level API and can only be accessed from Parallel Thread Execution (PTX).
 * CUDA user code should use <<< >>> to launch the kernels.
 *
 * \param func            - Pointer to the kernel to be launched
 * \param parameterBuffer - Holds the parameters to the launched kernel. parameterBuffer can be NULL. (Optional)
 * \param gridDimension   - Specifies grid dimensions
 * \param blockDimension  - Specifies block dimensions
 * \param sharedMemSize   - Specifies size of shared memory
 * \param stream          - Specifies the stream to be used
 *
 * \return
 * ::cudaSuccess, ::cudaErrorInvalidDevice, ::cudaErrorLaunchMaxDepthExceeded, ::cudaErrorInvalidConfiguration,
 * ::cudaErrorStartupFailure, ::cudaErrorLaunchPendingCountExceeded, ::cudaErrorLaunchOutOfResources
 * \notefnerr
 * \n Please refer to Execution Configuration and Parameter Buffer Layout from the CUDA Programming
 * Guide for the detailed descriptions of launch configuration and parameter layout respectively.
 *
 * \sa cudaGetParameterBuffer
*/
/*
__device__ __cudart_builtin__ ::std::pair<void*, cudaError_t> CUDARTAPI
//cudaGetParameterBufferV2(void* func, dim3 gridDimension, dim3 blockDimension, unsigned int sharedMemSize);
my::cudaGetParameterBufferV2(dim3 gridDimension, dim3 blockDimension, unsigned sharedMemSize)
{
	void* func;
	cuddaError_t error = ::cudaGetParameterBufferV2(func, gridDimension, blockDimension, sharedMemSize);
	return ::std::pair(func, error);
}

__device__ __cudart_builtin__ ::std::pair<void*, cudaError_t> CUDARTAPI
//cudaLaunchDevice_ptsz(void* func, void* parameterBuffer, dim3 gridDimension, dim3 blockDimension, unsigned int sharedMemSize, cudaStream_t stream);
my::cudaLaunchDevice_ptsz(void* parameterBuffer, dim3 gridDimension, dim3 blockDimension, unsigned sharedMemSize, cudaStream_t stream)
{
	void* func;
	cuddaError_t error = ::cudaLaunchDevice_ptsz(func, parameterBuffer, gridDimension, blockDimension, sharedMemSize, stream);
	return ::std::pair(func, error);
}

__device__ __cudart_builtin__ ::std::pair<void*, cudaError_t> CUDARTAPI
//cudaLaunchDeviceV2_ptsz(void* parameterBuffer, cudaStream_t stream);
my::cudaLaunchDeviceV2_ptsz(cudaStream_t stream)
{
	void* parameterBuffer;
	cuddaError_t error = cudaLaunchDeviceV2_ptsz(parameterBuffer, stream);
	return ::std::pair(parameterBuffer, error);
}

#if defined(CUDA_API_PER_THREAD_DEFAULT_STREAM) && defined(__CUDA_ARCH__)
	// When compiling for the device and per thread default stream is enabled, add a static inline redirect to the per thread stream entry points.
	//static __inline__ __device__ __cudart_builtin__ cudaError_t CUDARTAPI
	//cudaLaunchDevice(void* func, void* parameterBuffer, dim3 gridDimension, dim3 blockDimension, unsigned int sharedMemSize, cudaStream_t stream)
	//{
	//	return ::std::pair(cudaLaunchDevice_ptsz(func, parameterBuffer, gridDimension, blockDimension, sharedMemSize, stream);
	//}

	//static __inline__ __device__ __cudart_builtin__ cudaError_t CUDARTAPI
	//cudaLaunchDeviceV2(void* parameterBuffer, cudaStream_t stream)
	//{
	//	return ::std::pair(cudaLaunchDeviceV2_ptsz(parameterBuffer, stream);
	//}
#else
	//extern __device__ __cudart_builtin__ cudaError_t CUDARTAPI
	//cudaLaunchDevice(void* func, void* parameterBuffer, dim3 gridDimension, dim3 blockDimension, unsigned int sharedMemSize, cudaStream_t stream);

	//extern __device__ __cudart_builtin__ cudaError_t CUDARTAPI
	//cudaLaunchDeviceV2(void* parameterBuffer, cudaStream_t stream);
#endif
*/

//extern __device__ __cudart_builtin__ cudaError_t CUDARTAPI
//cudaOccupancyMaxActiveBlocksPerMultiprocessor(int* numBlocks, const void* func, int blockSize, size_t dynamicSmemSize);

//extern __device__ __cudart_builtin__ cudaError_t CUDARTAPI
//cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(int* numBlocks, const void* func, int blockSize, size_t dynamicSmemSize, unsigned int flags);

//extern __device__ __cudart_builtin__ unsigned long long CUDARTAPI
//cudaCGGetIntrinsicHandle(enum cudaCGScope scope);

//extern __device__ __cudart_builtin__ cudaError_t CUDARTAPI
//cudaCGSynchronize(unsigned long long handle, unsigned int flags);

//extern __device__ __cudart_builtin__ cudaError_t CUDARTAPI
//cudaCGSynchronizeGrid(unsigned long long handle, unsigned int flags);

//extern __device__ __cudart_builtin__ cudaError_t CUDARTAPI
//cudaCGGetSize(unsigned int* numThreads, unsigned int* numGrids, unsigned long long handle);

//extern __device__ __cudart_builtin__ cudaError_t CUDARTAPI
//cudaCGGetRank(unsigned int* threadRank, unsigned int* gridRank, unsigned long long handle);

//template <typename T>
//static __inline__ __device__ __cudart_builtin__ cudaError_t
//cudaMalloc(T** devPtr, size_t size);

//template <typename T>
//static __inline__ __device__ __cudart_builtin__ cudaError_t
//cudaFuncGetAttributes(struct cudaFuncAttributes* attr, T* entry);

//template <typename T>
//static __inline__ __device__ __cudart_builtin__ cudaError_t
//cudaOccupancyMaxActiveBlocksPerMultiprocessor(int* numBlocks, T func, int blockSize, size_t dynamicSmemSize);

//template <typename T>
//static __inline__ __device__ __cudart_builtin__ cudaError_t
//cudaOccupancyMaxActiveBlocksPerMultiprocessorWithFlags(int* numBlocks, T func, int blockSize, size_t dynamicSmemSize, unsigned int flags);
