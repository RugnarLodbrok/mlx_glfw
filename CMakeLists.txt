cmake_minimum_required(VERSION 3.6.2)
project(mlx_glfw C)
set(CMAKE_C_STANDARD 90)
include_directories(.)
include_directories(includes)
include_directories(libft)
add_library(mlx_glfw
		src/glad.c
		src/mlx.c
		src/hook.c
		src/framebuffer.c
		src/mlx_keys.c
		src/fps_meter.c
		)
target_link_libraries(mlx_glfw
		LINK_PUBLIC ${CMAKE_SOURCE_DIR}/libft.lib
		LINK_PUBLIC ${CMAKE_SOURCE_DIR}/glfw3.lib
		)
add_executable(mlx_test
		src/main.c
		)#SET_TARGET_PROPERTIES(opengl_sandbox PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(mlx_test
		LINK_PRIVATE mlx_glfw
		LINK_PUBLIC ${CMAKE_SOURCE_DIR}/glfw3.lib
		)
