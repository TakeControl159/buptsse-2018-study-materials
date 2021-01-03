package webservice;

import javax.xml.ws.Endpoint;

public class publishclass {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
Endpoint.publish("http://localhost:9090/stringService", new StringService());
	}

}
