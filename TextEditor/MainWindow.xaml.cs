using Microsoft.Win32;
using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Diagnostics;
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
using System.Windows.Shell;

namespace TextEditor
{
    /// <summary>
    /// Interaction logic for MainWindow.xaml
    /// </summary>
    public partial class MainWindow : Window
    {
        public MainWindow()
        {
            InitializeComponent();
            Loaded += delegate
            {
                SetupWindow();
            };
        }

        private void SetupWindow()
        {
            LineNumbers.Text = "1|\n";
        }

        private void UpdateLineNumbers(int increase)
        {
            LineNumbers.Text = string.Join('\n', Enumerable.Range(1, TextSpace.LineCount + increase).Select(i => $"{i}|"));
            LineNumberScrollViewer.ScrollToVerticalOffset(TextSpace.VerticalOffset);
        }

        private void TextBox_ScrollChanged(object sender, ScrollChangedEventArgs e)
        {
            LineNumberScrollViewer.ScrollToVerticalOffset(TextSpace.VerticalOffset);
        }

        private void TextBox_PreviewKeyDown(object sender, KeyEventArgs e)
        {
            if (e.Key == Key.Enter)
            {
                UpdateLineNumbers(1);
                return;
            }

            if (e.Key == Key.Back && TextSpace.LineCount > 1)
            {
                if (string.IsNullOrWhiteSpace(TextSpace.Text.Split('\n')[^1]))
                {
                    UpdateLineNumbers(-1);
                    return;
                }
                UpdateLineNumbers(0);
            }
        }

        private static EditorFile? LoadFile()
        {
            EditorFile? editorFile = null;
            OpenFileDialog dialog = new OpenFileDialog();
            dialog.Title = "Select a file";
            dialog.Filter = "Text Files (*.txt)|*.txt|All Files (*.*)|*.*";
            bool result = dialog.ShowDialog() ?? false;
            if (result)
            {
                Debug.WriteLine(dialog.FileName);
                editorFile = new EditorFile(dialog.FileName);
            }
            return editorFile;
        }


        private void PathButton_Click(object sender, RoutedEventArgs e)
        {
            EditorFile? editorFile = LoadFile();
            if (editorFile != null)
            {
                PathButton.Content = "file";
                PathButton.IsEnabled = false;
            }
        }

        private void Minimize_Click(object sender, RoutedEventArgs e)
        {
            this.WindowState = System.Windows.WindowState.Minimized;
        }

        private void Maximize_Click(object sender, RoutedEventArgs e)
        {
            if(this.WindowState == WindowState.Maximized)
            {
                this.WindowState = System.Windows.WindowState.Normal;
            }
            else
            {
                this.WindowState = System.Windows.WindowState.Maximized;
            }
        }

        private void Close_Click(object sender, RoutedEventArgs e)
        {
            Close();
        }

        private void Header_PreviewMouseDown(object sender, MouseButtonEventArgs e)
        {
            Point position = e.GetPosition(Header);
            HitTestResult hitTestResult = VisualTreeHelper.HitTest(Header, position);
            bool hitElementInHeader = hitTestResult?.VisualHit is FrameworkElement framework && framework != Header;
            if (e.LeftButton == MouseButtonState.Pressed && !hitElementInHeader)
            {
                DragMove();
            }
        }
    }
}
