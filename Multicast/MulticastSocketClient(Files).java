import java.net.MulticastSocket;
import java.net.InetAddress;
import java.net.DatagramSocket;
import java.net.DatagramPacket;

import java.io.FileOutputStream;

public class MulticastSocketClient{
	final static String Inet_Address = "228.1.1.1";
	final static String File_Address = "copy.mp4";
	final static int Port = 1234;
	final static int Buffer_size = 65507; 
	final static int TimeoutMilliseconds = 5000;
	//IPv4 protocol is 65,507 bytes (65,535 − 8 byte UDP header − 20 byte IP header).
	//It is the fastest

	public static void main(String[] args) throws Exception{
		InetAddress group = InetAddress.getByName(Inet_Address);
		FileOutputStream file = new FileOutputStream(File_Address,false);//bool append = true
		int port = Port;

		int count = 0;
		byte[] buff = new byte[Buffer_size];

		try (MulticastSocket clientSocket = new MulticastSocket(port)){
			DatagramPacket msgPacket = new DatagramPacket(buff,buff.length);
			clientSocket.setSoTimeout(TimeoutMilliseconds);
			clientSocket.joinGroup(group);
			while (true){
				clientSocket.receive(msgPacket);
				System.out.println("Receive packet " + (++count));
				file.write(buff,0,msgPacket.getLength());
			}
		}
		//Time out will cause IO Exception
		catch (Exception e){
			System.out.println("No msg received");
			file.close();
		}
	}

}