package FileSocket;

import java.net.Socket;
import java.net.ServerSocket;
import java.io.File;
import java.io.FileInputStream;
// import java.io.PrintWriter;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;


public class Server {
    // public static final File myFile = new File("helloworld.txt");
    public static void main(String[] args) throws Exception {

        File file = new File("test.zip");



        int portNumber;
        if (args.length == 0){
            portNumber = 2680;
        }
        else if (args.length == 1){
            portNumber = Integer.parseInt(args[0]);
        }
        else {
            System.out.println("Please give correct args or omit it to use default setting!");
            System.exit(-1);
            return;
        }
        System.out.println("Server address:\t\thttp://0.0.0.0:" + Integer.toString(portNumber) + "/");

        ServerSocket serverSocket = null;
        try {
            serverSocket = new ServerSocket(portNumber);
        } catch (IOException e){
            System.out.println("Error! Can't setup server on this port number, may be occupied.");
            System.exit(-1);
        }
        System.out.println("Server running...\tPress ctrl-c to stop.");

        try {
            while (true) {
                System.out.println("server is listening!");
                Socket clientSocket = serverSocket.accept();
                int count;
                byte[] buffer = new byte[16*1024];
                InputStream in = new FileInputStream(file);
                OutputStream out = clientSocket.getOutputStream();
                while ((count = in.read(buffer)) > 0) {
                    out.write(buffer, 0, count);
                }
                clientSocket.close();
                out.close();
                in.close();
            }
          } catch (IOException e){
              System.out.println("Error! Socket accept IO Exception.");
          } finally{
              System.out.println("close listening");
              serverSocket.close();
          }
    }
}
