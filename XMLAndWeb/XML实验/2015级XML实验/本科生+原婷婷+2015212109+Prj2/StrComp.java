package secproj;

public class StrComp {
	String str1="Hello";
	String str2="Aloha";
	public String compare(){
		if(str1.equals(str2)){
			return "不相等";
		}
		else{
			return "相等";
		}
	}
	public String StrLink(){
		return"Str1+Str2= "+str1+str2;
	}
}
