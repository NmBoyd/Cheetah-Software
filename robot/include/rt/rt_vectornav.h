#ifndef _rt_vectornav
#define _rt_vectornav

// incredibly obscure bug in SPI_IOC_MESSAGE macro is fixed by this
#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
extern "C" {
#endif

#include "vn/sensors.h"

#ifdef __cplusplus /* If this is a C++ compiler, use C linkage */
}
#endif



void init_vectornav();

#endif
