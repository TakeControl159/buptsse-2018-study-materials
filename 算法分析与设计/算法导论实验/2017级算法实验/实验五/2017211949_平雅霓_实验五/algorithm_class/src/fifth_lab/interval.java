package fifth_lab;
import java.util.Arrays;
import java.util.Vector;

public class interval {

	public static void main(String[] args) {
		int num=6;		
		int []startTime = {0,1,5,2,8,8};
		int []endTime = {4,6,7,9,10,11};
		int []weight = {2,4,4,7,2,1};
		Job[] jobs = new Job[num];       //创建的工作
		Vector<Integer> solveSpace[]=new Vector[6];

		int maxWeight;
		int i = 0;
		while(i<num){
			jobs[i]=new Job(startTime[i],endTime[i],weight[i]);
			solveSpace[i]=new Vector<Integer>(); 
			i++;
		}

		//对工作的结束时间进行排序
		Arrays.sort(jobs);    

		int dp[]= new int[num];	
		
		//动态规划表赋值
		for(i=0;i<num;i++) {
			if(i==0) {
				dp[i]= weight[i];
				(solveSpace[0]).add(i);
			}
			else {
				for(int j=i-1;j>=0;j--) {
					if(jobs[j].getEnd()<jobs[i].getStart()) {
						dp[i]=Math.max(dp[i], (dp[j]+jobs[i].getWeight()));
						for(int k=0;k<solveSpace[j].size();k++)
							solveSpace[i].add(solveSpace[j].get(k));
						solveSpace[i].add(i);
						break;
					}		
					if(j==0) {
						dp[i] = jobs[i].getWeight();
						solveSpace[i].add(i);}
				}	
			}
		}
		
		System.out.print("dp结果： ");
		for(i=0;i<num;i++){
			System.out.print(dp[i]+" ");
		}

		int flag = 0;
		maxWeight = dp[0];
		for(i=1;i<num;i++){
			if(dp[i]>maxWeight) {
				maxWeight = dp[i];
				flag = i;
			}
		}
		System.out.println("\n可执行的任务数为:"+solveSpace[flag].size());
		System.out.println("执行的任务为： ");
		for(i=0;i<solveSpace[flag].size();i++) {
			System.out.println("( "+jobs[solveSpace[flag].get(i)].getStart()+","+
					jobs[solveSpace[flag].get(i)].getEnd()+","+jobs[solveSpace[flag].get(i)].getWeight()+")");	
		}

	}
}

@SuppressWarnings("rawtypes")
class Job implements Comparable{	
	private int start;	
	private int end; 
	private int weight; 
	public Job(int start, int end,int weight) {	
		this.start = start;	
		this.end = end;	
		this.weight = weight;
	} 	
	public int getStart() {	
		return this.start;	
	} 
	public int getEnd() {	
		return this.end;
	} 
	public int getWeight() {	
		return this.weight;
	}
	@Override	
	public int compareTo(Object o) {	
		Job job = (Job) o;		
		if (this.end > job.getEnd())	
			return 1;		
		else if (this.end == job.getEnd())		
			return 0;		
		else			
			return -1;	
	}
}
