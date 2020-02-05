#include "main.h"

int main()
{
    system("color 3f");
    HuffmanTree HT=NULL;//哈夫曼树
    HuffmanCode HC;//各个字符的编码
    int count = 0;//字符数
    int e;//操作变量
    char hfmtree[Init_Max_Value]="HfmTree.txt";//哈夫曼树文件
    char tobetran[Init_Max_Value] = "ToBeTran.txt";//发送文件
    while (1) {
    printf("*****************************************************************\n");
    printf("*********************** 请先构建编码规则！***********************\n");
    printf("***********************                   ***********************\n");
    printf("*********************** 1：构建编码规则   ***********************\n");
    printf("*********************** 2：发送端         ***********************\n");
    printf("*********************** 3：接收端         ***********************\n");
    printf("*********************** 0：退出系统       ***********************\n");
    printf("*****************************************************************\n");
    printf("请输入你想进行的操作：");
    scanf_s("%d", &e);
    
        switch (e)
        {
        case 1:
            while (1) {
                int flag = 0;
                printf("*********************************************************************\n");
                printf("*********************** 1：由哈夫曼树文件读入 ***********************\n");
                printf("*********************** 2：由用户输入构建     ***********************\n");
                printf("*********************** 3：由发送文件构成     ***********************\n");
                printf("*********************** 4：打印哈夫曼树       ***********************\n");
                printf("*********************** 0：返回上一级菜单     ***********************\n");
                printf("*********************************************************************\n");
                printf("请输入你想进行的操作：");
                scanf_s("%d", &e);
                switch (e)
                {
                case 1:
                    system("cls");
                    printf("请输入构建哈夫曼树文件！\n");
                    scanf_s("%s", hfmtree, Init_Max_Value);
                    //判断输入的哈夫曼树文件是否存在
                    if (_access(hfmtree, 0)) {
                        printf("未检测到hfmTree文件！\n");
                        count = CreatHFMTree(HT, hfmtree);//构建哈夫曼树
                    }
                    break;
                case 2:
                    system("cls");
                    count = CreatHFMTree(HT, hfmtree);
                    break;
                case 3:
                    system("cls");
                    printf("请输入需要发送的文件名！\n");
                    scanf_s("%s", tobetran, Init_Max_Value);
                    //判断发送文件是否存在
                    if (_access(tobetran, 0)) {
                        printf("未检测到发送文件！\n");
                        flag = 1;
                        break;
                    }
                    FileCreate(HT, tobetran);//从文件构建哈夫曼树
                    count = 58;
                    break;
                case 4:
                    system("cls");
                    PrintHFMTree(HT, count, hfmtree);//打印哈夫曼树
                    break;
                case 0:
                    flag = 1;
                    break;
                default:
                    break;
                }
                if (flag) break;
                CharCoding(HT, count, HC, hfmtree);//各个字符的编码
                printf("*****************************************************************\n");
                printf("**************************  构建成功！  *************************\n");
            }
            break;
        case 2:
            system("cls");
            while (1) {
                int flag = 0;
                printf("*****************************************************************\n");
                printf("*********************** 1：编码发送       ***********************\n");
                printf("*********************** 0：返回上一级菜单 ***********************\n");
                printf("*****************************************************************\n");
                printf("请输入你想进行的操作：");
                scanf_s("%d", &e);
                switch (e)
                {
                case 1:
                    system("cls");
                    HFMCoding(HT, HC, count);//编码
                    break;
                case 0:
                    flag = 1;
                    break;
                default:
                    break;
                }
                if (flag) break;
            }
            break;
        case 3:
            system("cls");
            while (1) {
                int flag = 0;
                printf("*****************************************************************\n");
                printf("*********************** 1：译码读取       ***********************\n");
                printf("*********************** 0：返回上一级菜单 ***********************\n");
                printf("*****************************************************************\n");
                printf("请输入你想进行的操作：");
                scanf_s("%d", &e);
                switch (e)
                {
                case 1:
                    system("cls");
                    HFMDecoding(HT, count);//译码
                    break;
                case 0:
                    flag = 1;
                    break;
                default:
                    break;
                }
                if (flag) break;
            }
            break;
        case 0:
            exit(0);
        default:
            break;
        }
    }
    return 0;
}
