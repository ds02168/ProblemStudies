#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define ORDER 12
#define SIZE (1 << ORDER) //order�� 2��
#define MAX_GROUPS 100

static char table[SIZE]; //���� group���� ��ġ�Ǵ� table, ������ 0
static int position[MAX_GROUPS]; //group�� ������ġ, ������ -1
static int size[MAX_GROUPS]; //group�� ũ�� ,group���� ���� random��
static int used[MAX_GROUPS]; //group�� ���Ǿ����� ����, ��� �ȵ�=0,���=1

void allocator_init();
int allocate(int group, int len);
void clear(int group);

int main()
{
	char null[SIZE / 16] = { 0, };
	unsigned long long SCORE = 0;
	int run = 0;
	for (int c = 0; c<10; c++)
	{
		memset(table, 0, sizeof(table)); //table �迭�� 0���� �ʱ�ȭ
		for (int i = 0; i<MAX_GROUPS; i++) //�ʱ�ȭ
		{
			position[i] = -1; // -1=���ȵ�
			size[i] = 1 << (rand() % (ORDER - 3)); //size�� random
		} //table,used�� 0, size�� random, position�� -1�� �ʱ�ȭ
		allocator_init();
		clock_t t = clock();

		int idx = 0;
		for (int i = 0;i < 100000; i++)
		{
			idx++;
			int group = rand() % (MAX_GROUPS - 1) + 1; //group�� random��
			int s = size[group]; //������ size�迭�� ���� ������

			if (used[group] == 0) //��� �ȵ� group
			{
				int offset = allocate(group, s); //offset�� group�� ���� ��ġ

				if (offset <0)
				{
					SCORE += s;
				}
				else if (offset + s > SIZE) // ���� ���ϸ�
				{
					SCORE += 100000000;
				}
				else if (memcmp(&table[offset], null, s)) { //table[]offset ~ offset+s���� 0�� �ƴϸ�, �̹� ���� ������
					SCORE += 100000000;
					offset = allocate(group, s); //�ٽ� ��ġ �Ҵ�
				}
				else //�ش� group�� ���� ��� �ȵ�
				{
					memset(&table[offset], group, s); //table[] offset ~ offset+s��ŭ group���� ä��
					position[group] = offset;//�ش� geoup�� ���� ��ġ ����
				}
				used[group] = 1; //1:�ش� group�� ��� �Ǿ���
			}
			else //��� ������
			{
				if (position[group] != -1)//table �����Ǿ�������
				{
					clear(group); //�ش� �׷� ����
					memset(&table[position[group]], 0, s);//table���� ���
					position[group] = -1;//group������ġ �ʱ�ȭ
				}
				used[group] = 0; //��� ǥ��
			}
		}
		run += clock() - t; //�ɸ� �ð�
	}
	SCORE += run; //�ɸ� �ð� ���� ����
	printf("SCORE = %llu\n", SCORE);
	return 0;
}
