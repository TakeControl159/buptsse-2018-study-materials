package secproj;

@javax.jws.WebService(targetNamespace = "http://secproj/", serviceName = "StrCompService", portName = "StrCompPort", wsdlLocation = "WEB-INF/wsdl/StrCompService.wsdl")

public class StrCompDelegate {

	secproj.StrComp strComp = new secproj.StrComp();

	public String compare() {
		return strComp.compare();
	}

	public String StrLink() {
		return strComp.StrLink();
	}

}