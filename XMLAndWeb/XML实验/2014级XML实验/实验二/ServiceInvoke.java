package webservice.client;

import java.net.MalformedURLException;
import java.net.URL;

import javax.xml.namespace.QName;
import javax.xml.ws.Service;

import webservice.StringService;


public class ServiceInvoke {

	public static void main(String[] args) throws MalformedURLException {
		// TODO Auto-generated method stub
		URL url = new URL("http://localhost:9090/stringService?wsdl");
		QName serviceName = new QName("http://webservice/", "StringServiceService");
		Service service=Service.create(url,serviceName);
		StringService hs=service.getPort(new QName("http://webservice/", "StringServicePort"),
				StringService.class);
		String str1=hs.compareStr();
		System.out.println(str1);
		String str2=hs.linkStr();
		System.out.println(str2);
	}

}