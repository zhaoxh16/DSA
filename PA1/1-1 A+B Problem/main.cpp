#include <cstdio>
#include <cstdlib>
#include <cstring>

char input[1000 * 5010 + 101];//输入
char output[1000 * 5010 + 101];//输出
char* inputPos = input;//输入串下一个字符位置
char a[5010];//读入的a串
char b[5010];//读入的b串
char* aPos = a;//a串下一个读入字符位置
char* bPos = b;//b串下一个读入字符位置
char* awPos = a;//a串下一个拿去乘法的位置
char* bwPos = b;//b串下一个拿去做乘法的位置
long long product[1401];//记录8位一乘之后的结果
long long A[700];
long long B[700];
int totalSurplus = 0;
int outputLength = 0;
long long myProduct;

//从input中读入一个整型 O(1)
int readInt() {
	int myInt = 0;
	while (*inputPos<'0' || *inputPos>'9')
		++inputPos;
	while (*inputPos >= '0'&&*inputPos <= '9') {
		myInt = (myInt << 3) + (myInt << 1);//myInt*=10
		myInt += *inputPos - '0';
		++inputPos;
	}
	return myInt;
}

//从input中读入字符串给a O(m)
void readA() {
	aPos = a;
	while (*inputPos<'0' || *inputPos>'9')
		++inputPos;
	char* aStart = inputPos;
	while (*inputPos >= '0'&&*inputPos <= '9') {
		++inputPos;
	}
	aPos = a + (inputPos - aStart);
	memcpy(a, aStart, inputPos - aStart);
	int surplus = 8 - (inputPos - aStart) % 8;
	totalSurplus += surplus;
	for (int i = 0; i < surplus; ++i) {
		*aPos = '0';
		++aPos;
	}
}

//从input中读入字符串给b O(m)
void readB() {
	bPos = b;
	while (*inputPos<'0' || *inputPos>'9')
		++inputPos;
	char* bStart = inputPos;
	while (*inputPos >= '0'&&*inputPos <= '9') {
		++inputPos;
	}
	bPos = b + (inputPos - bStart);
	memcpy(b, bStart, bPos - b);
	int surplus = 8 - (bPos - b) % 8;
	totalSurplus += surplus;
	for (int i = 0; i < surplus; ++i) {
		*bPos = '0';
		++bPos;
	}
}

int main() {
	fread(input, 1, 1000 * 5010 + 101, stdin);
	int N = readInt();
	for (int i = 0; i < N; ++i) {
		memset(product, 0, sizeof(product));
		totalSurplus = 0;
		readA();
		readB();
		awPos = a;
		bwPos = b;
		int aLength = (aPos - a) / 8;
		int bLength = (bPos - b) / 8;
		for (int aStep = 0; aStep < aLength; ++aStep) {
			//获得b的第(bLength-bStep-1)*8到(bLength-bStep-1)*8+7位组成的数B
			A[aStep] = 0;
			for (int j = 0; j < 8; ++j) {
				A[aStep] = (A[aStep] << 3) + (A[aStep] << 1);
				A[aStep] += *awPos - '0';
				++awPos;
			}
		}
		for (int bStep = 0; bStep < bLength; ++bStep) {
			//获得b的第(bLength-bStep-1)*8到(bLength-bStep-1)*8+7位组成的数B
			B[bStep] = 0;
			for (int j = 0; j < 8; ++j) {
				B[bStep] = (B[bStep] << 3) + (B[bStep] << 1);
				B[bStep] += *bwPos - '0';
				++bwPos;
			}
		}
		for (int aStep = 0; aStep < aLength; ++aStep) {
			for (int bStep = 0; bStep < bLength; ++bStep) {
				myProduct = A[aStep] * B[bStep];
				product[aLength + bLength - aStep - bStep - 2] += myProduct;
			}
		}
		//处理进位
		long long temp = 0;
		for (int j = 0; j < 1400; ++j) {
			product[j] = product[j] + temp;
			temp = product[j] / 100000000;
			product[j] = product[j] - temp * 100000000;
		}
		//计算位数
		int iter = 1400;
		while (product[iter] == 0 && iter > 0)
			--iter;
		int smallIter = 0;
		temp = product[iter];
		while (temp != 0) {
			temp /= 10;
			++smallIter;
		}
		//乘积结果的长度
		int productLength = (iter << 3) + smallIter;
		int length = productLength;
		//放到output中 
		if (productLength == 0) {
			output[outputLength] = '0';
			output[++outputLength] = '\n';
			++outputLength;
		}
		else {
			for (int j = 0; j < iter; ++j) {
				for (int k = 0; k < 8; ++k) {
					output[--productLength + outputLength] = product[j] % 10 + '0';
					product[j] /= 10;
				}
			}
			while (productLength > 0) {
				output[--productLength + outputLength] = product[iter] % 10 + '0';
				product[iter] /= 10;
			}
			for (int j = 0; j < totalSurplus; ++j) {
				output[--length + outputLength] = 0;
			}
			output[outputLength + length] = '\n';
			outputLength = outputLength + length + 1;
		}
	}
	//输出
	fwrite(output, 1, outputLength, stdout);
	return 0;
}