import javafx.application.Application;
import javafx.application.Platform;
import javafx.event.EventHandler;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.*;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import javafx.scene.text.Text;
import javafx.stage.WindowEvent;

import java.io.ObjectInputStream;
import java.io.ObjectOutputStream;
import java.net.InetAddress;
import java.net.Socket;
import java.util.Timer;
import java.util.TimerTask;

public class Client extends Application {
    FrameInfo frameInfo = new FrameInfo();

    // 声明输入输出流
    ObjectOutputStream toServer = null;
    ObjectInputStream fromServer = null;

    // 发送结果提示
    Text infoTip = new Text();
    // 文本域,用于展示帧的发送结果
    TextArea messageText = new TextArea();

    /************************************客户端开始运行，展示界面**************************************/
    @Override
    public void start(Stage primaryStage){
        // 输入文本框，用于输入数据
        TextField packetData = new TextField();
        // 文本框提示标签
        Label tipLabel = new Label("Info: ");
        // 发送数据
        Button sendButton = new Button();
        sendButton.setText("发送数据");
        HBox inputDataHBox =new HBox();
        inputDataHBox.setAlignment(Pos.CENTER);//居中
        packetData.setStyle("-fx-font-size: 18");
        inputDataHBox.getChildren().addAll(tipLabel, packetData, sendButton);

        // 文本域,用于展示帧的发送结果
        messageText.setPrefColumnCount(30);
        messageText.setPrefRowCount(80);

        VBox vBox = new VBox();
        vBox.setAlignment(Pos.CENTER);
        infoTip.setStyle("-fx-font-size: 18");
        vBox.getChildren().addAll(inputDataHBox, infoTip, messageText);

        Scene scene = new Scene(vBox, 510, 800);
        primaryStage.setTitle("GoBackN客户端");
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

        try{
            /*************************与服务端建立连接************************************/
            Socket socket = new Socket("localhost", 8088);
            InetAddress inetAddress = socket.getInetAddress();

            // 与服务端建立输入输出流
            toServer = new ObjectOutputStream(socket.getOutputStream());
            fromServer = new ObjectInputStream(socket.getInputStream());
        }catch (Exception e){
            e.printStackTrace();
        }

        /******************************从服务端（物理层）接收帧 R - receive********************************/
        new Thread(()->{
            try{
                while(true){
                    Frame Rframe = (Frame) fromServer.readObject();
                    if(Rframe.kind.equals("data")){
                        if(Rframe.seq == frameInfo.frameExpected){
                            // 改变期待帧号
                            frameInfo.frameExpected = (frameInfo.frameExpected + 1) % (FrameInfo.MAX_SEQ + 1);
                        }
                        // 设定捎带确认帧计时器
                        frameInfo.piggyBackingTimer = new Timer();
                        frameInfo.piggyBackingTimer.schedule(new sendAckFrame(frameInfo.piggyBackingTimer), 2500);
                    }


                    // 查看ack信息
                    checkAck(Rframe);
                    Platform.runLater(()->{
                        // 显示结果
                        infoTip.setText("从物理层接收帧：" + Rframe.kind);
                        infoTip.setFill(Color.BLUE);
                        // 输出接收帧的信息
                        messageText.appendText("---------------------从服务端接收帧-------------------\n");
                        showResult(messageText, Rframe);
                    });
                }
            }catch (Exception e){
                e.printStackTrace();
            }
        }).start();


        /******************************点击发送数据按钮向（数据链路层）发送数据********************************/
        sendButton.setOnAction(e->{
            try{
                if(frameInfo.numBuffer < FrameInfo.MAX_SEQ){
                    // 存储数据到缓冲区
                    frameInfo.packetBuffer[frameInfo.nextFrameSend] = packetData.getText().trim();
                    frameInfo.numBuffer += 1;
                    // 发送帧
                    sendFrame(packetData.getText().trim());
                    // 取消捎带确认计时器
                    frameInfo.piggyBackingTimer.cancel();
                }else {
                    infoTip.setFill(Color.RED);
                    infoTip.setText("发送失败，缓冲区已满");
                }
            }catch (Exception dataE){
                dataE.printStackTrace();
                System.out.println("传输数据失败");
            }
        });
    }

    // 展示帧和数据链路层数据
    private void showResult(TextArea messageText, Frame frame){
        messageText.appendText("kind：" + frame.kind + "    ");
        messageText.appendText("seq：" + frame.seq + "    ");
        messageText.appendText("ack：" + frame.ack + "    ");
        messageText.appendText("packet：" + frame.packet + "\n");
        messageText.appendText("nextFrameSend：" + frameInfo.nextFrameSend + "    ");
        messageText.appendText("ackExpected：" + frameInfo.ackExpected + "    ");
        messageText.appendText("frameExpected：" + frameInfo.frameExpected + "\n");
        messageText.appendText("numBuffer：" + frameInfo.numBuffer + "\n");

    }

