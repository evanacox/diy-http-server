cmake_minimum_required (VERSION 3.15)
project (tcpserver LANGUAGES CXX)

# Make sure Boost.Asio is found
find_package (Boost 1.69 REQUIRED COMPONENTS system thread)

# Glob pattern for files, works as long as you re-run cmake on new files
file (GLOB_RECURSE SOURCE_FILES "src/*.cc" "src/**/*.cc")

# Include {fmt}
add_subdirectory (vendor/fmt EXCLUDE_FROM_ALL)

# Build the executable
add_executable (tcpserver ${SOURCE_FILES})
target_link_libraries (tcpserver fmt::fmt-header-only ${Boost_LIBRARIES})

# Enable C++17
set_target_properties (tcpserver PROPERTIES 
  CXX_STANDARD 17
  CXX_EXTENSIONS OFF
)
