#pragma once
#ifndef FILE123
#define FILE123

typedef struct {
    char let;//字符
    int num;//数量
    int frequency;//频度
}ALP;//定义结构体

int counter(char letter, FILE* fp);//计数
Status FileCreate(HuffmanTree& HT, char* filename);//字母频率排序

#endif // !FILE123
