package Lab4;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.Socket;

/**
 * Created by nikita on 11/18/15.
 * <p/>
 * My contacts:
 * GitHub: https://github.com/SigmaOne
 * Vk: https://vk.com/wavemeaside
 * Mail: sh.nickita@list.ru
 */
public class BatServer {
    public static void main(String[] args) throws IOException {
        new BatServerThread().start();
    }

    public int getPort() {
        return 4445;
    }
}

class BatServerThread extends Thread {
    private DatagramSocket socket;

    public BatServerThread() throws IOException {
        this("OneThreadBatServer");
    }
    public BatServerThread(String name) throws IOException {
        super(name);

        socket = new DatagramSocket(4445);
    }

    public void run() {
        if (socket == null)
            return;

        while(true) {
            try {
                byte[] buf = new byte[256];
                DatagramPacket packet = new DatagramPacket(buf, buf.length);
                socket.receive(packet);

                // TODO add logic
                buf[0] = new Integer(2).byteValue();

                InetAddress address = packet.getAddress();
                int port = packet.getPort();
                packet = new DatagramPacket(buf, 1, address, port);
                socket.send(packet);
            } catch (IOException ex) {
                return;
            }
            socket.close();
        }
    }
}