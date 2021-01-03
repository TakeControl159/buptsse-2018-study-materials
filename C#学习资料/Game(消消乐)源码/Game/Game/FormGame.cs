using System;
using System.Collections.Generic;
using System.Drawing;
using System.Windows.Forms;

namespace Game
{
    /// <summary>
    /// 窗体类
    /// </summary>
    public partial class FormGame : Form
    {
        #region   成员变量

        /// <summary>
        /// 游戏总得分
        /// </summary>
        int Score = 0;
        /// <summary>
        /// 排名
        /// </summary>
        ScoreRanking rankingScore;
        /// <summary>
        /// 星星集  长度10*10
        /// </summary>
        public PictureBox[,] pictureBox = new PictureBox[10,10];
        /// <summary>
        /// 标记相同项  个位-x 十位-y  用完清空
        /// </summary>
        public Star LocationOfSameStar = new Star();
        /// <summary>
        /// x轴平移
        /// </summary>
        int x = 4;
        /// <summary>
        /// y轴平移
        /// </summary>
        int y = 10;

        #endregion

        #region   函数方法
        /// <summary>
        /// 开始
        /// </summary>
        private void Start()
        {
            for (int X=0; X < 10; X++)
                for (int Y = 0; Y < 10; Y++)
                {
                    Star.RandomNext(X, Y);
                    PictureShow(X, Y);
                }

            /*
            Score = 0;
            labelScoreInt.Text = "0";*/
            labelScoreInt.Text = (Score = 0).ToString();
            pictureBoxStop.Hide();
            progressBarTime.Value = 7000;
            stars.Clear();
            GameStared = true;
            timerTime.Enabled = true;
            暂停ToolStripMenuItem2.Enabled = true;
            timerCheckStarAll.Enabled = true;
        }

        /// <summary>
        /// 初始化PictureBox控件
        /// </summary>
        public void PictureBoxShowFirst()
        {
            for (int X = 0; X < 10; X++)
            {
                for (int Y = 0; Y < 10; Y++)
                {
                    pictureBox[X, Y] = new PictureBox();
                    pictureBox[X, Y].Location = new Point(this.x, this.y);
                    pictureBox[X, Y].Size = new Size(30, 30);
                    pictureBox[X, Y].Image = imageListPng.Images[5];
                    pictureBox[X, Y].Name = X.ToString() + "-" + Y.ToString();
                    pictureBox[X, Y].Click += new EventHandler(PictureBox_Click);
                    pictureBox[X, Y].SizeMode = PictureBoxSizeMode.CenterImage;
                    groupBoxPic.Controls.Add(pictureBox[X, Y]);

                    this.y += 30;
                }

                this.x += 30;
                this.y = 10;
            }
        }

        /// <summary>
        /// 确认边框位置
        /// </summary>
        public enum Direction
        { Null,Top, Left, Right, Dawn };
        /// <summary>
        /// 检索相同项
        /// </summary>
        public bool CheckPicture()
        {
            //0-x 1-y
            Direction[,] eDirect = new Direction[2, 2];
            int[,] iNumberOfSamePicture = new int[,]{{1,1},{1,1}};  //{上下,左右}

            #region     判断边框位置
            for (int i=0; i<2; i++)
            {
                if (Star.PicturePoint[i].X == 9)
                    eDirect[i, 0] = Direction.Right;
                else if (Star.PicturePoint[0].X == 0)
                    eDirect[i, 0] = Direction.Left;
                else
                    eDirect[i,0] = Direction.Null;

                if (Star.PicturePoint[i].Y == 0)
                    eDirect[i, 1] = Direction.Top;
                else if (Star.PicturePoint[0].Y == 9)
                    eDirect[i, 1] = Direction.Dawn;
                else
                    eDirect[i,1] = Direction.Null;
            }
            #endregion

            #region   检索四周相同项
            for (int i = 0; i<2; i++)
            {
                //上检索
                if (eDirect[i, 1] != Direction.Top)
                {
                    for (int Y = Star.PicturePoint[i].Y; Y > 0; Y--)
                    {
                        if (Star.numberOfStar[Star.PicturePoint[i].X, Y] == Star.numberOfStar[Star.PicturePoint[i].X, Y - 1])
                        {
                            iNumberOfSamePicture[i, 1]++;
                        }
                        else
                            break;
                    }
                }

                //下检索
                if (eDirect[i, 1] != Direction.Dawn)
                {
                    for (int Y = Star.PicturePoint[i].Y; Y < 9; Y++)
                    {
                        if (Star.numberOfStar[Star.PicturePoint[i].X, Y] == Star.numberOfStar[Star.PicturePoint[i].X, Y + 1])
                        {
                            iNumberOfSamePicture[i, 1]++;
                        }
                        else
                            break;
                    }
                }

                //左检索
                if(eDirect[i,0] != Direction.Left)
                {
                    for (int X = Star.PicturePoint[i].X; X > 0; X--)
                    {
                        if (Star.numberOfStar[X, Star.PicturePoint[i].Y] == Star.numberOfStar[X - 1, Star.PicturePoint[i].Y])
                        {
                            iNumberOfSamePicture[i, 0]++;
                        }
                        else
                            break;
                    }
                }

                //右检索
                if (eDirect[i, 0] != Direction.Right)
                {
                    for (int X = Star.PicturePoint[i].X; X < 9; X++)
                    {
                        if (Star.numberOfStar[X, Star.PicturePoint[i].Y] == Star.numberOfStar[X + 1, Star.PicturePoint[i].Y])
                        {
                            iNumberOfSamePicture[i, 0]++;
                        }
                        else
                            break;
                    }
                }
            }
            #endregion

            int score = ScoringComputation(iNumberOfSamePicture, eDirect);

            if (score == 0)
                return true;

            Score += score*10;

            if ((progressBarTime.Value + score*10) > progressBarTime.Maximum)
                progressBarTime.Value = progressBarTime.Maximum;
            else
                progressBarTime.Value += score*10;

            labelScoreInt.Text = Score.ToString();

            return false;
        }

