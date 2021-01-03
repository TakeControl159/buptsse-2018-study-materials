package algorithm_class;
import java.util.ArrayList;

public class _01bag {
	static private int limited_weight=10;
	static ArrayList<ArrayList<Integer>> getSub(int args[])
	{
		ArrayList<ArrayList<Integer>> result = new ArrayList<ArrayList<	Integer>>();
		ArrayList<Integer> subList = null;
		int max = 1 << args.length;  //移完max是16（二进制为10000）

		for (int i = 0; i < max; i++)   //16个子集进行循环求解
		{
			subList = new ArrayList<Integer>();   //存放子集序列
			int k = i;
			int index = 0;
			while (k > 0)  //k=0时，子集为空集
			{
				if ((k & 1) > 0)   //当k=14时，不执行 
					subList.add(args[index]);
				k >>= 1;   //判断从右往左数的下一位是否加入子集当中
				index++;
			}
			result.add(subList);
		}
		return result;
	}
	public static void main(String[] args) {
		int w1[]= {7,3,4,5};      //每个物体的重量
		int v1[]= {42,12,40,25};  //每个物体的价值
		int index[]= {1,2,3,4};   //物体的标号
		int max_value=0;          //所有子集中总价值最大的价值
		int proposal=0;           //价值最大的方案的索引
		ArrayList<ArrayList<Integer>> list = null; //存放求出的子集

		list = getSub(index);        //调用函数求子集

		System.out.println("重量\t"+"价值"+"\t是否可行\t\t"+"方案");
		//遍历所有子集，求每个子集的总重量和总价值，并选出价值最大的方案
		for (int i = 0; i < list.size(); i++)
		{
			int total_value=0;
			int total_weight=0;
			ArrayList<Integer> subList = list.get(i);          
			for(int j=0;j<subList.size();j++) {
				total_weight += w1[subList.get(j)-1];
				total_value += v1[subList.get(j)-1];
			}
			if(total_weight>limited_weight)     //如果总重量超标
				System.out.println(+total_weight+"\t"+total_value+"\t不可行\t\t"+subList.toString());
			else  		//如果总重量未超标
			{
				System.out.println(total_weight+"\t"+total_value+"\t可行\t\t"+subList.toString());
				//比较找出总价值最大的方案
				if(total_value>max_value) {
					max_value=total_value;
					proposal = i;
				}
			}

		}
		//打印结果
		System.out.print("\n最佳方案为：");
		for(int i=0;i<list.get(proposal).size();i++) {
			System.out.print("物品"+(list.get(proposal).get(i))+"\t");
		}
		System.out.println("\n总价值为："+max_value);
	}

}
