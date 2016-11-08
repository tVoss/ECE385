//io_handler.c
#include <unistd.h>  // usleep
#include "io_handler.h"
#include <stdio.h>
#include "system.h"

#define otg_hpi_address		(volatile int*) 	OTG_HPI_ADDRESS_BASE
#define otg_hpi_data		(volatile int*)	    OTG_HPI_DATA_BASE
#define otg_hpi_r			(volatile char*)	OTG_HPI_R_BASE
#define otg_hpi_cs			(volatile char*)	OTG_HPI_CS_BASE //FOR SOME REASON CS BASE BEHAVES WEIRDLY MIGHT HAVE TO SET MANUALLY
#define otg_hpi_w			(volatile char*)	OTG_HPI_W_BASE


void IO_init(void)
{
	*otg_hpi_cs = 0;
	*otg_hpi_r = 1;
	*otg_hpi_w = 1;
	*otg_hpi_address = 0;
	*otg_hpi_data = 0;
}

void IO_write(alt_u8 Address, alt_u16 Data)
{
	// Set address
	*otg_hpi_address = Address;

	// Enable writing
	*otg_hpi_w = 0;

	// Write data
	*otg_hpi_data = Data;

	// Disable writing
	*otg_hpi_w = 1;
}

alt_u16 IO_read(alt_u8 Address)
{
	// Set address
	*otg_hpi_address = Address;

	// Enable reading
	*otg_hpi_r = 0;

	// Read data
	alt_u16 data = *otg_hpi_data;

	// Disable reading
	*otg_hpi_r = 1;

	return data;
}
