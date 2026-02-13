///////////////////////////////////////////////////////////
//
//  : Header file inclusion
//
///////////////////////////////////////////////////////////

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>
#include<unistd.h>

///////////////////////////////////////////////////////////
//
//  : User Define macros
//
///////////////////////////////////////////////////////////

// Maximum file size that we allow in the project
#define MAXFILESIZE 50

#define MAXOPENFILES 20

#define MAXINODE 5

#define READ 1
#define WRITE 2
#define EXECUTE 4

#define START 0
#define CURRENT 1
#define END 2

#define EXECUTE_SUCCESS 0

#define REGULARFILE 1
#define SPECIALFLE 2

///////////////////////////////////////////////////////////
//
//  : User Define macros for error handling
//
///////////////////////////////////////////////////////////
#define ERR_INVALID_PARAMETER -1

#define ERR_NO_INODE -2

#define ERR_FILE_ALREADY_EXIST -3
#define ERR_FILE_NOT_EXIST -4

#define ERR_PERMISSION_DENIED -5

#define ERR_INSUFFICIENT_SPACE -6
#define ERR_INSUFFICIENT_DATA -7

#define ERR_MAX_FILES_OPEN -8

///////////////////////////////////////////////////////////
//
//  : User Define structures
//
///////////////////////////////////////////////////////////

///////////////////////////////////////////////////////////
//
//  Structure name: BootBlock
//  Description   : Holds the information to boot the os
//
///////////////////////////////////////////////////////////
struct BootBlock
{
    char information[100];

};

///////////////////////////////////////////////////////////
//
//  Structure name: SuperBlock
//  Description   : Holds the information about the file-
//                  system
//
///////////////////////////////////////////////////////////

struct SuperBlock            /*It can be holds the data about Inode*/
{ 
    int TotalInodes;
    int FreeInode;
};

///////////////////////////////////////////////////////////
//
//  Structure name: Inode
//  Description   : Holds the information about the file
//                  
//
///////////////////////////////////////////////////////////
#pragma pack(1)

struct Inode
{
    char FileName[20];       /*this structure can be hold the metadata about the file*/
    int InodeNumber;
    int FileSize;
    int ActualFileSize;
    int FileType;
    int RefranceCount;
    int Permission;
    char*Buffer;
    struct Inode *next;

};
typedef struct Inode INODE;
typedef struct Inode * PINODE;
typedef struct Inode ** PPINODE;

///////////////////////////////////////////////////////////
//
//  Structure name: FileTable
//  Description   : Holds the information about the opend
//                  file
//
///////////////////////////////////////////////////////////
 

struct FileTable           //This structure can be hold the information 
{                          // open file
    int ReadOffset;
    int WriteOffset;
    int Mode;
    PINODE ptrinode;

};
typedef FileTable FILETABLE;
typedef FileTable * PFILETABLE; 

///////////////////////////////////////////////////////////
//
//  Structure name: UAERA
//  Description   : Holds the information about the process
//                  
//
///////////////////////////////////////////////////////////
struct UAREA
{
    char ProcessName[20];           //this structure point to filetable
    PFILETABLE UFDT[MAXOPENFILES];  //pointer array

};

///////////////////////////////////////////////////////////
//
// 
//  : Global variables or objects used in the project 
//                  
//
///////////////////////////////////////////////////////////

BootBlock bootobj;
SuperBlock superobj;
UAREA uareaobj;

