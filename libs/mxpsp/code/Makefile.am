
# set the include path found by configure

psp_path = `psp-config --psp-prefix`

CPATH= -I$(psp_path)/sdk/include

INCLUDES=  $(all_includes) $(CPATH)
# the library search path.
include_HEADERS= mxsurface.h mxclamp.h mxcontroller.h mxwnd.h mx.h
lib_LTLIBRARIES=libmxpsp.la
libmxpsp_la_SOURCES= mxsurface.cpp mxclamp.cpp mxcontroller.cpp mxwnd.cpp
 
