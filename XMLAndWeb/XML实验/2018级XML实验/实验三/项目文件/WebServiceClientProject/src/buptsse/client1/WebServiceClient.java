package buptsse.client1;

public class WebServiceClient {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		StringOperationService service = new StringOperationService();
		StringOperationDelegate delegate = service.getStringOperationPort();
		
		// 字符串相加
		System.out.print("\"XML&\" + \"&Web\" = ");
		System.out.println(delegate.addString("XML&", "&Web"));
		
		// 字符串比较
		System.out.print("\"Hello\" == \"Hello\" = ");
		System.out.println(delegate.compareString("Hello", "Hello"));
	}
}
