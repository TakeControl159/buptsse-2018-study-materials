package fifth_lab;

import java.util.Scanner;

public class carDriving {
	private static int N ;  
	private static int A; 
	private static int C; 
	private static int B; 
	private static int K;  

	private static int[][][] f = new int[50][50][2];
	private static int[][] s = {{-1,0,B},{0,-1,B},{1,0,0},{0,1,0}};

	private static int[][] a = new int[50][50];  //方形网络

	private static int MAX = 100000;
	private static int leastFee;

	public static void main(String[] args){
		Scanner input = new Scanner(System.in);
		N = input.nextInt();
		K = input.nextInt();
		A = input.nextInt();
		B = input.nextInt();
		C = input.nextInt();

		for(int i=1; i<=N; i++){//输入方形网络
			for(int j=1; j<=N; j++){
				a[i][j] = input.nextInt();
			}
		}

		leastFee = dynamic();
		System.out.println(leastFee);//最优行驶路线所需的费用，即最小费用
	}

	private static int dynamic(){
		int i, j, k;
		for (i=1;i<=N;i++){
			for (j=1;j<=N;j++){
				f[i][j][0]=MAX;
				f[i][j][1]=K;
			}
		}

		f[1][1][0] = 0;
		f[1][1][1] = K;

		boolean finish = false;
		int tx, ty;
		while(!finish){
			finish = true;
			for(i=1; i<=N; i++){
				for(j=1; j<=N; j++){
					if(i==1 && j==1)
						continue;
					int minFee = MAX;
					int driveEdges = MAX;
					int fee, canDriveEdges;
					for(k=0; k<4; k++){ //可走的四个方向
						tx = i + s[k][0];
						ty = j + s[k][1];
						if(tx<1 || ty<1 || tx>N || ty>N)  //如果出界
							continue;

						fee = f[tx][ty][0] + s[k][2];
						canDriveEdges = f[tx][ty][1] - 1;
						if(a[i][j] == 1){  //如果是油库
							fee += A;
							canDriveEdges = K;
						}
						if(a[i][j]==0 && canDriveEdges == 0 && (i!=N||j!=N)){  //如果不是油库,且油已经用完
							fee += A + C;
							canDriveEdges = K;
						}
						if(fee < minFee){  //记录更少费用
							minFee = fee;
							driveEdges = canDriveEdges;
						}
					}

					if(f[i][j][0] > minFee){  //如果有更优解
						finish = false;
						f[i][j][0] = minFee;
						f[i][j][1] = driveEdges;
					}
				}
			}
		}
		return f[N][N][0];//汽车从网格点(1,1)行驶至网格点(N,N)所需的最少费用（亦即从起点到终点），此为所求
	}
}
