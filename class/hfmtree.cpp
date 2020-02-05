#include "main.h"

//������������
int CreatHFMTree(HuffmanTree& HT, char t[])
{
	int m,n;//�ܸ���
	int i, s1, s2;//s1��СȨֵ�±� s2�ڶ�СȨֵ�±�
	HuffmanTree p;
	FILE* fp = NULL;
	printf("�������ַ�����С��");
	scanf_s("%d", &n);
	if (n <= 1) return ERROR;
	m = 2 * n - 1;

	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNote));//0��λ����
	if (!HT) return ERROR;
	//�ֶ������������ַ���Ȩֵ
	for (i = 1;i <= n;++i) {
		getchar();
		printf("�������ַ���");
		scanf_s("%c", &HT[i].value, 128);
		printf("�������Ӧ��Ȩֵ��");
		scanf_s("%d", &HT[i].weight);
	}
	//��ʼ��
	for (p = HT + 1, i = 1;i <= n;++i, ++p) {
		p->lchild = 0;
		p->rchild = 0;
		p->parent = 0;
	}
	for (;i <= m;++i, ++p) *p = { 0,0,0,0,0 };

	for (i = n + 1;i <= m;++i) {
		Select(HT, i - 1, s1, s2);//ѡ����С������Ȩֵ�±�
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
		HT[i].value = '#';
	}
	//��������浽���������ļ���
	fopen_s(&fp, t, "w");
	if (!fp) return ERROR;
	for (i = 1;i <= m;i++) {
		fprintf(fp, "%c %d %d %d %d\n", HT[i].value, HT[i].parent, HT[i].lchild, HT[i].rchild, HT[i].weight);
	}
	fclose(fp);
	return n;
}
//��ӡ��������
Status PrintHFMTree(HuffmanTree HT, int n, char t[])
{
	FILE* fp;
	int i, m = 2 * n - 1;//����
	fopen_s(&fp, t, "r");
	if (!fp) {
		printf("δ��������������\n");
		return ERROR;
	}
	for (i = 1;i <= m;i++) {
		printf("%3d��", i);
		printf("%c ", HT[i].value);
		printf("%3d ", HT[i].parent);
		printf("%3d ", HT[i].lchild);
		printf("%3d ", HT[i].rchild);
		printf("%4d \n", HT[i].weight);
	}
}
//ÿ���ַ��ı���
Status CharCoding(HuffmanTree& HT, int& n, HuffmanCode& HC, char t[])
{
	int i=1, j, k, c, m;
	char temp;
	char* cd;
	FILE* fp;
	//�ж��ַ����Ƿ�Ϊ0
	if (!n) {
		fopen_s(&fp, t, "r");
		if (!fp) return ERROR;
		//�����ַ���
		while (!feof(fp)) {
			fscanf_s(fp, "%c", &temp, 100);
			if (temp == '\n') n++;
		}
		fclose(fp);
		n = n / 2;
	}
	//�жϹ��������Ƿ�����ڴ���
	if (!HT) {
		fopen_s(&fp, t, "r");
		if (!fp) return ERROR;
		m = 2 * n - 1;
		HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNote));
		for (i = 1;i <= m;i++) {
			fscanf_s(fp, "%c%d%d%d%d%c", &HT[i].value, 128, &HT[i].parent, &HT[i].lchild, &HT[i].rchild, &HT[i].weight, &temp, 128);
		}
		fclose(fp);
	}
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));
	if (!HC) return ERROR;
	cd = (char*)malloc(n * sizeof(char));
	if (!cd) return ERROR;
	cd[n - 1] = '\0';
	//��������ַ��ı���
	for (i = 1;i <= n;i++) {
		j = n - 1;
		for (k = i, c = HT[i].parent;c != 0;k = c, c = HT[c].parent) {
			if (HT[c].lchild == k) cd[--j] = '0';
			else cd[--j] = '1';
			HC[i] = (char*)malloc((n - j) * sizeof(char));
			if (!HC[i]) return ERROR;
			strcpy_s(HC[i], strlen(&cd[j]) + 1, &cd[j]);
		}
	}
	free(cd);
	return OK;
}
//ѡ����С������Ȩֵ���±�
Status Select(HuffmanTree HT, int i, int& s1, int& s2)
{
	int j;
	unsigned int max1 = 1000, max2 = 1000;
	for (j = 1;j <= i; ++j) {
		if (HT[j].parent == 0) {
			if (HT[j].weight < max1) {
				max2 = max1;
				max1 = HT[j].weight;
				s1 = s2;
				s2 = j;
			}
			else if (HT[j].weight < max2) {
				max2 = HT[j].weight;
				s1 = j;
			}
		}
	}
	return OK;
}
//����
Status HFMCoding(HuffmanTree& HT, HuffmanCode& HC, int n)
{
	int i, j;
	char w[Init_Max_Value];//��������
	char r[Init_Max_Value];//���������
	char t[Init_Max_Value];//���͵��ļ���
	FILE* fp;
	printf("��������Ҫ���͵��ļ�����\n");
	scanf_s("%s", t, Init_Max_Value);
	//�жϷ����ļ��Ƿ����
	if (!_access(t, 0)) {
		fopen_s(&fp, t, "r");
		i = 0;
		//���ļ��е����ݴ�������
		while (!feof(fp)) {
			fscanf_s(fp, "%c", &w[i], 128);
			i++;
		}
		w[i] = '\0';
		fclose(fp);
	}
	else {
		printf("δ���ַ����ı��ļ���\n");
		printf("���������뷢�͵��ı���\n");
		scanf_s("%s", w, Init_Max_Value);
		//��������ı���������
		fopen_s(&fp, t, "w");
		if (!fp) return ERROR;
		fprintf(fp, "%s", w);
		fclose(fp);
	}
	
	r[0] = '\0';
	i = 0;
	//��ÿ���ַ���Ӧ����
	while (i<strlen(w)) {
		for (j = 1;j <= n;j++) {
			if (w[i] == HT[j].value) {
				strcat_s(r, HC[j]);
			}
		}
		i++;
	}
	fopen_s(&fp, "CodeFlie.dat", "wb");
	if (!fp) return ERROR;
	fprintf(fp, "%s", r);//�����������ݴ����ļ�
	fclose(fp);
	printf("*************************************************************\n");
	printf("**********************   ���뷢�ͳɹ��� *********************\n");
	return OK;
}
//����
Status HFMDecoding(HuffmanTree HT, int n)
{
	HuffmanTree pr, p;
	int i=0, j=0, m = 2 * n - 1;//����
	char w[Init_Max_Value];//����ǰ�ı�
	char r[Init_Max_Value];//������ı�
	FILE* fp;
	fopen_s(&fp, "CodeFlie.dat","r");
	//�жϱ����ļ��Ƿ����
	if (!fp) {
		printf("δ���յ���Ϣ��\n");
		return ERROR;
	}
	//�жϹ��������Ƿ񹹽�
	if (!HT) {
		printf("δ���ɱ��룡\n");
		return ERROR;
	}
	fscanf_s(fp, "%s", w, Init_Max_Value);//���ļ��ж���

	p = &HT[m];//ָ��������ָ��
	pr = p;
	while (i < strlen(w)) {
		//�����1ָ���Һ���
		if (w[i] == '1') {
			pr = &HT[p->rchild];
		}
		//�����0ָ������
		if (w[i] == '0') {
			pr = &HT[p->lchild];
		}
		p = pr;
		//ֱ��ֵ��Ϊ��#��ʱ�����ҵ�����ǰ�ַ�
		if (pr->value != '#') {
			r[j] = pr->value;
			j++;
			p = &HT[m];
			pr = p;
		}
		i++;
	}
	r[j] = '\0';
	printf("*****************************************************************\n");
	printf("**************************  ����ɹ���  *************************\n");
	printf("����Ϊ��\n");
	printf("%s\n", r);
	fclose(fp);
	return OK;
}