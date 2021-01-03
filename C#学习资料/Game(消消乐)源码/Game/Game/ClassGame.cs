using Game.Properties;
using Microsoft.VisualBasic;
using System;
using System.Collections.Generic;

namespace Game
{
    /// <summary>
    /// 自定义点阵
    /// </summary>
    public partial class MyPoint
    {
        public MyPoint(string pictureBoxName)
        {
            string[] xy = pictureBoxName.Split('-');

            x = int.Parse(xy[0]);
            y = int.Parse(xy[1]);
        }

        public MyPoint(MyPoint myPoint)
        {
            x = myPoint.X;
            y = myPoint.Y;
        }

        public MyPoint(int x,int y)
        {
            this.x = x;
            this.y = y;
        }

        private int x;
        public int X
        { get { return x; } }

        private int y;
        public int Y
        { get { return y; } }
    }

    /// <summary>
    /// 星星—主要用于记录相同项
    /// </summary>
    public partial class Star
    {
        #region   公共成员
        /// <summary>
        /// 星星序号  长度10*10
        /// </summary>
        public static int[,] numberOfStar = new int[10, 10];
        /// <summary>
        /// 随机变量
        /// </summary>
        public static Random rand = new Random();
        /// <summary>
        /// 地址记录  长度2
        /// </summary>
        public static MyPoint[] PicturePoint = new MyPoint[2];

        /// <summary>
        /// 交换
        /// </summary>
        public static void Swap(MyPoint[] PicturePoint)
        {
            numberOfStar[PicturePoint[0].X, PicturePoint[0].Y] = numberOfStar[PicturePoint[0].X, PicturePoint[0].Y]^numberOfStar[PicturePoint[1].X, PicturePoint[1].Y];
            numberOfStar[PicturePoint[1].X, PicturePoint[1].Y] = numberOfStar[PicturePoint[1].X, PicturePoint[1].Y]^numberOfStar[PicturePoint[0].X, PicturePoint[0].Y];
            numberOfStar[PicturePoint[0].X, PicturePoint[0].Y] = numberOfStar[PicturePoint[0].X, PicturePoint[0].Y]^numberOfStar[PicturePoint[1].X, PicturePoint[1].Y];
        }

        /// <summary>
        /// 生成随机量
        /// </summary>
        /// <param name="x">横坐标</param>
        /// <param name="y">纵坐标</param>
        public static void RandomNext(int x,int y)
        {
            numberOfStar[x, y] = rand.Next(0, 5);
        }
        #endregion

        #region   对象成员
        public List<MyPoint> Stars = new List<MyPoint>();

        /// <summary>
        /// 返回记录点个数
        /// </summary>
        public int Count
        { get { return Stars.Count; } }

        /// <summary>
        /// 查找相应的值
        /// </summary>
        /// <param name="point">点</param>
        /// <returns>是否查找到</returns>
        public bool Check(MyPoint point)
        {
            for(int i = 0;i < Stars.Count;i++)
            {
                if (Stars[i].X == point.X && Stars[i].Y == point.Y)
                    return true;
            }

            return false;
        }

        /// <summary>
        /// 清除原有项
        /// </summary>
        public void Clear()
        {
            Stars.Clear();
        }

        /// <summary>
        /// 添加新的点
        /// </summary>
        /// <param name="point">点</param>
        public void Add(MyPoint point)
        {
            Stars.Add(point);
        }

        /// <summary>
        /// 排序
        /// </summary>
        public void Short()
        {
            for (int i = 0; i < Stars.Count - 1; i++)
                for (int j = i + 1; j < Stars.Count; j++)
                {
                    MyPoint temp;
                    int n = i;

                    if (Stars[j].Y > Stars[n].Y)
                    { n = j; }

                    temp = new MyPoint(Stars[n]);
                    Stars[n] = Stars[i];
                    Stars[i] = temp;
                }
        }

