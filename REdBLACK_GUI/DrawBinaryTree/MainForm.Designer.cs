namespace DrawBinaryTree
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(MainForm));
            this.panel1 = new System.Windows.Forms.Panel();
            this.ins = new System.Windows.Forms.Button();
            this.input = new System.Windows.Forms.TextBox();
            this.find = new System.Windows.Forms.Button();
            this.erase = new System.Windows.Forms.Button();
            this.clear = new System.Windows.Forms.Button();
            this.treesize = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.White;
            this.panel1.Location = new System.Drawing.Point(13, 78);
            this.panel1.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(668, 346);
            this.panel1.TabIndex = 0;
            // 
            // ins
            // 
            this.ins.FlatAppearance.BorderColor = System.Drawing.SystemColors.ActiveBorder;
            this.ins.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.ins.Location = new System.Drawing.Point(12, 43);
            this.ins.Name = "ins";
            this.ins.Size = new System.Drawing.Size(133, 23);
            this.ins.TabIndex = 2;
            this.ins.Text = "Insert";
            this.ins.UseVisualStyleBackColor = true;
            this.ins.Click += new System.EventHandler(this.ins_Click);
            // 
            // input
            // 
            this.input.BorderStyle = System.Windows.Forms.BorderStyle.None;
            this.input.Location = new System.Drawing.Point(12, 12);
            this.input.Name = "input";
            this.input.Size = new System.Drawing.Size(670, 18);
            this.input.TabIndex = 3;
            // 
            // find
            // 
            this.find.FlatAppearance.BorderColor = System.Drawing.SystemColors.ActiveBorder;
            this.find.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.find.Location = new System.Drawing.Point(151, 43);
            this.find.Name = "find";
            this.find.Size = new System.Drawing.Size(133, 23);
            this.find.TabIndex = 4;
            this.find.Text = "Find";
            this.find.UseVisualStyleBackColor = true;
            this.find.Click += new System.EventHandler(this.find_Click);
            // 
            // erase
            // 
            this.erase.FlatAppearance.BorderColor = System.Drawing.SystemColors.ActiveBorder;
            this.erase.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.erase.Location = new System.Drawing.Point(290, 43);
            this.erase.Name = "erase";
            this.erase.Size = new System.Drawing.Size(133, 23);
            this.erase.TabIndex = 5;
            this.erase.Text = "Erase";
            this.erase.UseVisualStyleBackColor = true;
            this.erase.Click += new System.EventHandler(this.erase_Click);
            // 
            // clear
            // 
            this.clear.FlatAppearance.BorderColor = System.Drawing.SystemColors.ActiveBorder;
            this.clear.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.clear.Location = new System.Drawing.Point(429, 43);
            this.clear.Name = "clear";
            this.clear.Size = new System.Drawing.Size(133, 23);
            this.clear.TabIndex = 6;
            this.clear.Text = "Clear";
            this.clear.UseVisualStyleBackColor = true;
            this.clear.Click += new System.EventHandler(this.clear_Click);
            // 
            // treesize
            // 
            this.treesize.AutoSize = true;
            this.treesize.Location = new System.Drawing.Point(568, 47);
            this.treesize.Name = "treesize";
            this.treesize.Size = new System.Drawing.Size(55, 15);
            this.treesize.TabIndex = 7;
            this.treesize.Text = "Size 0";
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(694, 451);
            this.Controls.Add(this.treesize);
            this.Controls.Add(this.clear);
            this.Controls.Add(this.erase);
            this.Controls.Add(this.find);
            this.Controls.Add(this.input);
            this.Controls.Add(this.ins);
            this.Controls.Add(this.panel1);
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "RedBlack";
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.Panel panel1;
        private System.Windows.Forms.Button ins;
        private System.Windows.Forms.TextBox input;
        private System.Windows.Forms.Button find;
        private System.Windows.Forms.Button erase;
        private System.Windows.Forms.Button clear;
        private System.Windows.Forms.Label treesize;
    }
}

