#include <ioports.h>

#define FLOPPY_BASE	0x03f0
#define FLOPPY_IRQ	6

enum floppy_registers
{
	FLOPPY_SRA = 0, // Status register A		-- read-only
	FLOPPY_SRB = 1, // Status register B		-- read-only
	FLOPPY_DOR = 2, // Digital output register
	FLOPPY_TDR = 3, // Tape drive register
	FLOPPY_MSR = 4, // Main status register		-- read-only
	FLOPPY_DSR = 4, // Datarate select register	-- write-only
	FLOPPY_FIFO = 5, // Data FIFO
	FLOPPY_DIR = 7, // Digital input register	-- read-only
	FLOPPY_CCR = 7  // Configuration control register -- write-only
};

enum floppy_commands
{
	READ_TRACK =			2,
	SPECIFY =				3,
	SENSE_DRIVE_STATUS =	4,
	WRITE_DATA = 			5,
	READ_DATA =				6,
	RECALIBRATE = 			7,
	SENSE_INTERRUPT =		8,
	READ_ID =				10,
	READ_DELETED_DATA =		12,
	FORMAT_TRACK =			13,
	SEEK =					15,
	VERSION =				16,
	SCAN_EQUAL =			17,
	PERPENDICULAR_MODE =	18,
	CONFIGURE =				19,
	LOCK = 					20,
	VERIFY =				22,
	SCAN_LOW_OR_EQUAL =		25,
	SCAN_HIGH_OR_EQUAL =	29
};

static const char * drive_types[8] = {
	"none",
	"360kB 5.25\"",
	"1,2MB 5.25\"",
	"720kB 5.25\"",
	"1.44MB 3.5\"",
	"2.88MB 3.5\"",
	"unknown type",
	"unknown type"
};
