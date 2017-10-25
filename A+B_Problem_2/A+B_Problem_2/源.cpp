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
int totalSurplus = 0;
int outputLength = 0;
//从input中读入一个整型 O(1)
int readInt() {
	int myInt = 0;
	while (*inputPos<'0' || *inputPos>'9')
		++inputPos;
	while (*inputPos >= '0'&&*inputPos <= '9') {
		myInt=(myInt<<3)+(myInt<<1);//myInt*=10
		myInt += *inputPos - '0';
		++inputPos;
	}
	return myInt;
}

//从input中读入字符串给a O(m)
void readA() {
	memset(a, 0, 5010);
	aPos = a;
	while (*inputPos<'0' || *inputPos>'9')
		++inputPos;
	while (*inputPos >= '0'&&*inputPos <= '9') {
		*aPos = *inputPos;
		++inputPos;
		++aPos;
	}
	int surplus = 8 - (aPos - a) % 8;
	totalSurplus += surplus;
	for (int i = 0; i < surplus; ++i) {
		*aPos = '0';
		++aPos;
	}
}

//从input中读入字符串给b O(m)
void readB() {
	memset(b, 0, 5010);
	bPos = b;
	while (*inputPos<'0' || *inputPos>'9')
		++inputPos;
	while (*inputPos >= '0'&&*inputPos <= '9') {
		*bPos = *inputPos;
		++inputPos;
		++bPos;
	}
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
		int aLength = (aPos - a) / 8;
		int bLength = (bPos - b) / 8;
		for (int aStep = 0; aStep < aLength; ++aStep) {
			//获得a的第(aLength-aStep-1)*8到(aLength-aStep-1)*8+7位组成的数A
			int A = 0;
			for (int j = 0; j < 8; ++j) {
				A = (A<<3)+(A<<1);
				A += *awPos - '0';
				++awPos;
			}
			//分别获得B的每8位数字
			bwPos = b;
			for (int bStep = 0; bStep < bLength; ++bStep) {
				//获得b的第(bLength-bStep-1)*8到(bLength-bStep-1)*8+7位组成的数A
				int B = 0;
				for (int j = 0; j < 8; ++j) {
					B = (B<<3)+(B<<1);
					B += *bwPos - '0';
					++bwPos;
				}
				//加到product上
				long long myProduct = (long long)(A)*B;
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


	fwrite(output, 1, outputLength, stdout);
	return 0;
}