#include <cstdio>
#include <cstdlib>
char buffer[10010 * 500 + 1001];
char* bufferChar = buffer;
int N = 0;
char a[5001];
char b[5001];
int product[501][10100];
int productLength[501];
long long ab = 0;
char output[10010 * 500 + 1];
char* outputChar = output;
void plus(int pos,int i){
	char cab[17];
	int cabPos = 0;
	long long tempAb = ab;
	int abLength = 0;
	while (tempAb != 0) {
		tempAb /= 10;
		++abLength;
	}
	while (ab != 0) {
		long long temp = ab / 10;
		cab[cabPos] = ab - temp * 10;
		ab = temp;
		++cabPos;
	}
	int j = pos;
	for (j = pos; j < pos + cabPos; ++j) {
		product[i][j] += (cab[j - pos]);
	}
	//printf("%s\n", product[i]);
}
int main() {
	fread(buffer, 1, 10010 * 500 + 1001, stdin);
	while (*bufferChar >= '0'&&*bufferChar <= '9') {
		N *= 10;
		N += *buffer - '0';
		++bufferChar;
	}
	for (int i = 0; i < N; i++) {
		++bufferChar;
		char* posA = a;
		char* posB = b;
		//读取a
		int lengthA = 0;
		while (*bufferChar >= '0'&&*bufferChar <= '9') {
			*posA = *bufferChar;
			++posA;
			++bufferChar;
			++lengthA;
		}
		//读取b
		++bufferChar;
		int lengthB = 0;
		while (*bufferChar >= '0'&&*bufferChar <= '9') {
			*posB = *bufferChar;
			++posB;
			++bufferChar;
			++lengthB;
		}
		productLength[i] = lengthA + lengthB;
		//计算乘法
		int timeA = lengthA / 8;
		int timeB = lengthB / 8;
		int surplusA = lengthA - timeA * 8;
		int surplusB = lengthB - timeB * 8;
		char* pos1 = a;//当前A的读取位置
		for (int pA = 0; pA < timeA; ++pA) {
			long long intA = 0;//当前A这八位的数
			for (int j = 0; j < 8; ++j) {
				intA *= 10;
				intA += *pos1 - '0';
				++pos1;
			}
			char* pos2 = b;
			for (int pB = 0; pB < timeB; ++pB) {
				long long intB = 0;
				for (int k = 0; k < 8; ++k) {
					intB *= 10;
					intB += *pos2 - '0';
					++pos2;
				}
				ab = intA*intB;
				plus(lengthA-8-pA * 8 + lengthB-8-pB * 8,i);
			}
			long long intB = 0;
			for (int k = 0; k < surplusB; ++k) {
				intB *= 10;
				intB += *pos2 - '0';
				++pos2;
			}
			ab = intA*intB;
			plus(lengthA-8-pA * 8 + 0,i);
		}
		long long intA = 0;
		for (int j = 0; j < surplusA; ++j) {
			intA *= 10;
			intA += *pos1 - '0';
			++pos1;
		}
		char* pos2 = b;
		for (int pB = 0; pB < timeB; ++pB) {
			long long intB = 0;
			for (int k = 0; k < 8; ++k) {
				intB *= 10;
				intB += *pos2 - '0';
				++pos2;
			}
			ab = intA*intB;
			plus(0 + lengthB-8-pB * 8,i);
		}
		long long intB = 0;
		for (int k = 0; k < surplusB; ++k) {
			intB *= 10;
			intB += *pos2 - '0';
			++pos2;
		}
		ab = intA*intB;
		plus(0 + 0,i);
		int surplus = 0;
		for (int j = 0; j < productLength[i]; ++j) {
			int temp = product[i][j] + surplus;
			product[i][j] = temp % 10;
			surplus = temp / 10;
		}
		int j = productLength[i];
		while (surplus != 0) {
			product[i][j] = surplus % 10;
			surplus /= 10;
			++j;
			++productLength[i];
		}
		if (productLength[i] == 0)
			printf("0\n");
		else {
			if (product[i][productLength[i] - 1] == 0)
				--productLength[i];
			for (int j = productLength[i]-1; j >= 0;--j) {
				*outputChar = product[i][j] + '0';
				++outputChar;
			}
			*(outputChar) = '\n';
			++outputChar;
		}
	}
	fwrite(output, 1, outputChar - output, stdout);
	return 0;
}