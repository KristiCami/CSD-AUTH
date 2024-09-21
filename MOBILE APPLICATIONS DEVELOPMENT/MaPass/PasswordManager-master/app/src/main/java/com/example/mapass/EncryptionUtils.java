package com.example.mapass;

import android.os.Build;

import androidx.annotation.RequiresApi;

import javax.crypto.Cipher;
import javax.crypto.SecretKey;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.PBEKeySpec;
import javax.crypto.spec.PBEParameterSpec;
import java.security.spec.AlgorithmParameterSpec;
import java.security.spec.KeySpec;
import java.util.Base64;

public class EncryptionUtils {
    private static final String ENCRYPTION_ALGORITHM = "PBEWithMD5AndDES";
    private static final String ENCRYPTION_PASSWORD = "j^D0bqKzV@y#4&8";
    private static final byte[] SALT = {0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07, 0x08};

    @RequiresApi(api = Build.VERSION_CODES.O)
    public static String encrypt(String password) {
        try {
            SecretKeyFactory keyFactory = SecretKeyFactory.getInstance(ENCRYPTION_ALGORITHM);
            KeySpec keySpec = new PBEKeySpec(ENCRYPTION_PASSWORD.toCharArray(), SALT, 65536, 256);
            SecretKey secretKey = keyFactory.generateSecret(keySpec);

            Cipher cipher = Cipher.getInstance(ENCRYPTION_ALGORITHM);
            AlgorithmParameterSpec paramSpec = new PBEParameterSpec(SALT, 100);
            cipher.init(Cipher.ENCRYPT_MODE, secretKey, paramSpec);

            byte[] encryptedBytes = cipher.doFinal(password.getBytes("UTF-8"));
            return Base64.getEncoder().encodeToString(encryptedBytes);
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }

    @RequiresApi(api = Build.VERSION_CODES.O)
    public static String decrypt(String encryptedPassword) {
        try {
            SecretKeyFactory keyFactory = SecretKeyFactory.getInstance(ENCRYPTION_ALGORITHM);
            KeySpec keySpec = new PBEKeySpec(ENCRYPTION_PASSWORD.toCharArray(), SALT, 65536, 256);
            SecretKey secretKey = keyFactory.generateSecret(keySpec);

            Cipher cipher = Cipher.getInstance(ENCRYPTION_ALGORITHM);
            AlgorithmParameterSpec paramSpec = new PBEParameterSpec(SALT, 100);
            cipher.init(Cipher.DECRYPT_MODE, secretKey, paramSpec);

            byte[] decodedBytes = Base64.getDecoder().decode(encryptedPassword);
            byte[] decryptedBytes = cipher.doFinal(decodedBytes);
            return new String(decryptedBytes, "UTF-8");
        } catch (Exception e) {
            e.printStackTrace();
            return null;
        }
    }
}



