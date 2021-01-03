package buptsse;

import javax.jws.WebParam;

@javax.jws.WebService(targetNamespace = "http://buptsse/", serviceName = "WebStringService", portName = "WebStringPort", wsdlLocation = "WEB-INF/wsdl/WebStringService.wsdl")

public class WebStringDelegate {

	buptsse.WebString webString = new buptsse.WebString();

	public boolean isEqual(@WebParam(name = "a") String a, @WebParam(name = "b") String b) {
		return webString.isEqual(a, b);
	}

	public String addString(@WebParam(name = "a") String a, @WebParam(name = "b") String b) {
		return webString.addString(a, b);
	}

}