#include "main.h"

Status FileCreate(HuffmanTree& HT,char* filename)
{
    ALP letter[59];//储存字符及其频度
    int i = 0, sum = 0, n = 58, m = 2 * n - 1;
    int s1, s2;//最小的两个权值的下标
    HuffmanTree p;
    FILE* fp;//需要编译的文件
    fopen_s(&fp, filename, "r");
    //判断是否打开失败
    if (!fp) {
        printf("未发现文件！\n");
        exit(1);
    }
    //初始化
    letter[1].let = 'a';
    for (i = 1;i <= 26; i++) {
        letter[i + 1].let = letter[i].let + 1; 
    }
    letter[i].let = 'A';
    for (;i <= 52; i++) {
        letter[i + 1].let = letter[i].let + 1;
    }
    letter[i].let = 32;//空格
    letter[i + 1].let = 63;//?
    letter[i + 2].let = 44;//，
    letter[i + 3].let = 46;//.
    letter[i + 4].let = 33;//!
    letter[i + 5].let = '\n';//回车

    //循环文章，查找对应字符的个数
    for (i = 1;i <= n;i++) {
        letter[i].num = counter(letter[i].let, fp);
        rewind(fp);
    }
    //计算总文字数
    for (i = 1;i <= n ;i++) {
        sum += letter[i].num;
    }
    //printf("%d\n",sum);
    //计算各个字符的频度
    for (i = 1;i <= n;i++) {
        letter[i].frequency = (int)(letter[i].num / (double)sum * 100);
    }
    //for (i = 1;i <= n;i++) {
    //    printf("%c %d\n", letter[i].let, letter[i].num);    
    //}
    fclose(fp);
    HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNote));//0号位不用
    if (!HT) return ERROR;
    //将字符的频度转存至哈夫曼树中
    for (i = 1;i <= n;i++) {
        HT[i].value = letter[i].let;
        HT[i].weight = letter[i].frequency;
    }
    for (p = HT + 1, i = 1;i <= n;++i, ++p) {
        p->lchild = 0;
        p->rchild = 0;
        p->parent = 0;
    }
    //初始化
    for (;i <= m;++i, ++p) *p = { 0,0,0,0,0 };
    for (i = n + 1;i <= m;++i) {
        Select(HT, i - 1, s1, s2);
        HT[s1].parent = i;
        HT[s2].parent = i;
        HT[i].lchild = s1;
        HT[i].rchild = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
        HT[i].value = '#';
    }
    fopen_s(&fp, "HfmTree.txt", "w");
    if (!fp) return ERROR;
    for (i = 1;i <= m;i++) {
        fprintf(fp, "%c %d %d %d %d\n", HT[i].value, HT[i].parent, HT[i].lchild, HT[i].rchild, HT[i].weight);
    }
    fclose(fp);
}
//计数
int counter(char letter, FILE* fp)
{
    char flag;
    int num = 0;
    while (!feof(fp)) {
        fscanf_s(fp, "%c", &flag, 128);
        if (flag == letter) {
            num++;
        }
        
    }
    //printf("%c:%d\n",letter,num);
    return num;
}
