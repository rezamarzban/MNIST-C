#include <stdio.h>
#include <stdlib.h>
#define SIZE 1000

int bitsetcount(int in){
	
	int btsn[256] = {0, 1, 1, 2, 1, 2, 2, 3, 1, 2, 2, 3, 2, 3, 3, 4, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 1, 2, 2, 3, 2, 3, 3, 4, 2, 3, 3, 4, 3, 4, 4, 5, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 2, 3, 3, 4, 3, 4, 4, 5, 3, 4, 4, 5, 4, 5, 5, 6, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 3, 4, 4, 5, 4, 5, 5, 6, 4, 5, 5, 6, 5, 6, 6, 7, 4, 5, 5, 6, 5, 6, 6, 7, 5, 6, 6, 7, 6, 7, 7, 8};
	int ans;
	
	ans = btsn[in];
	
	return ans;
	
}

void showimg(char c[98])
{
    int split = 0;
    
    for(int i=0;i<98;i++){
        for (int j = 7; j >= 0; --j){
        	putchar((c[i] & (1 << j)) ? '1' : '0');
        	split++;
        	if((split % 28) == 0){
        		putchar('\n');
        	}
        }
    }
    putchar('\n');
}

void reportmatch(int m[10]){
	
	int total = 0;
	
	for(int i=0;i<10;i++){
		total = total + m[i];
	}
	
	for(int i=0;i<10;i++){
		
		int occurs = m[i];
		printf("%d: %d%% \n", i, (100*occurs/total));
	}
	
}

int argmax(int mat[10]){
	
	int prediction;
	int check = 0;
	
	for(int i=0;i<10;i++){
		int oc = mat[i];
		
		if(oc > check){
			check = oc;
			prediction = i;
		}
	}
	
	return prediction;
	
}

// Takes string to be encoded as input
// and its length and returns encoded string
char* base64Encoder(char input_str[], int len_str)
{
    // Character set of base64 encoding scheme
    char char_set[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
     
    // Resultant string
    char *res_str = (char *) malloc(SIZE * sizeof(char));
     
    int index, no_of_bits = 0, padding = 0, val = 0, count = 0, temp;
    int i, j, k = 0;
     
    // Loop takes 3 characters at a time from
    // input_str and stores it in val
    for (i = 0; i < len_str; i += 3)
        {
            val = 0, count = 0, no_of_bits = 0;
 
            for (j = i; j < len_str && j <= i + 2; j++)
            {
                // binary data of input_str is stored in val
                val = val << 8;
                 
                // (A + 0 = A) stores character in val
                val = val | input_str[j];
                 
                // calculates how many time loop
                // ran if "MEN" -> 3 otherwise "ON" -> 2
                count++;
             
            }
 
            no_of_bits = count * 8;
 
            // calculates how many "=" to append after res_str.
            padding = no_of_bits % 3;
 
            // extracts all bits from val (6 at a time)
            // and find the value of each block
            while (no_of_bits != 0)
            {
                // retrieve the value of each block
                if (no_of_bits >= 6)
                {
                    temp = no_of_bits - 6;
                     
                    // binary of 63 is (111111) f
                    index = (val >> temp) & 63;
                    no_of_bits -= 6;        
                }
                else
                {
                    temp = 6 - no_of_bits;
                     
                    // append zeros to right if bits are less than 6
                    index = (val << temp) & 63;
                    no_of_bits = 0;
                }
                res_str[k++] = char_set[index];
            }
    }
 
    // padding is done here
    for (i = 1; i <= padding; i++)
    {
        res_str[k++] = '=';
    }
 
    res_str[k] = '\0;';
 
    return res_str;
 
}

/* char_set = "ABCDEFGHIJKLMNOPQRSTUVWXYZ
abcdefghijklmnopqrstuvwxyz0123456789+/" */
 
char* base64Decoder(char encoded[], int len_str)
{
    char* decoded_string;
 
    decoded_string = (char*)malloc(sizeof(char) * SIZE);
 
    int i, j, k = 0;
 
    // stores the bitstream.
    int num = 0;
 
    // count_bits stores current
    // number of bits in num.
    int count_bits = 0;
 
    // selects 4 characters from
    // encoded string at a time.
    // find the position of each encoded
    // character in char_set and stores in num.
    for (i = 0; i < len_str; i += 4) {
        num = 0, count_bits = 0;
        for (j = 0; j < 4; j++) {
            // make space for 6 bits.
            if (encoded[i + j] != '=') {
                num = num << 6;
                count_bits += 6;
            }
 
            /* Finding the position of each encoded
            character in char_set
            and storing in "num", use OR
            '|' operator to store bits.*/
 
            // encoded[i + j] = 'E', 'E' - 'A' = 5
            // 'E' has 5th position in char_set.
            if (encoded[i + j] >= 'A' && encoded[i + j] <= 'Z')
                num = num | (encoded[i + j] - 'A');
 
            // encoded[i + j] = 'e', 'e' - 'a' = 5,
            // 5 + 26 = 31, 'e' has 31st position in char_set.
            else if (encoded[i + j] >= 'a' && encoded[i + j] <= 'z')
                num = num | (encoded[i + j] - 'a' + 26);
 
            // encoded[i + j] = '8', '8' - '0' = 8
            // 8 + 52 = 60, '8' has 60th position in char_set.
            else if (encoded[i + j] >= '0' && encoded[i + j] <= '9')
                num = num | (encoded[i + j] - '0' + 52);
 
            // '+' occurs in 62nd position in char_set.
            else if (encoded[i + j] == '+')
                num = num | 62;
 
            // '/' occurs in 63rd position in char_set.
            else if (encoded[i + j] == '/')
                num = num | 63;
 
            // ( str[i + j] == '=' ) remove 2 bits
            // to delete appended bits during encoding.
            else {
                num = num >> 2;
                count_bits -= 2;
            }
        }
 
        while (count_bits != 0) {
            count_bits -= 8;
 
            // 255 in binary is 11111111
            decoded_string[k++] = (num >> count_bits) & 255;
        }
    }
 
    // place NULL character to mark end of string.
    decoded_string[k] = '\0';
 
    return decoded_string;
}

int main()
{
	
	char encodedimg[] = "AAAAAAAAAAAAGAAAA4AAAHAAAA8AAAHgAAA8AAAHwAAAeAAADwAAAeAAAB/8AAP/4AA//gAH4OAAcB4ABwPAAHD4AAf/AAA/4AAD+AAAAAAAAAAAAAAAAAAAAAAAAAAAAAA=;";

   FILE * fp;
   FILE * label;
   int count = 98;
   char c[98];
   int match[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
   
   int seek = 0;

   fp = fopen("mnistImages.dat", "rb");
   
   label = fopen("mnistLabels.txt", "r");
    
    char* img = base64Decoder(encodedimg, sizeof(encodedimg));
    
    showimg(img);
    
    int limdif = 100;

   while(feof(fp) == 0)
    {

        fread(&c, sizeof(char), count, fp);
        seek++;
        
        int cnt = 0;
        
        for(int i=0;i<count;i++){
        int comp = (int)img[i] ^ (int)c[i];
        cnt = cnt + bitsetcount(comp);
        }
        
        if(cnt<limdif){
        	
        	int prediction;
        	char l;
        	
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
   
   /*
 /	@author: Reza Marzban
 /
 /	GitHub.com/marzban2030/MNIST-C
 /
 /	Ver: 1.00
 /
 */


}
