package buptsse;

import javax.jws.WebParam;

@javax.jws.WebService(targetNamespace = "http://buptsse/", serviceName = "StringOperationService", portName = "StringOperationPort", wsdlLocation = "WEB-INF/wsdl/StringOperationService.wsdl")

public class StringOperationDelegate {

	buptsse.StringOperation stringOperation = new buptsse.StringOperation();

	public Boolean CompareString(@WebParam(name = "str1") String str1, @WebParam(name = "str2") String str2) {
		return stringOperation.CompareString(str1, str2);
	}

	public String AddString(@WebParam(name = "str1") String str1, @WebParam(name = "str2") String str2) {
		return stringOperation.AddString(str1, str2);
	}

}