        /// <summary>
        /// 移除后续项
        /// </summary>
        /// <param name="n">需要移除数量</param>
        public void RemoveRange(int n)
        {
            Stars.RemoveRange(Stars.Count - n, n);
        }
        #endregion
    }

    /// <summary>
    /// 排行榜
    /// </summary>
    public partial class ScoreRanking
    {
        public ScoreRanking()
        {
            PlayerName[0] = Settings.Default.Player1;
            PlayerName[1] = Settings.Default.Player2;
            PlayerName[2] = Settings.Default.Player3;
            PlayerName[3] = Settings.Default.Player4;
            PlayerName[4] = Settings.Default.Player5;
            PlayerName[5] = Settings.Default.Player6;
            PlayerName[6] = Settings.Default.Player7;
            PlayerName[7] = Settings.Default.Player8;
            PlayerName[8] = Settings.Default.Player9;
            PlayerName[9] = Settings.Default.Player10;

            PlayerScore[0] = Settings.Default.Score1;
            PlayerScore[1] = Settings.Default.Score2;
            PlayerScore[2] = Settings.Default.Score3;
            PlayerScore[3] = Settings.Default.Score4;
            PlayerScore[4] = Settings.Default.Score5;
            PlayerScore[5] = Settings.Default.Score6;
            PlayerScore[6] = Settings.Default.Score7;
            PlayerScore[7] = Settings.Default.Score8;
            PlayerScore[8] = Settings.Default.Score9;
            PlayerScore[9] = Settings.Default.Score10;
        }

        public void Save()
        {
            Settings.Default.Player1 = PlayerName[0];
            Settings.Default.Player2 = PlayerName[1];
            Settings.Default.Player3 = PlayerName[2];
            Settings.Default.Player4 = PlayerName[3];
            Settings.Default.Player5 = PlayerName[4];
            Settings.Default.Player6 = PlayerName[5];
            Settings.Default.Player7 = PlayerName[6];
            Settings.Default.Player8 = PlayerName[7];
            Settings.Default.Player9 = PlayerName[8];
            Settings.Default.Player10 = PlayerName[9];

            Settings.Default.Score1 = PlayerScore[0];
            Settings.Default.Score2 = PlayerScore[1];
            Settings.Default.Score3 = PlayerScore[2];
            Settings.Default.Score4 = PlayerScore[3];
            Settings.Default.Score5 = PlayerScore[4];
            Settings.Default.Score6 = PlayerScore[5];
            Settings.Default.Score7 = PlayerScore[6];
            Settings.Default.Score8 = PlayerScore[7];
            Settings.Default.Score9 = PlayerScore[8];
            Settings.Default.Score10 = PlayerScore[9];
        }

        /// <summary>
        /// 排序
        /// </summary>
        public static string[] top10 = new string[] { "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "9th", "10th" };

        /// <summary>
        /// 排名 姓名
        /// </summary>
        public static string[] PlayerName = new string[10];
        /// <summary>
        /// 排名 分数
        /// </summary>
        public static int[] PlayerScore = new int[10];

        /// <summary>
        /// 排行榜窗口打开与否
        /// </summary>
        public static bool RankingBoxScoreShown = false;

        public static void Insert(int score)
        {
            for (int i = 0; i<10; i++)
            {
                if (PlayerScore[i] < score)
                {
                    //玩家名字
                    string playername = Interaction.InputBox("请输入姓名", top10[i], "PlayerName" + (i + 1).ToString());
                    if (playername.Length > 10) playername = playername.Remove(10);

                    //中转用
                    string swapName;

                    for (int j = i; j<10; j++)
                    {
                        PlayerScore[j] = PlayerScore[j]^score;
                        score = score^PlayerScore[j];
                        PlayerScore[j] = PlayerScore[j]^score;

                        swapName = PlayerName[j];
                        PlayerName[j] = playername;
                        playername = swapName;
                    }
                    break;
                }

                if (RankingBoxScoreShown)
                    RankingBoxScore.SocreChange();
            }
        }
    }
}
