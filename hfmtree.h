#ifndef HFMTREE123
#define HFMTREE123


typedef struct {
	ElemType value;//�ַ�
	unsigned int weight;//Ȩ��
	unsigned int parent, lchild, rchild;//���ڵ� ���� �Һ���
}HTNote, * HuffmanTree;
typedef char** HuffmanCode;

int CreatHFMTree(HuffmanTree& HT,char t[]);//������������
Status PrintHFMTree(HuffmanTree HT, int n, char t[]);//��ӡ��������
Status CharCoding(HuffmanTree& HT, int& n, HuffmanCode& HC, char t[]);//ÿ���ַ��ı���
Status Select(HuffmanTree HT, int i, int& s1, int& s2);//Ѱ����Ҫ�Ľڵ�
Status HFMCoding(HuffmanTree& HT, HuffmanCode& HC, int n);//����
Status HFMDecoding(HuffmanTree HC, int n);//����

#endif
