#include "flash.h"


/* Private variables ---------------------------------------------------------*/
uint32_t StartSector = 0, EndSector = 0, Address = 0, i=0;
__IO uint32_t data32 = 0 , MemoryProgramStatus = 0 ;

void Flash_write()
{
     FLASH_Unlock();
     FLASH_ClearFlag(FLASH_FLAG_EOP | FLASH_FLAG_OPERR | FLASH_FLAG_WRPERR |
     FLASH_FLAG_PGAERR | FLASH_FLAG_PGPERR|FLASH_FLAG_PGSERR);
     /* Lay number cua Sector bat dau va Sector ket thuc */
     StartSector = GetSector(FLASH_USER_START_ADDR);
     EndSector   = GetSector(FLASH_USER_END_ADDR);
     for (i = StartSector; i < EndSector; i += 8)
     {
         /* Hieu dien the nam trong khoang [2.7V den 3.6V] */
         if (FLASH_EraseSector(i, VoltageRange_3) != FLASH_COMPLETE)
         {
             /* Co loi khi xoa sector. Nguoi dung co the them code vao day de xu ly loi */
             while (1)
             {
               
             }
         }
     }
     /* Ghi tung word vao vung nho Flash danh cho nguoi dung
     (vung nho nam giua FLASH_USER_START_ADDR va FLASH_USER_END_ADDR) */
     Address = FLASH_USER_START_ADDR;
     while (Address < FLASH_USER_END_ADDR)
     {
         if (FLASH_ProgramWord(Address, DATA_32) == FLASH_COMPLETE)
         {
            Address = Address + 4;
         }
         else
         {
         /* Co loi khi ghi du lieu. Nguoi dung co the them code vao day de xu ly loi */
             while (1)
             {
             }
         }
     }
     /* Lock bo nho Flash de cam truy cap vao thanh ghi dieu khien Flash
     (nham bao ve Flash truoc nhung tac dong khong mong muon) */
     FLASH_Lock();
     /* Kiem tra xem viec ghi vao Flash co chinh xac khong
     MemoryProgramStatus = 0: du lieu duoc ghi chinh xac
     MemoryProgramStatus != 0: so word bi ghi khong chinh xac */
     Address = FLASH_USER_START_ADDR;
     MemoryProgramStatus = 0x0;
     while (Address < FLASH_USER_END_ADDR)
     {
         data32 = *(__IO uint32_t*)Address;
         if (data32 != DATA_32)
         {
            MemoryProgramStatus++;
         }
         Address = Address + 4;
     }
}

uint32_t Flash_read(uint32_t address){
    return (*(__IO uint32_t*) address);
}


uint32_t GetSector(uint32_t Address)
{
 uint32_t sector = 0;
 if((Address < ADDR_FLASH_SECTOR_1) && (Address >= ADDR_FLASH_SECTOR_0))
 {
 sector = FLASH_Sector_0;
 }
 else if((Address < ADDR_FLASH_SECTOR_2) && (Address >= ADDR_FLASH_SECTOR_1))
 {
 sector = FLASH_Sector_1;
 }
 else if((Address < ADDR_FLASH_SECTOR_3) && (Address >= ADDR_FLASH_SECTOR_2))
 {
 sector = FLASH_Sector_2;
 }
 else if((Address < ADDR_FLASH_SECTOR_4) && (Address >= ADDR_FLASH_SECTOR_3))
 {
 sector = FLASH_Sector_3;
 }
 else if((Address < ADDR_FLASH_SECTOR_5) && (Address >= ADDR_FLASH_SECTOR_4))
 {
 sector = FLASH_Sector_4;
 }
 else if((Address < ADDR_FLASH_SECTOR_6) && (Address >= ADDR_FLASH_SECTOR_5))
 {
 sector = FLASH_Sector_5;
 }
 else if((Address < ADDR_FLASH_SECTOR_7) && (Address >= ADDR_FLASH_SECTOR_6))
 {
 sector = FLASH_Sector_6;
 }
 else if((Address < ADDR_FLASH_SECTOR_8) && (Address >= ADDR_FLASH_SECTOR_7))
 {
 sector = FLASH_Sector_7;
 }
 else if((Address < ADDR_FLASH_SECTOR_9) && (Address >= ADDR_FLASH_SECTOR_8))
 {
 sector = FLASH_Sector_8;
 }
 else if((Address < ADDR_FLASH_SECTOR_10) && (Address >= ADDR_FLASH_SECTOR_9))
 {
 sector = FLASH_Sector_9;
 }
 else if((Address < ADDR_FLASH_SECTOR_11) && (Address >= ADDR_FLASH_SECTOR_10))
 {
 sector = FLASH_Sector_10;
 }
 else
 {
 sector = FLASH_Sector_11;
 }
 return sector;
}

