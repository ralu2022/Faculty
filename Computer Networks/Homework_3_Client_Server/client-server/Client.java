import java.io.*;
import java.net.InetAddress;
import java.net.Socket;
import java.net.UnknownHostException;
import java.math.BigInteger;
import java.security.SecureRandom;

public class Client {

    public static void main(String[] args) {
        Socket socket = null;
        DataInputStream input = null;
        DataOutputStream out = null;
        DataInputStream in = null;

        try {
            socket = new Socket(InetAddress.getLocalHost(), 2024);
            System.out.println("Connected");

            input = new DataInputStream(System.in);
            out = new DataOutputStream(socket.getOutputStream());
            in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));

            // parametrii Diffie-Hellman
            BigInteger p = new BigInteger("11"); // numar prim
            BigInteger g = new BigInteger("2");  // radacina primitiva

            // cheie privata client
            BigInteger a = new BigInteger(1024, new SecureRandom());
            // cheie publica client
            BigInteger A = g.modPow(a, p);

            // trimitea cheii publice a clientului catre server
            out.writeUTF(A.toString());

            // primirea cheii publice a serverului
            BigInteger B = new BigInteger(in.readUTF());

            // calcularea cheii secrete partajate
            BigInteger K = B.modPow(a, p);
            int secretKey = K.intValue();

            System.out.println("Shared secret key (K): " + secretKey);

            // Primele 5 paragrafe din Lorem ipsum

            String message = "Lorem ipsum dolor sit amet, consectetur adipiscing elit. "
                    + "Sed do eiusmod tempor incididunt ut labore et dolore magna aliqua. "
                    + "Ut enim ad minim veniam, quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat. "
                    + "Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur. "
                    + "Excepteur sint occaecat cupidatat non proident, sunt in culpa qui officia deserunt mollit anim id est laborum.";


            // criptarea mesajului utilizand Caesar Cipher
            String encryptedMessage = caesarCipher(message, secretKey);

            // trimiterea la server a mesajului criptat
            out.writeUTF(encryptedMessage);

            input.close();
            out.close();
            socket.close();
        } catch (UnknownHostException u) {
            System.out.println(u);
        } catch (IOException i) {
            System.out.println(i);
        }
    }

    public static String caesarCipher(String text, int shift) {
        StringBuilder result = new StringBuilder();
        for (char character : text.toCharArray()) {
            if (Character.isLetter(character)) {
                char base = Character.isLowerCase(character) ? 'a' : 'A';
                result.append((char) ((character - base + shift) % 26 + base));
            } else {
                result.append(character);
            }
        }
        return result.toString();
    }
}
