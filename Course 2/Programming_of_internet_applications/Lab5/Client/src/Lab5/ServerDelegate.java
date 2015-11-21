package Lab5;

import java.net.SocketTimeoutException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.awt.geom.Point2D;
import java.net.InetAddress;
import java.io.IOException;
import java.nio.ByteBuffer;
import java.util.Vector;

/**
 * Created by nikita on 11/19/15.
 * <p/>
 * My contacts:
 * GitHub: https://github.com/SigmaOne
 * Vk: https://vk.com/wavemeaside
 * Mail: sh.nickita@list.ru
 */
class ServerDelegate {
    public static Mark.States askIfContains(Point2D.Double point) {
        try {
            // prepare socket
            DatagramSocket socket  = new DatagramSocket();
            socket.setSoTimeout(10);

            // Put data in bytes.
            byte[] bytes = new byte[Integer.BYTES + Double.BYTES*2];
            ByteBuffer buf = ByteBuffer.wrap(bytes);
            buf.putInt(1);  // (!) First Integer - amount of points
            buf.putDouble(point.getX());
            buf.putDouble(point.getY());

            // send
            InetAddress address = InetAddress.getByName("127.0.0.1");
            DatagramPacket packet = new DatagramPacket(bytes, bytes.length, address, 4445);
            socket.send(packet);

            // receive
            bytes = new byte[1];
            packet = new DatagramPacket(bytes, bytes.length);
            socket.receive(packet);

            return (bytes[0] == 1)? Mark.States.in : Mark.States.outside;
        } catch (Exception ex) {
            // SocketTimeoutException and IOException
            return Mark.States.suspended;
        }
    }
    public static Vector<Mark.States> askIfContains(Vector<Point2D.Double> points) {
        try {
            // Prepare data
            DatagramSocket socket  = new DatagramSocket();
            socket.setSoTimeout(10);
            byte[] bytes = new byte[Integer.BYTES + 2*Double.BYTES*points.size()];
            ByteBuffer buf = ByteBuffer.wrap(bytes);

            // Put Points
            buf.putInt(points.size());  // (!) First Integer - amount of points
            for (Point2D.Double point: points) {
                buf.putDouble(point.getX());
                buf.putDouble(point.getY());
            }

            // Send
            InetAddress address = InetAddress.getByName("127.0.0.1");
            DatagramPacket packet = new DatagramPacket(bytes, bytes.length, address, 4445);
            socket.send(packet);

            // Prepare new data
            bytes = new byte[points.size()];
            Vector<Mark.States> newStates = new Vector(points.size());
            packet = new DatagramPacket(bytes, bytes.length);
            socket.receive(packet);
            bytes = packet.getData();

            // Decode
            buf = ByteBuffer.wrap(bytes);
            for (int i = 0; i < points.size(); i++) {
                switch(buf.get()) {
                    case 0: newStates.add(Mark.States.outside); break;
                    case 1: newStates.add(Mark.States.in); break;
                }
            }
            return newStates;
        }
        catch (SocketTimeoutException e) {
            Vector<Mark.States> newStates = new Vector(points.size());
            for (int i = 0; i < points.size(); i++)
                newStates.add(Mark.States.suspended);
            return newStates;
        }
        catch (IOException ex) {
            Vector<Mark.States> newStates = new Vector(points.size());
            for (int i = 0; i < points.size(); i++)
                newStates.add(Mark.States.suspended);
            return newStates;
        }
    }
}