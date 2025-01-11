cmake_minimum_required(VERSION 3.10)
project(SnakeGame)

# Set the C standard
set(CMAKE_C_STANDARD 99)

# Source files
set(SOURCE_FILES_COMMON plocha.c hra.c snake.c input.c)
set(SOURCE_FILES_SERVER server.c ${SOURCE_FILES_COMMON})
set(SOURCE_FILES_CLIENT client.c ${SOURCE_FILES_COMMON})

# Targets for server and client
add_executable(server main_server.c ${SOURCE_FILES_SERVER})
target_include_directories(server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

add_executable(client main_client.c ${SOURCE_FILES_CLIENT})
target_include_directories(client PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Standalone main target
add_executable(main main.c ${SOURCE_FILES_SERVER} ${SOURCE_FILES_CLIENT})
target_include_directories(main PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

# Custom clean target
add_custom_target(custom_clean
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMENT "Cleaning up generated files"
)

# Custom build_all target
add_custom_target(build_all DEPENDS server client main)

# Install targets (optional)
install(TARGETS server client main DESTINATION bin)
