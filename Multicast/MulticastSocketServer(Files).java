import java.net.MulticastSocket;
import java.net.InetAddress;
import java.net.DatagramSocket;
import java.net.DatagramPacket;

import java.io.FileInputStream;

public class MulticastSocketServer{
	final static String Inet_Address = "228.1.1.1";
	final static String File_Address = "blueshit.mp4";
	final static int Port = 1234;
	final static int Buffer_size = 65507; 
	//IPv4 protocol is 65,507 bytes (65,535 − 8 byte UDP header − 20 byte IP header).
	//It is the fastest


	public static void main(String[] args) throws Exception{
		InetAddress group = InetAddress.getByName(Inet_Address);
		FileInputStream file = new FileInputStream(File_Address);
		int port = Port;

		int count = 0;
		byte[] buff = new byte[Buffer_size];
		
		MulticastSocket serverSocket = new MulticastSocket();

		while(true){
			int readBytesLength = file.read(buff);
			if (readBytesLength == -1) break;
			System.out.println("Send packet " + (++count));
			DatagramPacket packet = new DatagramPacket(buff,0,readBytesLength,group,port);
			serverSocket.send(packet);
			Thread.sleep(1);
		}
		file.close();
	}

}