#pragma once
#ifndef FILE123
#define FILE123

typedef struct {
    char let;//�ַ�
    int num;//����
    int frequency;//Ƶ��
}ALP;//����ṹ��

int counter(char letter, FILE* fp);//����
Status FileCreate(HuffmanTree& HT, char* filename);//��ĸƵ������

#endif // !FILE123
