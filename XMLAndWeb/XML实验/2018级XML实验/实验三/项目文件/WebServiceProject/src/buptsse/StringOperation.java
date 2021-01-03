package buptsse;

public class StringOperation {
	public Boolean CompareString(String str1, String str2) {
		if(str1.equals(str2))
			return true;
		else
			return false;
	}
	
	public String AddString(String str1, String str2) {
		return str1.concat(str2);
	}
}