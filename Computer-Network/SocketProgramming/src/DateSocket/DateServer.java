package DateSocket;

import java.net.Socket;
import java.net.ServerSocket;
import java.io.PrintWriter;
import java.util.Date;
/**
 * A TCP server that runs on port 9090.  When a client connects, it
 * sends the client the current date and time, then closes the
 * connection with that client.  Arguably just about the simplest
 * server you can write.
 */
public class DateServer {

    /**
     * Runs the server.
     */
    public static void main(String[] args) throws Exception {
        if (args.length != 1){
          System.out.println("Please specify the port number!");
          System.exit(-1);
        }
        int portNumber = Integer.parseInt(args[0]);
        System.out.println(args[0]);
        ServerSocket serverSocket = new ServerSocket(portNumber);

        try {
            while (true) {
                System.out.println("server is listening!");
                Socket clientSocket = serverSocket.accept();
                try {
                  System.out.println("deal with output");
                  PrintWriter out = new PrintWriter(clientSocket.getOutputStream(), true);
                  out.println(new Date().toString());
                } finally {
                  System.out.println("closing the socket");
                  clientSocket.close();
                }
            }
        }
        catch (Exception e){
          System.out.println("error");
        }
        finally {
          System.out.println("close listening");
          serverSocket.close();
        }
    }
}
