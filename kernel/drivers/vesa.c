#include <stdio.h>
#include <kdriver.h>
#include <types.h>
#include <klog.h>
#include <ioports.h>
#include <string.h>
#include <pci.h>
#include <pci_config.h>
#include <memory.h>
#include <pagination.h>
#include <vmm.h>
#include <vesa_types.h>

#define VBE_DISPI_IOPORT_INDEX		0x01CE
#define VBE_DISPI_IOPORT_DATA		0x01CF
#define VBE_DISPI_INDEX_ID		0x0
#define VBE_DISPI_INDEX_XRES		0x1
#define VBE_DISPI_INDEX_YRES		0x2
#define VBE_DISPI_INDEX_BPP		0x3
#define VBE_DISPI_INDEX_ENABLE		0x4
#define VBE_DISPI_INDEX_BANK		0x5
#define VBE_DISPI_INDEX_VIRT_WIDTH	0x6
#define VBE_DISPI_INDEX_VIRT_HEIGHT	0x7
#define VBE_DISPI_INDEX_X_OFFSET	0x8
#define VBE_DISPI_INDEX_Y_OFFSET	0x9

#define VBE_DISPI_DISABLED		0x00
#define VBE_DISPI_ENABLED		0x01
#define VBE_DISPI_GETCAPS		0x02
#define VBE_DISPI_8BIT_DAC		0x20
#define VBE_DISPI_LFB_ENABLED		0x40
#define VBE_DISPI_NOCLEARMEM		0x80

#define V_BACKBUFFER_BASE		0x10000000

static int width;
static int height;
static int bpp;
static paddr_t p_lfb_base;
static paddr_t p_frontbuffer_base;
static paddr_t p_backbuffer_base;

static void vbe_write_reg(unsigned short index, unsigned short data) {
	outw(index, VBE_DISPI_IOPORT_INDEX);
	outw(data, VBE_DISPI_IOPORT_DATA);
}
 
static unsigned short vbe_read_reg(unsigned short index) __attribute__ ((unused));
static unsigned short vbe_read_reg(unsigned short index) {
	outw(index, VBE_DISPI_IOPORT_INDEX);
	return inw(VBE_DISPI_IOPORT_DATA);
}

static void remap_backbuffer(paddr_t p_addr_base) {
	size_t back_buffer_size = width * height * bpp;
	unsigned int page;
	for (page = 0; page < back_buffer_size/PAGE_SIZE; page++) {
		unmap(V_BACKBUFFER_BASE + page * PAGE_SIZE);
		map(p_addr_base + page * PAGE_SIZE, V_BACKBUFFER_BASE + page * PAGE_SIZE);
	}
}

static int vesa_ioctl(open_file_descriptor* ofd __attribute__ ((unused)), unsigned int request, unsigned long data) {
	struct vesa_setmode_req* req = (struct vesa_setmode_req*)data;
	switch (request) {
		case SETMODE:
			vbe_write_reg(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_DISABLED);
			vbe_write_reg(VBE_DISPI_INDEX_XRES, req->width);
			vbe_write_reg(VBE_DISPI_INDEX_YRES, req->height);
			vbe_write_reg(VBE_DISPI_INDEX_BPP, req->bpp);
			vbe_write_reg(VBE_DISPI_INDEX_VIRT_WIDTH, req->width);
			vbe_write_reg(VBE_DISPI_INDEX_X_OFFSET, 0);
			vbe_write_reg(VBE_DISPI_INDEX_Y_OFFSET, 0);
			vbe_write_reg(VBE_DISPI_INDEX_ENABLE, VBE_DISPI_ENABLED | VBE_DISPI_LFB_ENABLED);

			width = req->width;
			height = req->height;
			bpp = (req->bpp + (8 - 1))/8;

			p_backbuffer_base = p_lfb_base;
			p_frontbuffer_base = p_lfb_base + width * height * bpp;
		
			return 0;
		case FLUSH: {
			// Décalage de la zone du LFB affichée
			vbe_write_reg(VBE_DISPI_INDEX_Y_OFFSET, (p_backbuffer_base - p_lfb_base) / (width * bpp));
			// Swap backbuffer/frontbuffer
			paddr_t tmp = p_backbuffer_base; 
			p_backbuffer_base = p_frontbuffer_base;
			p_frontbuffer_base = tmp;
			// Remap backbuffer
			remap_backbuffer(p_backbuffer_base);
			// Vidage backbuffer
			memset((void*)V_BACKBUFFER_BASE, 0, width * height * bpp);

			return 0;
		}
		default:
			return -1;
	}
} 

static driver_interfaces di = {
	.read = NULL,
	.write = NULL,
	.seek = NULL,
	.open = NULL,
	.close = NULL,
	.flush = NULL,
	.ioctl = vesa_ioctl,
};

void init_vesa() {
	klog("initializating vesa driver...");

	if (register_driver("vesa", &di) != 0) {
		kerr("error registering vesa driver.");
	}

	p_lfb_base = pci_read_value(pci_find_device(0x1234, 0x1111), PCI_BAR0) & 0xFFFF0000;
	klog("base addr : %x\n", p_lfb_base);
	
	size_t video_mem_size = 16*1024*1024; // 16Mio
	unsigned int page;
	for (page = 0; page < video_mem_size/PAGE_SIZE; page++) {
		map(p_lfb_base + page*PAGE_SIZE, V_BACKBUFFER_BASE + page*PAGE_SIZE);
	}
}
