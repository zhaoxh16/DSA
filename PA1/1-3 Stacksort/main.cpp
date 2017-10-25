#include <cstdio>
#include <cstdlib>

int b[2000100];//�洢��k���������ֵ
int a[2000100];//�������ջ
int stack[2000100];//�������ջ
char buffer[16000000];//���������
char output[16000000];//���������
char* outputChar = output;//���λ��
int pos = -1;//����λ��
char temp[20];//����ת������Ϊ�ַ����Ա����������

//���������ĺ���
int readInt() {
	char myChar = buffer[++pos];
	while (myChar<'0' || myChar>'9') {
		myChar = buffer[++pos];
	}
	int myInt = 0;
	while (myChar >= '0'&&myChar <= '9') {
		myInt *= 10;
		myInt += myChar - '0';
		myChar = buffer[++pos];
	}
	return myInt;
}

//�������
void doOutput(int myOutput) {
	char* tempChar = temp;
	while (myOutput != 0) {
		*tempChar = '0'+myOutput % 10;
		++tempChar;
		myOutput /= 10;
	}
	while (tempChar != temp) {
		*outputChar = *(--tempChar);
		++outputChar;
	}
	*outputChar = ' ';
	++outputChar;
}

int main() {
	fread(buffer, 1, 16000000, stdin);
	int n;
	n = readInt();

	//������Ŀ����
	for (int i = 0; i < n; i++) {
		a[i] = readInt();
	}
	b[n - 1] = a[n - 1];

	//�Ժ�k�����ݵ����ֵ����Ԥ����
	for (int i = n - 2; i >= 0; i--) {
		if (a[i] > b[i + 1])
			b[i] = a[i];
		else
			b[i] = b[i + 1];
	}
	stack[0] = a[0];
	int stackNow = 0;

	//����ջ����
	for (int i = 1; i < n; i++) {
		while (stack[stackNow] > b[i]) {
			doOutput(stack[stackNow]);
			--stackNow;
		}
		++stackNow;
		stack[stackNow] = a[i];
	}
	for (int i = stackNow; i >= 0; i--) {
		doOutput(stack[i]);
	}
	fwrite(output, 1, outputChar - output, stdout);
	return 0;
}