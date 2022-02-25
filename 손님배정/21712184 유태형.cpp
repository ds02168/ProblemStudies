#define ORDER 12
#define SIZE (1 << ORDER) //order�� 2��
#define MAX_GROUPS 100
#define TRUE 1
#define FALSE 0

static char table[SIZE]; //���� group���� ��ġ�Ǵ� table, ������ 0
static int position[MAX_GROUPS]; //group�� ������ġ, ������ -1


void allocator_init() //�ʱ�ȭ �Լ�
{
	for (int i = 0; i < MAX_GROUPS; i++)
		position[i] = -1;
}

int allocate(int group, int len) //������� �Ҵ��ϴ� �Լ�
{
	int offset = position[group];
	int i;
	int flag;


	for (i = 0; i + len <= SIZE; i++) {//table�� ���� �ִ� �����ȿ���
		flag = TRUE;
		if (table[i] == 0) {
			for (int j = 0; j < len; j++) { //�����ؼ� 0���� Ȯ��
				if (table[i + j] != 0) { //0�ƴ� ����������
					flag = FALSE; //flag=0:��������
					break;
				}
			}

			if (flag = TRUE) { //flag=1:���� �ֽ��ϴ�.
				offset = i;
				position[group] = offset; //������ġ ����
				for (int index = i; index < i + len; index++) //table�� len��ŭ �־��ݴϴ�.
					table[index] = group;

				return offset;
			}
		}
	}

	if (offset < 0) //offset<0 �� ���
		return offset;
	else //offset + s > SIZE �� ���
		return i + len;
}
void clear(int group)
{
	int index;
	for (index = 0; index < SIZE; index++) {//table �ʱ�ȭ
		if (table[index] == group) {
			table[index] = 0;
		}
	}
	position[group] = -1; //������ġ �ʱ�ȭ
}