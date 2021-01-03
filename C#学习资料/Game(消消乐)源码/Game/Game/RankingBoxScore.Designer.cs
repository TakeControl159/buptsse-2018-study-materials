namespace Game
{
    partial class RankingBoxScore
    {
        /// <summary>
        /// 必需的设计器变量。
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// 清理所有正在使用的资源。
        /// </summary>
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
            this.groupBoxScoreAndName = new System.Windows.Forms.GroupBox();
            this.okButton = new System.Windows.Forms.Button();
            this.groupBoxScoreAndName.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBoxScoreAndName
            // 
            this.groupBoxScoreAndName.Controls.Add(this.okButton);
            this.groupBoxScoreAndName.Location = new System.Drawing.Point(12, 11);
            this.groupBoxScoreAndName.Name = "groupBoxScoreAndName";
            this.groupBoxScoreAndName.Size = new System.Drawing.Size(411, 239);
            this.groupBoxScoreAndName.TabIndex = 1;
            this.groupBoxScoreAndName.TabStop = false;
            this.groupBoxScoreAndName.Text = "排行榜";
            // 
            // okButton
            // 
            this.okButton.Anchor = ((System.Windows.Forms.AnchorStyles)((System.Windows.Forms.AnchorStyles.Bottom | System.Windows.Forms.AnchorStyles.Right)));
            this.okButton.DialogResult = System.Windows.Forms.DialogResult.Cancel;
            this.okButton.Location = new System.Drawing.Point(330, 212);
            this.okButton.Name = "okButton";
            this.okButton.Size = new System.Drawing.Size(75, 21);
            this.okButton.TabIndex = 25;
            this.okButton.Text = "确定(&O)";
            this.okButton.Click += new System.EventHandler(this.okButton_Click);
            // 
            // RankingBoxScore
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 12F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(435, 261);
            this.Controls.Add(this.groupBoxScoreAndName);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedDialog;
            this.MaximizeBox = false;
            this.MinimizeBox = false;
            this.Name = "RankingBoxScore";
            this.Padding = new System.Windows.Forms.Padding(9, 8, 9, 8);
            this.ShowIcon = false;
            this.ShowInTaskbar = false;
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterParent;
            this.Text = "排行榜";
            this.groupBoxScoreAndName.ResumeLayout(false);
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBoxScoreAndName;
        private System.Windows.Forms.Button okButton;


    }
}
