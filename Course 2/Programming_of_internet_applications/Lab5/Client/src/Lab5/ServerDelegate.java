package Lab5;

import sun.reflect.generics.reflectiveObjects.NotImplementedException;

import java.awt.*;
import java.awt.geom.Point2D;
import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;
import java.net.SocketTimeoutException;
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
    public ServerDelegate() {}

    public static Vector<Point> getFigurePoints() {
        /*try {
            DatagramSocket socket  = new DatagramSocket();
            byte[] buf = new byte[256];
            InetAddress address = InetAddress.getByName("127.0.0.1");
            DatagramPacket packet = new DatagramPacket(buf, buf.length, address, 4445);
            socket.send(packet);
        } catch (IOException ex) { }*/

//        byte[] bytes = new byte[1024];

//write data into byte array...

//        InputStream input = new ByteArrayInputStream(bytes);

//read first byte
//        int data = input.read();
//        while(data != -1) {
//            //do something with data
//
//            //read next byte
//            data = input.read();
//        }
        throw new NotImplementedException();
    }
    public static Mark.States doContains(Point2D.Double point) {
        try {
            DatagramSocket socket  = new DatagramSocket();
            socket.setSoTimeout(10);
            byte[] bytes = new byte[Integer.BYTES + Double.BYTES*2];
            ByteBuffer buf = ByteBuffer.wrap(bytes);

            buf.putInt(1);
            buf.putDouble(point.getX());
            buf.putDouble(point.getY());

            InetAddress address = InetAddress.getByName("127.0.0.1");
            DatagramPacket packet = new DatagramPacket(bytes, bytes.length, address, 4445);
            socket.send(packet);

            bytes = new byte[1];
            packet = new DatagramPacket(bytes, bytes.length);
            socket.receive(packet);

            return (bytes[0] == 1)? Mark.States.in : Mark.States.outside;
        }
        catch (SocketTimeoutException e) {
            return Mark.States.suspended;
        }
        catch (IOException ex) { return Mark.States.suspended; }
    }
    public static Vector<Mark.States> doContains(Vector<Point2D.Double> points) {
        try {
            // Prepare data
            DatagramSocket socket  = new DatagramSocket();
            socket.setSoTimeout(10);
            byte[] bytes = new byte[Integer.BYTES + 2*Double.BYTES*points.size()];
            ByteBuffer buf = ByteBuffer.wrap(bytes);

            // Put Points
            buf.putInt(points.size());
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

/*try {
            DatagramSocket socket  = new DatagramSocket();
            byte[] buf = new byte[256];
            InetAddress address = InetAddress.getByName("127.0.0.1");
            DatagramPacket packet = new DatagramPacket(buf, buf.length,
                    address, 4445);
            socket.send(packet);
        } catch (IOException ex) { }*/