        /// <summary>
        /// 计算得分
        /// </summary>
        /// <param name="iNumberOfPicture">检索所得结果(相同个数)</param>
        /// <param name="eDirect">边框位置记录</param>
        /// <returns>int 得分</returns>
        public int ScoringComputation(int[,] iNumberOfPicture, Direction[,] eDirect)
        {
            //得分
            int scoreOfNumber = 0;
            //0-x,1-y

            #region   检索 
            for (int i = 0; i < 2; i++)
            {
                #region   左右
                if (iNumberOfPicture[i, 0] >= 3)
                {
                    scoreOfNumber += iNumberOfPicture[i, 0];    //统计个数
                    LocationOfSameStar.Add(Star.PicturePoint[i]);

                    //左
                    if (eDirect[i, 0] != Direction.Left)
                        for (int X = Star.PicturePoint[i].X; X > 0; X--)
                            if (Star.numberOfStar[X, Star.PicturePoint[i].Y] == Star.numberOfStar[X -1, Star.PicturePoint[i].Y])
                            {
                                LocationOfSameStar.Add(new MyPoint(pictureBox[X - 1, Star.PicturePoint[i].Y].Name)); //记录位置
                            }
                            else
                                break;
                    //右
                    if (eDirect[i, 0] != Direction.Right)
                        for (int X = Star.PicturePoint[i].X; X < 9; X++)
                            if (Star.numberOfStar[X, Star.PicturePoint[i].Y] == Star.numberOfStar[X +1, Star.PicturePoint[i].Y])
                            {
                                LocationOfSameStar.Add(new MyPoint(pictureBox[X + 1, Star.PicturePoint[i].Y].Name));
                            }
                            else
                                break;
                }
                #endregion

                #region   上下
                if (iNumberOfPicture[i, 1] >= 3)
                {
                    scoreOfNumber += iNumberOfPicture[i, 1];    //统计个数
                    LocationOfSameStar.Add(Star.PicturePoint[i]);

                    //上
                    if (eDirect[i, 1] != Direction.Dawn)
                        for (int Y = Star.PicturePoint[i].Y; Y > 0; Y--)
                            if (Star.numberOfStar[Star.PicturePoint[i].X, Y] == Star.numberOfStar[Star.PicturePoint[i].X, Y - 1])
                            {
                                LocationOfSameStar.Add(new MyPoint(pictureBox[Star.PicturePoint[i].X, Y - 1].Name));
                            }
                            else
                                break;

                    //下
                    if (eDirect[i, 1] != Direction.Top)
                        for (int Y = Star.PicturePoint[i].Y; Y < 9; Y++)
                            if (Star.numberOfStar[Star.PicturePoint[i].X, Y] == Star.numberOfStar[Star.PicturePoint[i].X, Y + 1])
                            {
                                LocationOfSameStar.Add(new MyPoint(pictureBox[Star.PicturePoint[i].X, Y + 1].Name));
                            }
                            else
                                break;
                }
                #endregion
            }
            #endregion

            LocationOfSameStar.Short();

            StarFallDown(LocationOfSameStar.Stars, true, pictureBox);

            return scoreOfNumber;
        }

