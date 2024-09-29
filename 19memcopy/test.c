#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/// @brief 内存拷贝 单个字节拷贝 效率比较低
/// @param dst ,目的地址
/// @param src ,原地址
/// @param len ,拷贝的字节数
/// @return (void *)
void* my_memcpy(void *dst, const void *src, size_t len)
{
	if(NULL == dst || NULL == src){
		return NULL;
	}
	void *ret = dst;
	if(dst <= src || (char *)dst >= (char *)src + len){
		//没有内存重叠，从低地址开始复制
		while(len--){
			*(char *)dst = *(char *)src;
			dst = (char *)dst + 1;
			src = (char *)src + 1;
		}
	}else{
		//有内存重叠，从高地址开始复制
		src = (char *)src + len - 1;
		dst = (char *)dst + len - 1;
		while(len--){
			*(char *)dst = *(char *)src;
			dst = (char *)dst - 1;
			src = (char *)src - 1;
		}
	}
	return ret;
}


int main(int argc, char * argv[]){

    char s[20]="hello_world!";
    char d[20]="xxxxxxxxxxxxxxx";
    char num[6]="12345";
    char num2[6]="12345";

    memcpy(num,num+2,3);
    printf("num:%s\n",num);

    my_memcpy(num2,num2+2,3);
    printf("num2:%s\n",num2);

    return 0;
}