PINODE head = NULL;
///////////////////////////////////////////////////////////
//
//   Function name : InitilizeUarea
//   Description:    It is used to initilize the UAERA members
//   Author :        Pratik Dhananjay Dhayagude
//   Date :          13/01/2026
//
/////////////////////////////////////////////////////////// 
void InitilizeUAREA()
{
    strcpy(uareaobj.ProcessName,"Myexe");
    int i = 0;
    for(i=0;i<MAXOPENFILES;i++)
    {
        uareaobj.UFDT[i] = NULL;
    }
    printf("Marvellous CVFS : UAREA gets initilize succesfully\n");
    
}
///////////////////////////////////////////////////////////
//
//   Function name : InitilizeSuperBlock
//   Description:    It is initilize to super block members
//   Author :        Pratik Dhananjay Dhayagude
//   Date :          13/01/2026
// 
/////////////////////////////////////////////////////////// 
void InitilizeSuperBlock()
{
    superobj.TotalInodes = MAXINODE; 
    superobj.FreeInode  =  MAXINODE;

    printf("Marvellous CVFS : Super block gets initilize succesfully\n");
}

///////////////////////////////////////////////////////////
//
//   Function name : CreatDILB
//   Description:    It is used to creat link list of inode
//   Author :        Pratik Dhananjay Dhayagude
//   Date :          13/01/2026
//
/////////////////////////////////////////////////////////// 
void CreatDILB()
{
    int i = 1;
    PINODE newn = NULL;  //new node 
    PINODE temp = head;  //temp pointer initilize to head

    for(i = 1;i<=MAXINODE;i++)
        {
            newn  = (PINODE)malloc(sizeof(INODE));

            strcpy(newn->FileName,"\0");
            newn -> InodeNumber = i;
            newn->FileSize=0;
            newn->ActualFileSize =0;
            newn->FileType = 0;
            newn->RefranceCount=0;
            newn->Permission=0;
            newn->Buffer=0;
            newn->next = NULL;

            if(temp == NULL)  // ll is empty
            { 
                head = newn;
                temp = head;
            
            }
            else  //ll contains atleast one node
            {
                temp->next = newn;
                temp = temp->next;
            }

        }
        printf("Marvellous CVFS : DILB created Succesfully\n");
}

///////////////////////////////////////////////////////////
//
//   Function name : StartAuxillaryDataInitilization
//   Description:    It is used to call all such function which are 
//                   use to inilitize the Auxillary data
//   Author :        Pratik Dhananjay Dhayagude
//   Date :          13/01/2026
//
/////////////////////////////////////////////////////////// 

void  StartAuxillaryDataInitilization()
{
    strcpy(bootobj.information,"Booting process of Marvellous CVFS is done\n");
    printf("%s\n",bootobj.information);

    InitilizeSuperBlock();

    CreatDILB();

    InitilizeUAREA();

    printf("Marvellous CVFS : Auxillary data initilize succesfully\n");

}

///////////////////////////////////////////////////////////
//
//   Function name : DisplayHelp
//   Description:    It is used to Display help                
//   Author :        Pratik Dhananjay Dhayagude
//   Date :          14/01/2026
//
/////////////////////////////////////////////////////////// 

void DisplayHelp()
{
    printf("----------------------------------------------------------------\n");
    printf("------------------Marvellous CVFS help page-------------------- \n");
    printf("-----------------------------------------------------------------\n");

    printf("man   : It is used to display manual page\n");
    printf("clear : It is use to clear the terminal\n");
    printf("creat : It is used to creat the new file\n");
    printf("write : It is use to write the data into the file\n");
    printf("read  : It is use to read the data from the file\n");
    printf("stat  : It is use to display the statics of the file\n");
    printf("unlink: It is use to delete the file\n");
    printf("exit  : It is use to terminate Marvellous CVFS\n");

    printf("-----------------------------------------------------------------\n");

    
}
///////////////////////////////////////////////////////////
//
//   Function name : ManPageDisplay
//   Description:    It is used to Display help                
//   Author :        Pratik Dhananjay Dhayagude
//   Date :          14/01/2026
//
///////////////////////////////////////////////////////////
void ManPageDispaly(char Name[])
{
    if(strcmp("ls",Name)==0)
    {
        printf("About :It is use to display the list of all file\n");
        printf("Usage :ls\n");
    }
    else if(strcmp("man",Name)==0)
    {
        printf("About :It is use to display the manual page\n");
        printf("Usage :man command_name\n");
        printf("command_nmae:It is the name of command\n");
       
    }
    else if(strcmp("exit",Name)==0)
    {
        printf("About :It is use to terminate the shell\n");
        printf("Usage :exit\n");
        
    }
     else if(strcmp("clear",Name)==0)
    {
        printf("About :It is use to clear the shell \n");
        printf("Usage :clear\n");
        
    }
    else
    {
        printf("no manul entry for%s\n",Name);
    }
}
///////////////////////////////////////////////////////////
//
//   Function name : IsFileExist
//   Description:    It is used to cheak file already exist or not  
//   Input :         It accept file name
//   output :        It return TRUE or FALSE    
//   Author :        Pratik Dhananjay Dhayagude
//   Date :          16/01/2026
//
///////////////////////////////////////////////////////////

