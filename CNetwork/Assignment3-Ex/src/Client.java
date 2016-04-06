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

            int count;
            System.out.println("Download begin");

            //get Filename length
            byte[] lengthBuffer = new byte[1];

            byte[] buffer = new byte[16*1024];

            in.read(lengthBuffer);
            int length = (int)lengthBuffer[0];
            byte[] nameBuffer = new byte[length];
            //read Filename
            in.read(nameBuffer,0,length);
            String filename = new String(nameBuffer);
            System.out.println(length);
            System.out.println(filename);

            try {
                System.out.println("Downloads/"+filename);
                out = new FileOutputStream("Downloads/"+filename);
            }

            catch (IOException e){
                System.out.println("Error! No such file or directory.");
                // System.exit(-1);
            }

            //read File

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
