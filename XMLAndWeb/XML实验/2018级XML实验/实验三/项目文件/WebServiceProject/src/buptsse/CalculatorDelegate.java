package buptsse;

@javax.jws.WebService(targetNamespace = "http://localhost:8080/", serviceName = "CalculatorService", portName = "CalculatorPort")
@javax.jws.soap.SOAPBinding(style = javax.jws.soap.SOAPBinding.Style.RPC)
public class CalculatorDelegate {

	buptsse.Calculator calculator = new buptsse.Calculator();
	 
	public int add(int a, int b) {
		return calculator.add(a, b);
	}

	public int subtract(int a, int b) {
		return calculator.subtract(a, b);
	}

	public int multiply(int a, int b) {
		return calculator.multiply(a, b);
	}

	public int divide(int a, int b) {
		return calculator.divide(a, b);
	}

}