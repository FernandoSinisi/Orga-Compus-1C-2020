project(cache)
cmake_minimum_required()
add_executable(cache main.c memory.c cache.c input_file.c log.c utils.c utils.h cache_way.c cache_way.h cache_line.c cache_line.h)
