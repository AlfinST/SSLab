#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <limits.h>

#define dcnt (*NowRoot).data.dno
#define fcnt (*NowRoot).data.fno
#define Tdcnt (*DNode).data.dno
#define Tfcnt (*DNode).data.fno

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
    struct direct *roots[NAME_MAX+1];
};

//struct direct *TNowRoot;

int DelFile(struct direct *NowRoot,char *f)
{
    int k,jmp;
    char ftemp[NAME_MAX+1];
    snprintf(ftemp,PATH_MAX +1,"%s/%s",(*NowRoot).data.currAdd,f);
    printf("\n\tFile Add: %s",ftemp);
    for(k=0,jmp=0;k<fcnt;k++)
    {  
        if(strcmp(f, (*NowRoot).data.fname[k])==0)
            {
                strcpy((*NowRoot).data.fname[k],(*NowRoot).data.fname[fcnt-1]);
                fcnt--;
                
                if(remove(ftemp)==0)
                printf("\nFile %s is deleted ",f);
                jmp=1;
            }
    }
    return jmp;
}


//struct direct *stack[MAX_INPUT+1];
struct direct *queue[MAX_INPUT+1];
int StkCntr=-1;
int Qmax=-1;
//int StkCntr=-1;
void AddQueue(struct direct *NowRoot)
{
    Qmax++;
    queue[Qmax]=NowRoot;
}


void Deep(struct direct *DNode)
{
    int tempFcntr,i,j,k,n;
    struct direct *temp;
    temp=DNode;
    //printf("\n\tIn Deep Pointing %s\n",(*DNode).data.PresentName);
    if(StkCntr==-1)
    {
        return;
    }
    else
    {
        if(Tdcnt==0)
        {  
            tempFcntr=Tfcnt;
            printf("\nA leaf node!\n %s \t %d",(*DNode).data.currAdd,(*DNode).data.fno);
            for( i=0,j=0;i<tempFcntr;i++)
            {   
                
                j=DelFile(DNode,(*DNode).data.fname[i]);
                
                if(j==0)
                    printf("\n%s not deleted",(*DNode).data.fname[i]);
            }
            Tfcnt=0;
            rmdir((*DNode).data.currAdd);
            StkCntr--;
            n=((*DNode).parent)->data.dno;
            if( ((*DNode).parent)!= NULL)
                {   
                    //printf("something worked!\n");
                    for(i=0;i<n;i++)
                            if( ((*DNode).parent)->roots[i] == (DNode))
                                {   
                                    for(k=0;k<=Qmax;k++)
                                    {
                                        if(DNode == queue[k])
                                        {
                                            queue[k]=queue[Qmax];
                                            Qmax--;
                                            printf("\nRemoved From queue!");
                                        }
                                    }
                                    printf("\nDirectoy %s Deleted !\n",(*DNode).data.PresentName);
                                    ((*DNode).parent)->roots[i] = ((*DNode).parent)->roots[n-1];
                                    ((*DNode).parent)->data.dno--;
                                    free(DNode);

                                }
                }
            Deep((*temp).parent);
        }
        else
        {
            StkCntr++;
            //stack[StkCntr]=(*DNode).roots[0];
            Deep((*DNode).roots[0]);
        }
    }
}

void DelDepth(struct direct *DNode)
{   printf("\nIn DelDepth");
    StkCntr++;
    //stack[StkCntr]=DNode;
    Deep(DNode);
    printf("Done!\n");
}

void Search()
{
    int i,k,jmp;
    char f[NAME_MAX+1];
    struct direct *NowRoot;
    printf("Enter name of the file -- ");
    scanf("%s",f);  
    for (i=0;i<=Qmax;i++)
    {
        NowRoot=queue[i];
        printf("%s !!\n",(*NowRoot).data.PresentName);
        for(k=0,jmp=1;k<fcnt;k++)
        {   

            if(strcmp(f, (*NowRoot).data.fname[k])==0)
            {   
                printf("\nFile %s is Found in %s\n",f,(*NowRoot).data.currAdd);
                jmp=0;
            }

            if(jmp==0)
                break;
        }

        if(jmp==0)
            break;     
    }
    if(jmp==1)
        printf("File  Not Found\n");
}

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
    AddQueue(&MasterRoot);

    while(1)
    {
        status=0;
        printf("\nIn %s\n",(*NowRoot).data.PresentName);

        printf("\n 1. Create Directory\t 2. Create File\t 3. Delete File");
        printf("\t4. Search File \t \t 5. Display \t 6. Change Directory\t7. Destroy Directory\t 8.Exit \n Enter your choice : ");
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
                        AddQueue(NewDir);

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
                        //sprintf(ftemp,"%s/%s",(*NowRoot).data.currAdd,f);
                        //printf("Adress is :%s\n",ftemp);  
                        jmp = DelFile(NowRoot,f);
                        if(jmp==0)
                            printf("File %s not found",f);
                break;

                case 4: 
                        Search();
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
                        if(dcnt!=0)
                        {
                            printf("Enter Directory to Destroy:");
                            for(i=0;i<dcnt;i++)
                            {
                                printf("\nDirectory:%s",(*NowRoot).data.dirname[i]);
                            }
                            printf("\n::");
                            scanf("%s",dname);
                            for(i=0,k=0;i<dcnt;i++)
                                {
                                    strcpy(f,(*NowRoot).data.dirname[i]); 
                                    if(strcmp(dname,f) == 0) 
                                     {
                                        DelDepth((*NowRoot).roots[i]);
                                       // (*NowRoot).roots[i]=(*NowRoot).roots[dcnt-1];
                                    }
                                }
                        }
                        else
                            printf("No Directorites to destroy");
                break;
                default:ext=1;
            }                               
        
         printf("\n/\n///////////////////////////////////////////////////////////////////////////////////////////////////////\n");
        if(ext)
            break;
    }

}