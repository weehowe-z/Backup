package FileSocket;

import java.net.Socket;
import java.net.ServerSocket;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;


public class Server implements Runnable {
    // public static final File myFile = new File("helloworld.txt");
    public int portNumber;
    public String filename;
    public File file;

    public Server(File f,String n, int p) {
      file = f;
      filename = n;
      portNumber = p;
    }

    public void run (){
      // File file = new File("test.zip");

      // int portNumber = 2680;
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
              System.out.println("Server is listening!");
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
            System.out.println(e);
            System.exit(-1);
        } finally{
            System.out.println("close listening");
            try {
                serverSocket.close();
            }
            catch (IOException e){
              System.out.println(e);
              System.exit(-1);
            }
            System.exit(0);
        }
    }

}
