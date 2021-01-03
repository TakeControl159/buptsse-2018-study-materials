namespace Game
{
    partial class FormGame
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
        /// <param name="disposing">如果应释放托管资源，为 true；否则为 false。</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows 窗体设计器生成的代码

        /// <summary>
        /// 设计器支持所需的方法 - 不要
        /// 使用代码编辑器修改此方法的内容。
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(FormGame));
            this.progressBarTime = new System.Windows.Forms.ProgressBar();
            this.groupBoxPic = new System.Windows.Forms.GroupBox();
            this.pictureBoxStop = new System.Windows.Forms.PictureBox();
            this.imageListPng = new System.Windows.Forms.ImageList(this.components);
            this.labelScore = new System.Windows.Forms.Label();
            this.labelScoreInt = new System.Windows.Forms.Label();
            this.timerTime = new System.Windows.Forms.Timer(this.components);
            this.游戏ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.新游戏ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.暂停ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.退出ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.难度ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.关于ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.历史记录ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.游戏ToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.开始游戏ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.暂停ToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.退出ToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.得分纪录ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.关于ToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.menuStripGame = new System.Windows.Forms.MenuStrip();
            this.游戏ToolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.开始新游戏ToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.暂停ToolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.退出ToolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.得分纪录ToolStripMenuItem1 = new System.Windows.Forms.ToolStripMenuItem();
            this.关于ToolStripMenuItem2 = new System.Windows.Forms.ToolStripMenuItem();
            this.timerSwapPicture = new System.Windows.Forms.Timer(this.components);
            this.timerCheckStarAll = new System.Windows.Forms.Timer(this.components);
            this.groupBoxPic.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxStop)).BeginInit();
            this.menuStripGame.SuspendLayout();
            this.SuspendLayout();
            // 
            // progressBarTime
            // 
            this.progressBarTime.Location = new System.Drawing.Point(12, 351);
            this.progressBarTime.Maximum = 10000;
            this.progressBarTime.Name = "progressBarTime";
            this.progressBarTime.Size = new System.Drawing.Size(200, 13);
            this.progressBarTime.TabIndex = 0;
            this.progressBarTime.Value = 10000;
            // 
            // groupBoxPic
            // 
            this.groupBoxPic.Controls.Add(this.pictureBoxStop);
            this.groupBoxPic.Location = new System.Drawing.Point(12, 30);
            this.groupBoxPic.Name = "groupBoxPic";
            this.groupBoxPic.Size = new System.Drawing.Size(308, 315);
            this.groupBoxPic.TabIndex = 1;
            this.groupBoxPic.TabStop = false;
            // 
            // pictureBoxStop
            // 
            this.pictureBoxStop.Image = global::Game.Properties.Resources.Stop;
            this.pictureBoxStop.Location = new System.Drawing.Point(0, -6);
            this.pictureBoxStop.Name = "pictureBoxStop";
            this.pictureBoxStop.Size = new System.Drawing.Size(308, 321);
            this.pictureBoxStop.TabIndex = 5;
            this.pictureBoxStop.TabStop = false;
            // 
            // imageListPng
            // 
            this.imageListPng.ImageStream = ((System.Windows.Forms.ImageListStreamer)(resources.GetObject("imageListPng.ImageStream")));
            this.imageListPng.TransparentColor = System.Drawing.Color.Transparent;
            this.imageListPng.Images.SetKeyName(0, "1.png");
            this.imageListPng.Images.SetKeyName(1, "2.png");
            this.imageListPng.Images.SetKeyName(2, "3.png");
            this.imageListPng.Images.SetKeyName(3, "4.png");
            this.imageListPng.Images.SetKeyName(4, "5.png");
            this.imageListPng.Images.SetKeyName(5, "0.png");
            // 
            // labelScore
            // 
            this.labelScore.AutoSize = true;
            this.labelScore.Location = new System.Drawing.Point(218, 352);
            this.labelScore.Name = "labelScore";
            this.labelScore.Size = new System.Drawing.Size(41, 12);
            this.labelScore.TabIndex = 2;
            this.labelScore.Text = "得分：";
            // 
            // labelScoreInt
            // 
            this.labelScoreInt.AutoSize = true;
            this.labelScoreInt.Location = new System.Drawing.Point(265, 352);
            this.labelScoreInt.Name = "labelScoreInt";
            this.labelScoreInt.Size = new System.Drawing.Size(11, 12);
            this.labelScoreInt.TabIndex = 3;
            this.labelScoreInt.Text = "0";
            // 
            // timerTime
            // 
            this.timerTime.Interval = 1;
            this.timerTime.Tick += new System.EventHandler(this.timerTime_Tick);
            // 
            // 游戏ToolStripMenuItem
            // 
            this.游戏ToolStripMenuItem.Name = "游戏ToolStripMenuItem";
            this.游戏ToolStripMenuItem.Size = new System.Drawing.Size(32, 19);
            // 
            // 新游戏ToolStripMenuItem
            // 
            this.新游戏ToolStripMenuItem.Name = "新游戏ToolStripMenuItem";
            this.新游戏ToolStripMenuItem.Size = new System.Drawing.Size(32, 19);
            // 
            // 暂停ToolStripMenuItem
            // 
            this.暂停ToolStripMenuItem.Name = "暂停ToolStripMenuItem";
            this.暂停ToolStripMenuItem.Size = new System.Drawing.Size(32, 19);
            // 
            // 退出ToolStripMenuItem
            // 
            this.退出ToolStripMenuItem.Name = "退出ToolStripMenuItem";
            this.退出ToolStripMenuItem.Size = new System.Drawing.Size(32, 19);
            // 
            // 难度ToolStripMenuItem
            // 
            this.难度ToolStripMenuItem.Name = "难度ToolStripMenuItem";
            this.难度ToolStripMenuItem.Size = new System.Drawing.Size(32, 19);
            // 
            // 关于ToolStripMenuItem
            // 
            this.关于ToolStripMenuItem.Name = "关于ToolStripMenuItem";
            this.关于ToolStripMenuItem.Size = new System.Drawing.Size(32, 19);
            // 
            // 历史记录ToolStripMenuItem
            // 
            this.历史记录ToolStripMenuItem.Name = "历史记录ToolStripMenuItem";
            this.历史记录ToolStripMenuItem.Size = new System.Drawing.Size(32, 19);
            // 
            // 游戏ToolStripMenuItem1
            // 
            this.游戏ToolStripMenuItem1.Name = "游戏ToolStripMenuItem1";
            this.游戏ToolStripMenuItem1.Size = new System.Drawing.Size(32, 19);
            // 
            // 开始游戏ToolStripMenuItem
            // 
            this.开始游戏ToolStripMenuItem.Name = "开始游戏ToolStripMenuItem";
            this.开始游戏ToolStripMenuItem.Size = new System.Drawing.Size(32, 19);
            // 
            // 暂停ToolStripMenuItem1
            // 
            this.暂停ToolStripMenuItem1.Name = "暂停ToolStripMenuItem1";
            this.暂停ToolStripMenuItem1.Size = new System.Drawing.Size(32, 19);
            // 
            // 退出ToolStripMenuItem1
            // 
            this.退出ToolStripMenuItem1.Name = "退出ToolStripMenuItem1";
            this.退出ToolStripMenuItem1.Size = new System.Drawing.Size(32, 19);
            // 
            // 得分纪录ToolStripMenuItem
            // 
            this.得分纪录ToolStripMenuItem.Name = "得分纪录ToolStripMenuItem";
            this.得分纪录ToolStripMenuItem.Size = new System.Drawing.Size(32, 19);
            // 
            // 关于ToolStripMenuItem1
            // 
            this.关于ToolStripMenuItem1.Name = "关于ToolStripMenuItem1";
            this.关于ToolStripMenuItem1.Size = new System.Drawing.Size(32, 19);
            // 
            // menuStripGame
            // 
            this.menuStripGame.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.游戏ToolStripMenuItem2,
            this.得分纪录ToolStripMenuItem1,
            this.关于ToolStripMenuItem2});
            this.menuStripGame.Location = new System.Drawing.Point(0, 0);
            this.menuStripGame.Name = "menuStripGame";
            this.menuStripGame.Size = new System.Drawing.Size(333, 25);
            this.menuStripGame.TabIndex = 4;
            this.menuStripGame.Text = "menuStrip1";
            // 
            // 游戏ToolStripMenuItem2
            // 
            this.游戏ToolStripMenuItem2.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.开始新游戏ToolStripMenuItem,
            this.暂停ToolStripMenuItem2,
            this.退出ToolStripMenuItem2});
            this.游戏ToolStripMenuItem2.Name = "游戏ToolStripMenuItem2";
            this.游戏ToolStripMenuItem2.Size = new System.Drawing.Size(44, 21);
            this.游戏ToolStripMenuItem2.Text = "游戏";
            // 
            // 开始新游戏ToolStripMenuItem
            // 
            this.开始新游戏ToolStripMenuItem.Name = "开始新游戏ToolStripMenuItem";
            this.开始新游戏ToolStripMenuItem.Size = new System.Drawing.Size(136, 22);
            this.开始新游戏ToolStripMenuItem.Text = "开始新游戏";
            this.开始新游戏ToolStripMenuItem.Click += new System.EventHandler(this.开始新游戏ToolStripMenuItem_Click);
            // 
            // 暂停ToolStripMenuItem2
            // 
            this.暂停ToolStripMenuItem2.Name = "暂停ToolStripMenuItem2";
            this.暂停ToolStripMenuItem2.Size = new System.Drawing.Size(136, 22);
            this.暂停ToolStripMenuItem2.Text = "暂停";
            this.暂停ToolStripMenuItem2.Click += new System.EventHandler(this.暂停ToolStripMenuItem2_Click);
            // 
            // 退出ToolStripMenuItem2
            // 
            this.退出ToolStripMenuItem2.Name = "退出ToolStripMenuItem2";
            this.退出ToolStripMenuItem2.Size = new System.Drawing.Size(136, 22);
            this.退出ToolStripMenuItem2.Text = "退出";
            this.退出ToolStripMenuItem2.Click += new System.EventHandler(this.退出ToolStripMenuItem2_Click);
            // 
            // 得分纪录ToolStripMenuItem1
            // 
            this.得分纪录ToolStripMenuItem1.Name = "得分纪录ToolStripMenuItem1";
            this.得分纪录ToolStripMenuItem1.Size = new System.Drawing.Size(68, 21);
            this.得分纪录ToolStripMenuItem1.Text = "得分纪录";
            this.得分纪录ToolStripMenuItem1.Click += new System.EventHandler(this.得分纪录ToolStripMenuItem1_Click);
            // 
            // 关于ToolStripMenuItem2
            // 
            this.关于ToolStripMenuItem2.Name = "关于ToolStripMenuItem2";
            this.关于ToolStripMenuItem2.Size = new System.Drawing.Size(44, 21);
            this.关于ToolStripMenuItem2.Text = "关于";
            this.关于ToolStripMenuItem2.Click += new System.EventHandler(this.关于ToolStripMenuItem2_Click);
            // 
            // timerSwapPicture
            // 
            this.timerSwapPicture.Interval = 500;
            this.timerSwapPicture.Tick += new System.EventHandler(this.timerSwapPic_Tick);
            // 
            // timerCheckStarAll
            // 
            this.timerCheckStarAll.Interval = 1000;
            this.timerCheckStarAll.Tick += new System.EventHandler(this.timerCheckStarAll_Tick);
            // 
            // FormGame
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(333, 376);
            this.Controls.Add(this.labelScoreInt);
            this.Controls.Add(this.labelScore);
            this.Controls.Add(this.groupBoxPic);
            this.Controls.Add(this.progressBarTime);
            this.Controls.Add(this.menuStripGame);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.MainMenuStrip = this.menuStripGame;
            this.MaximizeBox = false;
            this.Name = "FormGame";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "消消乐";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.FormGame_FormClosing);
            this.groupBoxPic.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.pictureBoxStop)).EndInit();
            this.menuStripGame.ResumeLayout(false);
            this.menuStripGame.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ProgressBar progressBarTime;
        public System.Windows.Forms.ImageList imageListPng;
        protected internal System.Windows.Forms.GroupBox groupBoxPic;
        private System.Windows.Forms.Label labelScore;
        private System.Windows.Forms.Label labelScoreInt;
        private System.Windows.Forms.Timer timerTime;
        private System.Windows.Forms.ToolStripMenuItem 游戏ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 新游戏ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 暂停ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 退出ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 难度ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 关于ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 历史记录ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 游戏ToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem 开始游戏ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 暂停ToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem 退出ToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem 得分纪录ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 关于ToolStripMenuItem1;
        private System.Windows.Forms.MenuStrip menuStripGame;
        private System.Windows.Forms.ToolStripMenuItem 游戏ToolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem 开始新游戏ToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem 暂停ToolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem 退出ToolStripMenuItem2;
        private System.Windows.Forms.ToolStripMenuItem 得分纪录ToolStripMenuItem1;
        private System.Windows.Forms.ToolStripMenuItem 关于ToolStripMenuItem2;
        private System.Windows.Forms.Timer timerSwapPicture;
        private System.Windows.Forms.PictureBox pictureBoxStop;
        private System.Windows.Forms.Timer timerCheckStarAll;
    }
}

