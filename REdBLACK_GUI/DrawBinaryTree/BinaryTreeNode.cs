using System;

namespace DrawBinaryTree
{
    public class BinaryTreeNode<T> : Node<T>
    {
        public static int NULL_VALUE = -10;
        public BinaryTreeNode() : base() { treeHeight = NULL_VALUE; }
        public BinaryTreeNode(T data) : base(data, null) { }
        public BinaryTreeNode(T data, BinaryTreeNode<T> left, BinaryTreeNode<T> right)
        {
            base.Value = data;
            NodeList<T> children = new NodeList<T>(2);
            children[0] = left;
            children[1] = right;

            base.Neighbors = children;
        }

        public int treeHeight { get; set; }
        public bool heightIsSet() { return treeHeight != NULL_VALUE; }

        public JsonData valueData { get; set; }

        public string color
        {
            get { return valueData.Type; }
            set { valueData.Type = value; }
        }
        public string height
        {
            get { return valueData.Height; }
            set { valueData.Height = value; }
        }
        public string value
        {
            get { return valueData.Value; }
            set { valueData.Value = value; }
        }

        public BinaryTreeNode<T> Left
        {
            get
            {
                if (base.Neighbors == null)
                    return null;
                else
                    return (BinaryTreeNode<T>)base.Neighbors[0];
            }
            set
            {
                if (base.Neighbors == null)
                    base.Neighbors = new NodeList<T>(2);

                base.Neighbors[0] = value;
            }
        }

        public BinaryTreeNode<T> Right
        {
            get
            {
                if (base.Neighbors == null)
                    return null;
                else
                    return (BinaryTreeNode<T>)base.Neighbors[1];
            }
            set
            {
                if (base.Neighbors == null)
                    base.Neighbors = new NodeList<T>(2);

                base.Neighbors[1] = value;
            }
        }
    }
}
