using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;
using System.Runtime.InteropServices;
using System.Diagnostics;
using System.Collections.ObjectModel;
using System.Threading;
using System.Collections.Concurrent;
using System.IO;

namespace DS_ZIP_GUI
{
    /// <summary>
    /// MainWindow.xaml 的交互逻辑
    /// </summary>
    public partial class MainWindow : Window
    {
        private ObservableCollection<CharInfo> lst;
        public MainWindow()
        {
            InitializeComponent();
            lst = new ObservableCollection<CharInfo>();
            charList.ItemsSource = lst;
            bar.IsIndeterminate = true;
            setBar(false);
            setList(false);
        }

        void setList(bool f)
        {
            mainWindow.Dispatcher.Invoke(() =>
            {
                if (f)
                {
                    charList.Visibility = Visibility.Visible;
                }
                else
                {
                    outputTime.Text = "Welcome, Young Man. Have a good day!";
                    charList.Visibility = Visibility.Hidden;
                    charList.Visibility = Visibility.Collapsed;
                }
            });
            double heightNow = 0;
            mainWindow.Dispatcher.Invoke(() =>
            {
                heightNow = mainWindow.Height;
                if (!f && heightNow > 300)
                {
                    mainWindow.Height = 185;
                }
                else if (f && heightNow < 300)
                {
                    mainWindow.Height = 526;
                }
            });
        }

        void setBar(bool f, bool thread = true)
        {
            if (thread)
                bar.Dispatcher.Invoke(() =>
                {
                    bar.Visibility = (f) ? Visibility.Visible : Visibility.Hidden;
                });
            else bar.Visibility = (f) ? Visibility.Visible : Visibility.Hidden;
        }
        private void setAll(bool f)
        {
            mainWindow.Dispatcher.Invoke(() =>
            {
                output.IsEnabled = f;
                input.IsEnabled = f;
                selectInput.IsEnabled = f;
                selectOutput.IsEnabled = f;
                zip.IsEnabled = f;
                unzip.IsEnabled = f;
                swap.IsEnabled = f;
            });
        }
        private void selectInput_Click(object sender, RoutedEventArgs e)
        {
            setList(false);
            OpenFileDialog openFileDialog = new OpenFileDialog();
            openFileDialog.Filter = "All Files(*.*)|*.*|Compressed Files(*.hcd)|*.hcd|Text Files(*.txt)|*.txt";
            openFileDialog.DefaultExt = "*";
            if (openFileDialog.ShowDialog() == true)
                input.Text = openFileDialog.FileName;
        }

        private void selectOutput_Click(object sender, RoutedEventArgs e)
        {
            setList(false);
            SaveFileDialog saveFileDialog = new SaveFileDialog();
            saveFileDialog.Filter = "Compressed Files(*.hcd)|*.hcd|Text Files(*.txt)|*.txt|All Files(*.*)|*.*";
            saveFileDialog.DefaultExt = "hcd";
            if (saveFileDialog.ShowDialog() == true)
                output.Text = saveFileDialog.FileName;
        }

        private void run_zip(string _in, string _out, bool _d)
        {
            setBar(true,false);
            setAll(false);
            lst.Clear();
            Process proc = new Process
            {
                StartInfo = new ProcessStartInfo
                {
                    FileName = "DS_EXP_PROJECT.exe",
                    Arguments = _in + " " + _out + (_d ? " d" : ""),
                    UseShellExecute = false,
                    RedirectStandardOutput = true,
                    CreateNoWindow = true
                }
            };
            string s="";
            proc.EnableRaisingEvents = true;
            proc.Exited += new EventHandler((o, e) =>
            {
                using (Stream ss = GenerateStreamFromString(s))
                {
                    StreamReader reader = new StreamReader(ss);
                    setBar(false);
                    outputTime.Dispatcher.Invoke(() =>
                    {
                        outputTime.Text = (reader.ReadLine());
                    });
                    while (!reader.EndOfStream)
                    {
                        string ascii = (reader.ReadLine());
                        string code = (reader.ReadLine());
                        string cnt = (reader.ReadLine());
                        charList.Dispatcher.Invoke(() =>
                        {
                            lst.Add(new CharInfo() { ASCII = ascii, Counts = cnt, Code = code });
                        });
                    }
                }
                setAll(true);
                setList(true);
            });
            Task.Run(() =>
            {
                try
                {
                    DateTime time = DateTime.Now;
                    proc.Start();
                    s = proc.StandardOutput.ReadToEnd();
                }
                catch (Exception)
                {
                    MessageBox.Show("Error", "Something went wrong");
                }
            });
        }

        private Stream GenerateStreamFromString(string s)
        {
            MemoryStream stream = new MemoryStream();
            StreamWriter writer = new StreamWriter(stream);
            writer.Write(s);
            writer.Flush();
            stream.Position = 0;
            return stream;
        }

        private void zip_Click(object sender, RoutedEventArgs e)
        {
            run_zip(input.Text, output.Text, false);
        }

        private void unzip_Click(object sender, RoutedEventArgs e)
        {
            run_zip(input.Text, output.Text, true);
        }

        private void swap_Click(object sender, RoutedEventArgs e)
        {
            setList(false);
            string tmp = input.Text;
            input.Text = output.Text;
            output.Text = tmp;
        }

        private void input_TextChanged(object sender, TextChangedEventArgs e)
        {
        }

        private void output_TextChanged(object sender, TextChangedEventArgs e)
        {
        }
    }

    public class CharInfo
    {
        public string ASCII { get; set; }
        public string Counts { get; set; }
        public string Code { get; set; }
    }
}
