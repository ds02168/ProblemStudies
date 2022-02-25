#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define ORDER 12
#define SIZE (1 << ORDER) //order의 2배
#define MAX_GROUPS 100

static char table[SIZE]; //실제 group들이 배치되는 table, 없으면 0
static int position[MAX_GROUPS]; //group의 시작위치, 없으면 -1
static int size[MAX_GROUPS]; //group의 크기 ,group마다 값은 random함
static int used[MAX_GROUPS]; //group이 사용되었는지 여부, 사용 안됨=0,사용=1

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
		memset(table, 0, sizeof(table)); //table 배열을 0으로 초기화
		for (int i = 0; i<MAX_GROUPS; i++) //초기화
		{
			position[i] = -1; // -1=사용안됨
			size[i] = 1 << (rand() % (ORDER - 3)); //size는 random
		} //table,used는 0, size는 random, position은 -1로 초기화
		allocator_init();
		clock_t t = clock();

		int idx = 0;
		for (int i = 0;i < 100000; i++)
		{
			idx++;
			int group = rand() % (MAX_GROUPS - 1) + 1; //group은 random값
			int s = size[group]; //임의의 size배열의 원소 가져옴

			if (used[group] == 0) //사용 안된 group
			{
				int offset = allocate(group, s); //offset은 group의 시작 위치

				if (offset <0)
				{
					SCORE += s;
				}
				else if (offset + s > SIZE) // 들어가지 못하면
				{
					SCORE += 100000000;
				}
				else if (memcmp(&table[offset], null, s)) { //table[]offset ~ offset+s까지 0이 아니면, 이미 값이 있으면
					SCORE += 100000000;
					offset = allocate(group, s); //다시 위치 할당
				}
				else //해당 group이 아직 사용 안됨
				{
					memset(&table[offset], group, s); //table[] offset ~ offset+s만큼 group으로 채움
					position[group] = offset;//해당 geoup의 시작 위치 저장
				}
				used[group] = 1; //1:해당 group은 사용 되었음
			}
			else //사용 됬으면
			{
				if (position[group] != -1)//table 배정되어있으면
				{
					clear(group); //해당 그룹 삭제
					memset(&table[position[group]], 0, s);//table에서 비움
					position[group] = -1;//group시작위치 초기화
				}
				used[group] = 0; //사용 표시
			}
		}
		run += clock() - t; //걸린 시간
	}
	SCORE += run; //걸린 시간 점수 포함
	printf("SCORE = %llu\n", SCORE);
	return 0;
}
