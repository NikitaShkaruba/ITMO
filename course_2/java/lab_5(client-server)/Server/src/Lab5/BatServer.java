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
        System.out.println("BatServer started.");

        while (true) {
            byte[] bytes = new byte[Double.BYTES*100];
            DatagramPacket packet = new DatagramPacket(bytes, bytes.length);
            socket.receive(packet);

            // Let this guy handle received packet
            new PacketHandlerThread(socket, packet, figure).start();
        }
    }
}

class PacketHandlerThread extends Thread {
    private DatagramSocket socket;
    private DatagramPacket packet;
    private BatmanFigure figure;

    public PacketHandlerThread(DatagramSocket socket, DatagramPacket packet, BatmanFigure figure) throws IOException {
        super("BatRequestHandler");

        this.socket = socket;
        this.packet = packet;
        this.figure = figure;
    }

    public void run() {
        if (socket == null)
            return;

        try {
            // Prepare data
            byte[] bytes = packet.getData();
            ByteBuffer buf = ByteBuffer.wrap(bytes);
            int amountOfPoints = buf.getInt();

            // Write to the same packet
            for(int i = 0; i < amountOfPoints; i++)
                bytes[i] = (byte)(figure.Contains(new Point2D.Double(buf.getDouble(), buf.getDouble()))? 1 : 0);

            // Send
            InetAddress address = packet.getAddress();
            int port = packet.getPort();
            packet = new DatagramPacket(bytes, amountOfPoints, address, port);
            socket.send(packet);
        } catch (IOException ex) {
            return;
        }
    }
}