package buptsse;

public class WebClient {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		StringOperationService service = new StringOperationService();
		StringOperationDelegate delegate = service.getStringOperationPort();
		
		// ×Ö·û´®Ïà¼Ó
		System.out.print("×Ö·û´®\"XML%\" + ×Ö·û´®\"&Web\"");
		System.out.println(delegate.compareString("Hello", "Hello"));
		
		// ×Ö·û´®±È½Ï
		System.out.print("×Ö·û´®\"Hello\" == ×Ö·û´®\"Hello\"");
		System.out.println(delegate.compareString("Hello", "Hello"));
	}
}