        /// <summary>
        /// 星星下落
        /// </summary>
        private void StarFallDown(List<MyPoint> LocationOfSameStar,bool Click,object[,] pictureBox)
        {
            for (int i = 0; i < LocationOfSameStar.Count; i++)
            {
                //消除星星
                Star.numberOfStar[LocationOfSameStar[i].X, LocationOfSameStar[i].Y] = 5;
                PictureShow(LocationOfSameStar[i].X, LocationOfSameStar[i].Y);

                if (Click)
                {
                    (pictureBox[Star.PicturePoint[0].X, Star.PicturePoint[0].Y] as PictureBox).BackColor = Color.Transparent;
                    (pictureBox[Star.PicturePoint[1].X, Star.PicturePoint[1].Y] as PictureBox).BackColor = Color.Transparent;
                }

                for (int Y = LocationOfSameStar[i].Y; Y > 0; Y--)
                {
                    //星星下落
                    Star.numberOfStar[LocationOfSameStar[i].X, Y] = Star.numberOfStar[LocationOfSameStar[i].X, Y - 1];
                    Star.numberOfStar[LocationOfSameStar[i].X, Y - 1] = 5;
                    PictureShow(LocationOfSameStar[i].X, Y);
                    PictureShow(LocationOfSameStar[i].X, Y-1);
                }

                Star.RandomNext(LocationOfSameStar[i].X, 0);
                PictureShow(LocationOfSameStar[i].X, 0);
            }

            LocationOfSameStar.Clear();  //清空上次使用项
        }

        /// <summary>
        /// ArryList-MyPoint 重排列
        /// </summary>
        private void MyShort(List<MyPoint> LocationOfSameStar)
        {
            for(int i = 0;i < LocationOfSameStar.Count - 1;i++)
                for (int j = i + 1; j < LocationOfSameStar.Count; j++)
                {
                    MyPoint temp;
                    int n = i;

                    if (LocationOfSameStar[j].Y > LocationOfSameStar[n].Y)
                    { n = j; }

                    temp = new MyPoint(LocationOfSameStar[n]);
                    LocationOfSameStar[n] = LocationOfSameStar[i];
                    LocationOfSameStar[i] = temp;
                }
        }

        /// <summary>
        /// 显示星星
        /// </summary>
        /// <param name="X">横坐标</param>
        /// <param name="Y">纵坐标</param>
        public void PictureShow(int X,int Y)
        {
            pictureBox[X, Y].Image = imageListPng.Images[Star.numberOfStar[X, Y]];
        }
        #endregion

        #region    控件事件
        /// <summary>
        /// 初始化窗口
        /// </summary>
        public FormGame()
        {
            InitializeComponent();
            PictureBoxShowFirst();
            rankingScore = new ScoreRanking();
            暂停ToolStripMenuItem2.Enabled = false;
        }

        /// <summary>
        /// 单击
        /// </summary>
        bool bClick = false;
        /// <summary>
        /// pictureBox事件
        /// </summary>
        /// <param name="sender">触发对象</param>
        /// <param name="e">事件状态</param>
        private void PictureBox_Click(object sender, EventArgs e)
        {
            Star.PicturePoint[1] = new MyPoint(((PictureBox)sender).Name);

            if (!bClick)
            {
                ((PictureBox)sender).BackColor = Color.Orange;
                Star.PicturePoint[0] = new MyPoint(((PictureBox)sender).Name);
                bClick = true;
            }
            else
            {
                if (Star.PicturePoint[0] == Star.PicturePoint[1])
                {
                    ((PictureBox)sender).BackColor = Color.Transparent;
                }
                else if (Star.PicturePoint[0].X == Star.PicturePoint[1].X - 1 || Star.PicturePoint[0].X == Star.PicturePoint[1].X + 1 || Star.PicturePoint[0].Y == Star.PicturePoint[1].Y + 1 || Star.PicturePoint[0].Y == Star.PicturePoint[1].Y - 1)
                {
                    ((PictureBox)sender).BackColor = Color.Orange;
                    Star.Swap(Star.PicturePoint);
                    PictureShow(Star.PicturePoint[1].X, Star.PicturePoint[1].Y);
                    PictureShow(Star.PicturePoint[0].X, Star.PicturePoint[0].Y);

                    timerSwapPicture.Enabled = CheckPicture(); //是否交换回图片

                    pictureBox[Star.PicturePoint[0].X, Star.PicturePoint[0].Y].BackColor = Color.Transparent;
                    pictureBox[Star.PicturePoint[1].X, Star.PicturePoint[1].Y].BackColor = Color.Transparent;
                }
                else
                    pictureBox[Star.PicturePoint[0].X, Star.PicturePoint[0].Y].BackColor = Color.Transparent;

                bClick = false;
            }
        }

        /// <summary>
        /// 时间条
        /// </summary>
        private void timerTime_Tick(object sender, EventArgs e)
        {
            progressBarTime.Value--;
            if(progressBarTime.Value == 0)
            {
                timerTime.Enabled = false;
                pictureBoxStop.Show();
                MessageBox.Show("游戏结束！");
                暂停ToolStripMenuItem2.Enabled = false;
                GameStared = false;
                timerCheckStarAll.Enabled = false;

                ScoreRanking.Insert(Score);
            }
        }

