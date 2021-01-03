package webservice.client;
import java.net.URL;
import javax.xml.namespace.QName;
import javax.xml.ws.Service;
import buptsse.StringOperation;

public class ServerInvoke {

	public static void main(String[] args) {
		try {
			// 访问web service说明书地址
			URL url = new URL("http://localhost:8080/WebServiceProject/StringOperationPort?WSDL");
			
			// 指定命名空间，服务的名称，作用定位到那个服务
			QName serviceName = new QName("http://buptsse/", "StringOperationService");
			Service service = Service.create(url, serviceName);
			
			// 获取接口的实例
			StringOperation stringOperation = service.getPort(new QName("http://buptsse/", "StringOperationPort"), 
					StringOperation.class);
			
			// 调用接口
			String addString = stringOperation.AddString("XML", "Web");
			Boolean isEqual = stringOperation.CompareString("Hello", "Hello");
			
			// 输出结果
			System.out.println("字符串相加的结果为：" + addString);
			System.out.println("字符串比较的结果为：" + isEqual);
			
		}catch(Exception e) {
			System.out.println(e);
		}
	}
}
