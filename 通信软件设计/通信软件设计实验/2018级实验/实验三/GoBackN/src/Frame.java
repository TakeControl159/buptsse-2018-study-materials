import java.io.Serializable;

public class Frame implements Serializable {
    // 数据帧类型
    public String kind = "";
    // 序号
    public int seq = 0;
    // ack值
    public int ack = 0;
    // 报数据
    public String packet = "";

    public Frame(String kind, int seq, int ack, String packet) {
        this.kind = kind;
        this.seq = seq;
        this.ack = ack;
        this.packet = packet;
    }
    public Frame(){
    }
}


