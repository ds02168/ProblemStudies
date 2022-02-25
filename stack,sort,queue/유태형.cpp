#define SIZE 10000

void my_push(int);
int my_pop(int);
void enqueue(void);

static int temp[SIZE];
static int ts;
static int hold;


void test_main(void)
{
	int stack;
	int site;
	ts = 0;


	for (int i = 0; i < SIZE; i++) //0은temp, 나머지는 stack[site][]
	{
		hold = my_pop(0);
		site = (hold / 128) + 2; //나누는 기준 113

		if (hold == 0)
			my_push(1);
		else
			my_push(site);
	}


	for (int i = 2; i < 10; i++)
	{
		site = my_pop(i);
		my_push(0);

		stack = my_pop(i);
		my_push(1);

		while (stack > 0)
		{
			while (site > stack)
			{
				site = my_pop(0);
				if (site <= stack)
					my_push(0);
				else
					my_push(i);
			}

			while (site <= stack)
			{
				site = my_pop(1);
				if (site <= 0)
					my_push(1);
				else
					my_push(0);

				stack = my_pop(i);
				if (stack <= 0)
					my_push(i);
				else
					my_push(1);
			}
		}

		for (hold = my_pop(0); hold > 0; hold = my_pop(0))
			my_push(i);
		my_push(0);

		hold = my_pop(i);
		while (hold > 0)
		{
			enqueue();
			hold = my_pop(i);
		}
	}

}