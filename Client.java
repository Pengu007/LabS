import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.Socket;
import java.util.Scanner;

public class Client {
    public static void main(String[] args) {
        try {
            // Connect to the server on a specific address and port
            Socket socket = new Socket("localhost", 12345);

            // Get input and output streams for communication
            InputStream inputStream = socket.getInputStream();
            OutputStream outputStream = socket.getOutputStream();

            Scanner scanner = new Scanner(System.in);

            while (true) {
                // Send data to the server
                System.out.print("Enter a message for Server: ");
                String message = scanner.nextLine();
		if("END".equalsIgnoreCase(message)){
			outputStream.write(message.getBytes());
			break;
		}
		else{
                	outputStream.write(message.getBytes());

               		// Read the response from the server
                	byte[] buffer = new byte[1024];
                	int bytesRead = inputStream.read(buffer);
                	String serverResponse = new String(buffer, 0, bytesRead);
                	System.out.println("Received from Server: " + serverResponse);
            	}
	    }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
