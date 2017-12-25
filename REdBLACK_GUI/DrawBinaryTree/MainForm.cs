
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Threading.Tasks;
using System.Windows.Forms;
using Newtonsoft.Json;
using System.Threading;

namespace DrawBinaryTree
{
    public partial class MainForm : Form
    {
        private int maxTreeHeight, totalNodes;
        private BinaryTreeNode<string> root;
        private Pen blackPen;
        private SolidBrush blackBrush;
        private string valueNow;
        private bool found = false;
        private bool isSelected = false;
        Process process;
        Dictionary<PointF,JsonData> map;

        private void InorderTraversal(BinaryTreeNode<string> t, int depth)
        {
            if (t != null)
            {
                InorderTraversal(t.Left, depth + 1);
                t.Xpos = totalNodes++ + 1;
                t.Ypos = depth - 1;
                InorderTraversal(t.Right, depth + 1);
            }
        }

        private void ComputeNodePositions()
        {
            int depth = 1;
            InorderTraversal(root, depth);
        }

        private int TreeHeight(BinaryTreeNode<string> t)
        {
            if (t == null) return -1;
            else if (t.heightIsSet()) return t.treeHeight;
            else return t.treeHeight = 1 + Math.Max(TreeHeight(t.Left), TreeHeight(t.Right));
        }

        private BinaryTreeNode<string> CreateTreeImpl(List<JsonData> lst)
        {
            if (lst.Count == 0) return null;
            if (Char.IsLower(lst[0].Type[0])) found = true;
            if (lst[0].Type == "N")
            {
                lst.Remove(lst[0]);
                return null;
            }
            BinaryTreeNode<string> r = new BinaryTreeNode<string>() {valueData=lst[0]};
            lst.Remove(lst[0]);
                
            r.Left = CreateTreeImpl(lst);
            r.Right = CreateTreeImpl(lst);
            return r;
        }

        bool isNumeric(string s) { return double.TryParse(s, out var n); }

        private void CreateTree(List<JsonData> lst)
        {
            root = CreateTreeImpl(lst);
            totalNodes = 0;
            ComputeNodePositions();
            maxTreeHeight = TreeHeight(root);
        }
        private Font outFont;

        public MainForm()
        {
            InitializeComponent();

            panel1.Paint += new PaintEventHandler(panel1_Paint);
            panel1.Font = new Font("Tahoma", 12.0f, FontStyle.Regular);
            outFont = new Font("Tahoma", 12.3f, FontStyle.Regular);
            blackPen = new Pen(Color.White,2f);
            blackPen.DashStyle = System.Drawing.Drawing2D.DashStyle.Custom;
            blackPen.DashPattern = new float[] { 10f, 10f };
            blackBrush = new SolidBrush(Color.Black);
            nodeInfo.BringToFront();
            SetStyle(ControlStyles.AllPaintingInWmPaint, true);
            SetStyle(ControlStyles.UserPaint, true);
            map = new Dictionary<PointF, JsonData>();
            try
            {
                process = new Process
                {
                    StartInfo = new ProcessStartInfo
                    {
                        FileName = "DS_EXP_PROJECT.exe",
                        Arguments = "",
                        UseShellExecute = false,
                        RedirectStandardOutput = true,
                        RedirectStandardInput = true,
                        CreateNoWindow = true
                    }
                };
                process.Start();
            }
            catch (Exception e){
                MessageBox.Show(e.Message, "Error!");
                this.Close();
                Environment.Exit(0);
            }
        }
        private void ParseMessage(string message)
        {
            previus = "";
            process.StandardInput.WriteLine(message);
            treesize.Text = "Size : " + process.StandardOutput.ReadLine();

            List<JsonData> jsonData =
            JsonConvert.DeserializeObject<List<JsonData>>(process.StandardOutput.ReadLine());
            CreateTree(jsonData);
            repaintPanel();
        }
        
        private void repaintPanel()
        {
            map.Clear();
            if (!sizeNow.Equals(this.Size))
            {
                panel1.Invalidate();
                needRepaint = true;
            }
        }

        private void resetFound() { found = false; }

        private void foundMessage(bool isDelete)
        {
            if (!found)
            {
                MessageBox.Show( "What you want to " +
                    (isDelete ? "delete" : "find") + " does not exist", "Not good!");
            }
           
        }

