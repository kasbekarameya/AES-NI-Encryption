import os
import time
from cryptography.hazmat.primitives.ciphers import Cipher, algorithms, modes
from cryptography.hazmat.backends import default_backend

start_time = time.time()

print("\tPERFORMING AES ENCRYPTION & DECRYPTION")

backend = default_backend() # The default_backend() is used to provide methods for encryption & decryption. 
newkey = os.urandom(16) # The unrandom() is used to generate 128 bit or 16 byte key. 

plaintext ="Hi this is Ameya" #input("\nEnter plaintext to encrypt:")

def padding(temptext): #padding() function is used to pad the plaintext to make its length to 16 or 32 bytes.

	if(len(temptext)<16):
		s = (16 - len(temptext)) % 16
		temptext = temptext + "%"*s  
		return temptext
	elif(len(temptext)>16):
		s = (32 - len(temptext)) % 32
		temptext = temptext + "%"*s
		return temptext
	else:
		return temptext

newptext = padding(plaintext).encode() # This is used to convert padded plaintext to byte type.

cipher = Cipher(algorithms.AES(newkey), modes.ECB(), backend=backend) #Here we create a Cipher object that takes three parameters i.e. Algorithm used, Mode used & Backend used.

def aesencrypt(): # aesenc() is used to encrypt the plaintext
	encpt = cipher.encryptor()
	tempcyt = encpt.update(newptext) + encpt.finalize()
	return tempcyt
	
def aesdecrypt(tempcyt): #desenc() is used to decrypt the ciphertext
	decpt = cipher.decryptor()
	tempdyt = decpt.update(tempcyt) + decpt.finalize()
	return tempdyt

for i in range(0-999):
	ciphertext = aesencrypt()
	print("\nEnrypted text is:",ciphertext)

'''deciphertext = aesdecrypt(ciphertext)	
dt = deciphertext.decode().replace("%","") # This is used to remove extra padded characters once the decryption process is complete. 
print("\nDecrypted text is:",dt)
'''
print("--- %s seconds ---" % (time.time() - start_time))