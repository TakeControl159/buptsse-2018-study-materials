import java.util.Timer;

// 用于记录目前帧的信息
public class FrameInfo {
    // 最大帧序号
    public static final int MAX_SEQ = 7;
    // 数据包缓冲区
    public String packetBuffer[] = new String[MAX_SEQ + 1];
    // 下一发送帧的帧号
    int nextFrameSend = 0;
    // 期待的确认帧号
    int ackExpected = 0;
    // 期待接收下一帧的帧号
    int frameExpected = 0;
    // 缓冲区帧的数量
    int numBuffer = 0;
    // 计时器数组
    public Timer frameTimer[] = new Timer[MAX_SEQ + 1];
    // 捎带确认计时器
    public Timer piggyBackingTimer = new Timer();
}
