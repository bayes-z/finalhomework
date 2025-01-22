#include <stdio.h>
#include <string.h>
#include <stdlib.h>


void func_cp()//复制模块
{
    //定义数组存储文件的当前路径和目标路径
    char filepath1[40]="NULL";
    char filepath2[40]="NULL";
    int result;
    printf("请输入文件当前路径：\n");
    scanf("%s",filepath1);
    //printf("%s",filepath1);
    printf("请输入文件目标路径：\n");
    scanf("%s",filepath2);
    //printf("%s",filepath2);
    //根据用户输入的信息整合命令语句
    char command[100]="NULL";
    sprintf(command,"cp %s %s",filepath1,filepath2);
    result = system(command);
    if (result==0)
        printf("文件已复制\n");
    else
        printf("文件复制失败\n"); 
}
void func_rm()//删除模块
{   int result;
    char file_name[40]="NULL" ;
    char file_path[40]="NULL" ;
    printf("请输入文件路径：\n");
    scanf("%s",file_path);
    char command1[100]="NULL";
    sprintf(command1,"rm %s",file_path);
    result = system(command1);
    //判断指令是否成功执行
    if (result==0)
        printf("文件已删除\n");
    else
        printf("文件删除失败\n"); 
    
}
void func_tar()//压缩模块
{   
    int result;
    char command[100]="NULL";
    char current_filepath[40]="NULL";
    char target_filepath[40]="NULL";
    char file_name[40]="NULL";
    printf("请输入待压缩文件名或目录的归档文件名");
    scanf("%s",file_name) ;
    printf("请输入待压缩文件或目录的地址");
    scanf("%s",current_filepath) ;
    printf("请输入文件目标位置");
    scanf("%s",target_filepath) ;
    if (strcmp(current_filepath, "./") == 0)
    {
        memset(current_filepath,0,sizeof(current_filepath));
        strcpy(current_filepath,".");
    }
    sprintf(command,"tar -czvf %s/%s %s",target_filepath,file_name,current_filepath);
    result = system(command);
    if (result==0)
        printf("文件已压缩\n");
    else
        printf("文件压缩失败\n"); 
}
void func_untar()//解压模块
{
    int result;
    char source_filepath[40]="NULL";
    char target_filepath[40]="NULL";
    char command[100]="NULL";
    printf("请输入待解压文件或目录的地址");
    scanf("%s",source_filepath) ;
    printf("请输入目标目录地址");
    scanf("%s",target_filepath) ;
    if(strcmp(target_filepath, "./") == 0)
    {
        sprintf(command,"tar -xzvf %s ",source_filepath);
        result = system(command); 
    }
    else
    {
    sprintf(command,"tar -xzvf %s -C %s ",source_filepath,target_filepath);
    result = system(command);  
    }
    if (result==0)
        printf("文件已解压\n");
    else
        printf("文件解压失败\n");           
    }
int main()
{
    char command[100];  // 假设输入的命令长度不超过100

    while(1)
    {
        printf("欢迎使用文件管理系统\n请根据需求输入命令并按照提示进行操作(copy/delete/zip/unzip/exit)：");
        scanf("%s", command);  // 读取字符串类型的命令

        // 使用if...else结构进行判断
        if (strcmp(command, "copy") == 0)
            func_cp();  // 如果输入的是"command1"，则执行func1函数
        else if (strcmp(command, "delete") == 0)
            func_rm();  // 如果输入的是"command2"，则执行func2函数
        else if (strcmp(command, "zip") == 0)
            func_tar();  // 如果输入的是"command3"，则执行func3函数
        else if (strcmp(command, "unzip") == 0)
            func_untar();  // 如果输入的是"command4"，则执行func4函数
        else if (strcmp(command, "exit") == 0)
            break;
        else
            printf("未知命令\n");  // 如果输入的命令不匹配，则输出未知命令
    }
    return 0;
}