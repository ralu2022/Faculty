import java.io.*;
import java.net.ServerSocket;
import java.net.Socket;
import java.math.BigInteger;
import java.security.SecureRandom;

public class Server {
	public static void main(String[] args) {
		Socket socket = null;
		ServerSocket server = null;
		DataInputStream in = null;
		DataOutputStream out = null;

		try {
			server = new ServerSocket(2024);
			System.out.println("Server started");
			System.out.println("Waiting for a client ...");

			socket = server.accept();
			System.out.println("Client accepted");

			in = new DataInputStream(new BufferedInputStream(socket.getInputStream()));
			out = new DataOutputStream(socket.getOutputStream());

			// parametrii Diffie-Hellman
			BigInteger p = new BigInteger("11"); // prime number
			BigInteger g = new BigInteger("2");  // primitive root modulo p

			// cheie privata server
			BigInteger b = new BigInteger(1024, new SecureRandom());
			// cheie publica server
			BigInteger B = g.modPow(b, p);

			// receptionare cheie publica client
			BigInteger A = new BigInteger(in.readUTF());

			// trimitere cheie publica catre client
			out.writeUTF(B.toString());

			// calculare cheii secrete partajate
			BigInteger K = A.modPow(b, p);
			int secretKey = K.intValue();

			System.out.println("Shared private key (K): " + secretKey);

			// receptionare mesaj criptat de la client
			String encryptedMessage = in.readUTF();
			System.out.println("Encrypted message from client: " + encryptedMessage);

			// descifrare mesaj cu Caesar Cipher
			String decryptedMessage = caesarCipher(encryptedMessage, 26 - secretKey);
			System.out.println("Decrypted message: " + decryptedMessage);

			socket.close();
			in.close();
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
