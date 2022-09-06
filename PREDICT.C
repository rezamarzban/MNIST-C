#include <stdio.h>

int bitsetcount(int in){
	
	int btsn[256] = 
	{0, 1, 1, 2, 1, 2, 2, 3, 1, 2,
	 2, 3, 2, 3, 3, 4, 1, 2, 2, 3,
	 2, 3, 3, 4, 2, 3, 3, 4, 3, 4,
	 4, 5, 1, 2, 2, 3, 2, 3, 3, 4,
	 2, 3, 3, 4, 3, 4, 4, 5, 2, 3,
	 3, 4, 3, 4, 4, 5, 3, 4, 4, 5,
	 4, 5, 5, 6, 1, 2, 2, 3, 2, 3,
	 3, 4, 2, 3, 3, 4, 3, 4, 4, 5,
	 2, 3, 3, 4, 3, 4, 4, 5, 3, 4,
	 4, 5, 4, 5, 5, 6, 2, 3, 3, 4,
	 3, 4, 4, 5, 3, 4, 4, 5, 4, 5,
	 5, 6, 3, 4, 4, 5, 4, 5, 5, 6,
	 4, 5, 5, 6, 5, 6, 6, 7, 1, 2,
	 2, 3, 2, 3, 3, 4, 2, 3, 3, 4,
	 3, 4, 4, 5, 2, 3, 3, 4, 3, 4,
	 4, 5, 3, 4, 4, 5, 4, 5, 5, 6,
	 2, 3, 3, 4, 3, 4, 4, 5, 3, 4,
	 4, 5, 4, 5, 5, 6, 3, 4, 4, 5,
	 4, 5, 5, 6, 4, 5, 5, 6, 5, 6,
	 6, 7, 2, 3, 3, 4, 3, 4, 4, 5,
	 3, 4, 4, 5, 4, 5, 5, 6, 3, 4,
	 4, 5, 4, 5, 5, 6, 4, 5, 5, 6,
	 5, 6, 6, 7, 3, 4, 4, 5, 4, 5,
	 5, 6, 4, 5, 5, 6, 5, 6, 6, 7,
	 4, 5, 5, 6, 5, 6, 6, 7, 5, 6,
	 6, 7, 6, 7, 7, 8};
	
	int ans;
	
	ans = btsn[in];
	
	return ans;
	
}

void showimg(char c[98])
{
    int split = 0;
    int i, j;
    
    for(i=0;i<98;i++){
        for (j = 7; j >= 0; --j){
        	putchar((c[i] & (1 << j)) ? '1' : '0');
        	split++;
        	if((split % 28) == 0){
        		putchar('\n');
        	}
        }
    }
    putchar('\n');
}

void reportmatch(int m[10])
{
	int total = 0;
	int i, occurs;
	
	for(i=0;i<10;i++){
		total = total + m[i];
	}
	for(i=0;i<10;i++){
		occurs = m[i];
		printf("%d: %d%% \n", i, (100*occurs/total));
		
	}
}

int argmax(int mat[10])
{
	int prediction;
	int check = 0;
	int i;
	
	for(i=0;i<10;i++){
		int oc = mat[i];
		if(oc > check){
			check = oc;
			prediction = i;
		}
	}
	return prediction;
}

int main()
{

   FILE * fp;
   FILE * label;
   int count = 98;
   char img[98];
   char c[98];
   int match[] = 
   {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
   int seek = 0;
   int limdif = 100;
   int i, cnt, comp;
   int prediction;
   char l;

   fp = fopen("mnistImages.dat", "rb");
   
   label = fopen("mnistLabels.txt", "r");
   

   seek= 2;
   fseek(fp, seek*count, SEEK_SET);
   fread(&img, sizeof(char), count, fp);
   seek++;


    showimg(img);
    while(feof(fp) == 0)
    {

        fread(&c, sizeof(char), count, fp);
        seek++;
        cnt = 0;
        for(i=0;i<count;i++){
        comp = (int)img[i] ^ (int)c[i];
        cnt = cnt + bitsetcount(comp);
        }
        
        if(cnt<limdif){
        	limdif = cnt;
        	fseek(label, ((seek-1)*2), SEEK_SET);
        	fread(&l, sizeof(char), 1, label);
        	prediction = l - '0';
        	match[prediction]++;
        }
   }
   
   printf("It is probably a digit %d.\nMatch percents:\n", argmax(match));
   
   reportmatch(match);
   
   fclose(label);
   fclose(fp);
   
   return 0;

}
