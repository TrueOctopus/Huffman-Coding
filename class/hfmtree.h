#ifndef HFMTREE123
#define HFMTREE123


typedef struct {
	ElemType value;//字符
	unsigned int weight;//权重
	unsigned int parent, lchild, rchild;//父节点 左孩子 右孩子
}HTNote, * HuffmanTree;
typedef char** HuffmanCode;

int CreatHFMTree(HuffmanTree& HT,char t[]);//构建哈夫曼树
Status PrintHFMTree(HuffmanTree HT, int n, char t[]);//打印哈夫曼树
Status CharCoding(HuffmanTree& HT, int& n, HuffmanCode& HC, char t[]);//每个字符的编码
Status Select(HuffmanTree HT, int i, int& s1, int& s2);//寻找需要的节点
Status HFMCoding(HuffmanTree& HT, HuffmanCode& HC, int n);//编码
Status HFMDecoding(HuffmanTree HC, int n);//译码

#endif
