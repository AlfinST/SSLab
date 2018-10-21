#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>

#define dcnt (*NowRoot).data.dno
#define fcnt (*NowRoot).data.fno
struct node
{
    char PresentName[NAME_MAX+1];
    char fname[10][NAME_MAX+1];
    char dirname[10][NAME_MAX+1];
    int fno,dno;
    char currAdd[NAME_MAX+1];
};

struct direct
{
    struct node data;
    struct direct *parent;
    struct direct *roots[10];
};

struct direct* newDirectory()
{
    return (struct direct*)malloc(sizeof(struct direct));
}

void main()
{

    struct direct MasterRoot;
    struct direct *NowRoot = &MasterRoot;
    int i,ch,k,ext=0;
    int jmp=0,status;
    struct stat st = {0};
    char f[NAME_MAX+1],ftemp[NAME_MAX+1], d[NAME_MAX+1],dname[NAME_MAX+1];

    MasterRoot.data.fno=0;
    dcnt=0;
    fcnt=0;
    MasterRoot.parent=NULL;
    strcpy(MasterRoot.data.currAdd,".");
    strcpy(MasterRoot.data.PresentName ,"Master");

    while(1)
    {
        status=0;
        printf("\nIn %s\n",(*NowRoot).data.PresentName);

        printf("\n 1. Create Directory\t 2. Create File\t 3. Delete File");
        printf("\t4. Search File \t \t 5. Display \t 6. Change Directory\t7. Test\t 8.Exit \n Enter your choice : ");
        scanf("%d",&ch);
        printf("**////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////**\n");
        switch(ch)
        {
                case 1: printf("\n Enter name of directory -- ");
                        scanf("%s",dname);
                        strcpy((*NowRoot).data.dirname[dcnt],dname);
                        struct direct *NewDir;
                        struct stat st = {0};
                        NewDir=newDirectory();
                        NewDir->parent= NowRoot;
                        (*NowRoot).roots[dcnt]=NewDir;
                        NewDir->data.fno=0;
                        NewDir->data.dno=0;

                        sprintf(NewDir->data.currAdd,"%s/%s",(*NowRoot).data.currAdd,dname);
                        printf("NewDirCurrAdd::%s\n",NewDir->data.currAdd);
                        strcpy(NewDir->data.PresentName,dname);
                        dcnt++;
                        char libPath[PATH_MAX+1];
                        snprintf(libPath, PATH_MAX + 1, "%s/%s/", (*NowRoot).data.currAdd,dname);
                        printf("\n\n Path::%s\n",libPath );
                        
                        if (stat(NewDir->data.currAdd, &st) == -1) 
                        {
                            printf("stat OK\n");
                            if(mkdir(libPath, 0755) != -1)
                            {
                                strcpy(ftemp,libPath);
                                FILE *fLib = fopen(strcat(ftemp,"/temp.txt"), "w+");
                                fclose(fLib);
                                status=remove(ftemp);
                                if(status==0)
                                    printf("properly done!\n");
                                printf("closed file!\n");
                            }
                            else    
                            {
                                perror("mkdir: ");
                            }
                        }                        

                        printf("Directory created ,(%d)",dcnt);
                break;
                case 2:
                                 printf("\nEnter name of the file -- ");
                                 scanf("%s",f);
                                 strcpy((*NowRoot).data.fname[fcnt],f);
                                 fcnt++;
                                 printf("CurrAdd::%s\nFilename::%s\n",(*NowRoot).data.currAdd,f);
                                 snprintf(ftemp, PATH_MAX + 1, "%s/", (*NowRoot).data.currAdd);
                                 FILE * fPointer = fopen( strcat(ftemp,f),"w+");
                                 fclose(fPointer);
                                 printf("File created(%d)\n\n",fcnt);
                break;
                   
                case 3: 
                        printf("Enter name of the file -- ");
                        scanf("%s",f);

                        for(k=0,jmp=0;k<fcnt;k++)
                        {   
                            if(strcmp(f, (*NowRoot).data.fname[k])==0)
                                {
                                    strcpy((*NowRoot).data.fname[k],(*NowRoot).data.fname[fcnt-1]);
                                    fcnt--;
                                    if(remove(f)==0)
                                    printf("File %s is deleted ",f);
                                    jmp=1;
                                }
                        }

                        if(jmp==0)
                            printf("File %s not found",f);
                break;

                case 4: 
                         printf("Enter name of the file -- ");
                         scanf("%s",f);
                        for(k=0,jmp=1;k<fcnt;k++)
                        {   

                            if(strcmp(f, (*NowRoot).data.fname[k])==0)
                            {   
                                printf("File %s is Found! ",f);
                                jmp=0;
                            }
                            if(jmp==0)
                                break;
                        }

                        if(jmp==1)
                            printf("File %s not found",f);
                break;
                case 5:
                        if(dcnt==0)
                        {
                            printf("\nNo Directory\n ");
                        }
                        if(fcnt==0)
                        {
                            printf("\nNo Files\n ");
                        }
                        for(i=0;i<dcnt;i++)
                        {
                            printf("\nDirectory:%s",(*NowRoot).data.dirname[i]);
                            }
                        printf("\n");
                        for(k=0;k<fcnt;k++)
                        {
                            printf("File:%s\n",(*NowRoot).data.fname[k]);
                        } 
                        
                        
                break;
                case 6:
                        printf("Change to Directory(s) :\n");
                        for(i=0;i<dcnt;i++)
                            {
                                printf("\nDirectory:%s",(*NowRoot).data.dirname[i]);
                             }
                        printf("\nFor Previous Directory use ~\n");
                        printf("\nChoose:");
                        scanf("%s",d);
                        if( d[0]=='~')
                            {
                                if((*NowRoot).parent !=NULL)
                                NowRoot=(*NowRoot).parent;
                            }
                        else
                            for(i=0;i<dcnt;i++)
                                {
                                    
                                    strcpy(f,(*NowRoot).data.dirname[i]); 
                                    if(strcmp(d,f) == 0)   
                                        NowRoot=(*NowRoot).roots[i];  
                                    
                                }
                break;
                case 7:
                        printf("Parent : %s\n",(*NowRoot).parent->data.PresentName );
                         for(i=0;i<dcnt;i++)
                        {
                         printf("Dir name:%s\n ",(*NowRoot).data.dirname[i]);
                         printf("Root Name:%s\n\n",((*NowRoot).roots[i])->data.PresentName);   
                        }
                break;
                default:ext=1;
            }                               
        
         printf("\n/\n///////////////////////////////////////////////////////////////////////////////////////////////////////\n");
        if(ext)
            break;
    }

}