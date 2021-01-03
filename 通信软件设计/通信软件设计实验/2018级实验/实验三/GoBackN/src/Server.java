import javafx.application.Application;
import javafx.application.Platform;
import javafx.collections.FXCollections;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.stage.Stage;
import javafx.stage.WindowEvent;
import javafx.event.EventHandler;

import java.io.IOException;
import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.ServerSocket;
import java.net.Socket;

public class Server extends Application {

    // 声明输入输出数据流
    ObjectInputStream fromClient = null;
    ObjectOutputStream toClient = null;

    // 文本域,用于展示数据的发送结果
    TextArea messageText = new TextArea();
    @Override
    public void start(Stage primaryStage){

        /************************************服务端开始运行，展示界面**************************************/
        // 帧信息设置窗口
        ChoiceBox cb = new ChoiceBox(FXCollections.observableArrayList(
                "data", "ack"));
        cb.getSelectionModel().select(0); // 默认选择第一个
        TextField frameAck = new TextField();
        TextField frameSeq = new TextField();
        TextField framePacket = new TextField();
        Label labelKind = new Label("kind: ");
        Label labelSeq = new Label("seq: ");
        Label labelAck = new Label("ack: ");
        Label labelPacketInfo = new Label("PacketInfo: ");

        HBox hbox1 = new HBox();
        hbox1.setAlignment(Pos.CENTER);
        hbox1.getChildren().addAll(labelKind, cb);

        HBox hbox2 = new HBox();
        hbox2.setAlignment(Pos.CENTER);
        hbox2.getChildren().addAll(labelSeq, frameSeq );

        HBox hbox3 = new HBox();
        hbox3.setAlignment(Pos.CENTER);
        hbox3.getChildren().addAll(labelAck, frameAck);

        HBox hbox4 = new HBox();
        hbox4.setAlignment(Pos.CENTER);
        hbox4.getChildren().addAll(labelPacketInfo, framePacket);

        // 文本域,用于展示帧的发送结果
        messageText.setStyle("-fx-font-size: 20");
        messageText.setPrefColumnCount(30);
        messageText.setPrefRowCount(80);

        // 发送按钮
        Button sendButton = new Button();
        sendButton.setText("发送数据帧");

        VBox vBox = new VBox();
        vBox.setAlignment(Pos.CENTER);
        vBox.getChildren().addAll(hbox1, hbox2, hbox3, hbox4, sendButton, messageText);

        Scene scene = new Scene(vBox, 510, 800);
        primaryStage.setTitle("GoBackN服务端");
        primaryStage.setScene(scene);
        // 展示图形界面
        primaryStage.show();

        // 当退出窗口时，程序结束
        primaryStage.setOnCloseRequest(new EventHandler<WindowEvent>() {
            @Override
            public void handle(WindowEvent event) {
                System.exit(0);
            }
        });

        new Thread(()->{
            try{
                /****************以本机作为服务器提供服务，端口为8088*****************************/
                ServerSocket serverSocket = new ServerSocket(8088);
                System.out.println("服务器启动:\n");
                // 收听客户端的连接请求
                Socket socket = serverSocket.accept();

                // 与客户端建立输入输出流
                fromClient = new ObjectInputStream(socket.getInputStream());
                toClient = new ObjectOutputStream(socket.getOutputStream());
                System.out.println("客户端已连接");

                /*********************检测帧客户端(数据链路层）是否发送帧******************/
                while(true)
                {
                    Frame frame = (Frame) fromClient.readObject();
                    Platform.runLater(() -> {
                        messageText.appendText("---------------------从客户端接收帧-------------------\n");
                        showResult(messageText, frame);
                    });
                }
            }catch (ClassNotFoundException e){
                e.printStackTrace();
                System.out.println("接收数据出错！！");
            }catch (IOException e){
                System.out.println("客户端断开连接");
                fromClient = null;
                toClient = null;

            }
        }).start();

        /******************************点击发送数据按钮向（数据链路层）发送数据********************************/
        sendButton.setOnAction(e ->{
            try{
                Frame frame = new Frame();
                // 读取帧的数据类型
                frame.kind = cb.getSelectionModel().getSelectedItem().toString();
                // 读取帧序号
                if (frameSeq.getText().trim().isEmpty()){
                    frame.seq = -1;
                }else {
                    frame.seq = Integer.parseInt(frameSeq.getText().trim());
                }
                // 读取确认帧号
                if (frameAck.getText().trim().isEmpty()){
                    frame.ack = -1;
                }else {
                    frame.ack = Integer.parseInt(frameAck.getText().trim());
                }
                // 获取帧的数据
                if (framePacket.getText().trim().isEmpty()){
                    frame.packet = "";
                }else {
                    frame.packet = framePacket.getText().trim();
                }

                // 显示发送的帧信息
                messageText.appendText("---------------------向客户端发送帧-------------------\n");
                showResult(messageText, frame);

                // 向客户端发送帧
                toClient.writeObject(frame);
                toClient.flush();
            }catch (Exception e1){
                e1.printStackTrace();
                messageText.appendText("------数据填写错误，发送失败-------\n");
            }
        });
    }

    private void showResult(TextArea messageText, Frame frame){
        messageText.appendText("kind：" + frame.kind + "    ");
        messageText.appendText("seq：" + frame.seq + "    ");
        messageText.appendText("ack：" + frame.ack + "    ");
        messageText.appendText("packet：" + frame.packet + "\n");
    }
}
