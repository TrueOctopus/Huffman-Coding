#include "main.h"

Status FileCreate(HuffmanTree& HT,char* filename)
{
    ALP letter[59];//�����ַ�����Ƶ��
    int i = 0, sum = 0, n = 58, m = 2 * n - 1;
    int s1, s2;//��С������Ȩֵ���±�
    HuffmanTree p;
    FILE* fp;//��Ҫ������ļ�
    fopen_s(&fp, filename, "r");
    //�ж��Ƿ��ʧ��
    if (!fp) {
        printf("δ�����ļ���\n");
        exit(1);
    }
    //��ʼ��
    letter[1].let = 'a';
    for (i = 1;i <= 26; i++) {
        letter[i + 1].let = letter[i].let + 1; 
    }
    letter[i].let = 'A';
    for (;i <= 52; i++) {
        letter[i + 1].let = letter[i].let + 1;
    }
    letter[i].let = 32;//�ո�
    letter[i + 1].let = 63;//?
    letter[i + 2].let = 44;//��
    letter[i + 3].let = 46;//.
    letter[i + 4].let = 33;//!
    letter[i + 5].let = '\n';//�س�

    //ѭ�����£����Ҷ�Ӧ�ַ��ĸ���
    for (i = 1;i <= n;i++) {
        letter[i].num = counter(letter[i].let, fp);
        rewind(fp);
    }
    //������������
    for (i = 1;i <= n ;i++) {
        sum += letter[i].num;
    }
    //printf("%d\n",sum);
    //��������ַ���Ƶ��
    for (i = 1;i <= n;i++) {
        letter[i].frequency = (int)(letter[i].num / (double)sum * 100);
    }
    //for (i = 1;i <= n;i++) {
    //    printf("%c %d\n", letter[i].let, letter[i].num);    
    //}
    fclose(fp);
    HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNote));//0��λ����
    if (!HT) return ERROR;
    //���ַ���Ƶ��ת��������������
    for (i = 1;i <= n;i++) {
        HT[i].value = letter[i].let;
        HT[i].weight = letter[i].frequency;
    }
    for (p = HT + 1, i = 1;i <= n;++i, ++p) {
        p->lchild = 0;
        p->rchild = 0;
        p->parent = 0;
    }
    //��ʼ��
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
//����
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
