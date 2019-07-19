/*
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/


/*
|****************************************************************************
|****************************************************************************
* Project                                         :<Soft_PLC>
* Programm name                                   :softPLC_rt.c
* Author                                          :Shults1981
* Data create                                     :01/06/2019
* Purpose                                         :

|***************************************************************************
|***************************************************************************
*/

#define DEBUG

#define _windows_

#ifdef _windows_

    #define test_prog  "E:\\SOFT_PLC\\soft_plc_rt\\test_prg.splcobj"

#endif

#ifdef _linux_
    #define test_prog  "//home//alex//programing//SOFT_PLC//soft_plc_rt//test_prg.splcobj"
#endif



#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <op_code.h>


typedef unsigned char BYTE;



//=====================Point Instriction Registers
static int PI_R;



//=====================Accumulators registers
#define MAX_OPERAND_SIZE 4


static unsigned int ACC1_i,ACC2_i;
static float ACC1_f,ACC2_f;

static BYTE ACC1[4];
static BYTE ACC2[4];

//==================Operand registrer


static BYTE OPERAND_R[MAX_OPERAND_SIZE];



/*=====================FLAG REGISTER===================*/
//

static unsigned short FLAG_R;

//

//     The bits of FLAG register and operations whith them

//

// bit 0  -  /FC First Check Bit - Флаг первичного опроса

#define SET_CF (FLAG_R = FLAG_R | (1))

#define RESET_CF (FLAG_R = FLAG_R & (~1))

#define READ_CF (FLAG_R & 1)



// bit 1  -  RLO - Result of Logic Operation - Флаг логического результата

#define SET_RLO (FLAG_R = FLAG_R | (1<<1))

#define RESET_RLO (FLAG_R =FLAG_R & (~(1<<1)))

#define READ_RLO (FLAG_R & (1<<1))



// bit 2  -  STA - Status Bit - Флаг статуса

#define SET_STA (FLAG_R = FLAG_R | (1<<2))

#define RESET_STA (FLAG_R = FLAG_R & (~(1<<2)))

#define READ_STA (FLAG_R & (1<<2))



// bit 3  -  OR - Флаг операции ИЛИ

#define SET_OR (FLAG_R = FLAG_R | (1<<3))

#define RESET_OR (FLAG_R = FLAG_R & (~(1<<3)))

#define READ_OR (FLAG_R & (1<<3))



// bit 4  -  OV - Overflow - Флаг преполнения

#define SET_OV (FLAG_R = FLAG_R | (1<<4))

#define RESET_OV (FLAG_R = FLAG_R & (~(1<<4)))

#define READ_OV (FLAG_R & (1<<4))



// bit 5  -  OS - Overflow Stored - Флаг преполнения c памятью

#define SET_OS (FLAG_R = FLAG_R | (1<<5))

#define RESET_OS (FLAG_R = FLAG_R & (~(1<<5)))

#define READ_OS (FLAG_R & (1<<5))



// bit 6  -  CC0 - Condition Codes - Флаг условия #0

#define SET_CC0 (FLAG_R = FLAG_R | (1<<6))

#define RESET_CC0 (FLAG_R = FLAG_R & (~(1<<6)))

#define READ_CC0 (FLAG_R & (1<<6))



// bit 7  -  CC1 - Condition Codes - Флаг условия #1

#define SET_CC1 (FLAG_R = FLAG_R | (1<<7))

#define RESET_CC1 (FLAG_R = FLAG_R & (~(1<<7)))

#define READ_CC1 (FLAG_R & (1<<7))



// bit 8  -  BR - Binary Result Bit - Флаг двоичного резульата

#define SET_BR (FLAG_R = FLAG_R | (1<<8))

#define RESET_BR (FLAG_R = FLAG_R & (~(1<<8)))

#define READ_BR (FLAG_R & (1<<8))
//======================================================================






/*==================== RAM ===================*/

// merkers rigion
#define SIZE_OF_MERKER_REGION 256
static BYTE MERKER[SIZE_OF_MERKER_REGION];

#define SET_MERKER_BIT(X,N) MERKER[X]=MERKER[X]|(1<<N)
#define RESET_MERKER_BIT(X,N) MERKER[X]=MERKER[X]&(~(1<<N))
#define READ_MERKER_BIT(X,N)  MERKER[X]&(1<<M)

// programm region
#define SIZE_OF_EXEC_PRG_REGION 256
static BYTE EXEC_PRG[SIZE_OF_EXEC_PRG_REGION] ;



//


int read_programm_image (char* img_file_name)  //load program from file image"ROM" to RAM
{
    FILE *img_file;
    int c;
    int index=0;
    int addr=0;
    img_file= fopen(img_file_name,"r");
    if(img_file == NULL)
        {
            printf("can`t open file '%s'",img_file_name);
            return 0;
        }

    else
        {
            printf("programm file:\n");
            while ((c=getc(img_file))!=EOF){

                printf("%x ",c);
                if (index>31){
                   EXEC_PRG[addr]=(BYTE)(c);
                   addr++;
                }
                index++;
            }


        }
    fclose(img_file);
    return 1;

}
//-------------------------------
static void (*PUI)(int, BYTE*); //---- pointer to ALU instruction


