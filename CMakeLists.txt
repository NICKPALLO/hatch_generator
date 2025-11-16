cmake_minimum_required (VERSION 3.8)

if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project ("hatch_generator")

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")

  set(MODULES_OBJS "")

  add_custom_command(
      OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/hatching.o
      COMMAND ${CMAKE_CXX_COMPILER} -c -std=c++20 -fmodules-ts ${CMAKE_CURRENT_SOURCE_DIR}/hatching.cxx -o ${CMAKE_CURRENT_BINARY_DIR}/hatching.o
      DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/hatching.cxx
  )
  list(APPEND MODULES_OBJS ${CMAKE_CURRENT_BINARY_DIR}/hatching.o)

  add_custom_command(
      OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/SVGDocument.o
      COMMAND ${CMAKE_CXX_COMPILER} -c -std=c++20 -fmodules-ts ${CMAKE_CURRENT_SOURCE_DIR}/SVGDocument.cxx -o ${CMAKE_CURRENT_BINARY_DIR}/SVGDocument.o
      DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/hatching.o ${CMAKE_CURRENT_SOURCE_DIR}/SVGDocument.cxx
  )
  list(APPEND MODULES_OBJS ${CMAKE_CURRENT_BINARY_DIR}/SVGDocument.o)

  add_custom_command(
      OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/main.o
      COMMAND ${CMAKE_CXX_COMPILER} -c -std=c++20 -fmodules-ts
              ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
              -o ${CMAKE_CURRENT_BINARY_DIR}/main.o
      DEPENDS ${MODULES_OBJS} ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
  )
  list(APPEND MODULES_OBJS ${CMAKE_CURRENT_BINARY_DIR}/main.o)

  add_custom_target(hatch_all ALL
      DEPENDS ${MODULES_OBJS}
  )

  add_custom_command(
      TARGET hatch_all POST_BUILD
      COMMAND ${CMAKE_CXX_COMPILER} ${MODULES_OBJS} -o ${CMAKE_CURRENT_BINARY_DIR}/hatch_generator.exe
  )
else()
  add_executable(hatch_generator main.cpp
  )
  target_sources(hatch_generator
      PRIVATE
          FILE_SET modules TYPE CXX_MODULES
          BASE_DIRS ${CMAKE_CURRENT_SOURCE_DIR}
          FILES
            hatching.cxx
            SVGDocument.cxx
  )
endif()
