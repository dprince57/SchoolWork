
import java.io.*;
import java.net.*;

class Client {
  public static void main(String args[]) throws Exception {
    DatagramSocket sock = new DatagramSocket();
    InetAddress addr = InetAddress.getByName("cs.indstate.edu");
    byte[] data = new byte[1536];
    String user = new String(System.getProperty("user.name"));
    long time = System.currentTimeMillis();
    InetAddress ip = InetAddress.getLocalHost();
    String mess = new String(user + " " + time + " " + ip.getHostAddress());
    data = mess.getBytes();
    DatagramPacket pack = new DatagramPacket(data,data.length,addr,2300);
    sock.send(pack);
    sock.close();
  }
}
