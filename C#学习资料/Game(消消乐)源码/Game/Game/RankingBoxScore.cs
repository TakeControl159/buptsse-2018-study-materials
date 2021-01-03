using System;
using System.Collections;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Linq;
using System.Reflection;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Game
{
    partial class RankingBoxScore : Form
    {
        /// <summary>
        /// 排行榜 0 - Name 1 - Score
        /// </summary>
        public static Label[,] labelPlayer = new Label[2, 10];

        public RankingBoxScore()
        {
            InitializeComponent();
            
            int x = 10;
            int y = 20;

            for(int i = 0; i < 10;i++)
            {
                //nameLabel
                labelPlayer[0, i]= new Label();

                labelPlayer[0, i].Name = "PlayerName" + i.ToString();
                labelPlayer[0, i].Location = new Point(x, y);
                labelPlayer[0, i].Text = (i + 1).ToString() + ":" + ScoreRanking.PlayerName[i] + "：";
                //labelPlayer[0, i].Text = (i + 1).ToString() + "：nnnnn：";  共可容纳5个字符
                labelPlayer[0, i].Font = new Font("雅黑",10);
                //labelPlayer[0, i].Size = new Size(80, 25);
                groupBoxScoreAndName.Controls.Add(labelPlayer[0, i]);

                //scoreLabel
                labelPlayer[1, i]= new Label();

                labelPlayer[1, i].Name = "PlayerScore" + i.ToString();
                labelPlayer[1, i].Location = new Point(x + labelPlayer[0, i].Size.Width, y);
                labelPlayer[1, i].Text = ScoreRanking.PlayerScore[i].ToString();
                //labelPlayer[1, i].Text = "12345678910";  共可容纳11位数
                labelPlayer[1, i].Font = new Font("雅黑", 10);
                //labelPlayer[1, i].Size = new Size(100, 30);
                groupBoxScoreAndName.Controls.Add(labelPlayer[1, i]);

                if(i%5 == 0 && i != 0)
                {
                    y = 25;
                    x += 200;
                }
                else
                {
                    y += 30;
                }
            }
        }

        private void okButton_Click(object sender, EventArgs e)
        {
            ScoreRanking.RankingBoxScoreShown = false;
            this.Close();
        }

        public static void SocreChange()
        {
            for(int i = 0;i <10 ;i++)
            {
                labelPlayer[1, i].Text = ScoreRanking.PlayerScore[i].ToString();
                labelPlayer[0, i].Text = (i + 1).ToString() + ":" + ScoreRanking.PlayerName[i] + "：";
            }
        }
    }
}