static void _load(int _operand_size, BYTE _operand)
{
    #ifdef DEBUG
    printf(" LOAD \n\n");

    #endif
    //basic actions
    for (int i=0;i<4;i++ )
        ACC2[i]=ACC1[i];

    for (int i=0;i<_operand_size;i++ )
        ACC1[i]=OPERAND_R[i];

    //flag

}
static void _transmit(int _operand_size, BYTE _operand)
{

}

static void _nop(int _operand_size, BYTE _operand)
{
    #ifdef DEBUG
    printf(" NOP \n\n");
    #endif
}

static void _add(int _operand_size,BYTE _operand)
{

}
//-----------------------------------

int  DECODE_OP_CODE_(BYTE op_code[2],int* _operand_size)
{
    if ((op_code[0]==0x7b) && (op_code[1]==0x7b)){
        *_operand_size=0;
        PUI=&_nop;
        return 1;
    }

    if ((op_code[0]==0x7d) && (op_code[1]==0x7d)){
        *_operand_size=0;
        PUI=&_nop;
        return 0;
    }

    if ((op_code[0]==0x30) && (op_code[1]==0x30)){
        *_operand_size=1;
        PUI=&_load;
        return 1;
    }

    return -1;
}


void _DEBUG_OUT(void)
{

    printf("ACC_1=");
    for (int i=3;i>=0;i--)
        printf("%d",ACC1[i]);
    printf("    ACC_2=");
    for (int i=3;i>=0;i--)
        printf("%d",ACC2[i]);
    printf("    FLAG_=");
    for (int i=15;i>=0;i--)
        FLAG_R&(1<<i)?printf("%d",1):printf("%d",0);
    printf("\n");


}





int main(int argc, char* argv[])

{
    int i=0;
    int addr=0;
    int BeginOfPOU_flag=2;
    int EndOfPOU_flag=0;
    int count_of_tic=0;
    BYTE cur_op_code[2]={0x00,0x00};
//    BYTE operand=0;
    int operand_size=0;
    int end_of_circle=1;



    //-------initialize PLC
    FLAG_R=0x00;
    PI_R=0;

    ACC1_i=0;
    ACC2_i=0;

    ACC1_f=0.0;
    ACC2_f=0.0;

    for (i=0;i<SIZE_OF_MERKER_REGION;i++)
        MERKER[i]=0x00;

    PUI=_nop;

    //-----------------------

    read_programm_image(test_prog);

    #ifdef DEBUG
    printf("\n__________________________________________\n");
    printf("programm dump:\n");
    addr=0;
    while ((addr<SIZE_OF_EXEC_PRG_REGION) && (EndOfPOU_flag!=2))
       {
            printf("%d-%x\n",addr,EXEC_PRG[addr] );
            if (EXEC_PRG[addr]==0x7b)
                BeginOfPOU_flag--;
            if (EXEC_PRG[addr]==0x7d)
                EndOfPOU_flag++;
            addr++;
       }

    printf("\n__________________________________________\n");
    #endif

    //    execute POU
    count_of_tic=1;

    while(count_of_tic) // main execute circle
    {
        addr=0;
        PI_R=addr;
        end_of_circle=1;

        #ifdef DEBUG
        printf("                      tic #%d\n",count_of_tic);
        #endif

        while (end_of_circle)
        {
            #ifdef DEBUG
            _DEBUG_OUT(); // debug information
            #endif
            //--- GET OPATION CODE
            cur_op_code[0]=EXEC_PRG[PI_R];
            PI_R++;
            cur_op_code[1]=EXEC_PRG[PI_R];

            end_of_circle=DECODE_OP_CODE_(cur_op_code, &operand_size);
            #ifdef DEBUG
            printf("cmd=%x%x;  operand_size=%d;",cur_op_code[0],cur_op_code[1], operand_size);
            #endif

            //---- GET OPERAND
            if ((operand_size>0)&&(operand_size<=MAX_OPERAND_SIZE)){
                for (i=1;i<=operand_size;++i)
                {
                    PI_R+=i;
                    OPERAND_R[i-1]=EXEC_PRG[PI_R];
                    #ifdef DEBUG
                    printf("  operand=%x",OPERAND_R[i-1]);// debug msg
                    #endif
                }
            }
            #ifdef DEBUG
            else
                 printf("  no operand"); // debug msg
            printf("\n");// debug msg
            #endif

            //--- EXECUTE OPERATION
            PUI(operand_size,OPERAND_R);

            // goto next operation
            PI_R++;
        }


        count_of_tic--;
    }



    return 0;

}



