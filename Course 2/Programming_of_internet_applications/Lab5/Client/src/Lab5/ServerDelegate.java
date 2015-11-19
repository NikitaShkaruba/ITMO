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
            byte[] bytes = new byte[Double.BYTES*2];
            ByteBuffer buf = ByteBuffer.wrap(bytes);

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
}

/*try {
            DatagramSocket socket  = new DatagramSocket();
            byte[] buf = new byte[256];
            InetAddress address = InetAddress.getByName("127.0.0.1");
            DatagramPacket packet = new DatagramPacket(buf, buf.length,
                    address, 4445);
            socket.send(packet);
        } catch (IOException ex) { }*/
