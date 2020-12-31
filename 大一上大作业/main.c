#include<stdio.h>
#include<stdlib.h>
#include<string.h>

//结构体之数据
struct student
{
    char name[10];//名字
    int score;//分数
    //这里只保存一个分数，你有需要可以自己加,比如高数，c语言啥的
    int number;//号
    int age;//年纪
};

//结构体之指针
struct Node
{
    struct student data;
    struct Node *next;//指针，灵魂
};
typedef struct Node LinkList;

///--------------------------------------------------------------------------函数头区域
//全体使用void ,没有使用返回头指针。可以但是没必要（其实是没写而已
void regard();//关于
void help_help();//帮助
void meum();//菜单
void key_in(LinkList *head_student);//选择输入
void add_headnode(LinkList *head_student);//插入节点（头插）
void show_student(LinkList *head_student);//浏览
void delete_student(LinkList *head_student);//删除
void change_student(LinkList *head_student);//修改
void save(LinkList *head_student);//保存
void refresh(LinkList *head_student);//手动读取历史文件
///----------------------------------------------------------------------------

int main()
{
    LinkList *head_student=NULL;//主，表头
    head_student=(LinkList *)malloc(sizeof(LinkList));
    if(head_student==NULL)
    {
        printf("分配头节点出错!");
        exit(0);
    }
    memset(head_student,0,sizeof(LinkList));//清空
    head_student->next=NULL;
    while(1)
    {
        system("cls");//清屏
        meum();
        key_in(head_student);
        printf("\n     下一步操作:");
        printf("\n     1.返回主界面");
        printf("\n     2.退出系统");
        printf("\n     请输入操作:");
        int i;//现定义，现用
        scanf("%d",&i);
        if(i==2)
            break;
    }

    system("pause");
    return 0;//好习惯！
}



void meum()
{
    printf("\n   *****************************   \n");
    printf("         学生信息管理系统          \n");
    printf("   *****************************   \n");
    printf("           系统菜单功能            \n");
    printf("   *****************************   \n");
    printf("          1.查看学生信息           \n");
    printf("          2.添加学生信息           \n");
    printf("          3.删除学生信息           \n");
    printf("          4.修改学生信息           \n");
    printf("          5.保存学生信息           \n");
    printf("          6.刷新学生信息           \n");
    printf("          7.关于                  \n");
    printf("          8.帮助                  \n");
    printf("          0.退出系统               \n");
}

void key_in(LinkList *head_student)
{
    int num;
    int key;
    printf("\n\n请输入菜单选项:");
    scanf("%d",&num);
    switch (num)
    {
        case 0:
            for(key=1;key<=3;key++){
                printf("Thanks for you!!\n Bye bye\n");
            }
            break;
        case 1:
            show_student(head_student);
            break;
        case 2:
            add_headnode(head_student);
            break;
        case 3:
            delete_student(head_student);
            break;
        case 4:
            change_student(head_student);
            break;
        case 5:
            save(head_student);
            break;
        case 6:
            refresh(head_student);
            break;
        case 7:
            regard();
            break;
        case 8:
            help_help();
            break;
        default:
            printf("请你认真输入，好吧！\n");
    }
}

//头插，这里先写头插法
void add_headnode(LinkList *head_student)
{
    LinkList *node=NULL;
    LinkList *temp=head_student->next;
    node=(LinkList *)malloc(sizeof(LinkList));
    if(node==NULL)
    {
        printf("分配节点出错!");
        exit(0);
    }
    memset(node,0,sizeof(LinkList));
    printf("\n请输入学生学号:");
    scanf("%d",&node->data.number);
    printf("\n请输入学生名:");
    scanf("%s",node->data.name);
    printf("\n请输入学生成绩:");
    scanf("%d",&node->data.score);
    printf("\n请输入学生年龄:");
    scanf("%d",&node->data.age);

    head_student->next=node;
    node->next=temp;
}

void show_student(LinkList *head_student)
{
    LinkList *p=head_student->next;
    if(p==NULL){
        printf("Error!");
        return;
    }
    printf("\n    **************************      \n");
    printf("            学生信息                \n");
    printf("    **************************      \n");
    printf("   \t学号\t   姓名\t   成绩\t   年龄\t\n");
    while(p!=NULL)
    {
        printf("\t%d\t   %s\t    %d\t   %d\t\n",p->data.number,p->data.name,p->data.score,p->data.age);
        p=p->next;
    }
}

void delete_student(LinkList *head_student)//删除
{
    int x=0;//判断的关键
    int number;//按学号
    char name[10];//按名字
    LinkList *temp,*p;
    temp=head_student->next;
    while(1)
    {
        //我们还是担心有人乱输，所以不输入1/2不准出去
        printf("\n    请选择:");
        printf("\n    【1】.按学号删除!");
        printf("\n    【2】.按姓名删除!");
        printf("\n    请输入选择:");
        scanf("%d",&x);
        if(x==1 || x==2)
            break;
        else
            printf("\n   输入错误,请重新输入!");
    }
    if(x==1)///按学号
    {
        printf("\n    请输入要删除的学生学号:");
        scanf("%d",&number);
        while(temp->data.number!=number && temp->next!=NULL)//找到了或者找空了
        {
            p=temp;
            temp=temp->next;
        }
        if(temp->data.number==number)
        {
            p->next=temp->next;
            //被删除节点的前一个直接连接后一个
            free(temp);//释放！！
        }
        ///这就删除成功
        else//未成功
        {
            printf("\n没有所要删除的学生学号!");
        }
    }
    else if(x==2)//按名字
    {
        printf("\n请输入要删除的学生名字:");
        scanf("%s",name);
        while(strcmp(temp->data.name,name)!=0 && temp->next!=NULL)//找到了或者找空了
        {
            p=temp;
            temp=temp->next;
        }
        if(strcmp(temp->data.name,name)==0)
        {
            p->next=temp->next;
            free(temp);
        }
        else
        {
            printf("\n没有要删除的学生姓名!");
        }
    }
    //过程基本相同，只是比较的东西不一样
}

