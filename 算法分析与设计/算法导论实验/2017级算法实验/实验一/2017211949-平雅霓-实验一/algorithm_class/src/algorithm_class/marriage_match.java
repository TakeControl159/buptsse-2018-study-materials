package algorithm_class;


/*婚姻匹配问题*/
public class marriage_match {
	public static void main(String[] args) {
		String[][] data = {{"Xavier","Yancey","Zeus"},{"Amy","Bertha","Clare"}};
		int men_pre[][]= {{0,1,2},{1,0,2},{0,1,2}};  //三位男生喜欢的女生排行
		int women_pre[][]= {{1,0,2},{0,1,2},{0,1,2}};  //三位女生喜欢的男生排行
		int current_girlfriend[]= {-1,-1,-1};  //男生当前是否有女朋友
		int current_boyfriend[]= {-1,-1,-1};   //女生当前是否有男朋友
		int manIndex[]= {0,0,0};  //记录男生被拒绝后应该选择的女朋友

		boolean manSingle=false;  //设置有男生单身
		int i,j,m,w;
		
		//有男性单身则一直循环
		while(!manSingle) {
			manSingle=true;
			for(i=0;i<3;i++){
				if(current_girlfriend[i]!=-1) // 如果男生i已经有了女朋友
					continue;
				manSingle=false;
				j=manIndex[i]++; // 男生i现在该选择喜好排行中的第j个女生
				w=men_pre[i][j];    //第j个女生是第w号
				m= current_boyfriend[w];    //女生w现在的男朋友m
				if(m==-1 || women_pre[w][i]<women_pre[w][m]){ // 如果女孩w没有男朋友或者更喜欢男生i
					current_boyfriend[w]=i;
					current_girlfriend[i]=w;
					if(m!=-1)  //如果女生要更换男朋友，则前男友当前的女朋友置为-1
						current_girlfriend[m]=-1;
				}
			}
		}
		for(i=0;i<3;i++) {
			System.out.println(data[0][i]+"——"+data[1][current_girlfriend[i]]);
		}
	}
}
