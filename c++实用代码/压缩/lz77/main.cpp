#include <windows.h>   
#include <stdio.h>   
#include <memory.h>   

#include "lz77.h"   
#include "lz77.cpp"   
//////////////////////////////////////////////////////////////////   
// out file format:   
//      0;flag2;buffer;0;flag2;buffer;...flag1;flag2;bufferlast   
// flag1 - 2 bytes, source buffer block length   
//          if block size is 65536, be zero   
// flag2 - 2 bytes, compressed buffer length   
//          if can not compress, be same with flag1   
//////////////////////////////////////////////////////////////////   


int main(int argc, char* argv[])   
{      
/*if (argc != 4)   
{   
puts("Usage: ");   
printf("    Compress : %s c sourcefile destfile\n", argv[0]);   
printf("  Decompress : %s d sourcefile destfile\n", argv[0]);   
return;   
} */  
	
    BYTE soubuf[65536];   
    BYTE destbuf[65536 + 16];   
	
    FILE* in;   
    FILE* out;  
	/* in = fopen("input.txt", "rb");   
    if (in == NULL)   
    {   
	puts("Can't open source file");   
	return;   
    }   
    out = fopen("compress.txt", "wb");   
    if (out == NULL)   
    {   
	puts("Can't open dest file");   
	fclose(in);   
	return;   
    } 
	
	  fseek(in, 0, SEEK_END);   
	  long soulen = ftell(in);   
	  fseek(in, 0, SEEK_SET);   
	  
		CCompressLZ77 cc;   
    WORD flag1, flag2; */ 
	int temp;
    printf("compress(0) or decompress(1)?:");  
	scanf("%d",&temp);
    if (temp == 0) // compress   
    { 
		in = fopen("input.txt", "rb");   
		if (in == NULL)   
		{   
			puts("Can't open source file");   
			return 0;   
		}   
		out = fopen("compress.txt", "wb");   
		if (out == NULL)   
		{   
			puts("Can't open dest file");   
			fclose(in);   
			return 0;   
		} 
		
		fseek(in, 0, SEEK_END);   
		long soulen = ftell(in);   
		fseek(in, 0, SEEK_SET);   
		
		CCompressLZ77 cc;   
		WORD flag1, flag2;  
        int last = soulen, act;   
        while ( last > 0 )   
        {   
            act = min(65536, last);   
            fread(soubuf, act, 1, in);   
            last -= act;   
            if (act == 65536)           // out 65536 bytes                 
                flag1 = 0;         
            else                    // out last blocks   
                flag1 = act;   
            fwrite(&flag1, sizeof(WORD), 1, out);   
			
            int destlen = cc.Compress((BYTE*)soubuf, act, (BYTE*)destbuf);   
            if (destlen == 0)       // can't compress the block   
            {   
                flag2 = flag1;   
                fwrite(&flag2, sizeof(WORD), 1, out);   
                fwrite(soubuf, act, 1, out);   
            }   
            else   
            {   
                flag2 = (WORD)destlen;   
                fwrite(&flag2, sizeof(WORD), 1, out);                  
                fwrite(destbuf, destlen, 1, out);                  
            }   
        }   
    }   
    else if (temp == 1) // decompress   
    {   
		in = fopen("compress.txt", "rb");   
		if (in == NULL)   
		{   
			puts("Can't open source file");   
			return 0;   
		}   
		out = fopen("decompress.txt", "wb");   
		if (out == NULL)   
		{   
			puts("Can't open dest file");   
			fclose(in);   
			return 0;   
		} 
		
		fseek(in, 0, SEEK_END);   
		long soulen = ftell(in);   
		fseek(in, 0, SEEK_SET);   
		
		CCompressLZ77 cc;   
		WORD flag1, flag2;  
        int last = soulen, act;   
        while (last > 0)   
        {   
            fread(&flag1, sizeof(WORD), 1, in);   
            fread(&flag2, sizeof(WORD), 1, in);   
            last -= 2 * sizeof(WORD);   
            if (flag1 == 0)   
                act = 65536;   
            else   
                act = flag1;   
            last-= flag2 ? (flag2) : act;   
			
            if (flag2 == flag1)   
            {   
                fread(soubuf, act, 1, in);                 
            }   
            else   
            {   
                fread(destbuf, flag2, 1, in);   
                if (!cc.Decompress((BYTE*)soubuf, act, (BYTE*)destbuf))   
                {   
                    puts("Decompress error");   
                    fclose(in);   
                    fclose(out);   
                    return 0;   
                }   
            }   
            fwrite((BYTE*)soubuf, act, 1, out);                
        }   
    }   
    else   
    {   
        puts("Usage: ");   
        printf("    Compress : %s c sourcefile destfile\n", argv[0]);   
        printf("  Decompress : %s d sourcefile destfile\n", argv[0]);          
    }   
	
    fclose(in);   
    fclose(out);   
}