void change_student(LinkList *head_student)
{
    int x=0;
    int number;
    char name[10];
    LinkList *temp;
    temp=head_student->next;
    while(1)
    {
        //老规矩，不输入1/2不让走
        printf("\n    请选择:");
        printf("\n    1.知道要修改学生的学号");
        printf("\n    2.知道要修改学生的名字");
        printf("\n    请输入选择:");
        scanf("%d",&x);
        if(x==1 || x==2)
            break;
        else
            printf("\n 输入错误,请重新输入!");
    }
    if(x==1)
    {
        printf("\n    请输入要修改学生的学号:");
        scanf("%d",&number);
        while(temp->data.number!=number && temp->next!=NULL)
        {
            temp=temp->next;
        }
        if(temp->data.number==number)
        {
            printf("\n已经找到要修改学生的信息!");
        }
        else
        {
            printf("\n没有要修改学生的学号!");
            return;
            //没找到，回去
        }
    }
    else if(x==2)
    {
        printf("\n请输入要修改学生的名字:");
        scanf("%s",name);
        while(strcmp(temp->data.name,name)!=0 && temp->next!=NULL)
        {
            temp=temp->next;
        }
        if(strcmp(temp->data.name,name)==0)
        {
            printf("\n已经找到要修改学生的信息!");
        }
        else
        {
            printf("\n没有要修改学生的姓名!");
            return;
            //没找到，回去
        }
    }
    printf("\n     ************************");
    printf("\n   姓名:%s  学号:%d  成绩:%d  年龄:%d",temp->data.name,temp->data.number,temp->data.score,temp->data.age);
    do{
        printf("\n     请选择:");
        printf("\n     1.修改学号!");
        printf("\n     2.修改名字!");
        printf("\n     3.修改成绩!");
        printf("\n     4.修改年龄!");
        printf("\n     请输入选择:");
        scanf("%d",&x);
    }while(x<1 || x>4);//不输入正确不准出去
    if(x==1)
    {
        printf("\n     请输入修改后的学号:");
        scanf("%d",&temp->data.number);
    }
    if(x==2)
    {
        printf("\n     请输入修改后的名字:");
        scanf("%s",temp->data.name);
    }
    if(x==3)
    {
        printf("\n     请输入修改后的成绩:");
        scanf("%d",&temp->data.score);
    }
    if(x==4)
    {
        printf("\n     请输入修改后的年龄:");
        scanf("%d",&temp->data.age);
    }
}

//将新的数据读入末尾
void save(LinkList *head_student)
{
    FILE *fp;
    int i=0;
    LinkList *temp;
    temp=head_student->next;
    if((fp=fopen("student.txt","w"))==NULL)
    {
        printf("\n无法打开文件!");
        exit(0);
    }
    while(temp!=NULL)
    {
        fprintf(fp,"%d %s %d %d \n",temp->data.number,temp->data.name,temp->data.score,temp->data.age);
        temp=temp->next;
    }
    fclose(fp);
}


//将文档中的数据读出
void refresh(LinkList *head_student) {
    FILE *fp;
    LinkList *node=NULL;
    LinkList *temp=head_student->next;
    temp=(LinkList *)malloc(sizeof(LinkList));
    node=(LinkList *)malloc(sizeof(LinkList));
    if(node==NULL)
    {
        printf("分配节点出错!");
        exit(0);
    }
    memset(node,0,sizeof(LinkList));//清空
    fp=fopen("student.txt","r+");//只读打开文件
    head_student->next=node;
    if(fp==NULL)
    {
        printf("\n无法打开文件!");
        exit(0);
    }
    while(!feof(fp))
    {
        fscanf(fp,"%d %s %d %d",&temp->data.number,temp->data.name,&temp->data.score,&temp->data.age);//文本形式读出单个节点
        node->next=temp;
        node=temp;
        temp=(LinkList *)malloc(sizeof(LinkList));
        if(temp==NULL)
        {
            printf("分配节点出错!");
            exit(0);
        }
        memset(temp,0,sizeof(LinkList));//清空一次
    }
    printf("\n成功刷新学生信息!");
}

void help_help(){
    printf("\n【帮助】\n");
    printf("这是一个简易的学生管理系统,\n"
           "他初步拥有添加，显示，删除，\n"
           "修改学生信息的功能。");
    printf("关于文件读写：\n"
           "你可以读取本来存在的信息，\n"
           "并对其进行操作。\n"
           "但是，由于文件保存时每次\n都会覆盖原有数据，\n所以你自己看着吧。");
    printf("做的比较简陋，很抱歉");
    system("pause");
}

void regard(){
    FILE  *fp;
    int i=0;
    char temp[1000];
    if(!(fp=fopen("abort.txt","r")))//判断能否打开abort.txt
    {
        printf("打开文件失败...\n");
        printf("按任意键继续...\n");
        system("pause");
        return ;
    }
    while((temp[i]=fgetc(fp))!=EOF)//将文件中的数据储存到cb中
    {
        i++;
    }
    temp[i]='\0';//这是一个字符串，我们需要手动加入/0
    printf("%s\n",temp);
    printf("按任意键继续...\n");
    system("pause");
}