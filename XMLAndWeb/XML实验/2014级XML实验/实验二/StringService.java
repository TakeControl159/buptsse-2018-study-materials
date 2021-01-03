package webservice;

import javax.jws.WebMethod;
import javax.jws.WebService;
@WebService
public class StringService {
	String name="euphemia";
	String iDString = "2014211990";
	@WebMethod
	public String compareStr()
	{
		if (name.compareTo(iDString)==0) {
			return "两个字符串相等";
		} else {
			return "两个字符串不相等";
		}
		
	}
	@WebMethod
	public String linkStr() {
		return "两个字符串连接的结果是："+name+iDString;
	}
	
	
}
