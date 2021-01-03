package buptsse;
import javax.xml.ws.Endpoint;

public class PublishClass {
	public static void main(String[] args){
		Endpoint.publish("http://localhost:8080/WebStringService",new WebStringService());
	}
}