bool IsFileExist(
                  char*name

                )
{
    PINODE temp = head;
    bool bFlag = false;

    while(temp != NULL)
    {
        if((strcmp(name,temp->FileName)==0)&&(temp->FileType == REGULARFILE))
        {
            bFlag=true;
            break;
        }
        temp=temp->next;

    }
    return bFlag;
}



///////////////////////////////////////////////////////////
//
//   Function name : CreateFile
//   Description:    It is used to create file   
//   Input :         It accept file name and permission
//   output :        It return file descriptor    
//   Author :        Pratik Dhananjay Dhayagude
//   Date :          16/01/2026
//
///////////////////////////////////////////////////////////

int CreateFile(
               char*name,  //name of new file
               int permission //permission for that file 
              )
{
   PINODE temp = head;
   int i = 0;
   
   printf("Total number of inodes remaining :%d\n",superobj.FreeInode);
   //if name is missing 
   if(name == NULL)
   {
     return ERR_INVALID_PARAMETER;
   }
   //if the permission value is wrong
   //if permission 1-> read
   //if permission 2-> write 
   //if permission 3-> read write 
   if(permission<1||permission>3)
   {
    return ERR_INVALID_PARAMETER;
   }

   //if inodes are full

   if(superobj.FreeInode==0)
   {
    return  ERR_NO_INODE;
   }

   //if file is already preasent

   if(IsFileExist(name)==true)
   {
     return ERR_FILE_ALREADY_EXIST;
   }

   //Search empty inode
   while(temp != NULL)
   {
     if((temp -> FileType == 0))
        {
           break; 
           
        }
        temp = temp->next;

   }

    if(temp == NULL)
    {
        printf("There is no inode\n");
        return ERR_NO_INODE;
    }

    //search for empty UFDT entry
    // note = 0,1,2 reserved
    for(i =3;i<MAXOPENFILES;i++)
    {
        if(uareaobj.UFDT[i]==NULL)
        {    
            break;
        }
 
    }
    //UFDT is full
     if(i==MAXOPENFILES)
     {
        return ERR_MAX_FILES_OPEN;
     } 
   
    //Allocate memory for file table
    
    uareaobj.UFDT[i] = (PFILETABLE)malloc(sizeof(FileTable));

    //Initilize file table 

    uareaobj.UFDT[i]->ReadOffset= 0;
    uareaobj.UFDT[i]->WriteOffset= 0;
    uareaobj.UFDT[i]->Mode=permission;

    //connect file table with inode

     uareaobj.UFDT[i]->ptrinode = temp;

     //Initilize elements of inode

     strcpy(uareaobj.UFDT[i]->ptrinode->FileName,name);
     uareaobj.UFDT[i]->ptrinode->FileSize=MAXFILESIZE;
     uareaobj.UFDT[i]->ptrinode->ActualFileSize=0;
     uareaobj.UFDT[i]->ptrinode->FileType= REGULARFILE;
     uareaobj.UFDT[i]->ptrinode->RefranceCount=1;
     uareaobj.UFDT[i]->ptrinode->Permission=permission;
     //Allocate memory file for file data
     uareaobj.UFDT[i]->ptrinode->Buffer = (char*)malloc(MAXFILESIZE);

     superobj.FreeInode--;
     return i; // File descriptor  

}

