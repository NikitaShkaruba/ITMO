package Lab5;

import java.awt.geom.Point2D;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.nio.ByteBuffer;
import java.util.Vector;

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
        DatagramSocket socket = new DatagramSocket(4445);

        while (true) {
            byte[] bytes = new byte[Double.BYTES*100];
            DatagramPacket packet = new DatagramPacket(bytes, bytes.length);
            socket.receive(packet);

            // Let this guy handle recieved packet
            new PacketHandlerThread(socket, packet, figure).start();
        }
    }

    public int getPort() {
        return 4445;
    }
}

class PacketHandlerThread extends Thread {
    private BatmanFigure figure;
    private DatagramSocket socket;
    private DatagramPacket packet;

    public PacketHandlerThread(DatagramSocket socket, DatagramPacket packet, BatmanFigure figure) throws IOException {
        super("BatRequestHandler");

        this.figure = figure;
        this.socket = socket;
        this.packet = packet;
    }

    public void run() {
        if (socket == null)
            return;

        try {
            byte[] bytes = packet.getData();
            ByteBuffer buf = ByteBuffer.wrap(bytes);
            int Length = buf.getInt();

            for(int i = 0; i < Length; i++)
                bytes[i] = (byte)(figure.Contains(new Point2D.Double(buf.getDouble(), buf.getDouble()))? 1 : 0);

            InetAddress address = packet.getAddress();
            int port = packet.getPort();
            packet = new DatagramPacket(bytes, Length, address, port);
            socket.send(packet);
        } catch (IOException ex) {
            return;
        }
    }
}