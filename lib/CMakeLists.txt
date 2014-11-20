add_custom_command(OUTPUT ${CMAKE_CURRENT_BINARY_DIR}/BASEIO.h ${CMAKE_CURRENT_BINARY_DIR}/BASEIO.cc COMMAND python2 ${CMAKE_SOURCE_DIR}/createIOCode.py ${CMAKE_SOURCE_DIR}/lib/content.def BASEIO DEPENDS ${CMAKE_SOURCE_DIR}/createIOCode.py ${CMAKE_SOURCE_DIR}/lib/content.def)

include_directories(${CMAKE_CURRENT_BINARY_DIR})

set(ATSrcs iohelper.cc iohelper.h ${CMAKE_CURRENT_BINARY_DIR}/BASEIO.h ${CMAKE_CURRENT_BINARY_DIR}/BASEIO.cc)

add_library(AnalysisTool SHARED ${ATSrcs})
target_link_libraries(AnalysisTool ${ROOT_LIBRARIES})

install(TARGETS AnalysisTool DESTINATION lib)
install(FILES BASEIO/*.h iohelper.h DESTINATION include/AnalysisTool/)