    /*****************************查看返回的确认帧是否正确*************************/
    private void checkAck(Frame frame){
        while(true){
            if((frameInfo.ackExpected <= frame.ack) && (frame.ack < frameInfo.nextFrameSend) ||
                    (frameInfo.nextFrameSend < frameInfo.ackExpected) && (frameInfo.ackExpected <= frame.ack) ||
                    (frame.ack < frameInfo.nextFrameSend) && (frameInfo.nextFrameSend < frameInfo.ackExpected)){
                // 释放缓冲区
                frameInfo.numBuffer -= 1;
                // 取消计时器
                frameInfo.frameTimer[frameInfo.ackExpected].cancel();
                // 改变期待帧的帧号
                frameInfo.ackExpected = (frameInfo.ackExpected + 1) % (FrameInfo.MAX_SEQ + 1);
            }else{
                break;
            }
        }
    }

    // 发送数据帧
    private void sendFrame(String packetData){
        try{
            // 创建帧 S - send
            Frame Sframe = new Frame("data", frameInfo.nextFrameSend, 0 , packetData);
            Sframe.ack = (frameInfo.frameExpected + FrameInfo.MAX_SEQ) % (FrameInfo.MAX_SEQ + 1);

            // 向服务端发送帧
            toServer.writeObject(Sframe);
            toServer.flush();

            // 设置定时器,在5秒延时后重发
            frameInfo.frameTimer[Sframe.seq] = new Timer();
            frameInfo.frameTimer[Sframe.seq].schedule(new FrameTimeOut(Sframe.seq), 5000);
            System.out.println(frameInfo.frameTimer[Sframe.seq]);

            // 显示发送结果
            Platform.runLater(()->{
                messageText.appendText("---------------------向服务端发送帧-------------------\n");
                showResult(messageText, Sframe);
                if(!infoTip.getText().trim().contains("号帧计时器超时")){
                    infoTip.setFill(Color.GREEN);
                    infoTip.setText("发送成功");
                }
            });

            // 改变下一发送帧号
            frameInfo.nextFrameSend = (frameInfo.nextFrameSend + 1) % (FrameInfo.MAX_SEQ + 1);
            System.out.println("增加后" + frameInfo.nextFrameSend);


        }catch (Exception e){
            e.printStackTrace();
            System.out.println("发送帧失败");
        }
    }


    /*********************************帧计时器超时重发**********************************/
    class FrameTimeOut extends TimerTask{
        int frameSeq = 0;
        public FrameTimeOut(int frameSeq){
            this.frameSeq = frameSeq;
        }

        @Override
        public void run()
        {
            try{
                Platform.runLater(()->{
                    // 显示超时
                    infoTip.setText("第" + frameSeq + "号帧计时器超时");
                    messageText.appendText("-----------------------计时器超时---------------------\n");
                    infoTip.setFill(Color.RED);
                });
                //System.out.println("第" + frameSeq + "号帧计时器超时");
                frameInfo.nextFrameSend = frameInfo.ackExpected;
                // 回退取消计时器
                int seq = frameInfo.nextFrameSend;
                for (int i = 1; i <= frameInfo.numBuffer; i++) {
                    frameInfo.frameTimer[seq].cancel();
                    // System.out.println(frameInfo.frameTimer[seq] + "取消");
                    seq  = (seq + 1) % (FrameInfo.MAX_SEQ + 1);
                }

                // 重新发送帧
                for (int i = 1; i <= frameInfo.numBuffer; i++) {
                    sendFrame(frameInfo.packetBuffer[frameInfo.nextFrameSend]);
                    frameInfo.piggyBackingTimer.cancel();
                    Thread.sleep(100);
                }
                System.out.println();
            }catch (Exception e){
                e.printStackTrace();
                System.out.println("超时重传发送错误");
            }
        }
    }

    /****************************发送确认帧************************/
    class sendAckFrame extends TimerTask{
        Timer piggyBackingTimer = null;
        public sendAckFrame(Timer piggyBackingTimer){
            this.piggyBackingTimer = piggyBackingTimer;
        }

        @Override
        public void run(){
            try{
                Frame ackFrame = new Frame("ack", -1, 0,"确认帧" );
                ackFrame.ack = (frameInfo.frameExpected + FrameInfo.MAX_SEQ) % (FrameInfo.MAX_SEQ + 1);
                // 向服务端发送帧
                toServer.writeObject(ackFrame);
                toServer.flush();

                // 取消捎带确认帧计时器
                piggyBackingTimer.cancel();

                Platform.runLater(()->{
                    // 显示已发送确认帧
                    infoTip.setText("发送ack：" + ackFrame.ack);
                    messageText.appendText("-----------------------发送ACK帧---------------------\n");
                    infoTip.setFill(Color.PURPLE);
                });
            }catch (Exception e){
                e.printStackTrace();
                System.out.println("发送确认帧失败");
            }
        }
    }
}