///////////////////////////////////////////////////////////
//
//   Function name : LsFile()
//   Description:    It is used to list all files   
//   Input :         Nothing
//   output :        Nothing   
//   Author :        Pratik Dhananjay Dhayagude
//   Date :          16/01/2026
//
///////////////////////////////////////////////////////////

void LsFile()
{
    PINODE temp = head;
    printf("----------------------------------------------------------------\n");
    printf("----------------Marvellous File names--------------------------- \n");
    printf("-----------------------------------------------------------------\n");
    while(temp!=NULL)
    {
        if(temp->FileType!=0)
        {
        printf("%d\t%s\t%d\n",temp->InodeNumber,temp->FileName,temp->ActualFileSize);
        }
        temp = temp->next;
    }
    printf("-----------------------------------------------------------------\n");
}


///////////////////////////////////////////////////////////
//
//   Function name : unlinkFile
//   Description:    It is used to delete the file 
//   Input :         file name
//   output :        Nothing   
//   Author :        Pratik Dhananjay Dhayagude
//   Date :          22/01/2026
//
///////////////////////////////////////////////////////////

int UnlinkFile(
                char * name
              )
{
    int i=0;

    if(name==NULL)
    {
        return ERR_INVALID_PARAMETER;
    }
    if(IsFileExist(name)==false)
    {
        return ERR_FILE_NOT_EXIST;
    }
     // Travel the ufdt
    for(i=0;i < MAXOPENFILES;i++)
    {
        if(uareaobj.UFDT[i]!= NULL)
        {
            if(strcmp(uareaobj.UFDT[i]->ptrinode->FileName,name)==0)
            {
                //deallocate the memory of char*buffer
                free(uareaobj.UFDT[i]->ptrinode->Buffer);
                uareaobj.UFDT[i]->ptrinode->Buffer=NULL;

                // reset all value of inode 
                // dont deallocate the memory of inode
                uareaobj.UFDT[i]->ptrinode->FileSize=0;
                uareaobj.UFDT[i]->ptrinode->ActualFileSize=0;
                uareaobj.UFDT[i]->ptrinode->FileType=0;
                uareaobj.UFDT[i]->ptrinode->RefranceCount=0;
                uareaobj.UFDT[i]->ptrinode->Permission=0;
                
                memset( uareaobj.UFDT[i]->ptrinode->FileName,'\0',sizeof( uareaobj.UFDT[i]->ptrinode->FileName));

                // deallocate the memory of file table 

                free(uareaobj.UFDT[i]);

                // set null to ufdt
                uareaobj.UFDT[i]=NULL;
                
                //Increament of free inode

                superobj.FreeInode++;

                break; //imp

            } // end of if
        }//end of if

    }//end of for loop
    return EXECUTE_SUCCESS;
}// end of function
///////////////////////////////////////////////////////////
//
//   Function name : WriteFile
//   Description:    It is used to write the data into the file
//    Input :        File descriptor 
//                   Adress of buffer which contains the data
//                   Size of data that we want to write
//  
//   output :        Number of bytes gets succesfully writen
//   Author :        Pratik Dhananjay Dhayagude
//   Date :          22/01/2026
//
///////////////////////////////////////////////////////////

