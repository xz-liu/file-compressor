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
            this.rand = new System.Windows.Forms.Button();
            this.nodeInfo = new System.Windows.Forms.Label();
            this.SuspendLayout();
            // 
            // panel1
            // 
            this.panel1.BackColor = System.Drawing.Color.Transparent;
            this.panel1.Location = new System.Drawing.Point(13, 78);
            this.panel1.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.panel1.Name = "panel1";
            this.panel1.Size = new System.Drawing.Size(668, 346);
            this.panel1.TabIndex = 0;
            this.panel1.MouseDown += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseDown);
            this.panel1.MouseMove += new System.Windows.Forms.MouseEventHandler(this.panel1_MouseMove);
            // 
            // ins
            // 
            this.ins.BackColor = System.Drawing.Color.Transparent;
            this.ins.FlatAppearance.BorderColor = System.Drawing.SystemColors.ActiveBorder;
            this.ins.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.ins.Font = new System.Drawing.Font("Tahoma", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ins.ForeColor = System.Drawing.Color.White;
            this.ins.Location = new System.Drawing.Point(13, 43);
            this.ins.Name = "ins";
            this.ins.Size = new System.Drawing.Size(94, 29);
            this.ins.TabIndex = 2;
            this.ins.Text = "Insert";
            this.ins.UseVisualStyleBackColor = false;
            this.ins.Click += new System.EventHandler(this.ins_Click);
            // 
            // input
            // 
            this.input.BackColor = System.Drawing.Color.Black;
            this.input.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.input.Font = new System.Drawing.Font("Tahoma", 9F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.input.ForeColor = System.Drawing.Color.White;
            this.input.Location = new System.Drawing.Point(12, 12);
            this.input.Name = "input";
            this.input.Size = new System.Drawing.Size(670, 26);
            this.input.TabIndex = 3;
            this.input.TextChanged += new System.EventHandler(this.input_TextChanged);
            // 
            // find
            // 
            this.find.BackColor = System.Drawing.Color.Transparent;
            this.find.FlatAppearance.BorderColor = System.Drawing.SystemColors.ActiveBorder;
            this.find.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.find.Font = new System.Drawing.Font("Tahoma", 9F);
            this.find.ForeColor = System.Drawing.Color.White;
            this.find.Location = new System.Drawing.Point(112, 43);
            this.find.Name = "find";
            this.find.Size = new System.Drawing.Size(94, 29);
            this.find.TabIndex = 4;
            this.find.Text = "Find";
            this.find.UseVisualStyleBackColor = false;
            this.find.Click += new System.EventHandler(this.find_Click);
            // 
            // erase
            // 
            this.erase.BackColor = System.Drawing.Color.Transparent;
            this.erase.FlatAppearance.BorderColor = System.Drawing.SystemColors.ActiveBorder;
            this.erase.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.erase.Font = new System.Drawing.Font("Tahoma", 9F);
            this.erase.ForeColor = System.Drawing.Color.White;
            this.erase.Location = new System.Drawing.Point(212, 43);
            this.erase.Name = "erase";
            this.erase.Size = new System.Drawing.Size(94, 29);
            this.erase.TabIndex = 5;
            this.erase.Text = "Erase";
            this.erase.UseVisualStyleBackColor = false;
            this.erase.Click += new System.EventHandler(this.erase_Click);
            // 
            // clear
            // 
            this.clear.BackColor = System.Drawing.Color.Transparent;
            this.clear.FlatAppearance.BorderColor = System.Drawing.SystemColors.ActiveBorder;
            this.clear.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.clear.Font = new System.Drawing.Font("Tahoma", 9F);
            this.clear.ForeColor = System.Drawing.Color.White;
            this.clear.Location = new System.Drawing.Point(312, 43);
            this.clear.Name = "clear";
            this.clear.Size = new System.Drawing.Size(94, 29);
            this.clear.TabIndex = 6;
            this.clear.Text = "Clear";
            this.clear.UseVisualStyleBackColor = false;
            this.clear.Click += new System.EventHandler(this.clear_Click);
            // 
            // treesize
            // 
            this.treesize.AutoSize = true;
            this.treesize.BackColor = System.Drawing.Color.Transparent;
            this.treesize.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.treesize.Font = new System.Drawing.Font("Tahoma", 9F);
            this.treesize.ForeColor = System.Drawing.Color.White;
            this.treesize.Location = new System.Drawing.Point(512, 48);
            this.treesize.Name = "treesize";
            this.treesize.Size = new System.Drawing.Size(58, 20);
            this.treesize.TabIndex = 7;
            this.treesize.Text = "Size : 0";
            // 
            // rand
            // 
            this.rand.BackColor = System.Drawing.Color.Transparent;
            this.rand.FlatAppearance.BorderColor = System.Drawing.SystemColors.ActiveBorder;
            this.rand.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.rand.Font = new System.Drawing.Font("Tahoma", 9F);
            this.rand.ForeColor = System.Drawing.Color.White;
            this.rand.Location = new System.Drawing.Point(412, 43);
            this.rand.Name = "rand";
            this.rand.Size = new System.Drawing.Size(94, 29);
            this.rand.TabIndex = 8;
            this.rand.Text = "Random";
            this.rand.UseVisualStyleBackColor = false;
            this.rand.Click += new System.EventHandler(this.rand_Click);
            // 
            // nodeInfo
            // 
            this.nodeInfo.AutoSize = true;
            this.nodeInfo.BackColor = System.Drawing.Color.Black;
            this.nodeInfo.BorderStyle = System.Windows.Forms.BorderStyle.FixedSingle;
            this.nodeInfo.FlatStyle = System.Windows.Forms.FlatStyle.Flat;
            this.nodeInfo.Font = new System.Drawing.Font("Tahoma", 9F);
            this.nodeInfo.ForeColor = System.Drawing.Color.White;
            this.nodeInfo.Location = new System.Drawing.Point(627, 427);
            this.nodeInfo.Name = "nodeInfo";
            this.nodeInfo.Size = new System.Drawing.Size(2, 20);
            this.nodeInfo.TabIndex = 9;
            this.nodeInfo.Visible = false;
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 15F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.BackColor = System.Drawing.Color.Black;
            this.BackgroundImageLayout = System.Windows.Forms.ImageLayout.Zoom;
            this.ClientSize = new System.Drawing.Size(744, 451);
            this.Controls.Add(this.ins);
            this.Controls.Add(this.nodeInfo);
            this.Controls.Add(this.rand);
            this.Controls.Add(this.clear);
            this.Controls.Add(this.erase);
            this.Controls.Add(this.find);
            this.Controls.Add(this.treesize);
            this.Controls.Add(this.input);
            this.Controls.Add(this.panel1);
            this.DoubleBuffered = true;
            this.HelpButton = true;
            this.Icon = ((System.Drawing.Icon)(resources.GetObject("$this.Icon")));
            this.ImeMode = System.Windows.Forms.ImeMode.NoControl;
            this.Margin = new System.Windows.Forms.Padding(4, 3, 4, 3);
            this.Name = "MainForm";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "RedBlack";
            this.ResizeBegin += new System.EventHandler(this.MainForm_ResizeBegin);
            this.ResizeEnd += new System.EventHandler(this.MainForm_ResizeEnd);
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
        private System.Windows.Forms.Button rand;
        private System.Windows.Forms.Label nodeInfo;
    }
}