        public void DrawTree(BinaryTreeNode<string> root, Graphics g)
        {
            panel1.Width = ClientSize.Width - 25;
            panel1.Height = ClientSize.Height - 80;
            int treeHeight = TreeHeight(root);
            Color outside = Color.White;//outsideByHeight[(uint)treeHeight % 7];
            Color inside = Color.Black;
            Pen[] lines = {
                new Pen(outside,6),
                new Pen(inside,2)
            };
            int Width = panel1.Width-20;
            int Height = panel1.Height-20;
            int dx = 0, dy = 0, dx2 = 0, dy2 = 0, ys = 30;
            int yShift = 20;
            int XSCALE, YSCALE;

            XSCALE = (int)(Width / (totalNodes+1));
            YSCALE = (int)((Height - ys) / (maxTreeHeight + 1));

            if (root != null)
            {
                dx = root.Xpos * XSCALE; 
                dy = root.Ypos * YSCALE;
                dy += yShift;
                string s = root.valueData.Value;
                var clr = root.valueData.Type.ToUpper();
                Color thisColor = clr == "R" ? Color.Red : Color.Black;
                Brush white = Brushes.White;
                
                if (root.Left != null)
                {
                    dx2 = root.Left.Xpos * XSCALE;
                    dy2 = root.Left.Ypos * YSCALE + yShift;
                    foreach (var p in lines)
                        //g.DrawLine(p, new Point(dx, dy), new Point(dx2, dy2));
                        g.DrawBezier(p, new Point(dx, dy), new Point(dx2, dy), new Point(dx2, dy), new Point(dx2, dy2));
                    //g.DrawBezier(p, new Point(dx, dy), new Point(dx, dy), new Point(dx2, dy2), new Point(dx2, dy2));

                }

                if (root.Right != null)
                {
                    dx2 = root.Right.Xpos * XSCALE;
                    dy2 = root.Right.Ypos * YSCALE + yShift;
                    foreach (var p in lines)
                        //g.DrawLine(p, new Point(dx, dy), new Point(dx2, dy2));
                        g.DrawBezier(p, new Point(dx, dy), new Point(dx2, dy), new Point(dx2, dy), new Point(dx2, dy2));
                }
                var layout = new RectangleF(dx - ys / 2, dy - ys / 2, ys, ys);
                if (Char.IsLower(root.valueData.Type[0])) {
                    g.DrawLine(blackPen, dx, 0, dx, panel1.Height);
                    g.DrawLine(blackPen, 0, dy, panel1.Width, dy);
                }
                    g.FillEllipse(new SolidBrush(
                    outside), new RectangleF(dx - ys / 2 - 2, dy - ys / 2 - 2, ys + 4, ys + 4));
                
                PointF now = new PointF(dx - ys / 2, dy - ys / 2), nowCenter = new PointF(dx, dy);
                if (!map.ContainsKey(nowCenter))map.Add(nowCenter, root.valueData);
                g.FillEllipse( new SolidBrush(thisColor), layout);
                g.DrawString(s, outFont, Brushes.Black, now);
                g.DrawString(s, panel1.Font, Brushes.White, now);
                DrawTree(root.Left, g);
                DrawTree(root.Right, g);
            }
        }

        private bool checkInput(string front)
        {
            resetFound();
            if (isNumeric(input.Text)){
                ParseMessage(front + input.Text);
                return true;
            }
            MessageBox.Show("Invalid input", "Error!");
            return false;
        }

        private void ins_Click(object sender, EventArgs e)
        {
            checkInput("i");
        }

        private void find_Click(object sender, EventArgs e)
        {
            if (checkInput("f"))
                foundMessage(false);
        }

        private void erase_Click(object sender, EventArgs e)
        {
            checkInput("e");
        }

        private void clear_Click(object sender, EventArgs e)
        {
            ParseMessage("c");
        }
        
        

        private bool inCircle(PointF center, PointF point)
        {
            return (Math.Abs((point.X - center.X) * (point.X - center.X) + (point.Y - center.Y) * (point.Y - center.Y)) <= 400f);
        }

        private void panel1_MouseMove(object sender, MouseEventArgs e)
        {
            foreach(var i in map)
            {
                if (inCircle(i.Key, new PointF(e.X, e.Y)))
                {
                    String color = i.Value.Type.ToUpper() == "R" ? "Red" : "Black";
                    nodeInfo.Location = new Point((int)i.Key.X + panel1.Location.X + 10, (int)i.Key.Y + panel1.Location.Y + 10);
                    nodeInfo.Text =
                        "Value : " + i.Value.Value + "\n" +
                        "Color : " + color + "\n" +
                        "Height: " + i.Value.Height;
                    nodeInfo.Visible = true;
                    nodeInfo.Invalidate();
                    isSelected = true;
                    valueNow = i.Value.Value;
                    return;
                }
            }
            isSelected = false;
            nodeInfo.Visible = false;
            nodeInfo.Invalidate();
        }

        private void panel1_MouseDown(object sender, MouseEventArgs e)
        {
            if (isSelected)
            {
                input.Text = valueNow;
                input.Invalidate();
            }
        }

        private void rand_Click(object sender, EventArgs e)
        {
            ParseMessage("r");
        }

        private bool needRepaint = false;
        private Size sizeNow;

        private void MainForm_ResizeEnd(object sender, EventArgs e)
        {
            repaintPanel();
        }

        private void MainForm_ResizeBegin(object sender, EventArgs e)
        {
            sizeNow = this.Size;
            needRepaint = false;
        }
        string previus = "";

        private void input_TextChanged(object sender, EventArgs e)
        {
            if (input.Text.Length == 0 || isNumeric(input.Text))
                previus = input.Text;
            else input.Text = previus;
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            if (needRepaint)
            {
                e.Graphics.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
                if (root != null)
                    DrawTree(root, e.Graphics);
            }
        }

    }

    public class JsonData
    {
        [JsonProperty("C")]
        public string Type { get; set; }

        [JsonProperty("V")]
        public string Value { get; set; }

        [JsonProperty("H")]
        public string Height { get; set; }
    }
}