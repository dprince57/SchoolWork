import java.io.*;
import java.net.*;
import java.sql.*;

class Server {
  public static void main(String args[]) throws Exception {
    DatagramSocket serverSocket = new DatagramSocket(2300);
    byte[] receiveData = new byte[1024];
    byte[] sendData = new byte[1024];
    /* SQLite creation section */
    Connection c = null;
    Statement stmt = null;
    try {
  	  Class.forName("org.sqlite.JDBC");
  	  c = DriverManager.getConnection("jdbc:sqlite:test.db");
      c.setAutoCommit(false);
    } catch ( Exception e ) {
  	  System.err.println( e.getClass().getName() + ": " + e.getMessage() );
  	  System.exit(0);
    }
    
    /* Server loop */
    while(true) {
      DatagramPacket receivePacket = new DatagramPacket(receiveData, receiveData.length);
      serverSocket.receive(receivePacket);
      String sentence = new String(receivePacket.getData());
      String[] derp = sentence.split(" "); // 0 = username, 1 = time, 2 = IP address 
      /* table updater */
      stmt = c.createStatement();
      String sql = "INSERT INTO USERS (UNAME,TIME,IPADD) " +
                   "VALUES ('" + derp[0] +"', '" + derp[1] + "', '" + derp[2] +
                   "' );";
      stmt.executeUpdate(sql);
    }
  }
}
