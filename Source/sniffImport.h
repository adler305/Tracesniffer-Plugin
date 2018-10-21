/** \file sniffImport.h
 * \brief sniffImport header file.
 * \details Collects all header files and has to be included into the FreeRTOSConfig.h.
 * Additionally it declares functions used for initialising the Tracer.
 * \author Jonas Mair
 * \date 2018
 */

#ifndef SNIFFIMPORT_H_INCLUDED
#define SNIFFIMPORT_H_INCLUDED

#define configUSE_TRACE_FACILITY  1 /**<Enables the hooks used from the TraceSniffer*/

#include <sniffHooks.h>
#include <sniffPayload.h>
#include <sniffFIFO.h>
#include <sniffPort.h>
#include <sniffTask.h>


uint8_t initialiseTraceSniffer();
void stopTraceSniffer();




#endif // SNIFFIMPORT_H_INCLUDED
