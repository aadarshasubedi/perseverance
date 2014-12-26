FIND_PATH( TMX_LOADER_INCLUDE_PATH tmx/MapLoader.h
	${TMX_LOADER_ROOT}/include
    $ENV{TMX_LOADER_ROOT}/include
	/usr/include
	/usr/local/include
	/sw/include
	/opt/local/include
	DOC "The directory where tmx/MapLoader.h resides")

FIND_LIBRARY( TMX_LOADER_LIBRARY
	NAMES TMX-LOADER tmx-loader
	PATH_SUFFIXES lib64 lib
	PATHS
	${TMX_LOADER_ROOT}/lib
    $ENV{TMX_LOADER_ROOT}/lib
    /usr
   	/usr/local
    DOC "The TMX Loader library")

SET(TMX_LOADER_FOUND "NO")
IF (TMX_LOADER_INCLUDE_PATH AND TMX_LOADER_LIBRARY)
	SET(TMX_LOADER_LIBRARIES ${TMX_LOADER_LIBRARY})
	SET(TMX_LOADER_FOUND "YES")
ENDIF (TMX_LOADER_INCLUDE_PATH AND TMX_LOADER_LIBRARY)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(TMX-LOADER DEFAULT_MSG TMX_LOADER_LIBRARY TMX_LOADER_INCLUDE_PATH)