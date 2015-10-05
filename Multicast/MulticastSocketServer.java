import java.net.MulticastSocket;
import java.net.InetAddress;
import java.net.DatagramSocket;
import java.net.DatagramPacket;

public class MulticastSocketServer{
	final static String Inet_Address = "228.1.1.1";
	final static int Port = 1234;

	public static void main(String[] args) throws Exception{
		InetAddress group = InetAddress.getByName(Inet_Address);
		int port = Port;
		try (MulticastSocket serverSocket = new MulticastSocket()){
			for (int i = 0; i < 5 ; i++){
				String msg = "Sent message No." + i;
				DatagramPacket msgPacket = new DatagramPacket(msg.getBytes(),msg.length(),group,port);
				serverSocket.send(msgPacket);
				System.out.println(msg.getBytes());
				System.out.println("Server sent packet with msg: " + msg);
				Thread.sleep(1000);
			}
		}
	}

}