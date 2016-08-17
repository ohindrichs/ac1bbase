include_directories(${CMAKE_SOURCE_DIR}/lib ${PROJECT_BINARY_DIR}/lib ${PROJECT_SOURCE_DIR}/libextra)

#set(LUMIxrootdSrcs LUMIxrootd.cc)
#add_executable(LUMIxrootd ${LUMIxrootdSrcs})
#target_link_libraries(LUMIxrootd AnalysisTool ${Boost_LIBRARIES} ${ROOT_LIBRARIES})

set(LUMIlocaldirSrcs LUMIlocaldir.cc)
add_executable(LUMIlocaldir ${LUMIlocaldirSrcs})
target_link_libraries(LUMIlocaldir AnalysisTool AnalysisSupport ${ROOT_LIBRARIES})


install(TARGETS LUMIlocaldir DESTINATION bin)
