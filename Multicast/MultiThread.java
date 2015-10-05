import java.net.MulticastSocket;
import java.net.InetAddress;
import java.net.DatagramPacket;
import java.net.URI;

import java.io.File;
import java.io.BufferedInputStream;
import java.io.InputStream;
import java.io.FileOutputStream;
import java.io.FileInputStream;
import java.util.Properties;//read conf

import org.apache.hadoop.conf.Configuration;
import org.apache.hadoop.fs.*;
import org.apache.hadoop.io.IOUtils;

public class MultiThread{
    public static void main(String args[]) throws Exception{
        Thread Server = new Thread(new MulticastSocketServer());
        Thread Client = new Thread(new MulticastSocketClient());
        Thread Copy = new Thread(new FileCopyToHDFS());

        Client.start();
        Thread.sleep(2000);
        Server.start();
        Client.join();//wait client to stop
        Copy.start();
    }
}

class MulticastSocketServer implements Runnable {
    public void run() {
        //read config files
        try {
            Properties property = new Properties();
            FileInputStream propertyFile = new FileInputStream("MulticastConfig.conf");
            property.load(propertyFile);
            propertyFile.close();

            String Inet_Address = property.getProperty("Inet_Address");
            String File_Address = property.getProperty("Input_File_Address");
            int Buffer_Size = Integer.parseInt(property.getProperty("Buffer_Size"));
            int Port = Integer.parseInt(property.getProperty("Port"));

            InetAddress Group = InetAddress.getByName(Inet_Address);
            FileInputStream InputFile = new FileInputStream(File_Address);

            int count = 0;
            byte[] buff = new byte[Buffer_Size];
            
            MulticastSocket serverSocket = new MulticastSocket();

            while(true){
                int readBytesLength = InputFile.read(buff);
                if (readBytesLength == -1) break;//read() will return -1 if has no bytes to read
                //System.out.println("Send packet " + (++count));
                DatagramPacket packet = new DatagramPacket(buff,0,readBytesLength,Group,Port);
                serverSocket.send(packet);
                Thread.sleep(1);
            }
            InputFile.close();
        }
        catch (Exception e)
        {
            System.out.println("MulticastSocketServer Error");
        }
    }
}

class MulticastSocketClient implements Runnable {
    public void run() {
        try{
            //read config files
            Properties property = new Properties();
            FileInputStream propertyFile = new FileInputStream("MulticastConfig.conf");
            property.load(propertyFile);
            propertyFile.close();

            String Inet_Address = property.getProperty("Inet_Address");
            String File_Address = property.getProperty("Output_File_Address");
            int Timeout_Milliseconds = Integer.parseInt(property.getProperty("Timeout_Milliseconds"));
            int Buffer_Size = Integer.parseInt(property.getProperty("Buffer_Size"));
            int Port = Integer.parseInt(property.getProperty("Port"));

            InetAddress Group = InetAddress.getByName(Inet_Address);
            FileOutputStream OutputFile = new FileOutputStream(File_Address,false);//bool append = true ? 

            int count = 0;
            byte[] buff = new byte[Buffer_Size];

            try (MulticastSocket clientSocket = new MulticastSocket(Port)){
                DatagramPacket msgPacket = new DatagramPacket(buff,buff.length);
                clientSocket.setSoTimeout(Timeout_Milliseconds);
                clientSocket.joinGroup(Group);
                while (true){
                    clientSocket.receive(msgPacket);
                    System.out.println("Receive packet " + (++count));
                    OutputFile.write(buff,0,msgPacket.getLength());
                }
            }
            //Time out will cause IO Exception
            catch (Exception e){
                System.out.println("No msg received");
                OutputFile.close();
            }
        }
        catch (Exception e)
        {
            System.out.println("MulticastSocketClient Error");
        }
    }
}

class FileCopyToHDFS implements Runnable{
    public void run() {
        try {
            //read config files
            Properties property = new Properties();
            FileInputStream propertyFile = new FileInputStream("MulticastConfig.conf");
            property.load(propertyFile);
            propertyFile.close();

            String File_Address = property.getProperty("Output_File_Address");
            String HDFS_Address = property.getProperty("HDFS_File_Address");

            File file = new File(File_Address);        
            Configuration conf = new Configuration();//means deafult setting in hadoop core-site.xml
            FileSystem fileSystem = FileSystem.get(URI.create(HDFS_Address),conf);
            InputStream InputFile = new BufferedInputStream(new FileInputStream(File_Address));
            FSDataOutputStream OutputFile = fileSystem.create(new Path(HDFS_Address));
            System.out.println("Begin copy to HDFS");
            IOUtils.copyBytes(InputFile, OutputFile, 4096, true);
            file.delete();
            //copyBytes(InputStream in, OutputStream out, int buffSize, boolean close)
        }
        catch (Exception e){
            System.out.println("File Copy To HDFS Error");
        }
    }
}
