
using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Drawing;
using System.Threading.Tasks;
using System.Windows.Forms;
using Newtonsoft.Json;
namespace DrawBinaryTree
{
    public partial class MainForm : Form
    {
        private int maxTreeHeight, totalNodes;
        private BinaryTreeNode<string> root;
        private Pen blackPen;
        private SolidBrush blackBrush;
        Process process;

        private void InorderTraversal(BinaryTreeNode<string> t, int depth)
        {
            if (t != null)
            {
                InorderTraversal(t.Left, depth + 1); //add 1 to depth (y coordinate) 
                t.Xpos = totalNodes++ + 1; //x coord is node number in inorder traversal
                t.Ypos = depth - 1; // mark y coord as depth
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
            else return 1 + Math.Max(TreeHeight(t.Left), TreeHeight(t.Right));
        }

        private BinaryTreeNode<string> CreateTreeImpl(List<JsonData> lst)
        {
            if (lst.Count == 0) return null;
            if (lst[0].Type == "N")
            {
                lst.Remove(lst[0]);
                return null;
            }
            BinaryTreeNode<string> r = new BinaryTreeNode<string>(lst[0].Value) { color=lst[0].Type};
            lst.Remove(lst[0]);
                
            r.Left = CreateTreeImpl(lst);
            r.Right = CreateTreeImpl(lst);
            return r;
        }

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
            //WindowState = FormWindowState.Maximized;
            panel1.Paint += new PaintEventHandler(panel1_Paint);
            panel1.SizeChanged += new EventHandler(panel1_SizeChanged);
            panel1.Font = new Font("Tahoma", 12.0f, FontStyle.Regular);
            outFont = new Font("Tahoma", 12.3f, FontStyle.Regular);
            blackPen = new Pen(Color.Black,2f);
            blackPen.DashStyle = System.Drawing.Drawing2D.DashStyle.Custom;
            blackPen.DashPattern = new float[] { 10f, 10f };
            blackBrush = new SolidBrush(Color.Black);
            process = new Process
            {
                StartInfo = new ProcessStartInfo
                {
                    FileName = "a.exe",
                    Arguments = "",
                    UseShellExecute = false,
                    RedirectStandardOutput = true,
                    RedirectStandardInput = true,
                    CreateNoWindow = true
                }
            };
            process.Start();
        }
        private void ParseMessage(string message)
        {
            process.StandardInput.WriteLine(message);
            treesize.Text = "Size " + process.StandardOutput.ReadLine();

            List<JsonData> jsonData =
            JsonConvert.DeserializeObject<List<JsonData>>(process.StandardOutput.ReadLine());
            CreateTree(jsonData);
            panel1.Invalidate();
        }

        private void panel1_SizeChanged(object sender, EventArgs e)
        {
            panel1.Invalidate();
        }

        public void DrawTree(BinaryTreeNode<string> root, Graphics g)
        {
            g.SmoothingMode = System.Drawing.Drawing2D.SmoothingMode.AntiAlias;
            panel1.Width = ClientSize.Width - 8;
            panel1.Height = ClientSize.Height - 8;
            Pen[] lines = {
                new Pen(Color.LightGoldenrodYellow, 6),
                new Pen(Color.Black,2)
            };
            int Width = panel1.Width-20;
            int Height = panel1.Height-20;
            int dx = 0, dy = 0, dx2 = 0, dy2 = 0, ys = 30;
            int yShift = 20;
            int XSCALE, YSCALE;
            int treeHeight = TreeHeight(root);

            XSCALE = (int)(Width / (totalNodes+1)); //scale x by total nodes in tree
            YSCALE = (int)((Height - ys) / (maxTreeHeight + 1)); //scale y by tree height

            if (root != null)
            {
                // preorder traversal to draw each node
                dx = root.Xpos * XSCALE; // get x,y coords., and scale them 
                dy = root.Ypos * YSCALE;
                dy += yShift;
                string s = root.Value.ToString(); //get the word at this node
                var clr = root.color.ToUpper();
                Color thisColor = clr == "R" ? Color.Red : Color.Black;
                Brush white = Brushes.White;

                // this draws the lines from a node to its children, if any
                if (root.Left != null)
                {
                    //draws the line to left child if it existsblackPen
                    dx2 = root.Left.Xpos * XSCALE;
                    dy2 = root.Left.Ypos * YSCALE + yShift;
                    foreach (var p in lines)
                        g.DrawBezier(p, new Point(dx, dy), new Point(dx2, dy), new Point(dx2, dy), new Point(dx2, dy2));
                }

                if (root.Right != null)
                {
                    //draws the line to right child if it exists
                    dx2 = root.Right.Xpos * XSCALE;//get right child x,y scaled position
                    dy2 = root.Right.Ypos * YSCALE + yShift;
                    foreach (var p in lines)
                    {
                        g.DrawBezier(p, new Point(dx, dy), new Point(dx2, dy), new Point(dx2, dy), new Point(dx2, dy2));
                    }
                }
                var layout = new RectangleF(dx - ys / 2, dy - ys / 2, ys, ys);
                if (Char.IsLower(root.color[0])) {
                    g.DrawLine(blackPen, dx, 0, dx, panel1.Height);
                    g.DrawLine(blackPen, 0, dy, panel1.Width, dy);
                    g.FillEllipse(new SolidBrush(
                    Color.Blue),  new RectangleF(dx - ys / 2 - 3, dy - ys / 2 - 3, ys + 6, ys + 6));
                }
                else
                {
                    g.FillEllipse(new SolidBrush(
                    Color.LightGoldenrodYellow), new RectangleF(dx - ys / 2 - 2, dy - ys / 2 - 2, ys + 4, ys + 4));
                }
                g.FillEllipse( new SolidBrush(thisColor), layout);
                g.DrawString(s, outFont, Brushes.Black, new PointF(dx - ys / 2, dy - ys / 2));
                g.DrawString(s, panel1.Font, Brushes.White, new PointF(dx - ys / 2, dy - ys / 2));
                DrawTree(root.Left, g); // do left side of preorder traversal 
                DrawTree(root.Right, g); //now do right side of preorder traversal 
            }
        }

        private void ins_Click(object sender, EventArgs e)
        {
            ParseMessage("i" + input.Text);
        }

        private void find_Click(object sender, EventArgs e)
        {
            ParseMessage("f" + input.Text);
        }

        private void erase_Click(object sender, EventArgs e)
        {
            ParseMessage("e" + input.Text);
        }

        private void clear_Click(object sender, EventArgs e)
        {
            ParseMessage("c");
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {
            if (root != null)
                DrawTree(root, e.Graphics);
        }

    }

    public class JsonData
    {
        [JsonProperty("Type")]
        public string Type { get; set; }

        [JsonProperty("Value")]
        public string Value { get; set; }

    }
}