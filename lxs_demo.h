#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*int main(){

//      int a = rand() % 513 ;
//      printf("%d\n",a);
//      这种情况就只生成一个重复的rand数
        int a, i;
//      srand((unsigned) time(1) );             cause segmentation fault
        srand((unsigned) time(0) );
        for(i = 0; i < 10; i++){
                a= rand()% 513;
                printf("%d\n",a);
        }

        return 0;
}
//这样就会生成不同的10个rand数，区间范围在0-512之间
*/

void lxs_get_random_num(int times,int range);
void lxs_get_random_num(int times,int range){
	int i, a;
	srand((unsigned) time(0));
	for(i = 0;i < times; i++){
		a = rand()%range;
		printf("%d\n",a);
	}
}

void lxs_get_2_num_max();
void lxs_get_2_num_max(){
	int a, b;
	printf("please insert 2 num,split with space\n");
	scanf("%d %d",&a, &b);
	if (a > b)
		printf("%d is bigger than %d\n", a, b);
	else if(a < b)
		printf("%d is bigger than %d\n", b ,a);
	else
		printf("%d is the same\n", a );
}



/*
void lxs_get_num_max(int num[], int len);
先搞两个数的吧
void lxs_get_num_max(int num[], int len ){
	//selection_sort
	int i, j, temp, a, b;
	for ( i = 0; i < len -1; i++){
		int min = i;
		for (j = i + 1; j < len; j++)//走访未排序的元素
		  if(num[j] < num[min]){	//找到目前的最小值
			min = j;				//记录最小值
			//下面是直接交换的函数 
			//解释以及源代码为https://www.runoob.com/w3cnote/selection-sort.html
			temp = num[min];		
			num[min] = num[j];
			num[j]= temp;
		  }
	}
		printf("sort array = %s\n ", num[1]);
}
*/


























