#include <stdio.h>
#include <conio.h>
#include <stdint.h>     
#include <string.h>     
#include <wmmintrin.h>  

#define ENCODE_FTN(mess,k) \
        mess = _mm_xor_si128(mess, k[ 0]); \
        mess = _mm_aesenc_si128(mess, k[ 1]); \
        mess = _mm_aesenc_si128(mess, k[ 2]); \
        mess = _mm_aesenc_si128(mess, k[ 3]); \
        mess = _mm_aesenc_si128(mess, k[ 4]); \
        mess = _mm_aesenc_si128(mess, k[ 5]); \
        mess = _mm_aesenc_si128(mess, k[ 6]); \
        mess = _mm_aesenc_si128(mess, k[ 7]); \
        mess = _mm_aesenc_si128(mess, k[ 8]); \
        mess = _mm_aesenc_si128(mess, k[ 9]); \
        mess = _mm_aesenclast_si128(mess, k[10]);\


#define DECODE_FTN(mess,k) \
        mess = _mm_xor_si128(mess, k[10]); \
        mess = _mm_aesdec_si128(mess, k[11]); \
        mess = _mm_aesdec_si128(mess, k[12]); \
        mess = _mm_aesdec_si128(mess, k[13]); \
        mess = _mm_aesdec_si128(mess, k[14]); \
        mess = _mm_aesdec_si128(mess, k[15]); \
        mess = _mm_aesdec_si128(mess, k[16]); \
        mess = _mm_aesdec_si128(mess, k[17]); \
        mess = _mm_aesdec_si128(mess, k[18]); \
        mess = _mm_aesdec_si128(mess, k[19]); \
        mess = _mm_aesdeclast_si128(mess, k[0]);\
   
// Macro ENCODE_FTN defined to perform all the AES NI encryption functions.The _mm_xor_si128() is used to perform EX-OR Operation on 128-bit message & the key.The _mm_aesenc_si128() is a AES NI operation ,used to perform one round of encryption. The _mm_aesenclast_si128() is a AES NI operation ,used to perform last round of encryption. The Macro DECODE_FTN defined to perform all the AES NI decryption functions.The _mm_aesdec_si128() is a AES NI operation ,used to perform one round of decryption.The _mm_aesdeclast_si128() is a AES NI operation ,used to perform last round of decryption.

static __m128i keytrans(__m128i key, __m128i keyg){ //This function is used to perform key expansion, using _mm_shuffle_epi32(), _mm_slli_si128() & _mm_xor_si128() instructions respectively. 
	__m128i temp;
	
	keyg = _mm_shuffle_epi32(keyg, _MM_SHUFFLE(3,3,3,3));

	temp = _mm_slli_si128(key, 4);
	key = _mm_xor_si128(key, temp);
	temp = _mm_slli_si128(temp, 4);
	key = _mm_xor_si128(key, temp);
	temp = _mm_slli_si128(temp, 4);
	key = _mm_xor_si128(key, temp);
	key = _mm_xor_si128(key, keyg);

	return key;
}


