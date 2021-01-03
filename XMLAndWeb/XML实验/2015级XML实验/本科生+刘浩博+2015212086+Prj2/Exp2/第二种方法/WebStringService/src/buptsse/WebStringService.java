package buptsse;

import javax.jws.WebService;

import java.util.Objects;

@WebService
public class WebStringService {
	public boolean isEqual(String a,String b){
		return Objects.equals(a, b);
	}
	
	public String addString(String a,String b){
		return a+b;
	}
	
}
