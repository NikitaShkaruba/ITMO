package Lab4;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

/**
 * Created by nikita on 11/18/15.
 * <p/>
 * My contacts:
 * GitHub: https://github.com/SigmaOne
 * Vk: https://vk.com/wavemeaside
 * Mail: sh.nickita@list.ru
 */
public class BatServer {
    static BatmanFigure figure = new BatmanFigure(0.01);

    public static void main(String[] args) throws IOException {
        new BatServerThread(figure).start();
    }

    public int getPort() {
        return 4445;
    }
}

class BatServerThread extends Thread {
    private DatagramSocket socket;
    private BatmanFigure figure;

    public BatServerThread(BatmanFigure figure) throws IOException {
        this("BatRequestHandler", figure);
    }
    public BatServerThread(String name, BatmanFigure figure) throws IOException {
        super(name);

        this.figure = figure;
        socket = new DatagramSocket(4445);
    }

    public void run() {
        if (socket == null)
            return;

        try {
            byte[] buf = new byte[256];
            DatagramPacket packet = new DatagramPacket(buf, buf.length);
            socket.receive(packet);

            // TODO add logic
            // Parse buf
            // if (figure.Contains(buf)) {
            //     buf[0] = new Integer(1).byteValue();
            // } else {
            //     buf[0] = new Integer(0).byteValue();
            // }

            buf[0] = new Integer(1).byteValue();  // remove this after creating logic

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