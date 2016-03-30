package DateSocket;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.Socket;

public class DateClient {
      /**
       * Runs the client as an application.  First it displays a dialog
       * box asking for the IP address or hostname of a host running
       * the date server, then connects to it and displays the date that
       * it serves.
       */
      public static void main(String[] args) throws IOException {

        if (args.length != 1){
          System.out.println("Please specify the port number!");
          System.exit(-1);
        }

        String serverAddress = "0.0.0.0";
        int portNumber = Integer.parseInt(args[0]);

        try{
          Socket socket = new Socket(serverAddress, portNumber);
          BufferedReader input =
              new BufferedReader(new InputStreamReader(socket.getInputStream()));
          // BufferedReader input =
          // new BufferedReader(new InputStreamReader(System.in));
          String inputText = input.readLine();
          System.out.println(inputText);
        }
        catch (Exception e)  {
          System.out.println("error");
          System.exit(-1);
        }
        finally{
          System.exit(0);
        }
      }
}
