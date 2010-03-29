#ifndef _FAT_H_
#define _FAT_H_

#include <types.h>

#define NB_CYLINDERS 80
#define NB_HEADS 2
#define NB_SECTORS 18

typedef struct addr_CHS {
	
	uint32_t	Cylinder;
	uint32_t	Head;
	uint32_t	Sector;
	
}__attribute__((packed)) addr_CHS_t;

typedef struct fat_BS
{
											//Offset
	uint8_t		bootjmp[3];					//0x00
	uint8_t		oem_name[8];				//0x03
	uint16_t	bytes_per_sector;			//0x0b
	uint8_t		sectors_per_cluster;		//0x0d
	uint16_t	reserved_sector_count;		//0x0e
	uint8_t		table_count;				//0x10
	uint16_t	root_entry_count;			//0x11
	uint16_t	total_sectors_16;			//0x13
	uint8_t		media_type;					//0x15
	uint16_t	table_size_16;				//0x16
	uint16_t	sectors_per_track;			//0x18
	uint16_t	head_side_count;			//0x1a
	uint32_t	hidden_sector_count;		//0x1c
	uint32_t	total_sectors_32;			//0x20
	uint8_t		bios_drive_num;				//0x24
	uint8_t		reserved;					//0x25
	uint8_t		boot_signature;				//0x26
	uint32_t	volume_id;					//0x27
	uint8_t		volume_label[11];			//0x2b
	uint8_t		fat_type_label[8];			//0x36
	uint8_t		os_boot_code[448];			//0x3e
	uint16_t	bs_signature;				//0x1fe
	
}__attribute__((packed)) fat_BS_t;

typedef struct fat_dir_entry {
	uint8_t		long_file_name[32];
	uint8_t		utf8_short_name[8];
	uint8_t		file_extension[3];
	uint8_t		file_attributes;
	uint8_t		reserved;
	uint8_t		create_time_ms;
	uint16_t	create_time;
	uint16_t	create_date;
	uint16_t	last_access_date;
	uint16_t	ea_index;
	uint16_t	last_modif_time;
	uint16_t	last_modif_date;
	uint16_t	cluster_pointer;
	uint32_t	file_size;
	
}__attribute__((packed)) fat_dir_entry_t;


typedef struct virtual_FS_dir {

	uint8_t		name[14];
	uint32_t	entries_count;
	uint16_t	cluster_pointer;
	struct virtual_FS_dir * sub_directories[8];
	
	struct virtual_FS_dir * root_dir;
	
}__attribute__((packed)) virtual_FS_dir_t;


void update_virtual_FS (virtual_FS_dir_t * vFS_dir, fat_dir_entry_t * fat_dir);
void read_fat_BS ();
void mount_fat_fs ();
void list_dir_entries ();
void present_dir ();

#endif
