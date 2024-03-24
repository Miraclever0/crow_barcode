find_package(PkgConfig REQUIRED)
pkg_check_modules(ZBAR REQUIRED IMPORTED_TARGET zbar)

if (TARGET PkgConfig::ZBAR)
set(ZBAR_FOUND TRUE)
else()
set(ZBAR_FOUND FALSE)
endif()

set(ZBAR_INCLUDE_DIRS ${PkgConfig_ZBAR_INCLUDE_DIRS})
set(ZBAR_LIBRARIES PkgConfig::ZBAR)

include_directories(${ZBAR_INCLUDE_DIRS})

target_link_libraries(${ZBAR_LIBRARIES} INTERFACE ${ZBAR_LINK_LIBRARIES})