int WriteFile(int fd ,
              char *data,
              int size

             )
{

    printf("File descriptor : %d\n",fd);
    printf("Data that we want to write:%s\n",data);
    printf("Number of bytes that we want to write:%d\n",size);

    if(fd<0||fd>MAXOPENFILES) // INvalid fd
    {
        return ERR_INVALID_PARAMETER;
    }
    if(uareaobj.UFDT[fd]==NULL) // fd pointes to null
    {
        return ERR_FILE_NOT_EXIST;
    }
    // there is no permission to write
    if(uareaobj.UFDT[fd]->ptrinode->Permission < WRITE)
    {
        return ERR_PERMISSION_DENIED;

    }
    /// insufficient space
    
    if(MAXFILESIZE - uareaobj.UFDT[fd]->WriteOffset<size)
    {
        return ERR_INSUFFICIENT_SPACE;
    }
    // write the data into the file
    
    strncpy(uareaobj.UFDT[fd]->ptrinode->Buffer + uareaobj.UFDT[fd]->WriteOffset,data,size);
    
    // update the write offset
    
    uareaobj.UFDT[fd]->WriteOffset= uareaobj.UFDT[fd]->WriteOffset+size;
    //update the actual file size
    uareaobj.UFDT[fd]->ptrinode->ActualFileSize =  uareaobj.UFDT[fd]->ptrinode->ActualFileSize+size;
    return size;

}

///////////////////////////////////////////////////////////
//
//   Function name : ReadFile
//   Description:    It is used to read the data into the file
//   Input :         File descriptor 
//                   Adress of empty Buffer which contains the data
//                   Size of data that we want to read
//  
//   output :        Number of bytes gets succesfully read
//   Author :        Pratik Dhananjay Dhayagude
//   Date :          22/01/2026
//
///////////////////////////////////////////////////////////

int ReadFile(
               int fd,
               char*data,
               int size
            )
{
    //Invalid fd
    if(fd<0||fd>MAXOPENFILES)
    {
        return ERR_INVALID_PARAMETER;
    }
    if(data ==NULL)
    {
        return ERR_INVALID_PARAMETER;
    }
    if(size <= 0)
    {
        return ERR_INVALID_PARAMETER;
    }
    if(uareaobj.UFDT[fd]==NULL)
    {
        return ERR_FILE_NOT_EXIST;
    }
    //filter for permission

    if(uareaobj.UFDT[fd]->ptrinode->Permission<READ)
    {
        return ERR_PERMISSION_DENIED;
    }

    //Insufficient data 

    if(MAXFILESIZE-uareaobj.UFDT[fd]->ReadOffset<size)
    {
        return ERR_INSUFFICIENT_DATA;
    }

    // read the data

    strncpy(data,uareaobj.UFDT[fd]->ptrinode->Buffer+uareaobj.UFDT[fd]->ReadOffset,size);

    //update the read ofset 

    uareaobj.UFDT[fd]->ReadOffset = uareaobj.UFDT[fd]->ReadOffset+size;

    return size;

}


