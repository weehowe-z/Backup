import java.net.MulticastSocket;
import java.net.InetAddress;
import java.net.DatagramPacket;

import java.io.FileOutputStream;
import java.io.FileInputStream;
import java.util.Properties;//read conf

public class MulticastSocketClient{
	public static void main(String[] args) throws Exception{
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
}