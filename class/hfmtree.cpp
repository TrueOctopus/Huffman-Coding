#include "main.h"

//构建哈夫曼树
int CreatHFMTree(HuffmanTree& HT, char t[])
{
	int m,n;//总个数
	int i, s1, s2;//s1最小权值下标 s2第二小权值下标
	HuffmanTree p;
	FILE* fp = NULL;
	printf("请输入字符集大小：");
	scanf_s("%d", &n);
	if (n <= 1) return ERROR;
	m = 2 * n - 1;

	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNote));//0号位不用
	if (!HT) return ERROR;
	//手动命令行输入字符和权值
	for (i = 1;i <= n;++i) {
		getchar();
		printf("请输入字符：");
		scanf_s("%c", &HT[i].value, 128);
		printf("请输入对应的权值：");
		scanf_s("%d", &HT[i].weight);
	}
	//初始化
	for (p = HT + 1, i = 1;i <= n;++i, ++p) {
		p->lchild = 0;
		p->rchild = 0;
		p->parent = 0;
	}
	for (;i <= m;++i, ++p) *p = { 0,0,0,0,0 };

	for (i = n + 1;i <= m;++i) {
		Select(HT, i - 1, s1, s2);//选择最小的两个权值下标
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
		HT[i].value = '#';
	}
	//将结果保存到哈夫曼树文件中
	fopen_s(&fp, t, "w");
	if (!fp) return ERROR;
	for (i = 1;i <= m;i++) {
		fprintf(fp, "%c %d %d %d %d\n", HT[i].value, HT[i].parent, HT[i].lchild, HT[i].rchild, HT[i].weight);
	}
	fclose(fp);
	return n;
}
//打印哈夫曼树
Status PrintHFMTree(HuffmanTree HT, int n, char t[])
{
	FILE* fp;
	int i, m = 2 * n - 1;//总数
	fopen_s(&fp, t, "r");
	if (!fp) {
		printf("未创建哈夫曼树！\n");
		return ERROR;
	}
	for (i = 1;i <= m;i++) {
		printf("%3d：", i);
		printf("%c ", HT[i].value);
		printf("%3d ", HT[i].parent);
		printf("%3d ", HT[i].lchild);
		printf("%3d ", HT[i].rchild);
		printf("%4d \n", HT[i].weight);
	}
}
//每个字符的编码
Status CharCoding(HuffmanTree& HT, int& n, HuffmanCode& HC, char t[])
{
	int i=1, j, k, c, m;
	char temp;
	char* cd;
	FILE* fp;
	//判断字符数是否为0
	if (!n) {
		fopen_s(&fp, t, "r");
		if (!fp) return ERROR;
		//计算字符数
		while (!feof(fp)) {
			fscanf_s(fp, "%c", &temp, 100);
			if (temp == '\n') n++;
		}
		fclose(fp);
		n = n / 2;
	}
	//判断哈夫曼树是否存在内存中
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
	//计算各个字符的编码
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
//选出最小的两个权值的下标
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
//编码
Status HFMCoding(HuffmanTree& HT, HuffmanCode& HC, int n)
{
	int i, j;
	char w[Init_Max_Value];//发送内容
	char r[Init_Max_Value];//编码后内容
	char t[Init_Max_Value];//发送的文件名
	FILE* fp;
	printf("请输入需要发送的文件名：\n");
	scanf_s("%s", t, Init_Max_Value);
	//判断发送文件是否存在
	if (!_access(t, 0)) {
		fopen_s(&fp, t, "r");
		i = 0;
		//将文件中的内容存入数组
		while (!feof(fp)) {
			fscanf_s(fp, "%c", &w[i], 128);
			i++;
		}
		w[i] = '\0';
		fclose(fp);
	}
	else {
		printf("未发现发送文本文件！\n");
		printf("请输入你想发送的文本：\n");
		scanf_s("%s", w, Init_Max_Value);
		//将输入的文本存入数组
		fopen_s(&fp, t, "w");
		if (!fp) return ERROR;
		fprintf(fp, "%s", w);
		fclose(fp);
	}
	
	r[0] = '\0';
	i = 0;
	//将每个字符对应编码
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
	fprintf(fp, "%s", r);//将编译后的内容存入文件
	fclose(fp);
	printf("*************************************************************\n");
	printf("**********************   编码发送成功！ *********************\n");
	return OK;
}
//译码
Status HFMDecoding(HuffmanTree HT, int n)
{
	HuffmanTree pr, p;
	int i=0, j=0, m = 2 * n - 1;//总数
	char w[Init_Max_Value];//编译前文本
	char r[Init_Max_Value];//编译后文本
	FILE* fp;
	fopen_s(&fp, "CodeFlie.dat","r");
	//判断编译文件是否存在
	if (!fp) {
		printf("未接收到信息！\n");
		return ERROR;
	}
	//判断哈夫曼树是否构建
	if (!HT) {
		printf("未生成编码！\n");
		return ERROR;
	}
	fscanf_s(fp, "%s", w, Init_Max_Value);//从文件中读入

	p = &HT[m];//指向树根的指针
	pr = p;
	while (i < strlen(w)) {
		//如果是1指向右孩子
		if (w[i] == '1') {
			pr = &HT[p->rchild];
		}
		//如果是0指向左孩子
		if (w[i] == '0') {
			pr = &HT[p->lchild];
		}
		p = pr;
		//直到值不为“#”时代表找到译码前字符
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
	printf("**************************  译码成功！  *************************\n");
	printf("内容为：\n");
	printf("%s\n", r);
	fclose(fp);
	return OK;
}