///////////////////////////////////////////////////////////
//
//  : Entry point function of the project
//
///////////////////////////////////////////////////////////
int main()
{
    char str[80]={'\0'};
    char Command[5][20]={{'\0'}};
    char InputBuffer[MAXFILESIZE]={'\0'};
    char * EmptyBuffer = NULL;

    int iCount = 0;
    int iRet = 0;

    StartAuxillaryDataInitilization();

    printf("----------------------------------------------------------------\n");
    printf("----------------Marvellous CVFS start succesfully -------------------- \n");
    printf("-----------------------------------------------------------------\n");
    //Infinite Listening shell
    while(1)
    {
        fflush(stdin);

        strcpy(str,"");

        printf("\nMarvellous CVFS : > ");
        fgets(str,sizeof(str),stdin);
        iCount = sscanf(str,("%s %s %s %s %s"),Command[0],Command[1],Command[2],Command[3],Command[4]);
       
        fflush(stdin);
        if(iCount == 1)
        { 
           //Marvellous CVFS : > exit
           if(strcmp("exit",Command[0]) == 0)
           {
             printf("thanku for using marvellous CVFS \n");
             printf("Deallocating all the allocated recources\n");
             break;
           }
           //Marvellous CVFS : > ls
           else if(strcmp("ls",Command[0])==0)
           {
             LsFile();
           } 
           //Marvellous CVFS : > help
           else if(strcmp("help",Command[0])==0)
           {
             DisplayHelp(); 
           }
           //Marvellous CVFS : > clear
           else if(strcmp("clear",Command[0])==0)
           {
                #ifdef _WIN32
                system("cls");
                #else
                system("clear");
                #endif
             
           }
           

        }//End of if

        else if(iCount == 2)
        {
            //Marvellous CVFS : > man ls
            if(strcmp("man",Command[0])==0)
            {
                ManPageDispaly(Command[1]);

            }

            //Marvellous CVFS : > unlink demo.txt (unlink to the file)
            if(strcmp("unlink",Command[0])==0)
            {
                iRet = UnlinkFile(Command[1]);
                if(iRet==ERR_INVALID_PARAMETER)
                {
                    printf("Error:Invalid parameter\n");
                }
                if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : Uable to delete as there is no such file\n");
                }
                if(iRet == EXECUTE_SUCCESS);
                {
                    printf("File gets succesfully deleted\n");
                }

            }
            //MArvellous cvfs > write 2
            else if(strcmp("write",Command[0])==0)
            {
                printf("Enter the data that you want to write:\n");
                fgets(InputBuffer,MAXFILESIZE,stdin);

                iRet = WriteFile(atoi(Command[1]),InputBuffer,strlen(InputBuffer)-1);
                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error: Invalid parameter\n");

                }
                else if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : There is no such file\n");
                }
                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error : As there is no such permission\n");
                }
                else if(iRet == ERR_INSUFFICIENT_SPACE)
                {
                    printf("Error : There is no space\n");
                }
                else
                {
                    printf("%d Bytes gets succesfully written\n",iRet);
                }
            }
            else 
            {
                printf("there is no such command\n");
            }


        }//End of else if 2

        else if(iCount == 3)
        {
            //Marvellous CVFS : > creat demo.txt 3
            if(strcmp("creat",Command[0])==0)
            {
                iRet = CreateFile(Command[1],atoi(Command[2]));
                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Unable to creat the file as parameter are invalid\n");
                    printf("Please refer man page\n");
                }

                if(iRet == ERR_NO_INODE)
                {
                    printf("Error : Unable to creat file as there are no inode\n");
                    
                }

                if(iRet == ERR_FILE_ALREADY_EXIST)
                {
                    printf("Error : Unable to create file because the file is already preasent\n");
                }

                if(iRet == ERR_MAX_FILES_OPEN)
                {
                    printf("Error : Unable to create file\n");
                    printf("Max opend file limit reached\n");
                }

                printf("File gets succesfully created with fd  %d\n",iRet);

            }
            // Marvellous cvfs> read 3 10
            if(strcmp("read",Command[0])==0)
            {
                EmptyBuffer=(char*)malloc(sizeof(atoi(Command[2])));
                iRet  = ReadFile(atoi(Command[1]),EmptyBuffer,atoi(Command[2]));
                if(iRet == ERR_INVALID_PARAMETER)
                {
                    printf("Error : Inbvalid parameter \n");
                }
                else if(iRet == ERR_FILE_NOT_EXIST)
                {
                    printf("Error : FIle not exist\n");
                }
                else if(iRet == ERR_PERMISSION_DENIED)
                {
                    printf("Error : Permission denied\n");

                }
                else if(iRet == ERR_INSUFFICIENT_DATA)
                {
                    printf("Error : Insufficient data\n");
                }
                else
                {
                    printf("Read operation is succesfull\n");
                    printf("Data from file os :%s\n",EmptyBuffer);
                    free(EmptyBuffer);
                }

            }
           
            else
            {
                printf("There is no such file\n");

            }

        }//End of else if 3

        else if(iCount == 4)
        {

        }//End of else if 4
        else
        {
            printf("Command not found\n");
            printf("please refer help optation to get more information\n");
        } // End of Else
  
    } // End of while

    return 0;
}//End of main

