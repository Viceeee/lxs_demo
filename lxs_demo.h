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

void lxs_get_random_num(times, range);
void lxs_get_random_num(int times,int range)
{
	int i, a;
	srand((unsigned) time(0));
	for(i = 0;i < times; i++){
		a = rand()%range;
		printf("%d\n",a);
	}
}
