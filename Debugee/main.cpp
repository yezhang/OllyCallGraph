typedef int(*Fun)(int);

typedef struct MyStruct
{
	int a;
	Fun functor;
} Data, *pData;

int globalFun(int a) {
	return a + 1;
}

Data data;



int main() {
	data.a = 5;
	data.functor = globalFun;

	while (true)
	{
		data.a = data.functor(data.a);
	}
	

	return 0;
}