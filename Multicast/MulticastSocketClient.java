import java.net.MulticastSocket;
import java.net.InetAddress;
import java.net.DatagramSocket;
import java.net.DatagramPacket;

public class MulticastSocketClient{
	final static String Inet_Address = "228.1.1.1";
	final static int Port = 1234;

	public static void main(String[] args) throws Exception{
		InetAddress group = InetAddress.getByName(Inet_Address);
		int port = Port;

		byte[] buff = new byte[1024];
		try (MulticastSocket clientSocket = new MulticastSocket(port)){
			clientSocket.joinGroup(group);
			while (true){
				DatagramPacket msgPacket = new DatagramPacket(buff,buff.length);
				clientSocket.receive(msgPacket);
				String msg = new String(buff, 0 , buff.length);
				System.out.println("Socket 1 received msg: " + msg + " ");
			}
		}
	}

}