        /// <summary>
        /// 图片交换还原
        /// </summary>
        private void timerSwapPic_Tick(object sender, EventArgs e)
        {
            Star.Swap(Star.PicturePoint);
            PictureShow(Star.PicturePoint[1].X, Star.PicturePoint[1].Y);
            PictureShow(Star.PicturePoint[0].X, Star.PicturePoint[0].Y);

            pictureBox[Star.PicturePoint[0].X, Star.PicturePoint[0].Y].BackColor = Color.Transparent;
            pictureBox[Star.PicturePoint[1].X, Star.PicturePoint[1].Y].BackColor = Color.Transparent;
            timerSwapPicture.Enabled = false;
        }

        /// <summary>
        /// 关于窗口显示与否
        /// </summary>
        public static bool AboutBoxShown = false;
        private void 关于ToolStripMenuItem2_Click(object sender, EventArgs e)
        {
            if (!AboutBoxShown)
            {
                AboutBoxGame about = new AboutBoxGame();
                AboutBoxShown = false;
                about.Show();
            }
        }

        private void 得分纪录ToolStripMenuItem1_Click(object sender, EventArgs e)
        {
            if (!ScoreRanking.RankingBoxScoreShown)
            {
                RankingBoxScore ranking = new RankingBoxScore();
                ScoreRanking.RankingBoxScoreShown = true;
                ranking.Show();
            }
        }

        /// <summary>
        /// 开始
        /// </summary>
        bool GameStared = false;
        private void 开始新游戏ToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (!GameStared)
            {
                Start();
            }
            else
            {
                DialogResult dialog  = MessageBox.Show("游戏已开始，是否放弃当前游戏进度?", "提示",MessageBoxButtons.YesNo);

                if(dialog == DialogResult.Yes)                
                    Start();
                
            }
        }

        private void 暂停ToolStripMenuItem2_Click(object sender, EventArgs e)
        {
            if(timerTime.Enabled)
            {
                timerTime.Enabled = false;
                timerCheckStarAll.Enabled = false;
                暂停ToolStripMenuItem2.Text = "继续";
                pictureBoxStop.Show();
            }
            else
            {
                timerTime.Enabled = true;
                timerCheckStarAll.Enabled = true;
                暂停ToolStripMenuItem2.Text = "暂停";
                pictureBoxStop.Hide();
            }
        }

        private void 退出ToolStripMenuItem2_Click(object sender, EventArgs e)
        {
            Application.Exit();
        }

        /// <summary>
        /// 检索非点击相同项
        /// </summary>
        Star stars = new Star();
        /// <summary>
        /// 检索相同项非点击
        /// </summary>
        private void timerCheckStarAll_Tick(object sender, EventArgs e)
        {//TODO  无法正常检索
            //int n = 1;

            #region    横向
            /*for (int Y = 0; Y < 10; Y++)
                for (int X = 0; X < 9; X++)
                {
                    stars.Add(new MyPoint(X, Y));

                    if (Star.numberOfStar[Y, X] == Star.numberOfStar[Y, X + 1])
                    {
                        stars.Add(new MyPoint(X + 1, Y));
                        n++;
                    }
                    else
                    {
                        if (n < 3)
                            stars.Stars.RemoveRange(stars.Count - n, n);

                        n = 1;
                    }

                    if(X == 9)
                    {
                        if (n < 3)
                            stars.Stars.RemoveRange(stars.Count - n, n);

                        n = 1;
                    }
                }*/
            #endregion

            //n = 1;
            
            #region    纵向
            /*
            for (int X = 0; X < 10; X++)
                for (int Y = 0; Y < 9; Y++)
                {
                    stars.Add(new MyPoint(X, Y));

                    if (Star.numberOfStar[X, Y] == Star.numberOfStar[X, Y + 1])
                    {
                        if (stars.Check(new MyPoint(X, Y + 1)))
                        {
                            stars.Add(new MyPoint(X, Y + 1));
                            n++;
                        }
                    }
                    else
                    {
                        if (n < 3)
                            stars.RemoveRange(n);

                        n = 1;
                    }

                    if (Y == 9)
                    {
                        if (n < 3)
                            stars.Stars.RemoveRange(stars.Count - n, n);

                        n = 1;
                    }
                }*/
            #endregion
            
            //stars.Short();
            //Score += stars.Count;
            //labelScoreInt.Text = Score.ToString();
            
            //StarFallDown(stars.Stars, false, pictureBox);
            
            stars.Clear();
        }

        /// <summary>
        /// 窗体关闭时
        /// </summary>
        private void FormGame_FormClosing(object sender, FormClosingEventArgs e)
        {
            rankingScore.Save();
            Application.Exit();
        }
        #endregion
    }
}
