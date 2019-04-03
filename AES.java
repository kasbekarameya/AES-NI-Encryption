import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.Arrays;
import java.util.Base64;
 
import javax.crypto.Cipher;
import javax.crypto.spec.SecretKeySpec;
 
public class AES {
 
    private static SecretKeySpec secretKey;
    private static byte[] key;
 
    public static void setKey(String myKey)
    {
        MessageDigest sha = null;
        try {
            key = myKey.getBytes("UTF-8");
            sha = MessageDigest.getInstance("SHA-1");
            key = sha.digest(key);
            key = Arrays.copyOf(key, 16);
            secretKey = new SecretKeySpec(key, "AES");
        }
        catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        }
        catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
    }
 
    public static String encrypt(String strToEncrypt, String secret)
    {
        try
        {
            setKey(secret);
            Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5Padding");
            cipher.init(Cipher.ENCRYPT_MODE, secretKey);
            return Base64.getEncoder().encodeToString(cipher.doFinal(strToEncrypt.getBytes("UTF-8")));
        }
        catch (Exception e)
        {
            System.out.println("Error while encrypting: " + e.toString());
        }
        return null;
    }
 
    public static String decrypt(String strToDecrypt, String secret)
    {
        try
        {
            setKey(secret);
            Cipher cipher = Cipher.getInstance("AES/ECB/PKCS5PADDING");
            cipher.init(Cipher.DECRYPT_MODE, secretKey);
            return new String(cipher.doFinal(Base64.getDecoder().decode(strToDecrypt)));
        }
        catch (Exception e)
        {
            System.out.println("Error while decrypting: " + e.toString());
        }
        return null;
    }
    public static void main(String[] args)
{
    final String secretKey = "ssshhhhhhhhhhh!!!!";
    
    String originalString = "howtodoinjava.com";

    long startTime = System.nanoTime();
    String encryptedString = AES.encrypt(originalString, secretKey) ;
    long endTime   = System.nanoTime();
    long totalencTime = endTime - startTime;
    System.out.println("Encryption Time:"+totalencTime);

    long startTime1 = System.nanoTime();
    String decryptedString = AES.decrypt(encryptedString, secretKey) ;
    long endTime1   = System.nanoTime();
    long totaldecTime = endTime1 - startTime1;
    System.out.println("Decryption Time:"+totaldecTime);

    System.out.println(originalString);
    System.out.println(encryptedString);
    System.out.println(decryptedString);
}
}