static void keyloader(uint8_t *encryptkey, __m128i *key_schedule){

	__m128i	keygened;

    key_schedule[0] = _mm_loadu_si128((const __m128i*) encryptkey);// _mm_loadu_si128() is used to load one byte key into the memory

    keygened = _mm_aeskeygenassist_si128(key_schedule[0], 0x01); //_mm_aeskeygenassist_si128() is used to generate round keys for encryption.
    key_schedule[1]  = keytrans(key_schedule[0], keygened);
    
    keygened = _mm_aeskeygenassist_si128(key_schedule[1], 0x02);
    key_schedule[2]  = keytrans(key_schedule[1], keygened);

    keygened = _mm_aeskeygenassist_si128(key_schedule[2], 0x04);
    key_schedule[3]  = keytrans(key_schedule[2],keygened);

    keygened = _mm_aeskeygenassist_si128(key_schedule[3], 0x08);
    key_schedule[4]  = keytrans(key_schedule[3], keygened);

    keygened = _mm_aeskeygenassist_si128(key_schedule[4], 0x10);
    key_schedule[5]  = keytrans(key_schedule[4], keygened);

    keygened = _mm_aeskeygenassist_si128(key_schedule[5], 0x20);
    key_schedule[6]  = keytrans(key_schedule[5], keygened);

    keygened = _mm_aeskeygenassist_si128(key_schedule[6], 0x40);
    key_schedule[7]  = keytrans(key_schedule[6], keygened);
	
	keygened = _mm_aeskeygenassist_si128(key_schedule[7], 0x80);
    key_schedule[8]  = keytrans(key_schedule[7], keygened);
 	
 	keygened = _mm_aeskeygenassist_si128(key_schedule[8], 0x1b);
    key_schedule[9]  = keytrans(key_schedule[8], keygened);
 	
 	keygened = _mm_aeskeygenassist_si128(key_schedule[9], 0x36);
    key_schedule[10] = keytrans(key_schedule[9], keygened);
    
    key_schedule[11] = _mm_aesimc_si128(key_schedule[9]); //_mm_aesimc_si128() is used to convert the key generated into a form that can be used for decryption.
    key_schedule[12] = _mm_aesimc_si128(key_schedule[8]);
    key_schedule[13] = _mm_aesimc_si128(key_schedule[7]);
    key_schedule[14] = _mm_aesimc_si128(key_schedule[6]);
    key_schedule[15] = _mm_aesimc_si128(key_schedule[5]);
    key_schedule[16] = _mm_aesimc_si128(key_schedule[4]);
    key_schedule[17] = _mm_aesimc_si128(key_schedule[3]);
    key_schedule[18] = _mm_aesimc_si128(key_schedule[2]);
    key_schedule[19] = _mm_aesimc_si128(key_schedule[1]);
}

static void encallftn(__m128i *key_schedule, uint8_t *plainText,uint8_t *cipherText){
    __m128i mess = _mm_loadu_si128((__m128i *) plainText); // _mm_loadu_si128() is used to load one byte plaintext message into the memory

    ENCODE_FTN(mess,key_schedule);

    _mm_storeu_si128((__m128i *) cipherText, mess); //_mm_storeu_si128() is used to store the 1 byte encrypted message into the memory
}

static void decallftn(__m128i *key_schedule, uint8_t *cipherText,uint8_t *plainText){
    __m128i mess = _mm_loadu_si128((__m128i *) cipherText); // _mm_loadu_si128() is used to load one byte encrypted message into the memory

    DECODE_FTN(mess,key_schedule);

    _mm_storeu_si128((__m128i *) plainText, mess); //_mm_storeu_si128() is used to store the 1 byte decrypted message into the memory
}


int main(){
	uint8_t hexmess[16] ;
	uint8_t encryptkey[] = {0x7a, 0x1c, 0x93, 0xdb, 0x7d, 0xde, 0x2c, 0x43, 0x99, 0x62, 0x75, 0x72, 0x05, 0xd0, 0xde, 0x15};
    uint8_t generatedcipher[16];
    uint8_t generatedtxt[16];
    int i=0;
    __m128i key_schedule[20];

	printf("\tAES-NI Encryption & Decryption using C");

	printf("\nEnter the text you want to encrypt:");
	for(i=0;i<16;i++){

	scanf("%c",&hexmess[i]);
    }
    
    keyloader(encryptkey,key_schedule);
    encallftn(key_schedule,hexmess,generatedcipher);

    printf("Encrypted text is:\t");
    for(i=0; i<16; i++)
    printf("%c ",generatedcipher[i]);

    decallftn(key_schedule,generatedcipher,generatedtxt);
    printf("\n");

    printf("Decrypted text is:\t");
    for(i=0; i<16; i++)
    printf("%c",generatedtxt[i]);

getch();
}



