#include <cstdio>
#include <cstdlib>
#include <iostream>

char buffer[1000000 * (10 + 1 + 10 + 1 + 10 + 1) + 1000];//���������
int bufferPos = -1;//�������ݵ�λ��
int N = 0;//��Ʊ����
int countStack[1000100];//�洢��Ʊ�ɹ��������Ķ���
int numberStack[1000100];//�洢��Ʊ��ŵĶ���
int stackPos = -1;
int stackStart = -1;
int stockNow = -1;
long long timeStart = 0;
long long timeNow = 0;
long long countNow = 0;
int exitStock = -1;
int stockOut = -1;
long long sum = 0;

//����һ������
int readInt() {
	char myChar = buffer[++bufferPos];
	int myInt = 0;
	while (myChar >= '0'&&myChar <= '9') {
		myInt *= 10;
		myInt += myChar - '0';
		myChar = buffer[++bufferPos];
	}
	return myInt;
}

int main() {
	fread(buffer, 1, 1000000 * (10 + 1 + 10 + 1 + 10 + 1) + 1000, stdin);
	N = readInt();
	
	//��ȡ��Ʊ����������Ϣ
	for (int i = 0; i < 2 * N; i++) {
		int time = readInt();
		timeNow += time;
		if (buffer[bufferPos] == ' ') {//���й�Ʊ
			int count = readInt();
			while (stackPos > stackStart) {
				if (count >= countStack[stackPos])
					--stackPos;
				else break;
			}
			countStack[++stackPos] = count;
			numberStack[stackPos] = ++stockOut;
		}
		else {//��Ʊ����
			if(++exitStock == numberStack[stackStart+1])
				++stackStart;
		}
		//��⵱ǰ��Ʊ�Ƿ�����ߵ�
		if (stackPos == stackStart) {
			sum += (timeNow - timeStart)*countNow;
			timeStart = timeNow;
			countNow = 0;
			stockNow = -1;
		}
		else if (stockNow != numberStack[stackStart + 1]) {
				sum += (timeNow - timeStart)*countNow;
				timeStart = timeNow;
				countNow = countStack[stackStart + 1];
				stockNow = numberStack[stackStart + 1];
		}
	}
	printf("%lld\n", sum);
	return 0;
}