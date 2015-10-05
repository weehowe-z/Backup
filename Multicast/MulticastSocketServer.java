import java.net.MulticastSocket;
import java.net.InetAddress;
import java.net.DatagramPacket;

import java.io.FileInputStream;
import java.util.Properties;//read conf


public class MulticastSocketServer{
	public static void main(String[] args) throws Exception{
		//read config files
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
			System.out.println("Send packet " + (++count));
			DatagramPacket packet = new DatagramPacket(buff,0,readBytesLength,Group,Port);
			serverSocket.send(packet);
			Thread.sleep(1);
		}
		InputFile.close();
	}

}