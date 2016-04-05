package FileSocket;

import java.net.Socket;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.OutputStream;


public class Client implements Runnable {
      public String hostname;
      public int portNumber;

      public Client(String host, int port){
        hostname = host;
        portNumber = port;
      }

      public void run(){
        System.out.println("Server address:\t\thttp://" + hostname +":" + Integer.toString(portNumber) + "/");

        try{
            Socket socket = new Socket(hostname, portNumber);
            InputStream in = socket.getInputStream();
            OutputStream out = null;
            try {
                out = new FileOutputStream("Downloads/test.zip");
            }
            catch (IOException e){
                System.out.println("Error! No such file or directory.");
                // System.exit(-1);
            }
            int count;
            System.out.println("Download begin");
            byte[] buffer = new byte[16*1024];
            while ((count = in.read(buffer)) > 0) {
                out.write(buffer, 0, count);
            }
            socket.close();
            out.close();
            in.close();
            System.out.println("Download finish");
            System.out.println("---------------");
        }
        catch (IOException e)  {
          System.out.println("Error! Socket accept IO Exception.");
          // System.exit(-1;
        }
        finally{
          // System.exit(0);
        }
      }

}
