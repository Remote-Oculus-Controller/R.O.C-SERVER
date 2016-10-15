# Once done these will be defined:
#
#  LIBX265_FOUND
#  LIBX265_INCLUDE_DIRS
#  LIBX265_LIBRARIES
#
# For use in OBS:
#
#  X265_INCLUDE_DIR

find_package(PkgConfig QUIET)
if (PKG_CONFIG_FOUND)
	pkg_check_modules(_X265 QUIET x265)
endif()

if(CMAKE_SIZEOF_VOID_P EQUAL 8)
	set(_lib_suffix 64)
else()
	set(_lib_suffix 32)
endif()

find_path(X265_INCLUDE_DIR
	NAMES x265.h
	HINTS
		ENV x265Path${_lib_suffix}
		ENV x265Path
		ENV DepsPath${_lib_suffix}
		ENV DepsPath
		${x265Path${_lib_suffix}}
		${x265Path}
		${DepsPath${_lib_suffix}}
		${DepsPath}
		${_X265_INCLUDE_DIRS}
	PATHS
		/usr/include /usr/local/include /opt/local/include /sw/include
	PATH_SUFFIXES
		include)

find_library(X265_LIB
	NAMES ${_X265_LIBRARIES} x265 libx265
	HINTS
		ENV x265Path${_lib_suffix}
		ENV x265Path
		ENV DepsPath${_lib_suffix}
		ENV DepsPath
		${x265Path${_lib_suffix}}
		${x265Path}
		${DepsPath${_lib_suffix}}
		${DepsPath}
		${_X265_LIBRARY_DIRS}
	PATHS
		/usr/lib /usr/local/lib /opt/local/lib /sw/lib
	PATH_SUFFIXES
		lib${_lib_suffix} lib
		libs${_lib_suffix} libs
		bin${_lib_suffix} bin
		../lib${_lib_suffix} ../lib
		../libs${_lib_suffix} ../libs
		../bin${_lib_suffix} ../bin)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(Libx265 DEFAULT_MSG X265_LIB X265_INCLUDE_DIR)
mark_as_advanced(X265_INCLUDE_DIR X265_LIB)

if(LIBX265_FOUND)
	set(LIBX265_INCLUDE_DIRS ${X265_INCLUDE_DIR})
	set(LIBX265_LIBRARIES ${X265_LIB})
endif()

