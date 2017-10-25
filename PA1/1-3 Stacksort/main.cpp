#include <cstdio>
#include <cstdlib>

int b[2000100];//存储后k个数的最大值
int a[2000100];//待排序的栈
int stack[2000100];//已排序的栈
char buffer[16000000];//输入的数据
char output[16000000];//输出的数据
char* outputChar = output;//输出位置
int pos = -1;//输入位置
char temp[20];//用来转换整数为字符串以便输出的数组

//读入整数的函数
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

//输出函数
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

	//读入题目数据
	for (int i = 0; i < n; i++) {
		a[i] = readInt();
	}
	b[n - 1] = a[n - 1];

	//对后k个数据的最大值进行预处理
	for (int i = n - 2; i >= 0; i--) {
		if (a[i] > b[i + 1])
			b[i] = a[i];
		else
			b[i] = b[i + 1];
	}
	stack[0] = a[0];
	int stackNow = 0;

	//进行栈排序
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