package algorithm_class;
import java.util.ArrayList;

public class tsp {
	static double[][] cost_matrix= {
			{Double.POSITIVE_INFINITY,3,6,7},
			{12,Double.POSITIVE_INFINITY,2,8},
			{8,6,Double.POSITIVE_INFINITY,2},
			{3,7,6,Double.POSITIVE_INFINITY}};
	static char[] location= {'a','b','c','d'};
	static public double least_cost=Double.POSITIVE_INFINITY;
	static public int[] proposal= {0,0,0,0,0};
	static public void pringArray(int [] arr,int n){
		// 打印数组
		double cost=0;
		//打印每次可选的路径
		System.out.print(location[arr[0]]+"->");
		for (int i = 1; i < arr.length; i++) {
			System.out.print(location[arr[i]]+"->");
		}
		System.out.print(location[arr[0]]);
		int j;
		for(j=0;j<3;j++) {
			cost+=cost_matrix[arr[j]][arr[j+1]];
		}
		cost+=cost_matrix[arr[j]][arr[0]];
		//比较，记录更小的代价对应的路径
		if(cost<least_cost) {
			least_cost=cost;
			proposal[0]=arr[0];
			proposal[1]=arr[1];
			proposal[2]=arr[2];
			proposal[3]=arr[3];
			proposal[4]=arr[0];
		}
		//打印每条路径的代价
		System.out.print("\t"+cost+"\n");
	}
	static public void swap(int [] arr,int i,int j){
		int temp = arr[i];
		arr[i] = arr[j];
		arr[j] = temp;
	}
	// 对数组arr进行全排列
	static public void perum(int [] arr,int p){
		// 递归结束条件
		if(p == arr.length-1){
			//  每次递归结束。将整个数组打印出来
				pringArray( arr,arr.length);
		}
		// for循环将数组中所有的元素和第一个元素进行交换。然后进行全排列。
		for(int i =p ;i <= arr.length-1;i++){
			swap(arr,i,p);
			// 把剩下的元素都做全排列。
			perum(arr,p+1);
			// 然后再交换回去，数组还原，保证下一次不会有重复交换。
			swap(arr,i,p);
		}
	}  
	public static void main(String[] args) {
		int index[]= {0,1,2,3};
		System.out.println("所有可能的路径为：");
		perum(index,1);
		System.out.println("\n最佳组合为：");
		System.out.println(location[proposal[0]]+"->"+location[proposal[1]]+"->"
		+location[proposal[2]]+"->"+location[proposal[3]]+"->"+location[proposal[0]]);
		System.out.println("最小成本为："+least_cost);
	}	
}
