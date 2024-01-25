import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;
import java.net.ServerSocket;
import java.net.Socket;
import java.util.Scanner;

public class Server {
    public static void main(String[] args) {
        try {
            // Create a server socket to listen on a specific port
            ServerSocket serverSocket = new ServerSocket(12345);
            System.out.println("Waiting for a connection...");

            // Accept a client connection
            Socket clientSocket = serverSocket.accept();
            System.out.println("Connection established.");

            // Get input and output streams for communication
            InputStream inputStream = clientSocket.getInputStream();
            OutputStream outputStream = clientSocket.getOutputStream();

            while (true) {
                // Read data from the client
                byte[] buffer = new byte[1024];
                int bytesRead = inputStream.read(buffer);
                String clientMessage = new String(buffer, 0, bytesRead);
                System.out.println("Received from Client: " + clientMessage);
		if("END".equalsIgnoreCase(clientMessage)){
			break;
		}

                // Send a response back to the client
		Scanner scanner = new Scanner(System.in);
		System.out.print("Replii a message for Client: ");
                String serverResponse = scanner.nextLine();
                outputStream.write(serverResponse.getBytes());
                System.out.println("Sent to Client: " + serverResponse);
            }
        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
