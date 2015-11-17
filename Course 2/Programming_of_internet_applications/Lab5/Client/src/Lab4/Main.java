package Lab4;
/**
 * Created by nikita on 11/18/15.
 * <p/>
 * My contacts:
 * GitHub: https://github.com/SigmaOne
 * Vk: https://vk.com/wavemeaside
 * Mail: sh.nickita@list.ru
 */

import javafx.application.Application;
import javafx.stage.Stage;

import java.io.IOException;
import java.net.DatagramPacket;
import java.net.DatagramSocket;
import java.net.InetAddress;

public class Main extends Application {
    public static void main(String[] args) {
        try {
            DatagramSocket socket  = new DatagramSocket();
            byte[] buf = new byte[256];
            InetAddress address = InetAddress.getByName("127.0.0.1");
            DatagramPacket packet = new DatagramPacket(buf, buf.length,
                    address, 4445);
            socket.send(packet);
        } catch (IOException ex) { }

        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        // TODO add Logic
    }
}
