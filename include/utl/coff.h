#pragma once

#include "utl/type.h"

typedef struct CoffFileHdr CoffFileHdr;
struct CoffFileHdr
{
    u16 machine;
    u16 number_of_sections;
    u32 time_date_stamp;
    u32 pointer_to_symbol_table;
    u32 number_of_symbols;
    u16 size_of_optional_header;
    u16 characteristics;
};

typedef struct CoffOptHdr CoffOptHdr;
struct CoffOptHdr 
{
    u16 magic;
    u8 major_linker_version;
    u8 minor_linker_version;
    u32 size_of_code;
    u32 size_of_initialized_data;
    u32 size_of_uninitialized_data;
    u32 address_of_entry_point;
    u32 base_of_code;
    u32 base_of_data;
};

typedef struct CoffSectionHdr CoffSectionHdr;
struct CoffSectionHdr
{
    u8 name[8];
    u32 virtual_size;
    u32 virtual_address;
    u32 size_of_raw_data;
    u32 pointer_to_raw_data;
    u32 pointer_to_relocations;
    u32 pointer_to_line_numbers;
    u16 number_of_relocations;
    u16 number_of_line_numbers;
    u32 characteristics;
};

typedef struct CoffReloc CoffReloc;
struct CoffReloc
{
    u32 virtual_address;
    u32 symbol_table_index;
    u16 type;
};

typedef struct CoffLineNum CoffLineNum;
struct CoffLineNum
{
    union {
        u32 symbol_table_index;
        u32 virtual_address;
    };
    u16 line_number;
};

typedef struct CoffSym CoffSym;
struct CoffSym 
{
    union {
        u8 name[8];
        struct
        {
            u32 zeroes;
            u32 str_table_offset;
        };
    };
    u32 value;
    i16 section_number;
    u16 type;
    u8 storage_class;
    u8 number_of_aux_symbols;
};

