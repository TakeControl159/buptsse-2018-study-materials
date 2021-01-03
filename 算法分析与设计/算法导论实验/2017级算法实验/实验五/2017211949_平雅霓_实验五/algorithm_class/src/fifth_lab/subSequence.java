package fifth_lab;

public class subSequence {
	public static int count=0;
	public static void main(String[] args) {
		String S_[] = {"买Yahoo股票","买eBay股票","买Yahoo股票","买Oracle股票"};
		String S[] = {"买Yahoo股票","买Oracle股票"};	
		int j=0;

		for(int i=0;i<S.length;i++)
			for(;j<S_.length;) {
				if(S[i].equals(S[j])) {
					count++;
					break;
				}				
				j++;
			}
		if(count==S.length)
			System.out.println("S'是S的子序列");
		else {
			System.out.println("S'不是S的子序列");
		}
	}
}
