######## CPU #########
file(GLOB MECHANISM_CPU_SRC ${CMAKE_CURRENT_SOURCE_DIR}/CPU/*.c ${CMAKE_CURRENT_SOURCE_DIR}/CPU/jacobs/*.c)
file(GLOB MECHANISM_CPU_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/CPU/*.h ${CMAKE_CURRENT_SOURCE_DIR}/CPU/jacobs/*.h)

add_library(mechanismCPU STATIC ${MECHANISM_CPU_SRC})
target_include_directories(mechanismCPU PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/CPU/)
target_include_directories(mechanismCPU PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/CPU/jacobs)

######### GPU ########
# Wrap source code
file(GLOB MECHANISM_GPU_SRC ${CMAKE_CURRENT_SOURCE_DIR}/GPU/*.cu ${CMAKE_CURRENT_SOURCE_DIR}/GPU/jacobs/*.cu ${CMAKE_CURRENT_SOURCE_DIR}/GPU/rates/*.cu)
file(GLOB MECHANISM_GPU_HEADERS ${CMAKE_CURRENT_SOURCE_DIR}/GPU/*.cuh ${CMAKE_CURRENT_SOURCE_DIR}/GPU/jacobs/*.cuh ${CMAKE_CURRENT_SOURCE_DIR}/GPU/rates/*.cuh)

add_library(mechanismGPU STATIC ${MECHANISM_GPU_SRC})

add_dependencies(mechanismGPU cuda-samplesProject)

target_include_directories(mechanismGPU PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/GPU)
target_include_directories(mechanismGPU PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/GPU/jacobs)
target_include_directories(mechanismGPU PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/GPU/rates)
target_include_directories(mechanismGPU PUBLIC ${CUDA_SAMPLES_INCLUDE_DIR})
target_include_directories(mechanismGPU PUBLIC ${CMAKE_CUDA_TOOLKIT_INCLUDE_DIRECTORIES})
# target_include_directories(mechanismGPU PUBLIC /usr/local/cuda/include)

set_target_properties(mechanismGPU PROPERTIES CUDA_SEPARABLE_COMPILATION ON)
target_compile_options(mechanismGPU PRIVATE $<$<COMPILE_LANGUAGE:CUDA>:-Xptxas --disable-optimizer-constants>)