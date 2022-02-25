#define ORDER 12
#define SIZE (1 << ORDER) //order의 2배
#define MAX_GROUPS 100
#define TRUE 1
#define FALSE 0

static char table[SIZE]; //실제 group들이 배치되는 table, 없으면 0
static int position[MAX_GROUPS]; //group의 시작위치, 없으면 -1


void allocator_init() //초기화 함수
{
	for (int i = 0; i < MAX_GROUPS; i++)
		position[i] = -1;
}

int allocate(int group, int len) //빈공간에 할당하는 함수
{
	int offset = position[group];
	int i;
	int flag;


	for (i = 0; i + len <= SIZE; i++) {//table의 들어갈수 있는 공간안에서
		flag = TRUE;
		if (table[i] == 0) {
			for (int j = 0; j < len; j++) { //연속해서 0인지 확인
				if (table[i + j] != 0) { //0아닌 숫자있으면
					flag = FALSE; //flag=0:들어갈수없다
					break;
				}
			}

			if (flag = TRUE) { //flag=1:들어갈수 있습니다.
				offset = i;
				position[group] = offset; //시작위치 지정
				for (int index = i; index < i + len; index++) //table에 len만큼 넣어줍니다.
					table[index] = group;

				return offset;
			}
		}
	}

	if (offset < 0) //offset<0 인 경우
		return offset;
	else //offset + s > SIZE 인 경우
		return i + len;
}
void clear(int group)
{
	int index;
	for (index = 0; index < SIZE; index++) {//table 초기화
		if (table[index] == group) {
			table[index] = 0;
		}
	}
	position[group] = -1; //시작위치 초기화
}